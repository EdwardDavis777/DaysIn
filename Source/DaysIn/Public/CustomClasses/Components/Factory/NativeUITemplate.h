#pragma once

/*
     Defines factory templates for NativeUIComponets 
     to be built in classes.
*/


//Other imports.
#include "CustomClasses/Components/NativeUIComponent.h"

//Engine imports.
#include "CoreMinimal.h"



namespace NativeUITemplate
{

    /*
        Constructs a UNativeUIComponent, and caches a pointer to the widget instance
        that implements the component, and the world pointer.

        @param WorldContext: pointer to the current world
        context.

        @param Owner: pointer to the owning widget class 
        instance.

        @tparam UNativeUIComponent: T must be a UNativeUIComponent
        class.

        @return UNativeUIComponent: a pointer to the created UNativeUIComponent
        instance to the caller.
    */
    template<typename TComponent>
    TComponent* CreateDefaultUIComponent(UWorld* WorldContext, UUserWidget* Owner)
    {
        if (!WorldContext || !Owner) return nullptr;

        static_assert(TIsDerivedFrom<TComponent, UNativeUIComponent>::IsDerived, "T must be a UNativeUIComponent class");
        if (TComponent* Component = NewObject<TComponent>(Owner))
        {
            Component->Initialize(WorldContext, Owner);
            return Component;
        }
        return nullptr;
    }
}