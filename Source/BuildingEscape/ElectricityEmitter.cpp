// Copyright Robert O'Quinn 2017

#include "ElectricityEmitter.h"
#include "ElectricityConductor.h"
#include "ElectricDoorOpener.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerSphere.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values for this component's properties
UElectricityEmitter::UElectricityEmitter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UElectricityEmitter::BeginPlay()
{
	Super::BeginPlay();

	if (!triggerSphere)
	{
		UE_LOG(LogTemp, Error, TEXT("ElectricityEmitter %s does not have a TriggerSphere assigned"), *(GetOwner()->GetName()));
	}
	else
	{
		triggerSphere->OnActorBeginOverlap.AddDynamic(this, &UElectricityEmitter::OnBeginOverlap);
		triggerSphere->OnActorEndOverlap.AddDynamic(this, &UElectricityEmitter::OnEndOverlap);

		// Find all overlapping actors
		TArray<AActor*> overlappingActors;
		triggerSphere->GetOverlappingActors(OUT overlappingActors);
		
		// Iterate through them adding their masses
		for (const auto* actor : overlappingActors)
		{
			UElectricityConductor* electricityConductor = actor->FindComponentByClass<UElectricityConductor>();
		
			if (electricityConductor)
			{
				connectedConductors.Add(electricityConductor);
			}
		}
	}

	if (!electricityParticleTemplate)
	{
		UE_LOG(LogTemp, Error, TEXT("ElectricityEmitter %s does not have a particle emitter template"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UElectricityEmitter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!triggerSphere)
	{
		return;
	}

	TArray<UElectricityConductor*> visited;

	for (auto* conductor : connectedConductors)
	{
		VisitConductor(conductor, visited);
	}
}

void UElectricityEmitter::VisitConductor(UElectricityConductor* conductor, TArray<UElectricityConductor*>& toSkip)
{
	toSkip.Add(conductor);

	UElectricDoorOpener* doorOpener = conductor->GetOwner()->FindComponentByClass<UElectricDoorOpener>();

	if (doorOpener)
	{
		doorOpener->ApplyPower();
	}

	for (auto* subConductor : conductor->GetConnectedConductors())
	{
		if (!toSkip.Contains(subConductor))
		{
			VisitConductor(subConductor, toSkip);
		}
	}
}

void UElectricityEmitter::OnBeginOverlap(AActor * myOverlappedActor, AActor * otherActor)
{
	UElectricityConductor* conductor = otherActor->FindComponentByClass<UElectricityConductor>();

	if (conductor && !connectedConductors.Contains(conductor))
	{
		connectedConductors.Add(conductor);

		if (electricityParticleTemplate)
		{
			UParticleSystemComponent* ParticleTemp;
			ParticleTemp = UGameplayStatics::SpawnEmitterAtLocation
			(GetOwner(),
				electricityParticleTemplate,
				conductor->GetOwner()->GetActorLocation(),
				conductor->GetOwner()->GetActorRotation(),
				false);

			ParticleTemp->SetActorParameter(FName(TEXT("BeamSource")), GetOwner());
			ParticleTemp->SetActorParameter(FName(TEXT("BeamTarget")), conductor->GetElectricTarget());
		}
	}
}

void UElectricityEmitter::OnEndOverlap(AActor * myOverlappedActor, AActor * otherActor)
{
	UElectricityConductor* conductor = otherActor->FindComponentByClass<UElectricityConductor>();

	if (conductor)
	{
		connectedConductors.Remove(conductor);
	}
}

