#pragma once

/*

    Handles triggering save events for all save class
	instances.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"


//Forward declares.
class USaveGame;
class ISaveInterface;



UCLASS()
class DAYSIN_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	/*
	                                Cache components.
	*/
	UPROPERTY()
	TMap<TObjectPtr<USaveGame>, TScriptInterface<ISaveInterface>> SaveClasses;

public:

	/*
	                                 Cache events.
	*/

	/*
	    Caches the passed save class allowing the save manager
		to manage save events for this class.

		@param SaveClass: pointer to the save class you
		wish to be managed.
	*/
	void ManageSave(USaveGame* SaveClass);


	/*
	                              Save event functions.
	*/

	/*
	     Performs a save event for all managed save 
		 classes.
	*/
	void Save();

	/*
	     Performs a load event for all managed save
		 classes.
	*/
	void Load();

	
	/*
	     Loads a preferred save class; the class must be currently managed
		 by the save manager subsystem, or the load will simply fail.

		 @param SaveClass: pointer to the class you wish to 
		 load.

		 @param WorldContext: pointer to the current world
		 context.
	*/
	void Load(USaveGame* SaveClass,UWorld* WorldContext);

	/*
	     Loads a save class instance that requires a dependency object
		 to load saves.

		 @param SaveClass: pointer to the save class instance
		 you wish to load.

		 @param WorldContext: pointer to the current world
		 context.

		 @param DependencyObject: pointer to the save dependent
		 object.
	*/
	void Load(USaveGame* SaveClass, UWorld* WorldContext, UObject* DependencyObject);
};