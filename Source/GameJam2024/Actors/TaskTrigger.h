#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskTrigger.generated.h"

UCLASS()
class GAMEJAM2024_API ATaskTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	ATaskTrigger();

protected:

	static TMap<FString, ATaskTrigger*> TaskTriggers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MarkerMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TriggerName;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	static const TMap<FString, ATaskTrigger*>& GetTaskTriggers() { return TaskTriggers; }

	virtual void Tick(float DeltaTime) override;

	void ActivateTrigger();
	void DeactivateTrigger();

};
