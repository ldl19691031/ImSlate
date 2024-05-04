// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ImSlateGameModeExample.generated.h"

/**
 * 
 */
UCLASS()
class AImSlateGameModeExample : public AGameModeBase
{
	GENERATED_BODY()
	AImSlateGameModeExample();
public:
	virtual void Tick(float DeltaTime) override;
};
