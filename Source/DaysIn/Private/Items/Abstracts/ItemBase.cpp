//Engine imports.
#include "Items/Abstracts/ItemBase.h"


//Component imports.
#include "Components/SphereComponent.h"



//Utility imports.
#include "Items/Utility/ItemInstanceTemplates.h"
#include "SubsystemUtilitys/SubsystemUtility.h" 


//Custom component imports.
#include "Items/Components/ItemPhysicsComponent.h"


//Subsystem imports.
#include "Subsystems/Item/ItemEventSubsystem.h"



 
AItemBase::AItemBase() 
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	RootComponent = CollisionSphere;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	ItemPhysicsComponent = CreateDefaultSubobject<UItemPhysicsComponent>(TEXT("ItemPhysicsComponent"));
}
 

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
     
	if (ItemDataAsset)
	{
		ItemEventSubsystem = SubUtility::FindSub<UItemEventSubsystem>(GetWorld());
		ItemInstance = ItemInstanceTemplate::CreateDefaultInstance<UItemInstance>(GetWorld(), ItemDataAsset, ItemDataAsset->ItemProperties.ItemInstanceClass);
	}
}



/*
							      Interface event functions.
*/

void AItemBase::Pickup()
{
}

void AItemBase::Drop(UItemInstance* Instance)
{
	if (!Instance) return;

	ItemDataAsset = ItemInstance->GetStaticItemData();
	ItemInstance = Instance;
	ItemEventSubsystem->Dispatches.ItemDropped.Broadcast(ItemInstance);
}


/*
                                       Accessors.
*/

UItemInstance* AItemBase::Instance()
{
	if (ItemInstance) return ItemInstance.Get();
	return nullptr;
}

const EEquipTag AItemBase::GetEquipTag() const 
{
	if (ItemDataAsset) return ItemDataAsset->ItemProperties.EquipTag;
	return EEquipTag::NONE;
}