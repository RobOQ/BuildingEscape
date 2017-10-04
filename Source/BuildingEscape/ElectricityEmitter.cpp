// Copyright Robert O'Quinn 2017

#include "ElectricityEmitter.h"
#include "ElectricityConductor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerSphere.h"

#define OUT

// Sets default values for this component's properties
UElectricityEmitter::UElectricityEmitter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UElectricityEmitter::BeginPlay()
{
	Super::BeginPlay();

	if (!triggerSphere)
	{
		UE_LOG(LogTemp, Error, TEXT("ElectricityEmitter %s does not have a TriggerSphere assigned"), *(GetOwner()->GetName()));
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

	timeSinceLastShock += DeltaTime;

	if (timeSinceLastShock > shockDelay)
	{
		// Find all overlapping actors
		TArray<AActor*> overlappingActors;
		triggerSphere->GetOverlappingActors(OUT overlappingActors);

		// Iterate through them adding their masses
		for (const auto* actor : overlappingActors)
		{
			UElectricityConductor* electricityConductor = actor->FindComponentByClass<UElectricityConductor>();

			if (electricityConductor)
			{
				UE_LOG(LogTemp, Warning, TEXT("ElectricityEmitter %s applying shock to %s"), *GetOwner()->GetName(), *actor->GetName());
				electricityConductor->ReceiveShock();
			}
		}

		timeSinceLastShock = 0.0f;
	}
}

