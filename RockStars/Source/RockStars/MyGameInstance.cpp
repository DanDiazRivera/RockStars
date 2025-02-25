// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MoviePlayer.h"

void UMyGameInstance::Init()
{
	// Call the base implementation
	Super::Init();

	// Bind the PreLoadMap and PostLoadMapWithWorld delegates
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);
}

void UMyGameInstance::BeginLoadingScreen(const FString& MapName)
{
	// If the loading screen is already playing, don't start another one.
	if (GetMoviePlayer()->IsMovieCurrentlyPlaying())
	{
		return;
	}
#if WITH_EDITOR
	// If GEngine is available, display a debug message
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Loading screen started!"));
	}
#endif

	if (!IsRunningDedicatedServer())
	{
		// All the attributes you can change: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/MoviePlayer/FLoadingScreenAttributes
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.MoviePaths.Add(TEXT("loading_screen"));
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 0.5f;

		// Adds a widget to the loading screen. Right now it shows three dots that animate.
		//LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);

		// Movie player interface: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/MoviePlayer/IGameMoviePlayer
	}
}

void UMyGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
#if WITH_EDITOR
	// Debug message that works like print strings in bps to show that the loading screen has ended.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Loading screen ended!"));
	}
#endif
}