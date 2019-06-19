// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#include "BTStateMachineSelector.h"
#include "BTStateTransitionDecorator.h"

void UBTStateMachineSelector::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTStateMachineSelector::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

UBTStateMachineSelector::UBTStateMachineSelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), 
	InitialStateId(0), ExitStateMachineId(0)
{
	NodeName = "StateMachineSelector";
}

int32 UBTStateMachineSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// go to initial state of state machine
		return FindChildIndexFromStateId(InitialStateId);
	}

	// if we failed we exit state machine
	if (LastResult == EBTNodeResult::Failed)
	{
		return BTSpecialChild::ReturnToParent;
	}

	return ShouldTransition(SearchData, PrevChild);
}

int32 UBTStateMachineSelector::FindChildIndexFromStateId(int32 StateId) const
{
	if (StateId == ExitStateMachineId)
	{
		return BTSpecialChild::ReturnToParent;
	}

	for (int i = 0; i < Children.Num(); ++i)
	{
		auto const& ChildInfo = Children[i];
		for (auto Decorator : ChildInfo.Decorators)
		{
			const auto StateTransitionDecorator = Cast<UBTStateTransitionDecorator>(Decorator);
			if (StateTransitionDecorator)
			{
				if (StateTransitionDecorator->StateId == StateId)
				{
					return i;
				}
			}
		}
	}

	UE_LOG(LogBehaviorTree, Error, TEXT("No State with Id: %d found!"), StateId);
	return 0;
}

int32 UBTStateMachineSelector::ShouldTransition(FBehaviorTreeSearchData& SearchData, int32 ChildIndex) const
{
	if (ChildIndex < 0 || ChildIndex > Children.Num())
	{
		// no children means that something went wrong
		return BTSpecialChild::ReturnToParent;
	}

	auto const& ChildInfo = Children[ChildIndex];
	for (auto Decorator : ChildInfo.Decorators)
	{
		const auto StateTransitionDecorator = Cast<UBTStateTransitionDecorator>(Decorator);
		if (StateTransitionDecorator)
		{		
			// search if any transitions have activated; will return first one found
			if (StateTransitionDecorator->ShouldTransition(SearchData))
			{
				const auto StateDecoratorMemory = StateTransitionDecorator->GetNodeMemory<FBTStateDecoratorMemory>(SearchData);
				int32 childId = StateDecoratorMemory->ChildToTransitionToId;
				return FindChildIndexFromStateId(childId);
			}
		}
	}

	// if no transitions have activated; just continue executing node
	return ChildIndex;
}
#if WITH_EDITOR
FName UBTStateMachineSelector::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Composite.Selector.Icon");
}
#endif
