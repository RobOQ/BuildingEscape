// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

private:
	UPROPERTY(VisibleAnywhere)
	float openAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.0f;

	UPROPERTY(EditAnywhere)
	float triggerMass = 50.0f;

	float lastDoorOpenTime;

	AActor* owner = nullptr;

	float GetTotalMassOfActorsOnPlate();
};
