#pragma once

/*

       Defines item spawner configs, used only in the item spawner 
       namespace for local configurations.

*/


//Engine imports.
#include "CoreMinimal.h"



/*
       Defines an empty spawn configuration list, zero spawn location,
       rotation with a forced spawn collision handling.

       Use when you want specific handling, or just zero zero
       behavior that will be adjusted manually.

*/
struct FEmptyConfig
{
    FActorSpawnParameters SpawnParams;
    FVector SpawnLoc;
    FRotator SpawnRot;

    FEmptyConfig()
    {
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        SpawnLoc = FVector::ZeroVector;
        SpawnRot = FRotator::ZeroRotator;
    }
};