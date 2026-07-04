//Engine imports.
#include "UI/Player/Components/UIPlayerMainComponent.h"


//Widget imports.
#include "UI/Player/UIPlayerMain.h"

 
//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"


//Subsystem imports.
#include "Subsystems/UI/UIGlobalManagerSubsystem.h"
#include "Subsystems/Player/PlayerUISubsystem.h"
#include "Subsystems/Player/PlayerSubsystem.h"



void UUIPlayerMainComponent::BeginPlay()
{
	Super::BeginPlay();


	UIGlobalManagerSubsystem = SubUtility::FindSub<UUIGlobalManagerSubsystem>(GetWorld());
	PlayerUISubsystem = SubUtility::FindSub<UPlayerUISubsystem>(GetWorld());
	PlayerSubsystem = SubUtility::FindSub<UPlayerSubsystem>(GetWorld());

	if (UIGlobalManagerSubsystem && PlayerUISubsystem && PlayerSubsystem)
	{
		MakeUIMain();
		BindDelegates();
	}
}

void UUIPlayerMainComponent::BindDelegates()
{
	if (!PlayerUISubsystem) return;
	PlayerUISubsystem->PlayerUISubsystemDispatches.ToggleUIMain.AddUObject(this, &UUIPlayerMainComponent::ToggleUIMain);
}



/*
									Widget construction functions.
*/

void UUIPlayerMainComponent::MakeUIMain()
{
	if (!UIMainClass || !PlayerUISubsystem) return;

	if (UIMain = CreateWidget<UUIPlayerMain>(GetWorld(), UIMainClass))
	{
		UIMain->FinishConstruction(PlayerSubsystem->GetPlayerController());
	} 
}


/*
									 Toggle UI main event functions.
*/

void UUIPlayerMainComponent::ToggleUIMain()
{
	if (!UIMain || !UIGlobalManagerSubsystem) return;

	if (!UIMain->bIsVisible() && UIGlobalManagerSubsystem->bIsViewportCleared())
	{
		UIGlobalManagerSubsystem->SetManagedWidget(UIMain);
		PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainInRender.Broadcast();
		UIMain->AddCursorInput();
	}
	else
	{
		UIGlobalManagerSubsystem->ClearManagedWidget(UIMain);
		PlayerUISubsystem->PlayerUISubsystemDispatches.UIMainOutRender.Broadcast();
		UIMain->RemoveCursorInput();
	}
}