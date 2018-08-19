// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"

#include "Components/HorizontalBoxSlot.h"
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

void UPaintingGrid::ClearPaintings()
{
	for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); ++i)
	{
		USizeBox* CardContainter = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
		if (!CardContainter) continue;

		CardContainter->ClearChildren();
	}		
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!PaginationBox) return;
	UPaginationDot* NewPaginationDot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (!NewPaginationDot) return;
	NewPaginationDot->SetActive(Active);
	UHorizontalBoxSlot* Slot = PaginationBox->AddChildToHorizontalBox(NewPaginationDot);
	
	Slot->SetPadding(FMargin(PaginationDotPadding,0));
}

void UPaintingGrid::ClearPaginationDots()
{
	if (!PaginationBox) return;
	PaginationBox->ClearChildren();
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
return PaintingGrid->GetChildrenCount();
}


