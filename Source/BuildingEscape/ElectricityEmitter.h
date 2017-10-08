// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElectricityEmitter.generated.h"

class ATriggerSphere;
class UElectricityConductor;
class UParticleSystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UElectricityEmitter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElectricityEmitter();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	ATriggerSphere* triggerSphere = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* electricityParticleTemplate = nullptr;

	void VisitConductor(UElectricityConductor* conductor, TArray<UElectricityConductor*>& toSkip);

	void AddBeam(UElectricityConductor* conductor);
	void DeactivateBeam(AActor* otherActor);

	UFUNCTION() void OnBeginOverlap(AActor* myOverlappedActor, AActor* otherActor);

	UFUNCTION() void OnEndOverlap(AActor* myOverlappedActor, AActor* otherActor);

	TArray<UElectricityConductor*> connectedConductors;
	TArray<UParticleSystemComponent*> activeBeams;
	TArray<UParticleSystemComponent*> inactiveBeams;
};
