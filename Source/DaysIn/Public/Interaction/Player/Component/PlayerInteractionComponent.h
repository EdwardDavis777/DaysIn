#pragma once


/* 
      Handles detecting player overlap events with item instances
	  in the world.

	  Note: add the component to a player class, then call the initialize 
	  overlap events function to use the component.

*/



//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"



//Forward declares.
class UCapsuleComponent;
class UPlayerSubsystem;
class ASurvivor;
class AItemBase;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAYSIN_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/*
	                                 Register event functions.
	*/

	/*
	     Registers a player capsule component for overlap and end overlap 
		 events for this component.

		 @param PlayerCapsule: pointer to the player capsule you
		 wish to detected overlap/end overlap events.
	*/
	void RegisterOverlapEvents(UCapsuleComponent* PlayerCapsule);

	/*
	     Binds class functions to global delegates/dispatches
		 that are defined.
	*/
	void BindDelegates();

private:

	/*
	                                    Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UPlayerSubsystem> PlayerSubsystem;

	UPROPERTY()
	TObjectPtr<ASurvivor> Player;

	UPROPERTY(VisibleAnywhere, Category = "Data| Memory", meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<AItemBase>> OverlappedItems;



	/*
	                                Overlap event functions.
	*/


	/*
	       Detects if a player character collision capsule has had some sort of 
		   overlap event with an actor in the world.
	*/
	UFUNCTION()
	void OnPlayerCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	/*
	      Detects if the player character collision capsule has had some sort of 
		  end overlap event with an actor in the world.
	*/
	UFUNCTION()
	void OnPlayerCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);


	/*
	    Delegated function; binded to the try pick-up dispatch in the 
		player subsytem; will simply parse all items the player is currently 
		overlapping and broadcast to listeners an address to the nearst 
		item.
	*/
	void HandleOverlappedItems();



	/*
	                                   Engine overrides.
	*/
	virtual void BeginPlay() override;
};