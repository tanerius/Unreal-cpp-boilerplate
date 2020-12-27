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
	m_initialSpawnPlace = 100.0f;

	PrimaryActorTick.bCanEverTick = true;
	

	FStringClassReference MyWidgetClassRef(TEXT("/Game/Widgets/MainMenuWidget.MainMenuWidget_C"));
	// Get the widget class
	MainMenuWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>();

	// get the sphere blueprint class and assign a reference to my variable
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Sphere.BP_Sphere'"));
	if (ItemBlueprint.Object) {
		SphereActorBP = (UClass*)ItemBlueprint.Object->GeneratedClass;
		UE_LOG(LogTemp, Warning, TEXT("Sphere blueprint assigned"));
	}
	else
	{
		SphereActorBP = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Sphere blueprint not assigned correctly"));
	}
	 
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
	if (SphereActorBP != nullptr && !WeakPointerToActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning a sphere at %f"), m_initialSpawnPlace);
		const FVector Location = { 0, 0, m_initialSpawnPlace };
		const FRotator Rotation = FRotator(0, 0, 0);
		// spawn an actor from a player conteroller
		WeakPointerToActor = GetWorld()->SpawnActor(SphereActorBP, &Location, &Rotation);

		m_initialSpawnPlace += 100.0f;
	}
	else
	{
		if (WeakPointerToActor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn sphere - sphere has already spawned"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn sphere - sphere blueprint class is null"));
		}
	}
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

