//Engine imports.
#include "UI/Player/UIRegionPanel.h"

//Component imports.
#include "Components/SizeBox.h"



void UUIRegionPanel::NativeConstruct()
{
	Super::NativeConstruct();
} 



/*
									Log methods.
*/

int32 UUIRegionPanel::LogRegionChildren(double logTime)
{
#if WITH_EDITOR

	if (!RootSizeBox) return 0;
	TArray<UWidget*> Children = RootSizeBox->GetAllChildren();
	int32 ChildCount = Children.Num();

	FString log = FString::Printf(TEXT("Region count: %i"), ChildCount);
	GEngine->AddOnScreenDebugMessage(-1, logTime, FColor::Purple, log);
	return ChildCount;
#endif
	return 0;
}



/*
									 Mutators.
*/

void UUIRegionPanel::RemoveChildFromRegion(UUserWidget* WidgetToRemove)
{
	if (!WidgetToRemove || !RootSizeBox) return;

	TArray<UWidget*> Children = RootSizeBox->GetAllChildren();
	if (Children.Contains(WidgetToRemove)) { Children.Remove(WidgetToRemove); RootSizeBox->RemoveChild(WidgetToRemove); }
}


/*
									Accessors.
*/

UWidget* UUIRegionPanel::GetChild()
{
	if (!RootSizeBox) return nullptr;

	TArray<UWidget*> Children = RootSizeBox->GetAllChildren();
	return Children[0];
}

USizeBox* UUIRegionPanel::GetSizeBox()
{
	return RootSizeBox.Get();
}