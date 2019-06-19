// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#include "BTStateTransitionDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTStateTransitionDecorator::UBTStateTransitionDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("State Decorator");
	bNotifyProcessed = true;

	bAllowAbortNone = false;
	bAllowAbortLowerPri = false;
	bAllowAbortChildNodes = false;
	bNotifyActivation = true;
	bNotifyTick = true;
	bTickIntervals = true;
	StateToTransitionId = 0;
}

void UBTStateTransitionDecorator::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTStateTransitionDecorator::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

bool UBTStateTransitionDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return true;
}

bool UBTStateTransitionDecorator::ShouldTransition(FBehaviorTreeSearchData& SearchData)
{
	if (ShouldTransition_Execute(SearchData))
	{
		FBTStateDecoratorMemory* StateDecoratorMemory = this->GetNodeMemory<FBTStateDecoratorMemory>(SearchData);
		StateDecoratorMemory->ChildToTransitionToId = StateToTransitionId;
		return true;
	}

	return false;
}

bool UBTStateTransitionDecorator::ShouldTransition_Execute(FBehaviorTreeSearchData& SearchData)
{
	return false;
}

uint16 UBTStateTransitionDecorator::GetInstanceMemorySize() const
{
	return sizeof(FBTStateDecoratorMemory);
}

void UBTStateTransitionDecorator::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

void UBTStateTransitionDecorator::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	
}