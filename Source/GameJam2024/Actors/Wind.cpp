#include "Wind.h"

#include <Components/BoxComponent.h>

AWind::AWind()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Wind Box Component"));
	RootComponent = BoxComponent;

	BoxComponent->InitBoxExtent(FVector(256.0f, 256.0f, 250.0f));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	StartSpeed = 150.f;

	HalfXBoundary = 1000.0f;
	HalfYBoundary = 1000.0f;

	MinTimerChangeVelocity = 15.0f;
	MaxTimerChangeVelocity = 30.0f;

	Timer = 0.0f;
}

void AWind::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	RandomizeVelocity();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWind::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AWind::OnEndOverlap);
}

void AWind::RandomizeVelocity()
{
	FVector vector = FMath::VRand();
	vector.Z = 0;
	Velocity = vector.GetSafeNormal2D() * StartSpeed;

	Timer = GetWorld()->GetTimeSeconds() + FMath::RandRange(MinTimerChangeVelocity, MaxTimerChangeVelocity);
}

void AWind::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UWindAffected>())
		OverlapWindAffected.Add(OtherActor);
}

void AWind::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UWindAffected>())
		OverlapWindAffected.Remove(OtherActor);
}

void AWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (AActor*& windAffected : OverlapWindAffected) 
	{
		if (windAffected)
			IWindAffected::Execute_ApplyWindForce(windAffected, Velocity * 2500.0f);
	}

	if (Timer < GetWorld()->GetTimeSeconds())
		RandomizeVelocity();

	AddActorWorldOffset(Velocity * DeltaTime);

	const FVector actorLocation = GetActorLocation();
	const bool outsideX1 = StartLocation.X - HalfXBoundary > actorLocation.X;
	const bool outsideX2 = StartLocation.X + HalfXBoundary < actorLocation.X;
	const bool outsideY1 = StartLocation.Y - HalfYBoundary > actorLocation.Y;
	const bool outsideY2 = StartLocation.Y + HalfYBoundary < actorLocation.Y;

	if (outsideX1 || outsideX2)
		Velocity.X *= -1;

	if (outsideY1 || outsideY2)
		Velocity.Y *= -1;
}

