//Engine imports.
#include "Characters/Player/Survivor.h"


//Component imports.
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
 
  
//Custom component imports.
#include "Input/Abstracts/InputRegistryComponent.h"
#include "Interaction/Player/Component/PlayerInteractionComponent.h"
#include "Interaction/Player/Component/PlayerCollectionComponent.h"
#include "UI/Player/Components/UIPlayerMainComponent.h"



ASurvivor::ASurvivor()
{
	PiviotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PiviotComponent"));
	PiviotComponent->SetupAttachment(RootComponent);

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMeshComponent"));
	PlayerMesh->SetupAttachment(PiviotComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCameraComponent"));
	PlayerCamera->SetupAttachment(PlayerMesh, CameraSocket);


	InputRegistryComponent = CreateDefaultSubobject<UInputRegistryComponent>(TEXT("InputRegistryComponent"));
	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("PlayerInteractionComponent"));
	PlayerCollectionComponent = CreateDefaultSubobject<UPlayerCollectionComponent>(TEXT("PlayerCollectionComponent"));
	UIPlayerMainComponent = CreateDefaultSubobject<UUIPlayerMainComponent>(TEXT("UIPlayerMainComponent"));
}


void ASurvivor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputRegistryComponent) return;
	if (auto* PlayerCont = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		InputRegistryComponent->RegisterInput(PlayerInputComponent, PlayerCont);
	}
}

void ASurvivor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PlayerInteractionComponent)
	{
		PlayerInteractionComponent->RegisterOverlapEvents(GetCapsuleComponent());
	}
}