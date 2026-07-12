//Engine imports.
#include "UI/Player/Components/UIPlayerLayers.h"

//Component imports.
#include "Kismet/GameplayStatics.h"


//Other imports.
#include "UI/Layers/UIDragLayer.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/UI/UISubsystem.h"



void UUIPlayerLayers::BeginPlay()
{
	Super::BeginPlay();

	if (UISubsystem = SubUtility::FindSub<UUISubsystem>(GetWorld()))
	{
		OwnerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		ConstructDragLayer();
	}
}




/*
								UI layer event functions.
*/

void UUIPlayerLayers::ConstructDragLayer()
{
	if (!DragLayerClass) return;

	if (DragLayer = CreateWidget<UUIDragLayer>(GetWorld(), DragLayerClass))
	{
		DragLayer->SetOwningPlayer(OwnerController);
		DragLayer->AddToViewport();
		UISubsystem->SetDragLayer(DragLayer);
	}
}