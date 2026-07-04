//Engine imports.
#include "Input/Abstracts/InputRegistryComponent.h"

//Custom component imports.
#include "Input/PlayerMovementInput.h"
#include "Input/PlayerInteractInput.h"
#include "Input/PlayerUIInput.h"
#include "Input/PlayerSaveInput.h"


 
UInputRegistryComponent::UInputRegistryComponent() 
{ 
	PlayerMovementInput = CreateDefaultSubobject<UPlayerMovementInput>(TEXT("PlayerMovementInputComponent"));
	PlayerInteractInput = CreateDefaultSubobject<UPlayerInteractInput>(TEXT("PlayerInteractInputComponent"));
	PlayerUIInput = CreateDefaultSubobject<UPlayerUIInput>(TEXT("PlayerUIInputComponent"));
	PlayerSaveInput = CreateDefaultSubobject<UPlayerSaveInput>(TEXT("PlayerSaveInputComponent"));
}





/*
									   Registry event functions.
*/

void UInputRegistryComponent::RegisterInput(UInputComponent* InputComponent, APlayerController* ControllerContext)
{
	if (!InputComponent || !ControllerContext) return;

	TSet<UActorComponent*> InputStreams = GetOwner()->GetComponents();
	for (auto& Stream : InputStreams)
	{
		if (auto* StreamComponent = Cast<UInputStreamBaseComponent>(Stream))
		{
			StreamComponent->CreateInputStream(InputComponent, ControllerContext);
		}
	}
	InputStreams.Empty();
}