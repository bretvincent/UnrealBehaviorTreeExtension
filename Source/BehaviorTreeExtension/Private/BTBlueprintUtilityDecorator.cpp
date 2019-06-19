// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.


#include "BTBlueprintUtilityDecorator.h"
#include "AIController.h"

UBTBlueprintUtilityDecorator::UBTBlueprintUtilityDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("BlueprintUtilityDecorator");
	bCreateNodeInstance = true;
}

float UBTBlueprintUtilityDecorator::CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	return CalculateUtilityFromBlueprint(AIController);
}

#if WITH_EDITOR
bool UBTBlueprintUtilityDecorator::UsesBlueprint() const
{
	return true;
}
#endif // WITH_EDITOR