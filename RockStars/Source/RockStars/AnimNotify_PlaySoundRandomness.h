// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "AnimNotify_PlaySoundRandomness.generated.h"

UCLASS()
class ROCKSTARS_API UAnimNotify_PlaySoundRandomness : public UAnimNotify
{
	GENERATED_BODY()

public:

	/** If true, the sound will be chosen randomly from the SoundsArray. Otherwise, the SoundToPlay will be used. */
	UPROPERTY(EditAnywhere, Category = "Sound")
	bool bUseRandomSound = false;

	/** If bUseRandomSound is true, the sound will be chosen randomly from this array, and the SoundToPlay will not be visible. */
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (EditCondition = "bUseRandomSound", EditConditionHides))
	TArray<USoundBase*> SoundsArray;

	/** If bUseRandomSound is false, this sound will be played, and the SoundsArray will not be visible. */
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (EditCondition = "!bUseRandomSound"))
	USoundBase* SoundToPlay;

	/** If true, spawn sound at the location of the actor playing the animation. Otherwise, use the SpawnLocation set by the user. */
	UPROPERTY(EditAnywhere, Category = "Location")
	bool bUseActorLocation = true;

	/** If true, the sound will be spawned at the location of the actor playing the animation and SpawnLocation will be hidden.
	 * If false, the sound will be spawned at the location set by the user. */
	UPROPERTY(EditAnywhere, Category = "Location", meta = (EditCondition = "!bUseActorLocation", EditConditionHides))	
	FVector SpawnLocation = FVector::ZeroVector;

	/** Min and max volume and pitch values used to randomize the sound. */ 
	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	float MinVolume = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	float MaxVolume = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	float MinPitch = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	float MaxPitch = 1.0f;

	/** The time in the audio clip to start playing the sound. */
	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	float StartTime = 0.0f;

	/** Attenuation settings used to determine how the sound is heard. */
	UPROPERTY(EditAnywhere, Category = "Sound Modifiers")
	USoundAttenuation* AttenuationSettings = nullptr;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	/** Allows for renaming of the animation notify. */
	virtual FString GetNotifyName_Implementation() const override;
};