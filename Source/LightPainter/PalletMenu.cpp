// Fill out your copyright notice in the Description page of Project Settings.

#include "PalletMenu.h"
#include "PaintingGameMode.h"

bool UPalletMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!SaveAndQuit) return false;


	SaveAndQuit->OnReleased.AddDynamic(this, &UPalletMenu::SaveAndQuitButtonClicked);

	return true;
}

void UPalletMenu::SaveAndQuitButtonClicked()
{
	auto* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->SaveAndQuit();
}
