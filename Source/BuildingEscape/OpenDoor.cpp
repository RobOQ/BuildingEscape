// Copyright Robert O'Quinn 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > triggerMass)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if(GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.0f;

	// Find all overlapping actors
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	// Iterate through them adding their masses
	for (const auto* actor : overlappingActors)
	{
		UPrimitiveComponent* primitiveComp = actor->FindComponentByClass<UPrimitiveComponent>();
		if (primitiveComp)
		{
			totalMass += primitiveComp->GetMass();
		}
	}

	return totalMass;
}

