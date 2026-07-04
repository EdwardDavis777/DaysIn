#pragma once

/*

    Implements run-time logic for the UIPlayerMain widget
	class instance. Such as updating the player UI subsystem
	etc.

*/

 
//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "PlayerMainUIComponent.generated.h"



//Forward declares.
class UUIPlayerMain;
class UPlayerUISubsystem;
class UPlayerSubsystem;
class UItemInstance;
class UDragDropOperation;


UCLASS()
class DAYSIN_API UPlayerMainUIComponent : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;
	void BindDelegates();


	/*
	                                 Event functions.
	*/

	/*
	    Updates the player UI subsystem with both the UIPlayerMain instance,
		and the UIPlayerEquipmentMain instance when called.
	*/
	void UpdateUISubsystem();


	/*
	    Dispatch function; performs a global event that cancels all drag events when the player main
		is closed.
	*/
	void CancelDragEvents();

	/*
	                                Spawn event functions.
	*/

	/*
	     Spawns an item through a payload instance when a widget is dropped
		 on the player UI main.

		 @param InOperation: pointer to the drag drop
		 operation.

		 @return TRUE/FLASE: true if the spawn event is successful,
		 false if it fails.
	*/
	bool SpawnEvent(UDragDropOperation* InOperation);

	/*
	    Dispatch function; when called, it will force spawn an item
		through an instnace into the world.

		@param ItemInstance: pointer to an item instance 
		you wish to spawn an actor from.
	*/
	void ForceSpawnEvent(UItemInstance* ItemInstance);


	/*
	    Spawns a new item through an item instance infront 
		of the player.

		@param ItemInstance: pointer to an item instance you wish
		to spawn an actor from.
	*/
	void SpawnItem(UItemInstance* ItemInstance);

private:

	/*
	                          UPlayerMainUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIPlayerMain> PlayerMain;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

	UPROPERTY()
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;
};