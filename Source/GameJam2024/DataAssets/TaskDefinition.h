#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TaskStep.h"
#include "TaskDefinition.generated.h"

UCLASS()
class GAMEJAM2024_API UTaskDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UTaskDefinition();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTaskStep> TriggersToVisit;

public:

	const FString& GetName() const { return Name; }
	const FString& GetDescription() const { return Description; }
	const TArray<FTaskStep>& GetTriggersToVisit() const { return TriggersToVisit; }

	
};
