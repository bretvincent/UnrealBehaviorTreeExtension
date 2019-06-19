// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTUtilitySelector.h"
#include "BTUtilityDecorator.h"

UBTUtilitySelector::UBTUtilitySelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "UtilitySelector";
}

void UBTUtilitySelector::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTUtilitySelector::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

int32 UBTUtilitySelector::FindNextChildToExecute(const TArray<FBTUtilityChild>& Utility) const
{
	switch (SelectionType)
	{
		case EActionSelectionType::PickHighestValue:
			if (Utility.Num() > 0)
			{
				return Utility[0].ChildIndex;
			}		
		case EActionSelectionType::SubsetWeightedRandom:
			return SubsetWeightedRandom(Utility);
		case EActionSelectionType::BucketedWeightedRandom:
			return BucketedWeightedRandom(Utility);
	}

	return 0;
}

void UBTUtilitySelector::CalculateUtilityScores(FBehaviorTreeSearchData& SearchData, FBTUtilitySelectorMemory* Memory) const
{
	Memory->Utility = TArray<FBTUtilityChild>();

	for (auto i = 0; i < Children.Num(); ++i)
	{
		FBTUtilityChild ChildUtility;
		ChildUtility.ChildIndex = i;
		Memory->Utility.Add(ChildUtility);

		auto const& ChildInfo = Children[i];

		for (auto Decorator : ChildInfo.Decorators)
		{
			const auto UtilityDecorator = Cast<UBTUtilityDecorator>(Decorator);
			if (UtilityDecorator)
			{
				Memory->Utility[i].Value = UtilityDecorator->CalculateUtility(SearchData.OwnerComp,
				                                                              UtilityDecorator->GetNodeMemory<uint8>(SearchData));
				Memory->Utility[i].PriorityValue = UtilityDecorator->BucketPriorityValue;
			}
		}
	}

	Memory->Utility.Sort([](const FBTUtilityChild& A, const FBTUtilityChild& B) {
		return A.Value > B.Value;
	});
}

int32 UBTUtilitySelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild,	EBTNodeResult::Type LastResult) const
{
	auto Memory = this->GetNodeMemory<FBTUtilitySelectorMemory>(SearchData);

	// we successfully executed the highest priority action
	if (LastResult == EBTNodeResult::Succeeded && PrevChild != BTSpecialChild::NotInitialized)
	{
		// empty array since we will re-calculate next time around
		Memory->Utility.Empty();

		return BTSpecialChild::ReturnToParent;
	}

	// we failed let's try next highest child
	if (LastResult == EBTNodeResult::Failed && PrevChild != BTSpecialChild::NotInitialized)
	{
		// we must have failed on all children
		if (Memory->Utility.Num() <= 0)
		{
			return BTSpecialChild::ReturnToParent;
		}

		for (auto i = 0; i < Memory->Utility.Num(); ++i)
		{
			if (Memory->Utility[i].ChildIndex == PrevChild)
			{
				// remove from consideration
				Memory->Utility.RemoveAt(i);
				return FindNextChildToExecute(Memory->Utility);
			}
		}
	}

	// first time in selector; get all utility scores
	if (Memory->Utility.Num() <= 0)
	{
		CalculateUtilityScores(SearchData, Memory);
		return FindNextChildToExecute(Memory->Utility);		
	}

	// we shouldn't get here
	return 0;
}

int32 UBTUtilitySelector::SubsetWeightedRandom(const TArray<FBTUtilityChild>& Utility) const
{
	TArray<FBTUtilityChild> SubsetArray;
	const int NewCount = Utility.Num() * SubsetChosenForWeightedRandom;

	ensureMsgf(NewCount <= Utility.Num(), TEXT("Subset chosen must be between 0 and 1"));

	for (auto i = 0; i < NewCount; ++i)
	{
		SubsetArray.Add(Utility[i]);
	}

	return WeightedRandom(SubsetArray);
}

int32 UBTUtilitySelector::WeightedRandom(const TArray<FBTUtilityChild>& Array) const
{
	float Sum = 0;
	for (auto i = 0; i < Array.Num(); ++i)
	{
		Sum += Array[i].Value;
	}

	const auto Roll = FMath::RandRange(0.0f, Sum);

	auto Value = 0.0f;
	for (auto i = 0; i < Array.Num(); ++i)
	{
		Value += Array[i].Value;
		if (Value >= Roll)
		{
			return Array[i].ChildIndex;
		}
	}

	// it's impossible to get here unless the utility values were negative
	ensureMsgf(true, TEXT("Negative Utility Values!"));

	// just return first child
	return 0;
}

int32 UBTUtilitySelector::BucketedWeightedRandom(const TArray<FBTUtilityChild>& Utility) const
{
	TMap<int32, TArray<FBTUtilityChild>> BucketMap;

	// fill map
	for (FBTUtilityChild Child : Utility)
	{
		if (!BucketMap.Contains(Child.PriorityValue))
		{
			// create new array to hold children
			TArray<FBTUtilityChild> Array;
			Array.Add(Child);
			BucketMap.Add(Child.PriorityValue, Array);
		}
		else
		{
			BucketMap[Child.PriorityValue].Add(Child);
		}		
	}

	// sort by priority value
	BucketMap.KeySort([](const int32& A, const int32& B) {
		return A > B;
	});

	for (const auto& Element : BucketMap)
	{
		// first one here is highest bucket
		return WeightedRandom(Element.Value);
	}

	// it shouldn't get here normally
	return 0;
}


uint16 UBTUtilitySelector::GetInstanceMemorySize() const
{
	return sizeof(FBTUtilitySelectorMemory);
}

#if WITH_EDITOR
FName UBTUtilitySelector::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Composite.Selector.Icon");
}
#endif
