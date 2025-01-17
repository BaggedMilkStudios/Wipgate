#include "UnitEffect.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "GeneralFunctionLibrary_CPP.h"

void UUnitEffect::Initialize(const EUnitEffectStat stat, const EUnitEffectType type, const float delay, const int magnitude, const int duration)
{
	AffectedStat = stat;
	Type = type;
	Delay = delay;
	Elapsed = -delay; // start delay negative so effect can start at 0
	Magnitude = magnitude;
	Duration = duration;
}

void UUnitEffect::SetParticles(UParticleSystem * tick, UParticleSystem * start, UParticleSystem * end, UParticleSystem* constant, FName socketName)
{
	TickParticles = tick;
	StartParticles = start;
	EndParticles = end;
	ConstantParticles = constant;
	SocketName = socketName;
}

void UUnitEffect::StartParticleConstant(USceneComponent* comp)
{
	if(!ParticleComponent)
		ParticleComponent = UGameplayStatics::SpawnEmitterAttached(ConstantParticles, comp);
}

void UUnitEffect::StopParticleConstant()
{
	if (ParticleComponent)
	{
		ParticleComponent->DestroyComponent();
	}
}

void UUnitEffect::AttachParticleToSocket(USceneComponent * skeletalMesh)
{
	if (!ParticleComponent) return;

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	
	if (skeletalMesh->GetAllSocketNames().Contains(SocketName))
		ParticleComponent->AttachToComponent(skeletalMesh, rules, SocketName);
}

void UUnitEffect::SetFloatParameter(const FName name, const float amount)
{
	ParticleComponent->SetFloatParameter(name, amount);
}
