// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PalletMenu.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPalletMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	bool Initialize() override;

	
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* SaveAndQuit;
	
	UFUNCTION()
	void SaveAndQuitButtonClicked();
};
