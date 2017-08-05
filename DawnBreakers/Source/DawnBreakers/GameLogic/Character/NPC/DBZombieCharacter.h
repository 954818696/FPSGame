// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic/Character/DBBaseCharacter.h"
#include "DBZombieCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DAWNBREAKERS_API ADBZombieCharacter : public ADBBaseCharacter
{
	GENERATED_UCLASS_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual bool IsSprinting() const override;
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
	void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void OnMeleeCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void OnRetriggerMeleeStrike();

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void PerformMeleeStrike(AActor* HitActor);

	void UpdateAudioLoop(bool bNewSensedTarget);

	void SimulateMeleeStrike();

	UAudioComponent* PlayCharacterSound(USoundCue* CueToPlay);

	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

protected:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, Category = "Attacking")
	UCapsuleComponent* MeleeCollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* AudioLoopComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SenseTimeOut;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	TSubclassOf<UDamageType> PunchDamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float MeleeDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float MeleeStrikeCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	UAnimMontage* MeleeAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundPlayerNoticed;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundHunting;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundIdle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundWandering;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* SoundAttackMelee;

private:
	float LastSeenTime;

	float LastHeardTime;

	float LastMeleeAttackTime;



	bool bSensedTarget;

	FTimerHandle TimerHandle_MeleeAttack;
};
