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

	inline TArray<UElectricityConductor*> GetConnectedConductors() const { return connectedConductors; }

	inline AActor* GetElectricTarget() const { return electricTarget; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerBase* triggerZone = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* electricTarget = nullptr;

	UFUNCTION() void OnBeginOverlap(AActor* myOverlappedActor, AActor* otherActor);

	UFUNCTION() void OnEndOverlap(AActor* myOverlappedActor, AActor* otherActor);

	TArray<UElectricityConductor*> connectedConductors;
};
