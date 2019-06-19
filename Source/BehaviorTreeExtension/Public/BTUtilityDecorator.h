// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTUtilityDecorator.generated.h"

/**
 * The base class for all Utility Decorator's that will be used by UtilitySelector to return a 
 * utility value
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTUtilityDecorator : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
public:
	/** The Higher the value the greater the priority for this action*/
	UPROPERTY(EditAnywhere)
	int32 BucketPriorityValue;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
