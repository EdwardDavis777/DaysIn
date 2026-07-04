//Engine imports.
#include "Input/Abstracts/InputStreamBaseComponent.h"


//Component imports.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h"

//Subsystem imports.
#include "Subsystems/Player/PlayerSubsystem.h"


UInputStreamBaseComponent::UInputStreamBaseComponent()
{
}


void UInputStreamBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerSubsystem = SubUtility::FindSub<UPlayerSubsystem>(GetWorld()))
	{
		Player = PlayerSubsystem->GetPlayer();
	}
}



/*
									  Input stream functions.
*/

void UInputStreamBaseComponent::CreateInputStream(UInputComponent* InputComponent, APlayerController* PlayerController)
{
	if (!InputComponent || !PlayerController) return;

	EnhancedContext = Cast<UEnhancedInputComponent>(InputComponent);
	ControllerContext = PlayerController;
}




/*
										Enhanced input methods.
*/

void UInputStreamBaseComponent::AddMappingContext(UInputMappingContext* MappingContext, APlayerController* PlayerController, uint32_t InputPrio)
{
	if (!MappingContext || !PlayerController) return;

	auto* LP = PlayerController->GetLocalPlayer();
	if (LP)
	{
		auto* System = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (System)
		{
			System->AddMappingContext(MappingContext, InputPrio);
		}
	}
}