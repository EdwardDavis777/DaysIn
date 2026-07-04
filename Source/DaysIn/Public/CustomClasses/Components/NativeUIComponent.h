#pragma once


/*
   
     Custom component class; meant to act similar to a UActorComponent, but designed 
	 for UUserWidget class types.

	 Note: I also provided a custom template class for constructing these components
	 in widget classes. Generally speaking you should use it, as it will fully construct
	 the actual component automatically. You should only really ever be manually creating
	 these components in memory if you have a really good reason to be honest.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NativeUIComponent.generated.h"




UCLASS()
class DAYSIN_API UNativeUIComponent : public UObject
{
	GENERATED_BODY()

public:

	/*
	                               Parent constructor.
	*/

	/*
	     Initializes the native UI component by setting a general
		 pointer to its owner widget, and fetching the world context
		 during construction.

		 Note: for specific owner pointers, use the provided template
		 function in the base.

		 @param WorldContext: pointer to the current world
		 context.

		 @param OwnerWidget: general pointer to the current widget
		 owner; the widget that will own this component.
	*/
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget);

protected:

	/*
	                                Cached components.
	*/
	UPROPERTY()
	TObjectPtr<UWorld> World;

	UPROPERTY()
	TObjectPtr<UUserWidget> Owner;




	/*
	                                Templated accessors.
	*/


	/*
	
	     Provides type safe way for children components to access a pointer to their
		 owner. Performs a safe cast using the general pointer owner cached during
		 construction, and returns a pointer of a UUserWidget with the class type 
		 provided by the caller.

		 @tparam UUserWidget: T must be a UUserWidget.

		 @return UUserWidget: a pointer to a UUserWidget with the class
		 type provided by the caller.
	
	*/
	template<typename TOwner>
	TOwner* FindOwner()
	{
		if (!Owner) return nullptr;

		static_assert(TIsDerivedFrom<TOwner, UUserWidget>::IsDerived, "T must be a UUserWidget");
		if (TOwner* TryOwner = CastChecked<TOwner>(Owner))
		{
			return TryOwner;
		}
		return nullptr;
	}
};