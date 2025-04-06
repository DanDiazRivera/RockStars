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
	// Allows us to override the Init function to bind to the PreLoadMap and PostLoadMapWithWorld delegates
	virtual void Init() override;

	// Init event for blueprint that will be called after the Init function in C++
	UFUNCTION(BlueprintImplementableEvent, Category= "Init")
	void Init_BP();

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);	
};