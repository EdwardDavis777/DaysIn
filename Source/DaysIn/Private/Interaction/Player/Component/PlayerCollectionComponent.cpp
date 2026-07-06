//Engine imports.
#include "Interaction/Player/Component/PlayerCollectionComponent.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"
#include "Interaction/Player/InteractionUtility/PlayerInteractionUtility.h"


//Subsystem imports.
#include "Subsystems/Player/PlayerSubsystem.h" 
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/Player/PlayerEquipmentSubsystem.h"



void UPlayerCollectionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerSubsystem = SubUtility::FindSub<UPlayerSubsystem>(GetWorld());
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());
	PlayerEquipmentSubsystem = SubUtility::FindSub<UPlayerEquipmentSubsystem>(GetWorld());

	BindDelegates();
}

void UPlayerCollectionComponent::BindDelegates()
{
	if (!PlayerSubsystem) return;
	PlayerSubsystem->PlayerSubsystemDispatch.PickupItem.AddUObject(this, &UPlayerCollectionComponent::OnCollection);
}


/*
							  Collection event functions.
*/

void UPlayerCollectionComponent::OnCollection(AItemBase* Item)
{
	if (!Item || !PlayerUISubsystem || !PlayerEquipmentSubsystem) return;

	if (!Interact::bStoreInSlot(PlayerUISubsystem->GetEquipmentMain(), Item))
	{
		Interact::StoreInExternalStorage(PlayerEquipmentSubsystem->GetPlayerStorages(), Item);
	}
}