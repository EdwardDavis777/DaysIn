//Engine imports.
#include "Subsystems/Player/PlayerSubsystem.h"

//Component imports.
#include "Kismet/GameplayStatics.h"


//Other imports.
#include "Characters/Player/Survivor.h"
 
 
 
void UPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPlayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}



/*
                                            Accessors.
*/

ASurvivor* UPlayerSubsystem::GetPlayer() const
{
	auto* Player = Cast<ASurvivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return Player;
}

APlayerController* UPlayerSubsystem::GetPlayerController() const
{
	auto* Controller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	return Controller;
}