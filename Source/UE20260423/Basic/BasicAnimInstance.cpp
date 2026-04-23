// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UBasicAnimInstance::NativeInitializeAnimation()
{
}

void UBasicAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Player = Cast<ACharacter>(TryGetPawnOwner());
	if (Player)
	{
		Speed = Player->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());
	}
}

void UBasicAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
