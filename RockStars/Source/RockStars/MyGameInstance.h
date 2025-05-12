// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SteamManager.h"
#include "MyGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserInputDeviceConnectionChanged, bool, bIsConnected);

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
	// Override the Shutdown function to do c++ functionality in addition to blueprint functionality
	virtual void Shutdown() override;

	// Init event for blueprint that will be called after the Init function in C++
	UFUNCTION(BlueprintImplementableEvent, Category= "Init")
	void Init_BP();

	// Event shutdown for blueprint that will be called after the Shutdown function in C++
	UFUNCTION(BlueprintImplementableEvent, Category = "Shutdown")
	void Shutdown_BP();

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);


	UPROPERTY(BlueprintAssignable, Category = "Controller")
	FOnUserInputDeviceConnectionChanged OnUserInputDeviceConnectionChange;
	// Function to run when the controller is plugged in or unplugged
	void ControllerConnectionChanged(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputDeviceID);

	UPROPERTY(BlueprintReadOnly, Category = "Steam")
	USteamManager* SteamManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steam")
	bool bIsSteamOverlayActive = false;

	const bool EnableUSteamManagerFeatures = true;

	void PublicOnSteamOverlayActive();
	void PublicOnSteamOverlayDeactive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Steam")
	void OnSteamOverlayActivated(bool isOverlayActive);
};