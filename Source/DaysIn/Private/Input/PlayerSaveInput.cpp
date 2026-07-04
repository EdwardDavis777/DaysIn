//Engine imports.
#include "Input/PlayerSaveInput.h"


//Component imports.
#include "EnhancedInputComponent.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Save/SaveManagerSubsystem.h"





void UPlayerSaveInput::BeginPlay()
{
	Super::BeginPlay();
	SaveManager = SubUtility::FindSub<USaveManagerSubsystem>(GetWorld());
}




void UPlayerSaveInput::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	Super::CreateInputStream(InputComponent, PlayerController);

	if (EnhancedContext)
	{
		AddMappingContext(MappingContext,PlayerController);
		EnhancedContext->BindAction(SaveAction, ETriggerEvent::Triggered, this, &UPlayerSaveInput::SaveEvent);
		EnhancedContext->BindAction(LoadAction, ETriggerEvent::Triggered, this, &UPlayerSaveInput::LoadEvent);
	}
}




/*
										Save event functions.
*/

void UPlayerSaveInput::SaveEvent(const FInputActionValue& ActionValue)
{
	if (!SaveManager) return;
	SaveManager->Save();
}

void UPlayerSaveInput::LoadEvent(const FInputActionValue& ActionValue)
{
	if (!SaveManager) return;
	SaveManager->Load();
}