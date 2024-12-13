#pragma once

#include "TaskStep.generated.h"

USTRUCT(BlueprintType)
struct GAMEJAM2024_API FTaskStep
{
	GENERATED_BODY()

public:

	FTaskStep();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Desctiption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TriggerName;
};
