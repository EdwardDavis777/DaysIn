#pragma once

/*
     Defines simple wrappers for accessing subsystems
     across classes.
*/


//Engine imports.
#include "CoreMinimal.h"



namespace SubUtility
{

     /*
          Finds a subsystem of type T, and returns the subsystem instance to 
          the caller.

          @param WorldContext: pointer to the current world
          context.

          @tparam UGameInstanceSubsystem: T must be type UGameInstanceSubsystem
          or the compiler will scream at you!!

          @return UGameInstanceSubsystem: a pointer to the subsystem with the class type
          provided by the caller.
     */
     template<typename TInstance>
     TInstance* FindSub(UWorld* WorldContext)
     {
         if (!WorldContext) return nullptr;

         static_assert(TIsDerivedFrom<TInstance, UGameInstanceSubsystem>::IsDerived, "T must be type UGameInstanceSubsystem");
         if (auto* GI = WorldContext->GetGameInstance())
         {
             TInstance* Subsystem = GI->GetSubsystem<TInstance>();
             return Subsystem;
         }
         return nullptr;
     }
}