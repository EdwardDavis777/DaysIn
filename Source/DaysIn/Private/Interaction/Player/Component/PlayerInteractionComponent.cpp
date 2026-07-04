//Engine imports.
#include "Interaction/Player/Component/PlayerInteractionComponent.h"

//Component imports.
#include "Components/CapsuleComponent.h"


//Other imports.
#include "Items/Abstracts/ItemBase.h"


//Utility imports.
#include "SubsystemUtilitys/SubsystemUtility.h" 
#include "Interaction/Player/InteractionUtility/PlayerInteractionUtility.h"



//Subsystem imports.
#include "Subsystems/Player/PlayerSubsystem.h"




void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (PlayerSubsystem = SubUtility::FindSub<UPlayerSubsystem>(GetWorld()))
	{
		Player = PlayerSubsystem->GetPlayer();
		BindDelegates();
	}
}

void UPlayerInteractionComponent::BindDelegates()
{
	if (!PlayerSubsystem) return;
	PlayerSubsystem->PlayerSubsystemDispatch.TryPickupItem.AddUObject(this, &UPlayerInteractionComponent::HandleOverlappedItems);
}



/*
								        Register event functions.
*/

void UPlayerInteractionComponent::RegisterOverlapEvents(UCapsuleComponent* PlayerCapsule)
{
	if (!PlayerCapsule) return;

	PlayerCapsule->OnComponentBeginOverlap.RemoveDynamic(this, &UPlayerInteractionComponent::OnPlayerCapsuleBeginOverlap);
	PlayerCapsule->OnComponentEndOverlap.RemoveDynamic(this, &UPlayerInteractionComponent::OnPlayerCapsuleEndOverlap);

	PlayerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractionComponent::OnPlayerCapsuleBeginOverlap);
	PlayerCapsule->OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractionComponent::OnPlayerCapsuleEndOverlap);
}





/*
									      Overlap event functions.
*/

void UPlayerInteractionComponent::OnPlayerCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	
	if (auto* Overlapped = Cast<AItemBase>(OtherActor))
	{
		if(!OverlappedItems.Contains(Overlapped))
		{ 
		    OverlappedItems.Emplace(TObjectPtr<AItemBase>(Overlapped));
		}
	}
}

void UPlayerInteractionComponent::OnPlayerCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	if (auto* EndOverlapped = Cast<AItemBase>(OtherActor))
	{
		if (OverlappedItems.Contains(EndOverlapped))
		{
			OverlappedItems.Remove(EndOverlapped);
		}
	}
}


void UPlayerInteractionComponent::HandleOverlappedItems()
{
	if (!PlayerSubsystem || !Player || OverlappedItems.IsEmpty()) return;

	if (auto* Nearest = Interact::FindNearest(OverlappedItems, Player))
	{
		PlayerSubsystem->PlayerSubsystemDispatch.PickupItem.Broadcast(Nearest);
	}
}