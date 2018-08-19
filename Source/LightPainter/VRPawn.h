// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "HandControllerBase.h"

#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();


protected:

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void RightTriggeredPressed() { if (RightHandController) RightHandController->TriggerPressed(); }
	void RightTriggeredReleased() { if (RightHandController) RightHandController->TriggerReleased(); }

	void PaginateRightAxisInput(float AxisValue);

	void UpdateCurrentPage(int32 Offset);

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerBaseClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerBaseClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationThumbstickTreshold = .6f;

	// Components
	UPROPERTY()
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// References
	UPROPERTY()
	class AHandControllerBase * RightHandController;

	UPROPERTY()
	class AHandControllerBase * LeftHandController;

	// State

	int32 LastPaginationOffset = 0;

};
