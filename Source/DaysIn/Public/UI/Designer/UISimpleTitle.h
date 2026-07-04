#pragma once

/*

     Simple title widget, legit just provides a border, canvas and a text block,
	 used for very simple titles for other UI widgets. Implements no UI input
	 or logic.

*/


//Engine imports.
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UISimpleTitle.generated.h"




//Forward declares.
class USizeBox;
class UBorder;
class UCanvasPanel;
class UBackgroundBlur;
class UTextBlock;




UCLASS()
class DAYSIN_API UUISimpleTitle : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

	/*
	                             UUISimpleTitle components.   
	*/
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<USizeBox> RootSizeBox;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBorder> MainBorder;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UCanvasPanel> GroupPanel;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UBackgroundBlur> BackgroundBlur;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Title;
};