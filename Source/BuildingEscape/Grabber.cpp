// Copyright Robert O'Quinn 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString());

	// Draw a red trace in the world to visualize
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;

	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 10.0f);


	// Ray-cast out to reach distance

	// See what we hit
}

