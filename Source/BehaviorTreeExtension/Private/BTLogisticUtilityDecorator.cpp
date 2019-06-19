// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTLogisticUtilityDecorator.h"

float UBTLogisticUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 1 / (1 + FMath::Exp(GetCurrentValue(OwnerComp, NodeMemory)));
}

float UBTLogisticUtilityDecorator::GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 0;
}
