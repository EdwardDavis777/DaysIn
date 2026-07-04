#pragma once

/*
     Defines all run-time structs that is defined on a weapons
	 run-time instance class.
*/


//Other imports.
#include "Weapons/Data/WeaponRunTimeStats.h"


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponRunTimeData.generated.h"



USTRUCT(BlueprintType)
struct FWepRunTimeData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	FWepRunTimeStats WeaponRunTimeStats;
};

UCLASS()
class DAYSIN_API UWeaponRunTimeData : public UObject
{
	GENERATED_BODY()
	
};