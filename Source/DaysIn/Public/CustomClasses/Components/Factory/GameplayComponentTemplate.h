#pragma once

/*
     Defines templates for constructing game play components
     for classes. The template fully initilizes every component
     that is made given valid parameters.
*/


//Other imports.
#include "CustomClasses/Components/GameplayComponent.h"


//Engine imports.
#include "CoreMinimal.h"



namespace GameplayTemplate
{

    /*
         Creates an initalized UGameplayComponent; calling its custom constructor
         and adding its outter to the owner class provided.

         @param WorldContext: pointer to the current world
         context.

         @param Owner: pointer to the owning UObject
         class.

         @tparam: T must be a UGameplayComponent.

         @return UGameplayComponent: pointer to a default constrcuted game play component
         with the class type provided by the caller.
    */
    template<typename TComponent>
    TComponent* CreateDefaultGameplayComponent(UWorld* WorldContext, UObject* Owner)
    {
        if (!WorldContext || !Owner) return nullptr;

        static_assert(TIsDerivedFrom<TComponent, UGameplayComponent>::IsDerived, "T must a be a UGameplayComponent");
        if (TComponent* Component = NewObject<TComponent>(Owner))
        {
            Component->Initialize(WorldContext, Owner);
            return Component;
        }
        return nullptr;
    }
}