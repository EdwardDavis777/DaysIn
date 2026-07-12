#pragma once

/*

      Handles the construction of UI layers that are dependent on 
	  player life-time.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIPlayerLayers.generated.h"


//Forward declares.
class UUIDragLayer;
class UUISubsystem;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DAYSIN_API UUIPlayerLayers : public UActorComponent
{
	GENERATED_BODY()

private:

    /*
	                              PlayerLayer components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Layers", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUIDragLayer> DragLayerClass;


	/*
	                           PlayerLayer cache components.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<APlayerController> OwnerController;
   
	UPROPERTY(VisibleAnywhere, Category = "Data|Memory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UUIDragLayer> DragLayer;

	UPROPERTY()
	TObjectPtr<UUISubsystem> UISubsystem;




    /*
	                             UI layer event functions.
	*/

	/*
	       Simply starts the construction of a drag layer.
	*/
	void ConstructDragLayer();
    


   /*
                                    Engine overrides.
   */
   virtual void BeginPlay() override;
};