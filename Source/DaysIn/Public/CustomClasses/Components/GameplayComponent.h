#pragma once

/*

     Defines defaults for gameplay components; acts similar to unreal's AActorComponent,
	 though is made to be defined onto UObject class instances. Allows a bit of 
	 composition for gameplay logic that should otherwise be handled by a consistent
	 state in memory.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayComponent.generated.h"




UCLASS()
class DAYSIN_API UGameplayComponent : public UObject
{
	GENERATED_BODY() 

public:

	/*
	     Caches a world pointer, and a general pointer to an owning
		 UObject class instance.

		 @param WorldContext: pointer to the current world
		 context.

		 @param OwnerObject: pointer to the UObject instance you
		 wish to own this component.
	*/
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject);

protected:

	/*
	                                    Components.
	*/
	UPROPERTY()
	TObjectPtr<UWorld> World;

	UPROPERTY()
	TObjectPtr<UObject> Owner;


	/*
	                                Generic accessors.
	*/

   /*
        Performs a cast using the base general pointer cache when this component
		is initialized.

		@tparam UObject: T must be a UObject.

		@return UObject: pointer to some UObject with the class
		type provided by the caller.
   */
   template<typename TOwner>
   TOwner* GetOwner()
   {
	   if (!Owner) return nullptr;
	   
	   static_assert(TIsDerivedFrom<TOwner, UObject>::IsDerived, "T must be a UObject");
	   if (TOwner* Own = Cast<TOwner>(Owner))
	   {
		   return Own;
	   }
	   return nullptr;
   }
};