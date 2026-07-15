//Engine imports.
#include "Subsystems/Save/SaveManagerSubsystem.h"


//Component imports.
#include "GameFramework/SaveGame.h"


//Other imports.
#include "Save/Interface/SaveClassInterfaces.h"



void USaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USaveManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}



/*
									  Cache events.
*/

void USaveManagerSubsystem::ManageSave(USaveGame* SaveClass)
{
	if (!SaveClass) return;

	if (auto* Interface = Cast<ISaveInterface>(SaveClass))
	{
		if (!SaveClasses.Contains(SaveClass)) { SaveClasses.Emplace(SaveClass, TScriptInterface<ISaveInterface>(SaveClass)); }
	}
}




/*
								  Save event functions.
*/

void USaveManagerSubsystem::Save()
{
	if (SaveClasses.IsEmpty()) return;

	for (TPair<TObjectPtr<USaveGame>,TScriptInterface<ISaveInterface>>& Save : SaveClasses)
	{
		if (!Save.Key.Get() || !Save.Value) continue;
		Save.Value->Save();
	}
} 

void USaveManagerSubsystem::Load()
{
	if (SaveClasses.IsEmpty()) return;

	for (TPair<TObjectPtr<USaveGame>, TScriptInterface<ISaveInterface>>& Save : SaveClasses)
	{
		if (!Save.Key.Get() || !Save.Value) continue;
		Save.Value->Load(GetWorld());
	}
}

void USaveManagerSubsystem::Load(USaveGame* SaveClass,UWorld* WorldContext)
{
	if (!SaveClass || !WorldContext) return;

	if (TScriptInterface<ISaveInterface>* SaveInterface = SaveClasses.Find(SaveClass))
	{
		SaveInterface->GetInterface()->Load(WorldContext);
	}
}


void USaveManagerSubsystem::Load(USaveGame* SaveClass, UWorld* WorldContext, UObject* DependencyObject)
{
	if (!SaveClass || !WorldContext || !DependencyObject) return;

	if (TScriptInterface<ISaveInterface>* SaveInterface = SaveClasses.Find(SaveClass))
	{
		SaveInterface->GetInterface()->Load(WorldContext,DependencyObject);
	}
}