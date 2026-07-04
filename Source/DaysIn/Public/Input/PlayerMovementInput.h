#pragma once

/*
	Derived from the UInputStreamBaseComponent; simply defines default player loco-motion
	input events such as movement/looking around.
*/
 

//Engine imports.
#include "CoreMinimal.h"
#include "Input/Abstracts/InputStreamBaseComponent.h"
#include "PlayerMovementInput.generated.h"


//Forward declares.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;




UCLASS()
class DAYSIN_API UPlayerMovementInput : public UInputStreamBaseComponent
{
	GENERATED_BODY()
	
private:
	virtual void CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController) override;
	
	/*
	                               UPlayerMovementInput input components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MappingContext", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LookAction;


	/*
	                                     Input event functions.
	*/
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
};
