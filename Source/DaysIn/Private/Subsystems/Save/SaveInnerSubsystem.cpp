//Engine imports.
#include "Subsystems/Save/SaveInnerSubsystem.h"


//Other imports.
#include "Save/Abstracts/SaveGenericInner.h"



//Subsystem imports.
#include "Subsystems/Item/ItemEventSubsystem.h"



void USaveInnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SaveGenericInner = MakeUnmanagedSave<USaveGenericInner>();
	BindDelegates();
}

void USaveInnerSubsystem::BindDelegates()
{
	if (!ItemEventSubsystem) return;
	ItemEventSubsystem->Dispatches.PostDeserizlieEvent.AddUObject(this, &USaveInnerSubsystem::PostOuterDeserialization);
}




/*
								 Save inner event functions.
*/

void USaveInnerSubsystem::PostOuterDeserialization(const TArray<FSPKGSubInstance>& SavePackages, TMap<TObjectPtr<AActor>, FSPKGSubInstance>& SentBackInners, UItemInstance* OuterInstance)
{
	if (SavePackages.IsEmpty() || !OuterInstance || !SaveGenericInner) return;
	SaveGenericInner->DeserializeInners(SavePackages, SentBackInners,OuterInstance,GetWorld());
}