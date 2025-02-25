// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROCKSTARS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Allows us to overrid the Init function to bind to the PreLoadMap and PostLoadMapWithWorld delegates
	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);	
};