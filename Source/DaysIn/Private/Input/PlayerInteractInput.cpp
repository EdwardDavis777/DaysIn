//Engine imports.
#include "Input/PlayerInteractInput.h"


//Component imports.
#include "EnhancedInputComponent.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerSubsystem.h"




void UPlayerInteractInput::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	Super::CreateInputStream(InputComponent, PlayerController);

	if (EnhancedContext)
	{
		AddMappingContext(MappingContext, PlayerController);
		EnhancedContext->BindAction(InteractAction, ETriggerEvent::Triggered, this, &UPlayerInteractInput::Interact);
    }
}



/*
								Interact event functions.
*/

void UPlayerInteractInput::Interact(const FInputActionValue& ActionValue)
{
	if (!PlayerSubsystem) return;
	PlayerSubsystem->PlayerSubsystemDispatch.TryPickupItem.Broadcast();
}