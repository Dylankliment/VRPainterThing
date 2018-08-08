// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"

#include "Engine/World.h"
#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"

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

	if (HandControllerBaseClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(HandControllerBaseClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}


}

void AVRPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("SpawnActor"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggeredPressed);
	PlayerInputComponent->BindAction(TEXT("SpawnActor"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggeredReleased);

	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);

}


void AVRPawn::Save()
{
	auto* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->Save();

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));

}