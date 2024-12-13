#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindAffected.h"
#include "Wind.generated.h"

UCLASS()
class GAMEJAM2024_API AWind : public AActor
{
	GENERATED_BODY()
	
public:	

	AWind();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<AActor*> OverlapWindAffected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HalfXBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HalfYBoundary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinTimerChangeVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxTimerChangeVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Timer;

	virtual void BeginPlay() override;

	void RandomizeVelocity();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	virtual void Tick(float DeltaTime) override;

};
