#include "PlayerVehicle.h"

#include "Components/PlayerMovementComponent.h"
#include "Components/PlayerTaskComponent.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

APlayerVehicle::APlayerVehicle()
{
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->TargetArmLength = 250.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));
	SpringArmComponent->SetupAttachment(GetMesh());
	
	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera Component"));
	PlayerCameraComponent->SetupAttachment(SpringArmComponent);

	PlayerMovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Player Movement Component"));
	PlayerTaskComponent = CreateDefaultSubobject<UPlayerTaskComponent>(TEXT("Player Task Component"));
}

void APlayerVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent)
		return;

	PlayerInputComponent->BindAxis("MouseX", this, &APlayerVehicle::InputMouseXAxis);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerVehicle::InputMouseYAxis);
	PlayerInputComponent->BindAxis("MouseScroll", this, &APlayerVehicle::InputMouseScrollAxis);

#define INPUT_BIND(name) PlayerInputComponent->BindAction(#name, IE_Pressed, this, &APlayerVehicle::Input##name##Pressed); PlayerInputComponent->BindAction(#name, IE_Released, this, &APlayerVehicle::Input##name##Released);

	INPUT_BIND(MoveForward);
	INPUT_BIND(MoveLeft);
	INPUT_BIND(MoveBack);
	INPUT_BIND(MoveRight);

	INPUT_BIND(Handbrake);
}
