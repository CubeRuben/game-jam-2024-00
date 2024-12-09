#include "PlayerMovementComponent.h"

#include "../PlayerVehicle.h"

#include <GameFramework/SpringArmComponent.h>
#include <ChaosVehicleMovementComponent.h>

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MinTargetArmLength = 250.f;
	MaxTargetArmLength = 750.f;
	StepArmLength = 25.0f;
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

	movementComponent->SetThrottleInput((float)playerInput.bMoveForward - (float)playerInput.bMoveBack);
	movementComponent->SetSteeringInput((float)playerInput.bMoveRight - (float)playerInput.bMoveLeft);

	const float sens = 1.0f;
	
	USpringArmComponent* const springArmComponent = PlayerPawn->GetSpringArmComponent();

	//springArmComponent->AddRelativeRotation(FRotator(0.0f, , 0.0f));

	FRotator rotation = springArmComponent->GetRelativeRotation();
	rotation.Yaw += playerInput.MouseX * sens;
	rotation.Pitch = FMath::Clamp(playerInput.MouseY * sens + rotation.Pitch, -70.0f, 10.0f);
	springArmComponent->SetRelativeRotation(rotation);

	springArmComponent->TargetArmLength = FMath::Clamp(springArmComponent->TargetArmLength - StepArmLength * playerInput.MouseScroll, MinTargetArmLength, MaxTargetArmLength);

}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleInput(DeltaTime);
}

