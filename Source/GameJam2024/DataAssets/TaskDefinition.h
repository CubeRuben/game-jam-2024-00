#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TaskStep.h"
#include "TaskDefinition.generated.h"

UENUM(BlueprintType)
enum class ETaskMod : uint8 
{
	None,
	RandomShaking,
	Timer,
	Heavy
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveFloat* HPToMoney;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETaskMod Modification;

public:

	const FString& GetName() const { return Name; }
	const FString& GetDescription() const { return Description; }
	const TArray<FTaskStep>& GetTriggersToVisit() const { return TriggersToVisit; }
	UCurveFloat* const & GetHPToMoney() const { return HPToMoney; }
	const ETaskMod& GetTaskModification() const { return Modification; }

	
};
