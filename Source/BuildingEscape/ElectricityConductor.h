// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElectricityConductor.generated.h"

class ATriggerBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UElectricityConductor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElectricityConductor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReceiveShock();

	void TransmitShock();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerBase* triggerZone;

	UPROPERTY(EditAnywhere)
	float transmissionDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float powerDownDelay = 1.25f;
	
	float timeSinceLastShock = 0.0f;

	float timeSinceLastTransmission = 0.0f;
};
