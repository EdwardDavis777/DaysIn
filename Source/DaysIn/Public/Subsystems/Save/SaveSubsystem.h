#pragma once

/*
 
     Defines class defaults for all save related subsystems.
	 Only subsystems that actually trigger save events at 
	 run-time.

*/


//Subsystem imports.
#include "Subsystems/Save/SaveManagerSubsystem.h"



//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveSubsystem.generated.h"



//Forward declares.
class USaveGame;
class UPlayerUISubsystem;



UCLASS()
class DAYSIN_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;



	/*
	                                   Components.
	*/
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManager;

	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

    

	/*
	                               Load event functions.
	*/

	/*
	     Loads a save at begin play when called. Note the save class that 
		 is passed must be managed by the save manager subsystem
		 or the load will fail.

		 @param SaveClass: pointer to the save class you wish 
		 to load.
	*/
	void LoadSaveAtBegin(USaveGame* SaveClass);


	/*
	                                  Class Generics.
	*/

	/*
	     Constructs a new save class with the class type provided by the caller,
		 and will pass the created instance into the save manager subsystem if and 
		 only if the constructed save class implements the ISaveInterface.

		 @tparam USaveGame: T must be a USaveGame.

		 @return USaveGame: a pointer to a USaveGame class instance with the class
		 type provided by the caller.
	*/
	template<typename TSaveClass>
	TSaveClass* MakeSave()
	{
		if (!SaveManager) return nullptr;

		static_assert(TIsDerivedFrom<TSaveClass, USaveGame>::IsDerived, "T must be a USaveGame");
		if (TSaveClass* SaveClass = NewObject<TSaveClass>())
		{
			SaveManager->ManageSave(SaveClass);
			return SaveClass;
		}
		return nullptr;
	}
};