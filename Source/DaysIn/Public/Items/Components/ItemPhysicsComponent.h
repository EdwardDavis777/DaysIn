#pragma once

/*
      Defines functions for item physics releated events,
	  provides mutliple over-loaded methods for both static 
	  and skeletal meshes.
*/


//Engine imports.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemPhysicsComponent.generated.h"



//Forward declares.
struct FItemPhysicsProps;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAYSIN_API UItemPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	/*
	                          Physics configuration functions.
	*/

	/*
	     Applies full collision to items, but makes them ignore the player 
		 character.

		 @param StaticMesh: pointer to a static mesh you wish to 
		 apply collision to.
	*/
	void ApplyCollisionButIgnorePawn(UStaticMeshComponent* StaticMesh);


	/*
		 Applies full collision to items, but makes them ignore the player
		 character.

		 @param SkeletalMesh: pointer to a skeletal mesh  you wish to
		 apply collision to.
	*/
	void ApplyCollisionButIgnorePawn(USkeletalMeshComponent* SkeletalMesh); 
    

	/*
		 Applies full collision and physics/gravity to items, but makes
		 them ignore the player character.

		 @param StaticMesh: pointer to a static mesh you wish to 
		 apply physics and collision to.

		 @param PhysicsProps: item physics properties.
	*/
	void ApplyCollisionAndPhysicsButIgnorePawn(UStaticMeshComponent* StaticMesh,const FItemPhysicsProps& PhysicsProps);



	/*
		 Applies full collision and physics/gravity to items, but makes 
		 them ignore the player character.

		 @param SkeletalMesh: pointer to a skeletal mesh  you wish to
		 apply physics and collision to.

		 @param PhysicsProps: item physics properties.
	*/
	void ApplyCollisionAndPhysicsButIgnorePawn(USkeletalMeshComponent* SkeletalMesh, const FItemPhysicsProps& PhysicsProps);
};