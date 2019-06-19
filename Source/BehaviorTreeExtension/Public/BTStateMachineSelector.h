// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTStateTransitionDecorator.h"
#include "BTStateMachineSelector.generated.h"

/**
 * Represents a state machine that will execute whatever child is currently set as the active state
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTStateMachineSelector : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

	/** The State Id to begin at when first entering state machine */
	UPROPERTY(EditAnywhere)
	int32 InitialStateId;

	/* Special Id to be used to exit state machine and return to parent must be unique among state id's*/
	UPROPERTY(EditAnywhere)
	int32 ExitStateMachineId;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
	int32 FindChildIndexFromStateId(int32 StateId) const;
	int32 ShouldTransition(FBehaviorTreeSearchData& SearchData, int32 ChildIndex) const;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif

};
