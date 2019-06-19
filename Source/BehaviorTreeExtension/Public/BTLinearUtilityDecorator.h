// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUtilityDecorator.h"
#include "BTLinearUtilityDecorator.generated.h"

/**
 * Utility Decorator that will calculate utility as a linear function of current value
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTLinearUtilityDecorator : public UBTUtilityDecorator
{
public:
	virtual float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual float GetCurrentValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	virtual float GetMaxValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
private:
	GENERATED_BODY()
	
};
