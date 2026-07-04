#pragma once

/*
    
	Defines tweakable physics defaults for item 
	obejects that can be found in the world.

	The physics config is defined inside of the UItemDataAsset
	class.

*/

//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemPhysicsProperties.generated.h"



USTRUCT(BlueprintType)
struct FItemPhysicsProps
{
	GENERATED_BODY()

	/*
	    Defines how much air resistance is applied linearly
		to a falling object.
	*/
	UPROPERTY(EditAnywhere)
	float LinearDamping;


	/*
		Defines how much air resistance is applied angularly?
		to a falling object haha.
	*/
	UPROPERTY(EditAnywhere)
	float AngularDamping;


	FItemPhysicsProps()
	: LinearDamping(), AngularDamping()
	{ }
};



UCLASS()
class DAYSIN_API UItemPhysicsProperties : public UObject
{
	GENERATED_BODY()
	
};
