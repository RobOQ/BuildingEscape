// Copyright Robert O'Quinn 2017

#include "PressurePlate.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UPressurePlate::UPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	if (!triggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("Door %s does not have a pressure plate TriggerVolume assigned"), *(GetOwner()->GetName()));
	}

	if (!doorToOpen)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure plate %s does not have a door assigned to open"), *(GetOwner()->GetName()));
	}
	else
	{
		openDoorComponent = doorToOpen->FindComponentByClass<UOpenDoor>();
	}
}


// Called every frame
void UPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!openDoorComponent)
	{
		return;
	}

	// TODO: This should not be in TickComponent, figure out to to hook this up to OnOverlap start/end.
	if (GetTotalMassOfActorsOnPlate() > triggerMass)
	{
		openDoorComponent->OnOpen.Broadcast();
	}
	else
	{
		openDoorComponent-> OnClose.Broadcast();
	}
}

float UPressurePlate::GetTotalMassOfActorsOnPlate()
{
	if (!triggerVolume)
	{
		return 0.0f;
	}

	float totalMass = 0.0f;

	// Find all overlapping actors
	TArray<AActor*> overlappingActors;
	triggerVolume->GetOverlappingActors(OUT overlappingActors);

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

