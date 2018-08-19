// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"

#include "Engine/World.h"
#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PaintingPicker/PaintingPicker.h"
#include "EngineUtils.h"

#include "Saving/PainterSaveGame.h"


AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Root"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}


void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if (RightHandControllerBaseClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerBaseClass);
		RightHandController->SetHandController(EControllerHand::Right);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

	if (LeftHandControllerBaseClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerBaseClass);
		LeftHandController->SetHandController(EControllerHand::Left);
		LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}

}

void AVRPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("SpawnActor"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggeredPressed);
	PlayerInputComponent->BindAction(TEXT("SpawnActor"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggeredReleased);

     PlayerInputComponent->BindAxis("PaginateRight", this, &AVRPawn::PaginateRightAxisInput);


}

void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThumbstickTreshold ? 1 : 0;
	PaginationOffset += AxisValue < -PaginationThumbstickTreshold ? -1 : 0;

	if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Paginate %d"), PaginationOffset);

		UpdateCurrentPage(PaginationOffset);
	}
	LastPaginationOffset = PaginationOffset;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}
