// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTInverterDecorator.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

UBTInverterDecorator::UBTInverterDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("Inverter");
	bNotifyProcessed = true;

	bAllowAbortNone = false;
	bAllowAbortLowerPri = false;
	bAllowAbortChildNodes = false;
}

void UBTInverterDecorator::OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult)
{
	switch (NodeResult) 
	{ 
		case EBTNodeResult::Succeeded:
			NodeResult = EBTNodeResult::Failed;
		break;
		case EBTNodeResult::Failed:
			NodeResult = EBTNodeResult::Succeeded;
		break;
	}
}

void UBTInverterDecorator::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTInverterDecorator::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}
