#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAPHICADVENTURE_UE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	void OnInteraction();

protected:
	virtual void BeginPlay() override;

	AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	AActor* NPC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	AActor* Door;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	float InteractionRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction");
	float InteractionAngle = 60.f;

	void CheckInteractionRadius(AActor& interactable, AActor& player);
	void CheckInteractionCone(AActor& interactable, AActor& player);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractionDelegate OnNpcInteraction;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractionDelegate OnDoorInteraction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractionDelegate CloseToInteractable;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void TriggerInteraction(AActor* interactable);

};
