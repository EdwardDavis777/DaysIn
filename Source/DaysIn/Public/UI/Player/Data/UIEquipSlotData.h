#pragma once

/*
     Defines run-time data for equipment slots.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIEquipSlotData.generated.h"


//Forward declares.
class UItemInstance;


USTRUCT(BlueprintType)
struct FEquipSlotData
{
	GENERATED_BODY()


	/*
	     Stores a general pointer to a stored item in 
		 this slot.
	*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemInstance> StoredItem;


	UPROPERTY(VisibleAnywhere)
	bool bOccupied;

	FEquipSlotData()
	: StoredItem(),bOccupied(false)
	{ }
};


USTRUCT(BlueprintType)
struct FEquipSlotColorData
{
	GENERATED_BODY()


	/*
	    Defines the color that is displayed when a hovered over
		item can be placed into this slot. The default is like
		transparent greenish shit.
	*/
	UPROPERTY(EditAnywhere)
	FLinearColor CanPlaceColor;

	/*
	    Holds the default border color; cached when this widget
		is constructed.
	*/
	UPROPERTY(VisibleAnywhere)
	FLinearColor DefaultBorderColor;



	FEquipSlotColorData()
	: CanPlaceColor(0, 0.5, 0.0f, 0.5),DefaultBorderColor()
	{ }
};

UCLASS()
class DAYSIN_API UUIEquipSlotData : public UObject
{
	GENERATED_BODY()
};