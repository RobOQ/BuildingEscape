// Copyright Robert O'Quinn 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

/// Look for attached InputComponent (only appears at run time)
void UGrabber::SetupInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found input component on %s"), *(GetOwner()->GetName()));
		/// Bind the input axis
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find InputComponent on %s"), *(GetOwner()->GetName()));
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;

	/// Setup query parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (aka ray-cast) out to reach distance
	FHitResult lineTraceHit;
	if (GetWorld()->LineTraceSingleByObjectType(OUT lineTraceHit, playerViewPointLocation, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParameters))
	{
		AActor* actorHit = lineTraceHit.GetActor();

		if (actorHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("LineTrace hit %s"), *(actorHit->GetName()));
		}
	}

	return lineTraceHit;
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandle)
	{
		/// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find PhysicsHandle component on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));

	/// Line trace and reach any actors with physics body collision channel set
	FHitResult lineTraceHit = GetFirstPhysicsBodyInReach();

	/// If we hit something then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	// TODO release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached, move the object that we're holding
}

