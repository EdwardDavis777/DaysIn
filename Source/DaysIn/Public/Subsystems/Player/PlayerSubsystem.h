#pragma once

/*
     Defines player character/survivor class related
	 events/variables for other classes.
*/

//Other imports.
#include "Subsystems/Player/Dispatches/PlayerSubsystemDispatches.h"


//Engine imports.
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"  
#include "PlayerSubsystem.generated.h"
 


//Forward declares.
class ASurvivor;



UCLASS()
class DAYSIN_API UPlayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	 FPlayerSubsystemDelegates PlayerSubsystemDispatch;



	/*
	                                        Accessors.
	*/
	ASurvivor* GetPlayer() const;
	APlayerController* GetPlayerController() const;
};