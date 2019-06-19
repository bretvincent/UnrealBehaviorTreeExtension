// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTWeightedRandomSelector.generated.h"

/**
 * Selector that picks which child to execute based off a weighted random roll from the weights given
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTWeightedRandomSelector : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

	/* The weights to be applied to each child from left to right */
	UPROPERTY(EditAnywhere)
	TArray<int32> Weights;

public:
	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	int32 WeightedRandomRoll() const;
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif

};
