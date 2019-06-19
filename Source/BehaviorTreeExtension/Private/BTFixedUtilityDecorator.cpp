// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTFixedUtilityDecorator.h"

float UBTFixedUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return Utility;
}
