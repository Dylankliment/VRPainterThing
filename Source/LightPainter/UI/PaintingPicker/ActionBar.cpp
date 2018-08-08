// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionBar.h"

bool UActionBar::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!AddButton || !DeleteButton) return false;


	AddButton->OnClicked.AddDynamic(this, &UActionBar::AddButtonClicked);
	DeleteButton->OnClicked.AddDynamic(this, &UActionBar::DeleteButtonClicked);

	return true;
}

void UActionBar::AddButtonClicked()
{

}

void UActionBar::DeleteButtonClicked()
{

}