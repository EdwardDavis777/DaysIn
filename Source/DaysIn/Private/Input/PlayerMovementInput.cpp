//Engine imports.
#include "Input/PlayerMovementInput.h"

//Component imports.
#include "EnhancedInputComponent.h"


//Other imports.
#include "Characters/Player/Survivor.h"

 

void UPlayerMovementInput::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	Super::CreateInputStream(InputComponent, PlayerController);

	if (EnhancedContext)
	{
		AddMappingContext(MappingContext,PlayerController);

		EnhancedContext->BindAction(MovementAction, ETriggerEvent::Triggered, this, &UPlayerMovementInput::Move);
		EnhancedContext->BindAction(LookAction, ETriggerEvent::Triggered, this, &UPlayerMovementInput::Look);
	}
}



/*
										 Input event functions.
*/

void UPlayerMovementInput::Move(const FInputActionValue& InputValue)
{
	if (!Player) return;

	FVector2D moveVector = InputValue.Get<FVector2D>();
	Player->AddMovementInput(Player->GetActorForwardVector(), moveVector.Y);
	Player->AddMovementInput(Player->GetActorRightVector(), moveVector.X);
}


void UPlayerMovementInput::Look(const FInputActionValue& InputValue)
{
	if (!Player) return;

	FVector2D lookVector = InputValue.Get<FVector2D>();
	Player->AddControllerPitchInput(lookVector.X);
	Player->AddControllerYawInput(lookVector.Y);
}
