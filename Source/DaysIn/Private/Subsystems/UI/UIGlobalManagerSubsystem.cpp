//Engine imports.
#include "Subsystems/UI/UIGlobalManagerSubsystem.h"

//Component imports.
#include "Blueprint/UserWidget.h"



void UUIGlobalManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIGlobalManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}


/*
										 Mutators.
*/

void UUIGlobalManagerSubsystem::SetManagedWidget(UUserWidget* Widget)
{
	if (!Widget || !bViewportCleared) return;
	
	Widget->SetVisibility(ESlateVisibility::Visible);
	ManagedWidget = Widget;
	bViewportCleared = false;
}

void UUIGlobalManagerSubsystem::ClearManagedWidget(UUserWidget* Widget)
{
	if (!Widget || Widget != ManagedWidget) return;

	Widget->SetVisibility(ESlateVisibility::Collapsed);
	ManagedWidget = nullptr;
	bViewportCleared = true;
}


/*
										 Accessors.
*/

const UUserWidget* UUIGlobalManagerSubsystem::GetManagedWidget() const
{
	return ManagedWidget.Get();
}

const bool& UUIGlobalManagerSubsystem::bIsViewportCleared() const
{
	return bViewportCleared;
}