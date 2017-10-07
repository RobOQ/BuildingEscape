// Copyright Robert O'Quinn 2017

#include "ElectricityConductor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBase.h"

#define OUT

// Sets default values for this component's properties
UElectricityConductor::UElectricityConductor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UElectricityConductor::BeginPlay()
{
	Super::BeginPlay();

	if (!triggerZone)
	{
		UE_LOG(LogTemp, Error, TEXT("ElectricityConductor %s does not have a trigger zone assigned"), *GetOwner()->GetName());
	}
	else
	{
		triggerZone->OnActorBeginOverlap.AddDynamic(this, &UElectricityConductor::OnBeginOverlap);
		triggerZone->OnActorEndOverlap.AddDynamic(this, &UElectricityConductor::OnEndOverlap);

		// Find all overlapping actors
		TArray<AActor*> overlappingActors;
		triggerZone->GetOverlappingActors(OUT overlappingActors);

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

	if (!electricTarget)
	{
		UE_LOG(LogTemp, Error, TEXT("ElectricityConductor %s does not have an electric target assigned"), *GetOwner()->GetName());
	}
}

// Called every frame
void UElectricityConductor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UElectricityConductor::OnBeginOverlap(AActor * myOverlappedActor, AActor * otherActor)
{
	UElectricityConductor* conductor = otherActor->FindComponentByClass<UElectricityConductor>();

	if (conductor && !connectedConductors.Contains(conductor))
	{
		connectedConductors.Add(conductor);
	}
}

void UElectricityConductor::OnEndOverlap(AActor * myOverlappedActor, AActor * otherActor)
{
	UElectricityConductor* conductor = otherActor->FindComponentByClass<UElectricityConductor>();

	if (conductor)
	{
		connectedConductors.Remove(conductor);
	}
}

