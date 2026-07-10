#pragma once

/*

      Defines methods for handling item instance UI related
	  runtime events.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/GameplayComponent.h"
#include "InstanceUIRuntimeComponent.generated.h"



//Forward declares.
class UItemInstance;
class UUISubsystem;
class UUIDraggableBase;
class UItemEventSubsystem;


UCLASS()
class DAYSIN_API UInstanceUIRuntimeComponent : public UGameplayComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(UWorld* WorldContext, UObject* OwnerObject) override;
	void BindDelegates();

    /*
	                         Item instance UI event functions.
	*/
    
	/*
	      Updates the item instance's UI data that it has been rotated, will then
		  forward a dispatch to all user interfaces about the rotation event.

		  @param RotatedItem: pointer to the rotated 
		  item instance.
		  
		  @param AssocaitedWidget: pointer to the assocaited
		  dragging widget instance.
	*/
	void NotifyRotated(UItemInstance* RotatedItem, UUIDraggableBase* AssocaitedWidget);



	/*
	     Called during an initial drag event or after a drop event; will simply reset the item instances
		 rotation state.

		 @param RotatedItem: pointer to the current item instance
		 that is being dragged or dropped into the world.
	*/
	void ResetRotated(UItemInstance* RotatedItem);


private:

	/*
	                               Components.
	*/
	UPROPERTY()
	TObjectPtr<UItemInstance> ItemInstance;

	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem;

	UPROPERTY()
	TObjectPtr<UItemEventSubsystem> ItemEventSubsystem;
};