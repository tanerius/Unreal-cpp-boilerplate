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

private:

	// A variable to hold the blueprint class od the sphere from which we can spawn shperes in the world
	TSubclassOf<class AActor> SphereActorBP = nullptr;
	float m_initialSpawnPlace = 100.0f;

	// The following weak pointer will hold a reference to the spawned 
	// AActor and will have IsValud() == true if actor is spawned
	TWeakObjectPtr<AActor> WeakPointerToActor;

public:
	ACustomPlayerController();

	UFUNCTION(BlueprintCallable, Category="Template")
	void DisplayMainMenu();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// handle input 
	virtual void SetupInputComponent() override;

	void DoSpwan(); // action event handler
	void SampleAxisEvent(float Value); // axis event handler

	/*
	* Add a single param delegate tot this actor
	*/
	BroadcastTimePassedDelegate TenSeconds_OnPassed;
};
