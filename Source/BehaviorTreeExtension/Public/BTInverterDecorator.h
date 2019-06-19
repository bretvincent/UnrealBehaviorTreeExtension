// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BTInverterDecorator.generated.h"

class UGameplayTask;
/**
 * This Decorator will reverse the result of it's child node: Success -> Fail; Fail -> Success
 */
UCLASS(HideCategories = (Condition))
class BEHAVIORTREEEXTENSION_API UBTInverterDecorator : public UBTDecorator
{

public:
	GENERATED_UCLASS_BODY()

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void OnNodeProcessed(struct FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) override;
};
