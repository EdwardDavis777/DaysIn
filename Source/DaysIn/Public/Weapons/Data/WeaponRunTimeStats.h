#pragma once

/*
      Defiens weapon run-time stats, such as current recoil stats,
	  durability etc.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponRunTimeStats.generated.h"


USTRUCT(BlueprintType)
struct FWepRunTimeStats
{
	GENERATED_BODY()

	
	UPROPERTY(SaveGame)
	float Durability;


	FWepRunTimeStats() :
	Durability(100.0f)
	{ }
};



UCLASS()
class DAYSIN_API UWeaponRunTimeStats : public UObject
{
	GENERATED_BODY()	
};