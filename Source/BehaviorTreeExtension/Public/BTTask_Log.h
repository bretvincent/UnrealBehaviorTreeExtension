// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Log.generated.h"

/**
 * Logs a message to console when Node is executed
 */
UCLASS()
class BEHAVIORTREEEXTENSION_API UBTTask_Log : public UBTTaskNode
{
	GENERATED_BODY()

public:
	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Message to display to screen and log */
	UPROPERTY(EditAnywhere)
	FString Message;

};
