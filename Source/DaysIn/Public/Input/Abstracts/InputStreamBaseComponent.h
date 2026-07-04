#pragma once


/*
	Defines default enhanced input methods, such as context mapping methods
	for sub-classes, and input context registry methods.

	Also allows sub-classes to create input streams by setting the player
	controller context, along with initalizing input component context.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputStreamBaseComponent.generated.h"


//Forward declares.
class UEnhancedInputComponent;
class UInputMappingContext;

class UPlayerSubsystem;
class ASurvivor;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAYSIN_API UInputStreamBaseComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UInputStreamBaseComponent();

	/*
	                            UInputStreamBaseComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedContext;
    
	UPROPERTY()
	TObjectPtr<APlayerController> ControllerContext;

	UPROPERTY()
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

	UPROPERTY()
	TObjectPtr<ASurvivor> Player;
public:

	/*
	                                   Input stream functions.
	*/


	/*
		 Initalizes an enhanced input component with the current player
		 input context, and initalizes the player controller context.

		 @param InputComponent: address to the current players input component
		 context.

		 @param PlayerController: address to the player character controller
		 context.
	*/
	virtual void CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController);



	/*
										Enhanced input methods.
	*/


	/*
		Creates a mapping context on the passed controller context.

		@param MappingContext: address to the mapping context asset.

		@param PlayerController: address to the current controller
		context.

		@param InputPrio: priority of the input
		mapping. Defaulted to the lowest (0).
	*/
	void AddMappingContext(UInputMappingContext* MappingContext, APlayerController* PlayerController, uint32_t InputPrio = 0);

	/* 
	                                        Engine imports.
	*/
	virtual void BeginPlay() override;
};
