// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTWeightedRandomSelector.h"

void UBTWeightedRandomSelector::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTWeightedRandomSelector::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

UBTWeightedRandomSelector::UBTWeightedRandomSelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "WeightedRandomSelector";
}

int32 UBTWeightedRandomSelector::WeightedRandomRoll() const
{
	if (Weights.Num() <= 0 || Weights.Num() != GetChildrenNum())
	{
		// no weights defined return first child
		ensureMsgf(true, TEXT("No Weights defined or number of weights does not equal number of children!"));
		return 0;
	}

	int32 SumWeight = 0;
	for (int32 Weight : Weights)
	{
		SumWeight += Weight;
	}

	ensureMsgf(SumWeight > 0, TEXT("Weights are negative they must be greater than 0"));

	int32 RandomNumber = FMath::RandRange(0, SumWeight);

	for (auto i = 0; i < Weights.Num(); ++i)
	{
		if (RandomNumber < Weights[i])
		{
			return i;
		}
		RandomNumber -= Weights[i];
	}

	// shouldn't get here
	return 0;
}

int32 UBTWeightedRandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	// success = quit
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// newly activated: randomly choose one
		NextChildIdx = WeightedRandomRoll();
	}
	else if (LastResult == EBTNodeResult::Failed)
	{
		// failed = choose next child
		NextChildIdx = WeightedRandomRoll();
	}

	return NextChildIdx;
}

#if WITH_EDITOR

FName UBTWeightedRandomSelector::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Composite.Selector.Icon");
}

#endif
