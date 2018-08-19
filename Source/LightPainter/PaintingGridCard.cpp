// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"



void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{	
	PaintingName = NewPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	NewCardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();

	// TODO: Refactor out magic string
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName);
}

