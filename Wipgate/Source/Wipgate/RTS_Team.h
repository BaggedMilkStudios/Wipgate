// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Helpers/EntityHelpers.h"
#include "Helpers/UpgradeHelpers.h"
#include "RTS_Team.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(RTS_TEAM_LOG, Log, All);

class ARTS_Entity;
class URTS_GameInstance;

UCLASS()
class WIPGATE_API URTS_Team : public UObject
{
	GENERATED_BODY()
	
	public:
		/* Functions */
		UFUNCTION(BlueprintCallable)
		void AddUpgrades(TArray<FUpgrade> upgrades);
		//This function should only be used to set the initial teams, use the unit's own alignment for alignment checks
		UFUNCTION()
		ETeamAlignment GetAlignment() const { return m_Alignment; }
		//This function should only be used to set the initial teams
		UFUNCTION()
			void SetAlignment(ETeamAlignment alignment) { m_Alignment = alignment; }
		UFUNCTION()
			void CalculateUpgradeEffects();


		FAttackStat GetUpgradedAttackStats(ARTS_Entity* entity);

		/* Variables */
		UPROPERTY(BlueprintReadWrite)
		TArray<ARTS_Entity*> Entities;
		UPROPERTY(BlueprintReadOnly)
		FLinearColor Color = FLinearColor(1, 1, 1, 1);
		UPROPERTY(BlueprintReadOnly)
		TArray<FUpgrade> Upgrades;
		URTS_GameInstance* GameInstance = nullptr;
	private:
		ETeamAlignment m_Alignment = ETeamAlignment::E_NEUTRAL_AI;
};
