// Copyright Robert O'Quinn 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

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
	/// Setup query parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (aka ray-cast) out to reach distance
	FHitResult lineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(OUT lineTraceHit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParameters);
	return lineTraceHit;
}

FVector UGrabber::GetReachLineStart() const
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	return playerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() const
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation);

	return playerViewPointLocation + playerViewPointRotation.Vector() * reach;
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find PhysicsHandle component on %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	/// Line trace and reach any actors with physics body collision channel set
	FHitResult lineTraceHit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* componentToGrab = lineTraceHit.GetComponent();
	AActor* actorHit = lineTraceHit.GetActor();

	if (actorHit && physicsHandle)
	{
		/// If we hit something then attach a physics handle
		physicsHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	if (physicsHandle)
	{
		physicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!physicsHandle)
	{
		return;
	}

	// If the physics handle is attached
	if (physicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

