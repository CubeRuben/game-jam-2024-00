#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"

UCLASS()
class GAMEJAM2024_API UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	

	UPlayerHealthComponent();

protected:

	class APlayerVehicle* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCurveFloat* VelocityToDamageCurve;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnVehicleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

	void ApplyDamage(float DamageAmount);

};
