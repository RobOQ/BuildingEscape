// Copyright Robert O'Quinn 2017

#include "ElectricDoorOpener.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UElectricDoorOpener::UElectricDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UElectricDoorOpener::BeginPlay()
{
	Super::BeginPlay();

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
void UElectricDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	timeSinceLastPowered += DeltaTime;

	if (!openDoorComponent)
	{
		return;
	}

	if(timeSinceLastPowered > closeDelay)
	{
		openDoorComponent->OnClose.Broadcast();
	}
}

void UElectricDoorOpener::ApplyPower()
{
	timeSinceLastPowered = 0.0f;

	if (!openDoorComponent)
	{
		return;
	}

	openDoorComponent->OnOpen.Broadcast();
}

