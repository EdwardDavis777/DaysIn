//Engine imports.
#include "UI/Items/SimpleStats/Components/WeaponDurabilityUIComponent.h"


//Component imports.
#include "Components/TextBlock.h"


//Widget imports.
#include "UI/Items/SimpleStats/UIWeaponDurability.h"


//Data imports.
#include "StaticData/Items/Weapon/WeaponDamageThresholds.h"



void UWeaponDurabilityUIComponent::Initialize(UWorld* WorldContext, UUserWidget* OwnerWidget)
{
	Super::Initialize(WorldContext, OwnerWidget);
	WeaponDurability = FindOwner<UUIWeaponDurability>();
}




/*
									   Event functions.
*/

void UWeaponDurabilityUIComponent::CalcualteDurability(const float& Durability, TObjectPtr<UTextBlock>& TextBlock)
{
	if (!TextBlock) return;
	
	TextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.0f%%"), Durability)));
	if (Durability >= Thresholds::Num::Full)
	{
		TextBlock->SetColorAndOpacity(Thresholds::Color::FullColor);
	}
	else if (Durability <= Thresholds::Num::Medium)
	{
		TextBlock->SetColorAndOpacity(Thresholds::Color::LowColor);
	}
	else if (Durability <= Thresholds::Num::Low)
	{
		TextBlock->SetColorAndOpacity(Thresholds::Color::LowColor);
	}
}