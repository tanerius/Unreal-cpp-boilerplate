// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
// Include for creating widgets
#include "Blueprint/UserWidget.h"


ACustomPlayerController::ACustomPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	timerCounter = 0.0f;

	PrimaryActorTick.bCanEverTick = true;
	

	FStringClassReference MyWidgetClassRef(TEXT("/Game/Widgets/MainMenuWidget.MainMenuWidget_C"));
	// Get the widget class
	MainMenuWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>();
}

void ACustomPlayerController::DisplayMainMenu()
{
	// Check if class was found
	if (MainMenuWidgetClass)
	{
		// Create the widget
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass, FName(TEXT("MainMenu")));
		// Check if widget was created
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			bShowMouseCursor = true;
		}
	}
}

// Called every frame
void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timerCounter += DeltaTime;
	if (timerCounter > 10.0f)
	{
		// check if any events are bound to delegate ?
		if (TenSeconds_OnPassed.IsBound())
		{
			TenSeconds_OnPassed.Broadcast(10 * timeOffset);
			timeOffset++;
			timerCounter = 0.f;
		}
	}
}

