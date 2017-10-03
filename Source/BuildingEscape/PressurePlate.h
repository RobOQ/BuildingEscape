// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PressurePlate.generated.h"

class ATriggerVolume;
class UOpenDoor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPressurePlate();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* triggerVolume = nullptr;

	UPROPERTY(EditAnywhere)
	float triggerMass = 50.0f;
	
	UPROPERTY(EditAnywhere)
	AActor* doorToOpen = nullptr;

	UFUNCTION() void OnOverlap(AActor* myOverlappedActor, AActor* otherActor);

	UOpenDoor* openDoorComponent = nullptr;

	float GetTotalMassOfActorsOnPlate();
};
