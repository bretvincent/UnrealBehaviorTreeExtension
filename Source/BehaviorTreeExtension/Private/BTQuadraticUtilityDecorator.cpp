// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTQuadraticUtilityDecorator.h"

float UBTQuadraticUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return FMath::Pow(GetCurrentValue(OwnerComp, NodeMemory) / GetMaxValue(OwnerComp, NodeMemory),
		GetPowerValue(OwnerComp, NodeMemory));
}

float UBTQuadraticUtilityDecorator::GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 0;
}

float UBTQuadraticUtilityDecorator::GetMaxValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 1;
}

float UBTQuadraticUtilityDecorator::GetPowerValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return 2;
}
