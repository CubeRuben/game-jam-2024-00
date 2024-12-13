#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "../Actors/WindAffected.h"
#include "PlayerVehicle.generated.h"

struct FPlayerInput
{
	FPlayerInput() {}

	bool bMoveForward = false;
	bool bMoveLeft = false;
	bool bMoveBack = false;
	bool bMoveRight = false;

	bool bHandbrake = false;

	float MouseX = 0.0f;
	float MouseY = 0.0f;
	float MouseScroll = 0.0f;
};

UCLASS()
class GAMEJAM2024_API APlayerVehicle : public AWheeledVehiclePawn, public IWindAffected
{
	GENERATED_BODY()
	
public:

	APlayerVehicle();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* PlayerCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerMovementComponent* PlayerMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerTaskComponent* PlayerTaskComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerHealthComponent* PlayerHealthComponent;

	FPlayerInput PlayerInput;

public:

	FPlayerInput& GetPlayerInput() { return PlayerInput; }

	class UCameraComponent* GetCameraComponent() const { return PlayerCameraComponent; }

	class UPlayerMovementComponent* GetPlayerMovementComponent() const { return PlayerMovementComponent; }
	class UPlayerTaskComponent* GetPlayerTaskComponent() const { return PlayerTaskComponent; }

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ApplyWindForce_Implementation(FVector Force) override;

#define INPUT_HANDLE(name) void Input##name##Pressed() { PlayerInput.b##name = true; }; void Input##name##Released() { PlayerInput.b##name = false; };

	INPUT_HANDLE(MoveForward);
	INPUT_HANDLE(MoveLeft);
	INPUT_HANDLE(MoveBack);
	INPUT_HANDLE(MoveRight);

	INPUT_HANDLE(Handbrake);

	void InputMouseXAxis(float Value) { PlayerInput.MouseX = Value; };
	void InputMouseYAxis(float Value) { PlayerInput.MouseY = Value; };
	void InputMouseScrollAxis(float Value) { PlayerInput.MouseScroll = Value; };
};
