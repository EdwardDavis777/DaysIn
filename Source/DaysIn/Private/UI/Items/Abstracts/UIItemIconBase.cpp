//Engine imports.
#include "UI/Items/Abstracts/UIItemIconBase.h"


//Component imports.
#include "Components/TextBlock.h"


//Other imports.
#include "Items/Abstracts/ItemInstance.h"
#include "Items/Abstracts/ItemBase.h"



void UUIItemIconBase::Init(UItemInstance* Instance)
{
	Super::Init(Instance);
	ItemName->SetText(Instance->GetUIName());
}

void UUIItemIconBase::Init(AItemBase* RawItem)
{
	Super::Init(RawItem);
	ItemName->SetText(RawItem->Instance()->GetUIName());
}