// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#include <BTTask_Log.h>
#include "Engine/Engine.h"

void UBTTask_Log::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UBTTask_Log::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UBTTask_Log::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue,
			FString::Printf(TEXT("%s"), *Message));
	}		
	UE_LOG(LogBehaviorTree, Display, TEXT("%s"), *Message);

	return EBTNodeResult::Succeeded;
}
