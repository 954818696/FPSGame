// Fill out your copyright notice in the Description page of Project Settings.

#include "DawnBreakers.h"
#include "DBZombieCharacter.h"

#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "DawnBreakers/GameLogic/AI/AIController/DBZombieAIController.h"


ADBZombieCharacter::ADBZombieCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;

	/* These values are matched up to the CapsuleComponent above and are used to find navigation paths */
	GetMovementComponent()->NavAgentProps.AgentRadius = 42;
	GetMovementComponent()->NavAgentProps.AgentHeight = 192;

	MeleeCollisionComp = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("MeleeCollision"));
	MeleeCollisionComp->SetRelativeLocation(FVector(45, 0, 25));
	MeleeCollisionComp->SetCapsuleHalfHeight(60);
	MeleeCollisionComp->SetCapsuleRadius(35, false);
	MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeCollisionComp->SetupAttachment(GetCapsuleComponent());

	AudioLoopComp = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("ZombieLoopedSoundComp"));
	AudioLoopComp->bAutoActivate = false;
	AudioLoopComp->bAutoDestroy = false;
	AudioLoopComp->SetupAttachment(RootComponent);

	Health = 1000;
	MeleeDamage = 20.0f;
	MeleeStrikeCooldown = 2.0f;
	SprintingSpeedModifier = 3.0f;

	SenseTimeOut = 2.5f;
}

void ADBZombieCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ADBZombieCharacter::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &ADBZombieCharacter::OnHearNoise);
	}
	if (MeleeCollisionComp)
	{
		MeleeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADBZombieCharacter::OnMeleeCompBeginOverlap);
	}
}

void ADBZombieCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bSensedTarget && 
		(GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut &&
		(GetWorld()->TimeSeconds - LastHeardTime) > SenseTimeOut)
	{
		ADBZombieAIController* AIController = Cast<ADBZombieAIController>(GetController());
		if (AIController)
		{
			bSensedTarget = false;
			AIController->SetTargetEnemy(nullptr);
			UpdateAudioLoop(false);
		}
	}
}

float ADBZombieCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (EventInstigator)
	{
		ADBZombieAIController* TController = Cast<ADBZombieAIController>(Controller);
		if (TController)
		{
			TController->SetTargetEnemy(EventInstigator->GetPawn());
		}
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

bool ADBZombieCharacter::IsSprinting() const
{
	return bSensedTarget && !GetVelocity().IsZero();
}

void ADBZombieCharacter::OnSeePlayer(APawn* Pawn)
{
	if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		UpdateAudioLoop(true);
	}

	LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;

	ADBZombieAIController* AIController = Cast<ADBZombieAIController>(GetController());
	ADBBaseCharacter* SensedPawn = Cast<ADBBaseCharacter>(Pawn);
	if (AIController && SensedPawn && SensedPawn->IsAlive())
	{
		AIController->SetTargetEnemy(SensedPawn);
	}
}

void ADBZombieCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		UpdateAudioLoop(true);
	}

	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	ADBZombieAIController* AIController = Cast<ADBZombieAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(PawnInstigator);
	}
} 

void ADBZombieCharacter::OnMeleeCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	TimerHandle_MeleeAttack.Invalidate();
	PerformMeleeStrike(OtherActor);
	GetWorldTimerManager().SetTimer(TimerHandle_MeleeAttack, this, &ADBZombieCharacter::OnRetriggerMeleeStrike, MeleeStrikeCooldown, true);
}

void ADBZombieCharacter::OnRetriggerMeleeStrike()
{
	TArray<AActor*> Overlaps;
	MeleeCollisionComp->GetOverlappingActors(Overlaps, ADBCharacter::StaticClass());
	for (int32 i = 0; i < Overlaps.Num(); i++)
	{
		ADBCharacter* OverlappingPawn = Cast<ADBCharacter>(Overlaps[i]);
		if (OverlappingPawn)
		{
			PerformMeleeStrike(OverlappingPawn);
			break;
		}
	}

	if (Overlaps.Num() == 0)
	{
		TimerHandle_MeleeAttack.Invalidate();
	}
}

void ADBZombieCharacter::PerformMeleeStrike(AActor* HitActor)
{
	if (LastMeleeAttackTime > GetWorld()->GetTimeSeconds() - MeleeStrikeCooldown)
	{
		return;
	}

	if (HitActor && HitActor != this && IsAlive())
	{
		ACharacter* OtherPawn = Cast<ACharacter>(HitActor);
		if (OtherPawn)
		{

			LastMeleeAttackTime = GetWorld()->GetTimeSeconds();

			FPointDamageEvent DmgEvent;
			DmgEvent.DamageTypeClass = PunchDamageType;
			DmgEvent.Damage = MeleeDamage;

			HitActor->TakeDamage(DmgEvent.Damage, DmgEvent, GetController(), this);
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s attacked"), *HitActor->GetName()));

			SimulateMeleeStrike();
		}
	}
}

void ADBZombieCharacter::UpdateAudioLoop(bool bNewSensedTarget)
{
	if (bNewSensedTarget && !bSensedTarget)
	{
		PlayCharacterSound(SoundPlayerNoticed);
		AudioLoopComp->SetSound(SoundHunting);
		AudioLoopComp->Play();
	}
	else
	{
		//AudioLoopComp->SetSound(SoundWandering);
		//AudioLoopComp->Play();
		AudioLoopComp->SetSound(SoundIdle);
		AudioLoopComp->Play();
	}
}

void ADBZombieCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled)
{
	Super::PlayHit(DamageTaken, DamageEvent, PawnInstigator, DamageCauser, bKilled);

	if (AudioLoopComp && bKilled)
	{
		AudioLoopComp->Stop();
	}
}

void ADBZombieCharacter::SimulateMeleeStrike()
{
	if (MeleeAnimMontage)
	{
		float AnimDuration = MeleeAnimMontage->SequenceLength;

		PlayAnimMontage(MeleeAnimMontage, AnimDuration / MeleeStrikeCooldown);
	}
	

	PlayCharacterSound(SoundAttackMelee);
}

UAudioComponent* ADBZombieCharacter::PlayCharacterSound(USoundCue* CueToPlay)
{
	if (CueToPlay)
	{
		return UGameplayStatics::SpawnSoundAttached(CueToPlay, RootComponent, NAME_None, FVector::ZeroVector, EAttachLocation::SnapToTarget, true);
	}

	return nullptr;
}
