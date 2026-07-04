#pragma once

/*

      Holds all player UI equipment slots; added directly into the player characters
	  UI main widget instance in the UMG.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIPlayerEquipmentMain.generated.h"



//Forward declares.
class USizeBox;
class UCanvasPanel;
class UBorder;




UCLASS()
class DAYSIN_API UUIPlayerEquipmentMain : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;


	/*
	                             UUIPlayerEquipmentMain components.
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;

public:

	/*
	                                       Accessors.
	*/
	UCanvasPanel* GetGroupPanel();
};