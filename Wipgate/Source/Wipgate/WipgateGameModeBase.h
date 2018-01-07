// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "Helpers/EntityHelpers.h"
#include "WipgateGameModeBase.generated.h"

class URTS_Team;

DECLARE_LOG_CATEGORY_EXTERN(WipgateGameModeBase, Log, All);

UCLASS()
class WIPGATE_API AWipgateGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	URTS_Team* GetTeamWithAlignment(ETeamAlignment alignment);

	UFUNCTION(BlueprintCallable)
		void SaveResources();

	UFUNCTION(BlueprintCallable)
		void NextLevel();

private:
	//Make sure the datatable is inheriting from FTeamRow
	UPROPERTY(EditAnywhere)
	UDataTable* m_TeamTable;

	//Make sure the datatable is inheriting from FEnemyUpgrade
	UPROPERTY(EditAnywhere)
		UDataTable* m_EnemyUpgradeTable;
};
