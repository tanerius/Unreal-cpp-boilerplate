// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorBasic.h"

// the following we need for UTextRenderComponent
#include "Components/TextRenderComponent.h"

// The following is needed for CustomComponent 
#include "CustomActorComponent.h"

// Sets default values
AActorBasic::AActorBasic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create dummy root scene component
	BasicActorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot0"));
	// Make it the actors root component
	RootComponent = BasicActorRoot;


	// Create the text component and give it a value
	SomeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SomeText0"));
	SomeText->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	SomeText->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	//SomeText->SetText(FText::Format(FText("Score: {0}"), FText::AsNumber(0));
	SomeText->SetText(FText::FromString(TEXT("Dynamically added text here")));
	SomeText->SetupAttachment(BasicActorRoot);


	// Initialize the custom component
	CustomComponent = CreateDefaultSubobject<UCustomActorComponent>(TEXT("MyComponent0"));
	

}

// Called when the game starts or when spawned
void AActorBasic::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AActorBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

