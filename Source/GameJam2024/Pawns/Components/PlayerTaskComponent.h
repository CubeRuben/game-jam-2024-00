#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../DataAssets/TaskStep.h"
#include "PlayerTaskComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskAssignDelegate, class UTaskDefinition*, TaskDefinition);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTaskStepFinishDelegate, int, FinishStepIndex);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskFinishDelegate);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaskCargoTakenDelegate);


UCLASS(BlueprintType)
class GAMEJAM2024_API UPlayerTaskComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPlayerTaskComponent();

protected:

	class APlayerVehicle* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTaskDefinition* CurrentTask;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentTaskStepIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ATaskTrigger* TriggerToVisit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ShakeChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ShakeStrength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HeavyOffset;

	UPROPERTY(BlueprintAssignable)
	FOnTaskAssignDelegate OnTaskAssign;

	UPROPERTY(BlueprintAssignable)
	FOnTaskStepFinishDelegate OnTaskStepFinish;

	UPROPERTY(BlueprintAssignable)
	FOnTaskCargoTakenDelegate OnTaskTargoTaken;

	UPROPERTY(BlueprintAssignable)
	FOnTaskFinishDelegate OnTaskFinish;

	virtual void BeginPlay() override;

	void OnTaskFinished();

	void Modification_OnStart();
	void Modification_OnTick(float DeltaTime);
	void Modification_OnFinish();

public:	

	bool CanDamage();

	class UTaskDefinition* GetCurrentTask() const { return CurrentTask; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AssignTask(class UTaskDefinition* TaskDefinition);

	UFUNCTION()
	void VisitedTrigger(class ATaskTrigger* TaskTrigger);

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
