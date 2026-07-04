#pragma once

/*
     Handles save events triggered by the player character.
	 Most use cases for key save events are for debugging, though
	 I assume a function here will later be hooked to some UI 
	 later.
*/



//Engine imports.
#include "CoreMinimal.h"
#include "Input/Abstracts/InputStreamBaseComponent.h"
#include "PlayerSaveInput.generated.h"



//Forward declares.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USaveManagerSubsystem;



UCLASS()
class DAYSIN_API UPlayerSaveInput : public UInputStreamBaseComponent
{
	GENERATED_BODY()
	
public:
	virtual void CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController) override;
private:


	/*
	                               UPlayerSaveInput input components.       
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> SaveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LoadAction;


	/*
	                                          Components.
	*/
	UPROPERTY()
	TObjectPtr<USaveManagerSubsystem> SaveManager;


	/*
	                                      Save event functions.
	*/
	void SaveEvent(const FInputActionValue& ActionValue);
	void LoadEvent(const FInputActionValue& ActionValue);


	/*
	                                        Engine overrides.
	*/
	virtual void BeginPlay() override;
};