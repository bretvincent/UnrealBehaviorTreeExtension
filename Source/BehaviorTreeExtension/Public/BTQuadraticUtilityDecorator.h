// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUtilityDecorator.h"
#include "BTQuadraticUtilityDecorator.generated.h"

/**
 * Utility Decorator that will calculate utility based off the quadratic function
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTQuadraticUtilityDecorator : public UBTUtilityDecorator
{
public:
	virtual float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual float GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	virtual float GetMaxValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	virtual float GetPowerValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	GENERATED_BODY()
	
};
