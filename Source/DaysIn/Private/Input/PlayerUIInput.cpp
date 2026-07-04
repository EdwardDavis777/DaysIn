//Engine imports.
#include "Input/PlayerUIInput.h"


//Component imports.
#include "EnhancedInputComponent.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"



void UPlayerUIInput::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	Super::CreateInputStream(InputComponent, PlayerController);

	if (EnhancedContext)
	{
		AddMappingContext(MappingContext, PlayerController);
		EnhancedContext->BindAction(ToggleUIMainAction, ETriggerEvent::Triggered, this, &UPlayerUIInput::ToggleUIMain);
	}
}

void UPlayerUIInput::BeginPlay()
{
	Super::BeginPlay();
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());
}





/*
								  UI input event functions.
*/

void UPlayerUIInput::ToggleUIMain(const FInputActionValue& InputValue)
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.ToggleUIMain.Broadcast();
}