// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * Use the GameMode  class to spicify other top level classes like:
 * GameState
 * PlayerController
 * Pawn
 *
 */
UCLASS()
class CUSTOMTEMPLATE_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** a proper constructor */
	ACustomGameMode(const FObjectInitializer& ObjectInitializer);

	/** A sample class to assign GameState etc */
	void AssignOtherClasses();
};
