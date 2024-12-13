#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementComponent.generated.h"

UCLASS()
class GAMEJAM2024_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPlayerMovementComponent();

protected:

	class APlayerVehicle* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float TrailOffset;

	virtual void BeginPlay() override;

	void HandleInput(float DeltaTime);

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
