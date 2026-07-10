//Engine imports.
#include "Input/PlayerUIInput.h"


//Component imports.
#include "EnhancedInputComponent.h" 
#include "Blueprint/DragDropOperation.h"


//Other imports.
#include "UI/Interactables/Abstracts/UIDraggableBase.h"
#include "UI/Interactables/Abstracts/GlobalEvents/DraggableTemplates/DraggableTemplates.h"
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Components/InstanceUIRuntimeComponent.h"

//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/UI/UISubsystem.h"




void UPlayerUIInput::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	Super::CreateInputStream(InputComponent, PlayerController);

	if (EnhancedContext)
	{
		AddMappingContext(MappingContext, PlayerController);
		EnhancedContext->BindAction(ToggleUIMainAction, ETriggerEvent::Triggered, this, &UPlayerUIInput::ToggleUIMain);
		EnhancedContext->BindAction(RotateAction, ETriggerEvent::Triggered, this, &UPlayerUIInput::RotateDraggingItem);
	}
}


void UPlayerUIInput::BeginPlay()
{
	Super::BeginPlay();

	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());
	UISubsystem = SubUtility::FindSub<UUISubsystem>(GetWorld());
}





/*
								  UI input event functions.
*/

void UPlayerUIInput::ToggleUIMain(const FInputActionValue& InputValue)
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.ToggleUIMain.Broadcast();
}


void UPlayerUIInput::RotateDraggingItem(const FInputActionValue& InputValue)
{
	if (!UISubsystem || !UISubsystem->GetDragOperation()) return;

	auto* ItemInstance = DraggableTemplate::GetPayloadInstance<UUIDraggableBase>(UISubsystem->GetDragOperation());
	auto* DragInstance = DraggableTemplate::GetPayload<UUIDraggableBase>(UISubsystem->GetDragOperation());
   
	if (ItemInstance && DragInstance)
	{
		ItemInstance->GetUIRuntimeComponent()->NotifyRotated(ItemInstance, DragInstance);
	}
}