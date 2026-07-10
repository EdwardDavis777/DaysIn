#pragma once

/*
     Defines player UI related input events.
*/



//Engine imports.
#include "CoreMinimal.h" 
#include "Input/Abstracts/InputStreamBaseComponent.h"
#include "PlayerUIInput.generated.h"



//Forward declares.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UPlayerUISubsystem;
class UUISubsystem;



UCLASS()
class DAYSIN_API UPlayerUIInput : public UInputStreamBaseComponent
{
	GENERATED_BODY()
	

private:
	virtual void CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController) override;


    /*
                                   UPlayerUIInput input components.
    */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> MappingContext;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> ToggleUIMainAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> RotateAction;



	/*
	                                      Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerUISubsystem> PlayerUISubsystem;

	UPROPERTY();
	TObjectPtr<UUISubsystem> UISubsystem;

	/*
	                                  UI input event functions.
	*/
	void ToggleUIMain(const FInputActionValue& InputValue);
	void RotateDraggingItem(const FInputActionValue& InputValue);



	/*
	                                     Engine overrides.
 	*/
	virtual void BeginPlay() override;
};