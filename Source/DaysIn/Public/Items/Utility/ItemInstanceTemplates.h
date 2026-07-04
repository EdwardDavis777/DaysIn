#pragma once

/*
     Defines wrappers for creating item instances; some fully 
     initialize the item instance others dont so just be mindful
     when constructing objects.
*/


//Other imports.
#include "Items/Abstracts/ItemInstance.h"


//Engine imports. 
#include "CoreMinimal.h"


//Forward declares.
class UItemDataAsset;



namespace ItemInstanceTemplate
{

    /*
        Creates a new item instance in memory, and fully initializes it, the returns
        a pointer to the instance to the caller. Note, its outer is set to be 
        the game instance.


        @param WorldContext: pointer to the current world 
        context.

        @param ItemDataAsset: pointer to the associated items 
        static data.
        
        @param InstanceClass: reference to the class type you 
        would like to construct.

        @tparam UItemInstance: T must be type UItemInstance or the compiler will
        scream at you!!

        @return UItemInstance: pointer to the created item instance back to 
        the caller.
    */
    template<typename TInstance>
    TInstance* CreateDefaultInstance(UWorld* WorldContext, UItemDataAsset* ItemDataAsset,TSubclassOf<UItemInstance>& InstanceClass)
    {
        if (!WorldContext || !ItemDataAsset || !InstanceClass || !WorldContext->GetGameInstance()) return nullptr;

        static_assert(TIsDerivedFrom<TInstance, UItemInstance>::IsDerived, "T must be type UItemInstance");
        if (TInstance* NewInstance = NewObject<TInstance>(WorldContext->GetGameInstance(), InstanceClass))
        {
            NewInstance->Initialize(WorldContext, ItemDataAsset);
            return NewInstance;
        }
        return nullptr;
    }
}