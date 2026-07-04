#pragma once

/*
     Simple class that displays to the user a weapons current
	 durability. Uses editor set colors for damage threshold
	 visibility etc.
*/



//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWeaponDurability.generated.h"



//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UTextBlock;
class UWeaponInstance;
class UWeaponDurabilityUIComponent;




UCLASS()
class DAYSIN_API UUIWeaponDurability : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;


	/* 
	                          UUIWeaponDurability components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> DurabilityText;



	/*
	                               Cache components.
	*/
	UPROPERTY()
	TObjectPtr<UWeaponInstance> WeaponInstance;



	/*
							       Custom components.
	*/
	UPROPERTY()
	TObjectPtr<UWeaponDurabilityUIComponent> WeaponDurabilityComponent;

public:


	/*
	                             Initialize functions.
	*/

	/*
	     Initializes this durability widget to read the passed instances
		 current durability when the calling widget is first constructed.

		 @param Instance: pointer to a weapon 
		 instance.
	*/
	void InitializeWeapon(TObjectPtr<UWeaponInstance>& Instance);
};