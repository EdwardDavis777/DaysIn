#pragma once

/*
     Defines tweakable data, and run-time data for 
	 all UIDraggableBase instances.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIDraggableData.generated.h"



//Forward declares.
class UItemInstance;
class UUIDraggableBase;





USTRUCT(BlueprintType)
struct FRuntimeData
{
	GENERATED_BODY()


    /*
	    Holds a general pointer to an item instance that is 
		assocaited with this draggable widget instance.
	*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemInstance> GeneralInstance;


	FRuntimeData() 
	: GeneralInstance()
	{ }
};


USTRUCT(BlueprintType)
struct FColorData
{
	GENERATED_BODY()


	/*
	    Not tweakable; simply updates based on the border color you choose
	    for the derived class in the UMG.
	*/
	UPROPERTY(VisibleAnywhere)
	FLinearColor DefaultBorderColor;


	/*
	    Defines the borders brush color when a draggable widget is 
		currently being dragged.
	*/
	UPROPERTY(EditAnywhere)
	FLinearColor DragBorderColor;


	/*
	     Defines the color of the draggable border when it can be 
		 dragged.
	*/
	UPROPERTY(EditAnywhere)
	FLinearColor HoverBorderColor;


	/*
	     Defines the color of the draggable border when it can be 
		 placed/dropped inside of some other user interface.
	*/
	UPROPERTY(EditAnywhere)
	FLinearColor CanPlaceColor;


	/*
	     Defines the color of the draggable border when it
		 cannot be place inside of some other user interface.
	*/
	UPROPERTY(EditAnywhere)
	FLinearColor CannotPlaceColor;



	FColorData()
	: DefaultBorderColor(),DragBorderColor(1.0f,1.0f,1.0f,0.15f),
	  HoverBorderColor(1.0f,1.0f,1.0f,0.15f), CanPlaceColor(0.0f,1.0f,0.0f,0.2f), 
	  CannotPlaceColor(1.0,0.0f,0.0f,0.2f)
	{ }
};



USTRUCT(BlueprintType)
struct FData 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Data|Memory")
	FRuntimeData RuntimeData;
};



UCLASS()
class DAYSIN_API UUIDraggableData : public UObject
{
	GENERATED_BODY()
};