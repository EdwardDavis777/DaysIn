#pragma once


/*

     Handles player interaction related input.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "Input/Abstracts/InputStreamBaseComponent.h"
#include "PlayerInteractInput.generated.h"




//Forward declares.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;





UCLASS()
class DAYSIN_API UPlayerInteractInput : public UInputStreamBaseComponent
{
	GENERATED_BODY()	

private:
	virtual void CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController) override;


	/*
	                                UPlayerInteract action components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InteractAction;



	/*
	                                    Interact event functions.
	*/
	void Interact(const FInputActionValue& ActionValue);
};
