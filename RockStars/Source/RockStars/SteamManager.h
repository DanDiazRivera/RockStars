// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdParty/Steamworks/Steamv157/sdk/public/steam/steam_api.h"
#include "UObject/NoExportTypes.h"
#include "SteamManager.generated.h"

class UMyGameInstance;

/**
 * 
 */
UCLASS()
class ROCKSTARS_API USteamManager : public UObject
{
	GENERATED_BODY()

private:
	STEAM_CALLBACK_MANUAL(USteamManager, SM_SteamOverlayActivated, GameOverlayActivated_t, OnSteamOverlayActivatedCallback);

public:
	void InitializeSteamManager();
	void SetGameInstanceRef(UMyGameInstance* GameInstance);

	UPROPERTY(BlueprintReadOnly, Category="Game Instance")
	UMyGameInstance* GameInstanceRef;
};
