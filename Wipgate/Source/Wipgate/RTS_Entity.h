// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "RTS_Team.h"

#include "RTS_Entity.generated.h"

class UTexture2D;
class UWidgetComponent;
class UMaterial;
class UUnitEffect;
class UStaticMeshComponent;
class USoundCue;
class USoundConcurrency;
class URTS_Team;
class ARTS_EntitySpawner;
class ARTS_DeathEffect;

DECLARE_LOG_CATEGORY_EXTERN(RTS_ENTITY_LOG, Log, All);

//TODO: Logging warning when unit is structure (EntityType)
UCLASS()
class WIPGATE_API ARTS_Entity : public ACharacter
{
	GENERATED_BODY()

public:
	ARTS_Entity();

public:
	UFUNCTION(BlueprintCallable)
		void SetSelected(bool selected);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintGetter, Category="Selection")
		bool IsSelected() const;

	UFUNCTION(BlueprintCallable)
		FVector GetGroundLocation();

	UFUNCTION(BlueprintCallable, Category = "Team")
		virtual void SetTeamMaterial(URTS_Team* t);

	UFUNCTION(BlueprintCallable)
		void PostInitialize();

	/* --- Unit effect functions --- */
	UFUNCTION(BlueprintGetter, Category = "Effects")
		TArray<UUnitEffect*> GetUnitEffects() const;
	UFUNCTION(BlueprintCallable, Category = "Effects")
		bool HasEffectWithTag(FName tag);
	UFUNCTION(BlueprintCallable, Category = "Effects")
		void RemoveUnitEffectWithTag(FName tag);
	UFUNCTION(BlueprintCallable, Category = "Effects")
		void AddUnitEffect(UUnitEffect* effect);
	UFUNCTION(BlueprintCallable, Category = "Effects")
		void RemoveUnitEffect(UUnitEffect* effect);

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool ApplyDamage(int damage, bool armor, ARTS_Entity* attacker);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ApplyHealing(int healing);
	UFUNCTION(BlueprintCallable, Category = "Health")
		virtual void Kill();
	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
		void Kill_NotifyBP();
	UFUNCTION(BlueprintPure, Category = "Health")
		bool IsAlive();

	UFUNCTION(BlueprintCallable)
		void AddToLumaSaturation(int32 LumaToAdd);

	UFUNCTION(BlueprintCallable)
		void RemoveLumaSaturation(int32 LumaToRemove);

	// Calling this function will make the selection ring flash for a short period
	UFUNCTION(BlueprintCallable)
		void SetHighlighted();


	UPROPERTY(BlueprintReadOnly)
		int LumaToRemoveOnEnemyDeath = 2;

	// When true, this unit's stats can not be changed, and it can not be targeted
	UPROPERTY(BlueprintReadWrite)
		bool Immaterial = false;

	//Minimum amount of luma this unit can drop
	UPROPERTY(EditAnywhere)
		int MinimumLumaDrop = 3;

	//Maximum amount of luma this unit can drop
	UPROPERTY(EditAnywhere)
		int MaximumLumaDrop = 10;

	//Class to spawn when unit dies
	UPROPERTY(EditAnywhere)
		TSubclassOf<ARTS_DeathEffect> DeathEffectClass;

	bool IsSelectableByPlayer() const;

public:
	/* Public blueprint editable variables */

	//SELECTION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
		FVector SelectionHitBox = FVector(30.0f, 30.0f, 100.0f);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Selection")
		UStaticMeshComponent* SelectionStaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
		float SelectionBrightness = 5.0f;

	//UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UWidgetComponent* BarWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UStaticMeshComponent* MinimapIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FName MinimapColorParameterName = "Color";

	FRotator BarRotation;

	//DEBUG
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool ShowUnitStats = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool RenderFlockingDebugInfo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
		bool ShowSelectionBox = false;


	//STATS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		FMovementStat BaseMovementStats;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		FMovementStat CurrentMovementStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		FAttackStat BaseAttackStats;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		FAttackStat CurrentAttackStats;

	UPROPERTY(BlueprintReadWrite)
		float TimerRateOfFire = 0.f;
	UPROPERTY(BlueprintReadWrite)
		bool m_IsAttackOnCooldown = false;
	UPROPERTY(BlueprintReadWrite)
		float AttackAdditionalAnimSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		FDefenceStat BaseDefenceStats;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		FDefenceStat CurrentDefenceStats;
	
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		FLumaStat CurrentLumaStats;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		int Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		FVisionStat BaseVisionStats;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
		FVisionStat CurrentVisionStats;

	// TEAM
	UPROPERTY(BlueprintReadWrite, Category = "Team")
		URTS_Team* Team;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Team")
		ETeamAlignment Alignment = ETeamAlignment::E_PLAYER;

	// TYPE
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEntityType EntityType = EEntityType::E_RANGED;

	UPROPERTY(BlueprintReadWrite)
		TArray<UUnitEffect*> UnitEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 IconIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		UTexture2D* LargeIconTexture;	//used when unit is only selected unit.

	const int NUM_ABILITIES = 3;
	bool ShowingAbilityIcons = false;

	// SOUNDS
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		USoundCue* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		USoundCue* CommandSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		USoundAttenuation* SoundAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		USoundConcurrency* SoundConcurrency;

	//DEATH
	UPROPERTY(BlueprintReadOnly)
		FVector LocationOfDeath;
	UPROPERTY(BlueprintReadOnly)
		FVector ForwardOnDeath;

	// OVERDOSED
	// How long to live once overdosed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_SecondsToLiveWhenOverdosed = 10.0f;

	// Timer that upon reaching zero will cause the entity to die
	UPROPERTY(BlueprintReadWrite)
		float m_SecondsLeftOfOverdose = 0.0f;

	//SPAWNER
	ARTS_EntitySpawner* Spawner;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	/* private functions */
	void ApplyEffectLinear(UUnitEffect* effect);
	void ApplyEffectOnce(UUnitEffect* effect);

	/* private members */
	UPROPERTY(VisibleAnywhere, Category = "Selection")
		bool m_Selected;

	/* HIGHLIGHTED */
	UPROPERTY(EditAnywhere)
		int m_HighlightFlashCount = 4;

	UPROPERTY(EditAnywhere)
		float m_SecondsToHighlight = 0.8f;

	// True when being targetted by the player (flashes selection mesh)
	bool m_Highlighted;

	// Timer used to determine how long to flash selection mesh for
	float m_SecondsLeftOfHighlighting = 0.0f;


	const int EFFECT_INTERVAL = 1;
	
};
