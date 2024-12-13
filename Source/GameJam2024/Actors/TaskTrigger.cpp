#include "TaskTrigger.h"

#include "../Pawns/PlayerVehicle.h"
#include "../Pawns/Components/PlayerTaskComponent.h"

#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>

TMap<FString, ATaskTrigger*> ATaskTrigger::TaskTriggers = TMap<FString, ATaskTrigger*>();

ATaskTrigger::ATaskTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	MarkerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker Mesh Component"));
	MarkerMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MarkerMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	MarkerMeshComponent->SetGenerateOverlapEvents(true);
	RootComponent = MarkerMeshComponent;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(50.0f, 50.0f));
	WidgetComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UUserWidget> TaskMarkerWidgetClassAsset(TEXT("/Game/UI/UW_TaskMarker"));

	if (TaskMarkerWidgetClassAsset.Class)
		WidgetComponent->SetWidgetClass(TaskMarkerWidgetClassAsset.Class);

	WidgetComponent->SetHiddenInGame(true);
	MarkerMeshComponent->SetHiddenInGame(true);
}

void ATaskTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	MarkerMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATaskTrigger::OnBeginOverlap);

	TaskTriggers.Add(TriggerName, this);
}

void ATaskTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerVehicle* playerPawn = Cast<APlayerVehicle>(OtherActor);

	if (!playerPawn)
		return;

	playerPawn->GetPlayerTaskComponent()->VisitedTrigger(this);
}

void ATaskTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaskTrigger::ActivateTrigger()
{
	WidgetComponent->SetHiddenInGame(false);
	MarkerMeshComponent->SetHiddenInGame(false);
}

void ATaskTrigger::DeactivateTrigger()
{
	WidgetComponent->SetHiddenInGame(true);
	MarkerMeshComponent->SetHiddenInGame(true);

	OnTriggerFinish();
}


