#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerHealthComponent.generated.h"

UCLASS()
class GAMEJAM2024_API APlayerHealthComponent : public AActor
{
	GENERATED_BODY()
	
public:	

	APlayerHealthComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
