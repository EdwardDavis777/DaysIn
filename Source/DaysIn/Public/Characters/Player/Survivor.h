#pragma once

/*
     Defines player character defaults, for the main
	 survivor character controlled by the player.
*/

 
 
//Engine imports. 
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Survivor.generated.h" 





//Forward declares.
class UCameraComponent;
class UInputRegistryComponent;
class UPlayerInteractionComponent;
class UPlayerCollectionComponent;
class UUIPlayerMainComponent;
class UUIPlayerLayers;




UCLASS()
class DAYSIN_API ASurvivor : public ACharacter
{
	GENERATED_BODY()

private:
	ASurvivor();
   
	/*
	                                       ASurvivor Components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	USceneComponent* PiviotComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations|Camera", meta = (AllowPrivateAccess = true))
	FName CameraSocket = FName("headSocket");


	/*
	                                   ASurvivor custom components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|InputComponent", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputRegistryComponent> InputRegistryComponent;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Interaction", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerInteractionComponent> PlayerInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Interaction", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerCollectionComponent> PlayerCollectionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|UI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UUIPlayerMainComponent> UIPlayerMainComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|UI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UUIPlayerLayers> UIPlayerLayers;

public:
	
	/*
	                                       Engine overrides.
	*/
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
};