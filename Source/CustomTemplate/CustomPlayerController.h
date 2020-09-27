// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(BroadcastTimePassedDelegate, int32);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CUSTOMTEMPLATE_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UUserWidget* MainMenuWidget = nullptr;
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

	float timerCounter;
	int32 timeOffset = 1;

public:
	ACustomPlayerController();

	UFUNCTION(BlueprintCallable, Category="Template")
	void DisplayMainMenu();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Add a single param delegate tot this actor
	*/
	BroadcastTimePassedDelegate TenSeconds_OnPassed;
};
