// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUtilityDecorator.h"
#include "BTLogisticUtilityDecorator.generated.h"

/**
 * Utility Decorator that will calculate utility value based off the logistic function
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTLogisticUtilityDecorator : public UBTUtilityDecorator
{
public:
	virtual float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual float GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	GENERATED_BODY()
	
};
