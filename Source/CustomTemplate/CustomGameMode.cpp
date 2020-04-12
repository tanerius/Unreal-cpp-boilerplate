// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomPawn.h"
#include "CustomPlayerController.h"
#include "CustomGameState.h"
#include "CustomPlayerState.h"


ACustomGameMode::ACustomGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{ 
	// construction code here
	AssignOtherClasses();
}



void ACustomGameMode::AssignOtherClasses()
{
	/** Disabling the following two lines will also make the game mode tick */
	// PrimaryActorTick.bCanEverTick = true;
	// PrimaryActorTick.bStartWithTickEnabled = true;

	// Assign a GameState class
	GameStateClass = ACustomGameState::StaticClass();

	// Assign a default pawn class
	DefaultPawnClass = ACustomPawn::StaticClass();

	// Assign a player controller
	PlayerControllerClass = ACustomPlayerController::StaticClass();

	// Assign a custom PlayerState controller
	PlayerStateClass = ACustomPlayerState::StaticClass();
}