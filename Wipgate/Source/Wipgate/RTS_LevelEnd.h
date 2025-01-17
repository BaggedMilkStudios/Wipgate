// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTS_LevelEnd.generated.h"

class ARTS_EntitySpawner;

UCLASS()
class WIPGATE_API ARTS_LevelEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTS_LevelEnd();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARTS_EntitySpawner* EntitySpawner = nullptr;
};
