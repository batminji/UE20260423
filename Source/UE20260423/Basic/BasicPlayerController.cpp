// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ABasicPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (InputSystem)
		{
			InputSystem->ClearAllMappings();

			for (const auto& IMC : InputMappingContexts)
			{
				if (IMC.IsValid())
				{
					InputSystem->AddMappingContext(IMC.LoadSynchronous(), 0);
					// UE_LOG(LogTemp, Warning, TEXT("Input Mapping Context %s added successfully"), *IMC.GetAssetName());
				}
			}
		}
	}
}

void ABasicPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (IsLocalPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* InputSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (InputSystem)
		{
			InputSystem->ClearAllMappings();
		}
	}
}
