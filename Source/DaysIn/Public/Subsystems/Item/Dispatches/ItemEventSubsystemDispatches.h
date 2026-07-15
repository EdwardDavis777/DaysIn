#pragma once

/*

       Defines dispatches for item runtime events. All dispatch
       signatures are defined inside of the item event subsystem.

*/

//Other imports.
#include "Save/Packages/Objects/Abstracts/SPKGSubInstance.h"


//Engine imports.
#include "CoreMinimal.h"


//Forward declares.
class UItemInstance;



/*
     Dispatched whenever an item is dropped inside of the world
     from a user interface or some other way.

     @param DroppedInstance: pointer to the dropped items
     new/re-used instance.
*/
DECLARE_MULTICAST_DELEGATE_OneParam(FItemDroppedSignature, UItemInstance* DroppedInstance);


/*
     Dispatched during a post de-serialize event has occured for
     an item instance.

     @param SavePackage: array of references to inner sub 
     save packages.

     @param SentBackInners: map of AActor pointers and their assocaited save package that will be populated
     during a deserialize event of inner actors/instances.

     @param OuterInstance: pointer to the outer
     instance.
*/
DECLARE_MULTICAST_DELEGATE_FourParams(FPostDeserizlieEventSignature, const TArray<FSPKGSubInstance>& SavePackages, TMap<TObjectPtr<AActor>, FSPKGSubInstance>& SentBackInners,UItemInstance* OuterInstance);


struct FItemEventSubsystemDelegates
{
    FItemDroppedSignature ItemDropped;
    FPostDeserizlieEventSignature PostDeserizlieEvent;
};