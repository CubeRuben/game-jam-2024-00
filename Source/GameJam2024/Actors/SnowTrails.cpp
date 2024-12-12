#include "SnowTrails.h"

FSnowTrailData::FSnowTrailData()
{
	TrailMeshComponent = nullptr;
	DeathWorldTime = 0.0f;
}

FSnowTrailData::FSnowTrailData(UStaticMeshComponent* NewTrailMeshComponent, float NewDeathWorldTime)
{
	TrailMeshComponent = NewTrailMeshComponent;
	DeathWorldTime = NewDeathWorldTime;
}

ASnowTrails* ASnowTrails::Instance = nullptr;

ASnowTrails::ASnowTrails()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	TrailLifeTime = 5.0f;
	RVTToRender = nullptr;
	TrailMesh = nullptr;
	TrailMaterial = nullptr;
	TrailCounter = 0;
}

void ASnowTrails::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;
}

void ASnowTrails::BeginDestroy()
{
	Super::BeginDestroy();

	Instance = nullptr;
}

void ASnowTrails::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float time = GetWorld()->GetTimeSeconds();

	for (int i = 0; i < TrailsComponents.Num(); i++) 
	{
		if (TrailsComponents[i].DeathWorldTime < time) 
		{
			if (TrailsComponents[i].TrailMeshComponent)
				TrailsComponents[i].TrailMeshComponent->DestroyComponent();

			TrailsComponents.RemoveAt(i);
			i--;
		}
	}
}

void ASnowTrails::AddSnowTrail(const FVector& Location, float YawRotation)
{
	UStaticMeshComponent* newTrail = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName(FString("Trail Mesh ") + FString::FromInt(TrailCounter)));
	newTrail->SetupAttachment(RootComponent);
	newTrail->RegisterComponent();
	AddInstanceComponent(newTrail);

	newTrail->SetStaticMesh(TrailMesh);
	newTrail->SetMaterial(0, TrailMaterial);
	newTrail->SetWorldLocation(Location);
	newTrail->SetWorldRotation(FRotator(0.0f, YawRotation, 0.0f));
	newTrail->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	newTrail->bOnlyOwnerSee = true;
	newTrail->RuntimeVirtualTextures.Add(RVTToRender);
	
	TrailsComponents.Add(FSnowTrailData(newTrail, GetWorld()->GetTimeSeconds() + TrailLifeTime));
	TrailCounter++;
}