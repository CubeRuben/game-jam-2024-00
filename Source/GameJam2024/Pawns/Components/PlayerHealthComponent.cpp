#include "PlayerHealthComponent.h"

APlayerHealthComponent::APlayerHealthComponent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerHealthComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

