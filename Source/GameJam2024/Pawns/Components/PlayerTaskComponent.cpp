#include "PlayerTaskComponent.h"

#include "../PlayerVehicle.h"
#include "../../DataAssets/TaskDefinition.h"
#include "../../Actors/TaskTrigger.h"

UPlayerTaskComponent::UPlayerTaskComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentTask = nullptr;
	CurrentTaskStepIndex = 0;
	TriggerToVisit = nullptr;
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Task finished");
}

void UPlayerTaskComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerTaskComponent::AssignTask(UTaskDefinition* TaskDefinition)
{
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
}

void UPlayerTaskComponent::VisitedTrigger(ATaskTrigger* TaskTrigger)
{
	if (!TaskTrigger)
		return;

	if (TaskTrigger != TriggerToVisit) 
		return;

	TriggerToVisit->DeactivateTrigger();
	CurrentTaskStepIndex += 1;

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