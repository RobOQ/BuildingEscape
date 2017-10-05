// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElectricDoorOpener.generated.h"

class UOpenDoor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UElectricDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElectricDoorOpener();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyPower();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	AActor* doorToOpen = nullptr;

	UPROPERTY(EditAnywhere)
	float closeDelay = 0.5f;

	UOpenDoor* openDoorComponent = nullptr;

	float timeSinceLastPowered = 0.0f;
};
