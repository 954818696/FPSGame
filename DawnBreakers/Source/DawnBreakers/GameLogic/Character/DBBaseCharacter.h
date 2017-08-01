// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DBBaseCharacter.generated.h"

UCLASS()
class DAWNBREAKERS_API ADBBaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = ADBBaseCharacter)
	bool IsAlive() const;

	virtual bool IsSprinting() const;

protected:
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser, bool bKilled);
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attr")
	float Health;
	

	UPROPERTY(EditDefaultsOnly, Category = "Attr")
	float SprintingSpeedModifier;
};
