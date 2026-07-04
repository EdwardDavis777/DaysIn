#pragma once


/*

	 Defines class defaults for all weapon objects that can be found
	 in the world.

*/
  



//Engine imports. 
#include "CoreMinimal.h"
#include "Items/Abstracts/ItemBase.h"
#include "WeaponBase.generated.h"
 


//Forward declares.
class UWeaponInstance;
class UWeaponDataAsset;



UCLASS()
class DAYSIN_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()
	
private:
	AWeaponBase();
 
	/*
	                                     AWeaponBase components.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;


	/*
	                                     AWeaponBase data components.
	*/
	UPROPERTY()
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;

	UPROPERTY()
	TObjectPtr<UWeaponInstance> WeaponInstance;
public:

	/*
							              Interface event functions.
	*/

	virtual void Pickup() override;
	virtual void Drop(UItemInstance* Instance) override;


	/*
	                                         Engine overrides.
	*/
	virtual void PostInitializeComponents() override;
};