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

void ACustomPlayerController::DoSpwan()
{
	UE_LOG(LogTemp, Warning, TEXT("Fired action DoSpawn"));
}


void ACustomPlayerController::SampleAxisEvent(float Value)
{
	if (Value > 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fired axis SampleAxisEvent with value %f"), Value);
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Sample for binding an action key to player controller
	InputComponent->BindAction("SpawnSamplePawn", IE_Pressed, this, &ACustomPlayerController::DoSpwan);
	// Sample for binding an axis - handler must have a float as a parameter
	InputComponent->BindAxis("AxisMappingSample",  this, &ACustomPlayerController::SampleAxisEvent);
	UE_LOG(LogTemp, Warning, TEXT("Called ACustomPlayerController::SetupInputComponent("));
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

