// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralFunctionLibrary_CPP.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "RTS_Entity.h"
#include "DrawDebugHelpers.h"
#include "CoreGlobals.h"
#include "ConfigCacheIni.h"

//ARTS_Entity* GetClosestEntity(ARTS_Entity* self, TArray<ARTS_Entity*> entities)
//{
//	float shortestDistance = TNumericLimits<float>::Max();
//	ARTS_Entity* closestEntity = NewObject<ARTS_Entity>(self->GetWorld());
//	float currentDistance;
//
//	for (auto e : entities)
//	{
//		currentDistance = self->GetDistanceTo(e);
//		if (currentDistance < shortestDistance)
//		{
//			shortestDistance = currentDistance;
//			closestEntity = e;
//		}
//	}
//
//	return closestEntity;
//}

UUnitEffect * UGeneralFunctionLibrary_CPP::CreateUnitEffect(UObject * outer, const EUnitEffectStat stat, const EUnitEffectType type,
	const float delay, const int magnitude, const int duration)
{
	UUnitEffect* unitEffect = NewObject<UUnitEffect>(outer);
	unitEffect->Initialize(stat, type, delay, magnitude, duration);
	return unitEffect;
}

UCommand_MoveToLocation * UGeneralFunctionLibrary_CPP::CreateCommand_MoveToLocation(UObject* outer, FVector location, const bool isForced)
{
	UCommand_MoveToLocation* command = NewObject<UCommand_MoveToLocation>(outer);
	command->IsForced = isForced;
	command->Target = location;
	return command;
}

UCommand_Attack * UGeneralFunctionLibrary_CPP::CreateCommand_Attack(UObject * outer, ARTS_Entity* target, const bool isForced)
{
	UCommand_Attack* command = NewObject<UCommand_Attack>(outer);
	command->IsForced = isForced;
	command->Target = target;
	return command;
}

FString UGeneralFunctionLibrary_CPP::GetProjectVersion()
{
	FString ProjectVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);
	return ProjectVersion;
}

FString UGeneralFunctionLibrary_CPP::GetProjectName()
{
	FString ProjectName;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectName"),
		ProjectName,
		GGameIni
	);
	return ProjectName;
}

FString UGeneralFunctionLibrary_CPP::GetProjectDescription()
{
	FString ProjectDescription;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("Description"),
		ProjectDescription,
		GGameIni
	);
	return ProjectDescription;
}

void UGeneralFunctionLibrary_CPP::FVector2DMinMax(FVector2D& vec1, FVector2D& vec2)
{
	FVector2D vec1Copy = vec1;
	FVector2D vec2Copy = vec2;

	vec1.X = FMath::Min(vec1Copy.X, vec2Copy.X);
	vec1.Y = FMath::Min(vec1Copy.Y, vec2Copy.Y);

	vec2.X = FMath::Max(vec1Copy.X, vec2Copy.X);
	vec2.Y = FMath::Max(vec1Copy.Y, vec2Copy.Y);
}

void UGeneralFunctionLibrary_CPP::FVectorMinMax(FVector& vec1, FVector& vec2)
{
	FVector vec1Copy = vec1;
	FVector vec2Copy = vec2;

	vec1.X = FMath::Min(vec1Copy.X, vec2Copy.X);
	vec1.Y = FMath::Min(vec1Copy.Y, vec2Copy.Y);
	vec1.Z = FMath::Min(vec1Copy.Z, vec2Copy.Z);

	vec2.X = FMath::Max(vec1Copy.X, vec2Copy.X);
	vec2.Y = FMath::Max(vec1Copy.Y, vec2Copy.Y);
	vec2.Z = FMath::Max(vec1Copy.Z, vec2Copy.Z);
}

bool UGeneralFunctionLibrary_CPP::PointInBounds2D(FVector2D point, FVector2D boundsMin, FVector2D boundsMax)
{
	bool result = ((point.X > boundsMin.X && point.X < boundsMax.X) &&
		(point.Y > boundsMin.Y && point.Y < boundsMax.Y));
	return result;
}

bool UGeneralFunctionLibrary_CPP::BoxesOverlap(FVector2D boxAMin, FVector2D boxAMax, FVector2D boxBMin, FVector2D boxBMax)
{
	bool result = !(
		boxBMin.X > boxAMax.X ||
		boxBMax.X < boxAMin.X ||
		boxBMin.Y > boxAMax.Y ||
		boxBMax.Y < boxAMin.Y);
	return result;
}

FVector2D UGeneralFunctionLibrary_CPP::GetNormalizedMousePosition(APlayerController* playerController)
{
	float mouseX, mouseY;
	playerController->GetMousePosition(mouseX, mouseY);

	int32 viewportSizeX, viewportSizeY;
	playerController->GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D result(mouseX / (float)viewportSizeX,
		mouseY / (float)viewportSizeY);
	return result;
}

FVector2D UGeneralFunctionLibrary_CPP::GetMousePositionVector2D(APlayerController* playerController)
{
	FVector2D result = {};
	float viewportScaleF = UWidgetLayoutLibrary::GetMousePositionScaledByDPI(playerController, result.X, result.Y);
	return result;
}

void UGeneralFunctionLibrary_CPP::DrawPointArray(const UWorld* world, const TArray<FVector>& points, const FColor & color, const float pointSize, const float lineSize)
{
	for (int32 i = 0; i < points.Num(); ++i)
	{
		FVector point = points[i];
		DrawDebugSphere(world, point, pointSize, 12, color, false, 0.f, (uint8)'\000', 1.f);

		if (i != 0)
		{
			DrawDebugLine(world, point, points[i - 1], color, false, 0.f, (uint8)'\000', lineSize);
		}
	}
}

void UGeneralFunctionLibrary_CPP::SortByDistance(FVector target, TArray<ARTS_Entity*> in, TArray<ARTS_Entity*>& out)
{
	in.Sort([target](const AActor& a, const AActor& b) {
		float distanceA = FVector::Distance(a.GetActorLocation(), target);
		float distanceB = FVector::Distance(b.GetActorLocation(), target);
		return distanceA > distanceB;
	});
	out = in;
}

void PrintStringToScreen(FString text, FColor Color, float TimeToDisplay)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, text);
	}
}
