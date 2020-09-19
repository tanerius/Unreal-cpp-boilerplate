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
