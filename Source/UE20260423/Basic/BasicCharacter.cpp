// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	JumpMaxCount = 2;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EIC)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABasicCharacter::Move);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABasicCharacter::Look);
		EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABasicCharacter::CustomJump);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABasicCharacter::StopJumping);
		EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &ABasicCharacter::StopJumping);
		// UE_LOG(LogTemp, Warning, TEXT("Input Actions bound successfully"));
	}
}

void ABasicCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D MoveDirection = InValue.Get<FVector2D>();

	FRotator ControllerRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControllerRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControllerRotation);

	UE_LOG(LogTemp, Warning, TEXT("Input Action Move"));
	AddMovementInput(ForwardVector * MoveDirection.X);
	AddMovementInput(RightVector * MoveDirection.Y);
}

void ABasicCharacter::Look(const FInputActionValue& InValue)
{
	FVector2D LookDirection = InValue.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("Input Action Look"));
	AddControllerPitchInput(LookDirection.Y);
	AddControllerYawInput(LookDirection.X);
}

void ABasicCharacter::CustomJump()
{
	if (CurrentJumpCount < 2)
	{		
		LaunchCharacter(FVector(0.f, 0.f, JumpHeight), false, true);
		CurrentJumpCount++;
		JumpHeight *= 2.0f;
	}
}

void ABasicCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	CurrentJumpCount = 0;
	JumpHeight = 500.0f;
}

