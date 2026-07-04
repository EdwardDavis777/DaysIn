#pragma once

/*
     Defines static item object configurations; defined inside of the
	 item data asset.
*/


//Other imports.
#include "SharedData/Interaction/ItemEquipTag.h"


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemProperties.generated.h"


//Forward declares.
class UItemInstance;
class AItemBase;

USTRUCT(BlueprintType)
struct FItemProps
{
	GENERATED_BODY()

	/*
	    Defines the UObject class type that will represent this actor
		in memory during run-time events.
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemInstance> ItemInstanceClass;


	/*
	    Defines what type of class this item actually belongs
		to. Needed for spawn events etc.
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItemBase> ItemClass;


	/*
	    Defines a custom item equip tag; should only be set for custom
		storage methods that you wish this item to implement.
	*/
	UPROPERTY(EditAnywhere)
	EEquipTag EquipTag;

	FItemProps() 
	: ItemInstanceClass(),ItemClass(), EquipTag(EEquipTag::NONE)
	{ }
};

UCLASS()
class DAYSIN_API UItemProperties : public UObject
{
	GENERATED_BODY()
	
};
