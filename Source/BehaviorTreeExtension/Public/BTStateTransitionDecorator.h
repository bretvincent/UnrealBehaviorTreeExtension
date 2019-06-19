// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTStateTransitionDecorator.generated.h"

struct FBTStateDecoratorMemory : public FBTAuxiliaryMemory
{
	// the id of the child to transition to
	int32 ChildToTransitionToId;
};


/**
 * It will allow execution of it's child node if no transition has activated;
 *  if transition activated; it will transition to child node set
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTStateTransitionDecorator : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
public:
	/** The Id of the state to transition to when activated*/
	UPROPERTY(EditAnywhere)
	int32 StateToTransitionId;

	/* The id of this state must be unique among all children of StateMachineSelector */
	UPROPERTY(EditAnywhere)
	int32 StateId;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	bool ShouldTransition(FBehaviorTreeSearchData& SearchData);
protected:
	virtual bool ShouldTransition_Execute(FBehaviorTreeSearchData& SearchData);
private:
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;

};
