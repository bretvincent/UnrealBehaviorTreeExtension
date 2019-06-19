// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTLinearUtilityDecorator.h"

float UBTLinearUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return GetCurrentValue(OwnerComp, NodeMemory) / GetMaxValue(OwnerComp, NodeMemory);
}

float UBTLinearUtilityDecorator::GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 0;
}

float UBTLinearUtilityDecorator::GetMaxValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 1.0f;
}
