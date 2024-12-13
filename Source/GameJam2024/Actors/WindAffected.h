#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WindAffected.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class UWindAffected : public UInterface
{
	GENERATED_BODY()
};

class GAMEJAM2024_API IWindAffected
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyWindForce(FVector Force);
	virtual void ApplyWindForce_Implementation(FVector Force);
};
