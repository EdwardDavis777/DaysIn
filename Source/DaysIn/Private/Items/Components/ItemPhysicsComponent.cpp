//Engine imports.
#include "Items/Components/ItemPhysicsComponent.h"

//Other imports.
#include "Items/Data/ItemPhysicsProperties.h"



/*
							    Physics configuration functions.
*/

void UItemPhysicsComponent::ApplyCollisionButIgnorePawn(UStaticMeshComponent* StaticMesh)
{
	if (!StaticMesh) return;

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
}

void UItemPhysicsComponent::ApplyCollisionButIgnorePawn(USkeletalMeshComponent* SkeletalMesh)
{
	if (!SkeletalMesh) return;

	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
}

void UItemPhysicsComponent::ApplyCollisionAndPhysicsButIgnorePawn(UStaticMeshComponent* StaticMesh, const FItemPhysicsProps& PhysicsProps)
{
	if (!StaticMesh) return;

	ApplyCollisionButIgnorePawn(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetEnableGravity(true);
	StaticMesh->SetLinearDamping(PhysicsProps.LinearDamping);
	StaticMesh->SetAngularDamping(PhysicsProps.AngularDamping);
}

void UItemPhysicsComponent::ApplyCollisionAndPhysicsButIgnorePawn(USkeletalMeshComponent* SkeletalMesh, const FItemPhysicsProps& PhysicsProps)
{
	if (!SkeletalMesh) return;

	ApplyCollisionButIgnorePawn(SkeletalMesh);
	SkeletalMesh->SetAllBodiesSimulatePhysics(true);
	SkeletalMesh->SetEnableGravity(true);
	SkeletalMesh->SetLinearDamping(PhysicsProps.LinearDamping);
	SkeletalMesh->SetAngularDamping(PhysicsProps.AngularDamping);
}