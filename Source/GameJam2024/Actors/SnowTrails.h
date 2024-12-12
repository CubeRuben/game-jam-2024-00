#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnowTrails.generated.h"

USTRUCT(BlueprintType)
struct GAMEJAM2024_API FSnowTrailData 
{
	GENERATED_BODY();

public: 

	FSnowTrailData();
	FSnowTrailData(UStaticMeshComponent* NewTrailMeshComponent, float NewDeathWorldTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> TrailMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeathWorldTime;
};

UCLASS()
class GAMEJAM2024_API ASnowTrails : public AActor
{
	GENERATED_BODY()
	
public:	

	ASnowTrails();

protected:

	static ASnowTrails* Instance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TrailLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	URuntimeVirtualTexture* RVTToRender;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* TrailMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* TrailMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSnowTrailData> TrailsComponents;

	int TrailCounter;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	

	static ASnowTrails* GetInstance() { return Instance; }

	virtual void Tick(float DeltaTime) override;

	void AddSnowTrail(const FVector& Location, float YawRotation);
};
