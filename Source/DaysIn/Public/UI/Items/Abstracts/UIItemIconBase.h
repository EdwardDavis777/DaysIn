#pragma once

/*
     Defines class defaults for draggable item icons
	 that are used for user interfaces.
*/



//Engine imports.
#include "CoreMinimal.h"
#include "UI/Interactables/Abstracts/UIDraggableBase.h"
#include "UIItemIconBase.generated.h"



//Forward declares.
class UTextBlock;



UCLASS(Abstract)
class DAYSIN_API UUIItemIconBase : public UUIDraggableBase
{
	GENERATED_BODY()
   
protected:
	   
	/*
	                       UUIItemIconBase components.
	*/
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

public:


	/*
	                      Virtual construction functions.
	*/
	virtual void Init(UItemInstance* Instance) override;
	virtual void Init(AItemBase* RawItem) override;
};