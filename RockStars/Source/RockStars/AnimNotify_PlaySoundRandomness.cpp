// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PlaySoundRandomness.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_PlaySoundRandomness::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	/** If the MeshComp is null, return. */
	if (!MeshComp) return;

	/** Get reference to the world so that we spawn the sound in the correct level.
	 * Without this, the sound may not play. Additionally, this is not included in blueprints
	 * because the blueprint node PlaySoundAtLocation automatically gets a reference to the world. */
	UWorld* World = MeshComp->GetWorld();
	if (!World) return;

	/** Create a pointer to the sound that will be played and make its default value nothing. */
	USoundBase* SelectedSound = nullptr;

	/** If bUseRandomSound is true and the SoundsArray has at least one sound, pick a random sound from the SoundsArray. */
	if (bUseRandomSound && SoundsArray.Num() > 0)
	{
		// Pick a random sound from the SoundsArray
		int32 const RandomIndex = FMath::RandRange(0, SoundsArray.Num() - 1);
		SelectedSound = SoundsArray[RandomIndex];
	}
	else
	{
		/** Use the SoundToPlay if bUseRandomSound is false. */
		SelectedSound = SoundToPlay; 
	}

	/** If we don't have a sound, then return because we can't be playing no sound. */
	if (!SelectedSound) return;

	/** If true, spawn the sound at the location of the actor playing the animation.
	 * If false, use the spawn location set by the user. */
	FVector const SoundLocation = bUseActorLocation ? MeshComp->GetComponentLocation() : SpawnLocation;

	/** Randomize the volume and pitch of the sound. */
	float const Volume = FMath::RandRange(MinVolume, MaxVolume);
	float const Pitch = FMath::RandRange(MinPitch, MaxPitch);

	/** Play the sound at the location using the values we determined above and our other variables. */
	UGameplayStatics::PlaySoundAtLocation(
		World,
		SelectedSound,
		SoundLocation,
		Volume,
		Pitch,
		StartTime,
		AttenuationSettings
	);
}

FString UAnimNotify_PlaySoundRandomness::GetNotifyName_Implementation() const
{
	/** If a random sound is being used and there is more than one sound in the SoundsArray, return the number of options.
	 * For example, having 5 sounds would make it read "Random Sound (5 Options)"*/
	if (bUseRandomSound && SoundsArray.Num() > 0)
	{
		return FString::Printf(TEXT("Random Sound (%d Options)"), SoundsArray.Num());
	}
	else if (SoundToPlay)
	{
		/** If a single sound is being used, return the name of the sound.
		 * For example, it might say "Sound: Erg_Footstep"*/
		return FString::Printf(TEXT("Sound: %s"), *SoundToPlay->GetName());
	}
	else
	{
		/** If there is no sound, display "Play Sound Notify" as the name. */
		return TEXT("Play Sound Notify");
	}
}