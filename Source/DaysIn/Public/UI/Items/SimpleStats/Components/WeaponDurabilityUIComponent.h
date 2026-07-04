#pragma once

/*
      Defines methods for a weapon durability widget instance.
*/




//Engine imports.
#include "CoreMinimal.h"
#include "CustomClasses/Components/NativeUIComponent.h"
#include "WeaponDurabilityUIComponent.generated.h"


//Forward declares.
class UUIWeaponDurability;
class UTextBlock;



UCLASS()
class DAYSIN_API UWeaponDurabilityUIComponent : public UNativeUIComponent
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget) override;



	/*
	                                  Event functions.
	*/

	/*
	    Calculates a durability text block description using the passed durability,
		will set the text block to the current durability, with a color that reflects
		its threshold.

		@param Durability: reference to the current weapons
		durability.

		@param TextBlock: pointer to a text block you wish
		to set.
	*/
	void CalcualteDurability(const float& Durability, TObjectPtr<UTextBlock>& TextBlock);


private:
	/*
	                       UWeaponDurabilityUIComponent components.
	*/
	UPROPERTY()
	TObjectPtr<UUIWeaponDurability> WeaponDurability;
};