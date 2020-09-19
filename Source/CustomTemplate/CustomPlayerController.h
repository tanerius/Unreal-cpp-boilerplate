// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMTEMPLATE_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UUserWidget* MainMenuWidget = nullptr;
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

public:
	ACustomPlayerController();

	UFUNCTION(BlueprintCallable, Category="Template")
	void DisplayMainMenu();
};
