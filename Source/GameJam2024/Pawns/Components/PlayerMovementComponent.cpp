#include "PlayerMovementComponent.h"

#include "../PlayerVehicle.h"
#include "../../Actors/SnowTrails.h"

#include <Camera/CameraComponent.h>
#include <ChaosVehicleMovementComponent.h>

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = Cast<APlayerVehicle>(GetOwner());
	
	if (!PlayerPawn)
		DestroyComponent();
}

void UPlayerMovementComponent::HandleInput(float DeltaTime)
{
	FPlayerInput& playerInput = PlayerPawn->GetPlayerInput();

	UChaosVehicleMovementComponent* const movementComponent = PlayerPawn->GetVehicleMovementComponent();

	movementComponent->SetHandbrakeInput(playerInput.bHandbrake);

	movementComponent->SetThrottleInput((float)playerInput.bMoveForward);
	movementComponent->SetBrakeInput((float)playerInput.bMoveBack);
	movementComponent->SetSteeringInput((float)playerInput.bMoveRight - (float)playerInput.bMoveLeft);

	const float sens = 1.0f;

	UCameraComponent* cameraComponent = PlayerPawn->GetCameraComponent();

	FRotator rotation = cameraComponent->GetRelativeRotation();
	rotation.Yaw += playerInput.MouseX * sens;
	rotation.Pitch = FMath::Clamp(playerInput.MouseY * sens + rotation.Pitch, -50.0f, 50.0f);
	cameraComponent->SetRelativeRotation(rotation);
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleInput(DeltaTime);

	ASnowTrails* const snowTrails = ASnowTrails::GetInstance();
	
	if (!snowTrails)
		return;

	snowTrails->AddSnowTrail(PlayerPawn->GetActorLocation() + FVector(0.0f, 0.0f, TrailOffset), PlayerPawn->GetActorRotation().Yaw);
}

