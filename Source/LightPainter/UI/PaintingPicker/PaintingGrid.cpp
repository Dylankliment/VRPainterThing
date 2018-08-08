// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"


#include "Components/SizeBox.h"


void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (!PaintingGrid) return;
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (!NewWidget) return;

	NewWidget->SetPaintingName(PaintingName);

	USizeBox* CardContainter = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex));
	if (!CardContainter) return;

	CardContainter->AddChild(NewWidget);	
}
