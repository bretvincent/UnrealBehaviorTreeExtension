// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "CoreMinimal.h"
#include "BTUtilitySelector.generated.h"

USTRUCT()
struct FBTUtilityChild
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		int32 ChildIndex;
	UPROPERTY()
		float Value;
	UPROPERTY()
		int32 PriorityValue;
};

struct FBTUtilitySelectorMemory : public FBTCompositeMemory
{
	UPROPERTY()
	TArray<FBTUtilityChild> Utility;
};

UENUM()
enum class EActionSelectionType
{
	PickHighestValue, // just picks action with highest utility value
	SubsetWeightedRandom, // will do a weighted random using utility values based off the x% eg. top 80%
	BucketedWeightedRandom // each action belongs to a bucket and buckets with higher priority are executed first; 
							// if there is multiple actions with same priority there will be a weighted random among those
};
/**
 * A selector that will execute its children based off their utility score (a value between 0 and 1)
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTUtilitySelector : public UBTCompositeNode
{
	GENERATED_UCLASS_BODY()

public:

	/* The method to use to decide which child gets executed after calculating their utility scores */
	UPROPERTY(EditAnywhere)
	EActionSelectionType SelectionType;

	/** Which percentage of actions should be considered eg. 0.8f will only picks the top 80th percentile actions dropping the last 20th percentile actions*/
	UPROPERTY(EditAnywhere)
	float SubsetChosenForWeightedRandom;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	int32 FindNextChildToExecute(const TArray<FBTUtilityChild>& Utility) const;
	void CalculateUtilityScores(FBehaviorTreeSearchData& SearchData, FBTUtilitySelectorMemory* Memory) const;
	int32 WeightedRandom(const TArray<FBTUtilityChild>& Array) const;
	int32 SubsetWeightedRandom(const TArray<FBTUtilityChild>& Utility) const;
	int32 BucketedWeightedRandom(const TArray<FBTUtilityChild>& Utility) const;
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const override;
	virtual uint16 GetInstanceMemorySize() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};
