// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode425.generated.h"

/**
 * Use the GameMode for version 4.25 class to spicify other top level classes like:
 * GameState
 * PlayerController
 * Pawn
 *
 */
UCLASS()
class CUSTOMTEMPLATE_API ACustomGameMode425 : public AGameModeBase
{
	GENERATED_BODY()
public:
	/** a proper constructor */
	ACustomGameMode425(const FObjectInitializer& ObjectInitializer);

	/** A sample class to assign GameState etc */
	void AssignOtherClasses();
};
