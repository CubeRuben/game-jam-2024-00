#include "PlayerTaskComponent.h"

#include "PlayerHealthComponent.h"
#include "../PlayerVehicle.h"
#include "../../DataAssets/TaskDefinition.h"
#include "../../Actors/TaskTrigger.h"

#include <ChaosVehicleMovementComponent.h>

UPlayerTaskComponent::UPlayerTaskComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentTask = nullptr;
	CurrentTaskStepIndex = 0;
	TriggerToVisit = nullptr;

	ShakeChance = 0.015f;
	ShakeStrength = 75000.0f;
	HeavyOffset = -25.0f;
}

void UPlayerTaskComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerVehicle>(GetOwner());

	if (!PlayerPawn)
		DestroyComponent();
}

void UPlayerTaskComponent::OnTaskFinished()
{
	const UCurveFloat* hpCurve = CurrentTask->GetHPToMoney();
	if (hpCurve)
		PlayerPawn->AddMoney(hpCurve->GetFloatValue(PlayerPawn->GetPlayerHealthComponent()->GetHealthPoints()));

	Modification_OnFinish();
	OnTaskFinish.Broadcast();

	AssignTask(nullptr);

	PlayerPawn->GetPlayerHealthComponent()->ResetHealthPoints();
}

void UPlayerTaskComponent::Modification_OnStart()
{
	if (!CurrentTask)
		return;

	if (CurrentTask->GetTaskModification() == ETaskMod::Heavy)
	{
		PlayerPawn->GetVehicleMovementComponent()->CenterOfMassOverride.Z += HeavyOffset;
	}
}

void UPlayerTaskComponent::Modification_OnTick(float DeltaTime)
{
	if (!CurrentTask || CurrentTaskStepIndex == 0)
		return;

	if (CurrentTask->GetTaskModification() == ETaskMod::RandomShaking) 
	{
		const float roll = FMath::RandRange(0.0f, 1.0f);
		const bool doShake = ShakeChance >= roll;

		if (!doShake)
			return;

		FVector shakeVector = PlayerPawn->GetActorRightVector();

		if (FMath::RandBool())
			shakeVector = -shakeVector;

		PlayerPawn->GetMesh()->AddImpulse(shakeVector * ShakeStrength);
	}
}

void UPlayerTaskComponent::Modification_OnFinish()
{
	if (CurrentTask->GetTaskModification() == ETaskMod::Heavy)
	{
		PlayerPawn->GetVehicleMovementComponent()->CenterOfMassOverride.Z -= HeavyOffset;
	}
}

bool UPlayerTaskComponent::CanDamage()
{
	return CurrentTask && CurrentTaskStepIndex != 0;
}

void UPlayerTaskComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Modification_OnTick(DeltaTime);

}

void UPlayerTaskComponent::AssignTask(UTaskDefinition* TaskDefinition)
{
	OnTaskFinish.Broadcast();

	CurrentTask = TaskDefinition;
	CurrentTaskStepIndex = 0;
	TriggerToVisit = nullptr;

	if (!CurrentTask)
		return;

	if (!CurrentTask->GetTriggersToVisit().IsValidIndex(CurrentTaskStepIndex))
	{
		CurrentTask = nullptr;
		return;
	}

	const FString& triggerName = CurrentTask->GetTriggersToVisit()[CurrentTaskStepIndex].TriggerName;
	ATaskTrigger* const * taskTrigger = ATaskTrigger::GetTaskTriggers().Find(triggerName);
	
	if (!taskTrigger)
		return;

	TriggerToVisit = *taskTrigger;
	TriggerToVisit->ActivateTrigger();
	OnTaskAssign.Broadcast(CurrentTask);
}

void UPlayerTaskComponent::VisitedTrigger(ATaskTrigger* TaskTrigger)
{
	if (!TaskTrigger)
		return;

	if (TaskTrigger != TriggerToVisit) 
		return;

	OnTaskStepFinish.Broadcast(CurrentTaskStepIndex);
	TriggerToVisit->DeactivateTrigger();
	CurrentTaskStepIndex += 1;

	if (CurrentTaskStepIndex == 1)
		Modification_OnStart();

	if (!CurrentTask->GetTriggersToVisit().IsValidIndex(CurrentTaskStepIndex))
	{
		OnTaskFinished();
		return;
	}

	const FString& triggerName = CurrentTask->GetTriggersToVisit()[CurrentTaskStepIndex].TriggerName;
	ATaskTrigger* const* taskTrigger = ATaskTrigger::GetTaskTriggers().Find(triggerName);

	if (!taskTrigger) 
	{
		OnTaskFinished();
		return;
	}

	TriggerToVisit = *taskTrigger;
	TriggerToVisit->ActivateTrigger();
}

#if WITH_EDITOR
void UPlayerTaskComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName propertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (propertyName == GET_MEMBER_NAME_CHECKED(UPlayerTaskComponent, CurrentTask))
	{
		AssignTask(CurrentTask);
	}
}
#endif