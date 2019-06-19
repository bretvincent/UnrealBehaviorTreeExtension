// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTUtilityDecorator.h"

UBTUtilityDecorator::UBTUtilityDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "UtilityDecorator";
}

void UBTUtilityDecorator::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTUtilityDecorator::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

bool UBTUtilityDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return true;
}

float UBTUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 0;
}
