#include "PlayerHealthComponent.h"

#include "../PlayerVehicle.h"
#include "PlayerTaskComponent.h"

UPlayerHealthComponent::UPlayerHealthComponent()
{
	HealthPoints = 100.0f;
	VelocityToDamageCurve = nullptr;
}

void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerVehicle>(GetOwner());

	if (!PlayerPawn)
		DestroyComponent();

	PlayerPawn->GetMesh()->OnComponentHit.AddDynamic(this, &UPlayerHealthComponent::OnVehicleHit);
}

void UPlayerHealthComponent::OnVehicleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HitComponent || !VelocityToDamageCurve)
		return;

	const float velocity = (NormalImpulse / HitComponent->GetMass()).Length();
	const float damageAmount = VelocityToDamageCurve->GetFloatValue(velocity);
	ApplyDamage(damageAmount);
}

void UPlayerHealthComponent::ApplyDamage(float DamageAmount)
{
	if (!PlayerPawn->GetPlayerTaskComponent()->GetCurrentTask())
		return;

	HealthPoints = FMath::Clamp(HealthPoints - DamageAmount, 0.0f, 100.0f);
}
