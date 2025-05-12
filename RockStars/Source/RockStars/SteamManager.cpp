// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamManager.h"
#include "MyGameInstance.h"
//#include "Async.h"

void USteamManager::InitializeSteamManager()
{
	OnSteamOverlayActivatedCallback.Register(this, &USteamManager::SM_SteamOverlayActivated);
}

void USteamManager::SetGameInstanceRef(UMyGameInstance* GameInstance)
{
	GameInstanceRef = GameInstance;
}

void USteamManager::SM_SteamOverlayActivated(GameOverlayActivated_t* pCallback)
{
	const bool isOverlayActive = ((pCallback->m_bActive) != 0);;
	GameInstanceRef;

	if (isOverlayActive)
	{
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			GameInstanceRef->PublicOnSteamOverlayActive();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Steam overlay active."));
		});
	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			GameInstanceRef->PublicOnSteamOverlayDeactive();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Steam overlay deactive."));
		});
	}
}