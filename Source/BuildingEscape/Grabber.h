// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

class UPhysicsHandleComponent;

#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Ray-cast and grab what's in reach
	void Grab();

	// Release what we're holding
	void Release();

	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	// Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

	// How far ahead of the player we can reach in cm
	UPROPERTY(EditAnywhere)
	float reach = 100.0f;
	
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;
};
