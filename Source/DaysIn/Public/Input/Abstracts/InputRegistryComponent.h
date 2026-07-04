#pragma once

 
/*
	Simply opens input streams to the player for linked input components on this class.
	Allows each one to implement their own input event functions. While allowing
	input streams to be cleaner/leaner.

	If you wish to implement a new input method, derive it from the player input stream
	base component, and simply define the component in this class's component list. At bein play
	the input stream will open, and it will be valid assuming all virtual functions
	are implemented properly.
*/  




//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputRegistryComponent.generated.h"



//Forward declares.
class UPlayerMovementInput;
class UPlayerInteractInput;
class UPlayerUIInput;
class UPlayerSaveInput;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DAYSIN_API UInputRegistryComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UInputRegistryComponent();


	/*
	                            UInputRegistryComponent components.
	*/ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom| Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerMovementInput> PlayerMovementInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom| Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerInteractInput> PlayerInteractInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom| Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerUIInput> PlayerUIInput;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom| Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerSaveInput> PlayerSaveInput;

public:
    
	/*
	                                Registry event functions.
	*/

	/*
	     Registers the player controller for input streams from other
		 input components on (this) component.

		 @param InputComponent: pointer to the current input component
		 context.

		 @param ControllerContext: pointer to the current player controller
		 context.
	*/
	void RegisterInput(UInputComponent* InputComponent, APlayerController* ControllerContext);
};