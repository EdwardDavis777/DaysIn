#pragma once

/*
     Defines class defaults for all backpacks that can be found
	 in the world.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "PlayerStorage/Abstracts/CollectableStorageBase.h"
#include "Backpack.generated.h"



UCLASS()
class DAYSIN_API ABackpack : public ACollectableStorageBase 
{
	GENERATED_BODY()
};