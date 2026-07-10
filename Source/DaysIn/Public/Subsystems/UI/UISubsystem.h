#pragma once

/*

     Handles global general UI event data driven
	 by UI events.

*/


//Other imports.
#include "Dispatches/UISubsystemDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UISubsystem.generated.h"




UCLASS()
class DAYSIN_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void BindDelegates();


	/*
	                               Cached components.
	*/
	UPROPERTY()
	TObjectPtr<UDragDropOperation> DragOperation;

	UPROPERTY()
	TObjectPtr<UDragDropOperation> DropOperation;


	/*
	                           UISubsystem event functions.
	*/

	/*
	    Sets this subsystems current drag operation 
		pointer.

		@param InOperation: pointer to the current 
		drag operation.
	*/
	void ForwardDragOperation(UDragDropOperation* InOperation);

     
	/*
	    Sets this subsystems current drop operation
		pointer.

		@param InOperation: pointer to the current drop
        operation.
	*/
	void ForwardDropOperation(UDragDropOperation* InOperation);


	/*
	    Clears the drag operation whenever a drop event dispatch
		is triggered.
        

		@param InOperation: pointer to the current drop 
		operation; only needed due to the dispatch.
	*/
	void ClearDragOperation(UDragDropOperation* InOperation);


	/*
	    Clears the drop operation pointer whenever a drag event
		dispatch is triggered.
		
		@param InOperation: pointer to the current 
		drop operation; only needed due to the dispatch signature.
	*/
	void ClearDropOperation(UDragDropOperation* InOperation);


public:
	FUISubsystemDelegates UISubsystemDispatches;


	/*
	                                    Accessors.
	*/
	TObjectPtr<UDragDropOperation>& GetDragOperation();
	TObjectPtr<UDragDropOperation>& GetDropOperation();
};