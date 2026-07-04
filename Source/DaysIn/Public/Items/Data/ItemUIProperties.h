#pragma once

/*
     Defines static item object UI configurations; defined inside of the 
	 item data asset.
*/


//Engine properties.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemUIProperties.generated.h"


//Forward declares.
class UUIDraggableBase;



USTRUCT(BlueprintType)
struct FItemUIProps
{
	GENERATED_BODY() 


	/*
	     Holds a class reference to the icon class type you
		 wish this item to implement/use in user interfaces.
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUIDraggableBase> IconClass;

    
	/*
	    Holds a string literal to the item name that is 
		displayed in user interfaces.
	*/
	UPROPERTY(EditAnywhere)
	FText UIName;


	/*
	     Defines the space an item will take up when added to 
		 a user interface.
	*/
	UPROPERTY(EditAnywhere)
	FIntPoint ItemSize;


	/*
	    Defines the texture that is displayed when items are filled
		in a user interface.
	*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon;



	FItemUIProps() 
	: IconClass(), UIName(),ItemSize(),Icon()
	{ }
};
UCLASS()
class DAYSIN_API UItemUIProperties : public UObject
{
	GENERATED_BODY()
	
};
