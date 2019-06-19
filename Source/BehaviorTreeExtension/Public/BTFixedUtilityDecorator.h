// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUtilityDecorator.h"
#include "BTFixedUtilityDecorator.generated.h"

/**
 * Utility Decorator that will return whatever is set as it's utility value
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTFixedUtilityDecorator : public UBTUtilityDecorator
{
public:
	float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	/** Utility value: must be between 0 and 1 */
	UPROPERTY(EditAnywhere)
		float Utility;
private:
	GENERATED_BODY()
	
};
