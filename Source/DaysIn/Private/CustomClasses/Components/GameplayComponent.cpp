//Engine imports.
#include "CustomClasses/Components/GameplayComponent.h"




void UGameplayComponent::Initialize(UWorld* WorldContext, UObject* OwnerObject)
{
	if (!WorldContext || !OwnerObject) return;
	World = WorldContext;
	Owner = OwnerObject;
}


