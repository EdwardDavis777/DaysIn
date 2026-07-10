//Engine imports.
#include "Subsystems/UI/UISubsystem.h"



void UUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BindDelegates();
}


void UUISubsystem::Deinitialize()
{
	Super::Deinitialize();
}


void UUISubsystem::BindDelegates()
{
	UISubsystemDispatches.ForwardDragOperation.AddUObject(this, &UUISubsystem::ForwardDragOperation);
	UISubsystemDispatches.ForwardDropOperation.AddUObject(this, &UUISubsystem::ForwardDropOperation);
	UISubsystemDispatches.ForwardDragOperation.AddUObject(this, &UUISubsystem::ClearDropOperation);
	UISubsystemDispatches.ForwardDropOperation.AddUObject(this, &UUISubsystem::ClearDragOperation);
}



/*
							   UISubsystem event functions.
*/

void UUISubsystem::ForwardDragOperation(UDragDropOperation* InOperation)
{
	if (!InOperation) return;
	DragOperation = InOperation;
}

void UUISubsystem::ForwardDropOperation(UDragDropOperation* InOperation)
{
	if (!InOperation) return;
	DropOperation = InOperation;
}

void UUISubsystem::ClearDragOperation(UDragDropOperation* InOperation)
{
	DragOperation = nullptr;
}

void UUISubsystem::ClearDropOperation(UDragDropOperation* InOperation)
{
	DropOperation = nullptr;
}




/*
										Accessors.
*/

TObjectPtr<UDragDropOperation>& UUISubsystem::GetDragOperation()
{
	return DragOperation;
}

TObjectPtr<UDragDropOperation>& UUISubsystem::GetDropOperation()
{
	return DropOperation;
}