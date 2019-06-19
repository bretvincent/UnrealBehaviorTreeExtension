// // Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#include "BTBlueprintStateTransition.h"

UBTBlueprintStateTransition::UBTBlueprintStateTransition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("BlueprintStateTransitionDecorator");
	bCreateNodeInstance = true;
}

bool UBTBlueprintStateTransition::ShouldTransition_Execute(FBehaviorTreeSearchData& SearchData)
{
	AAIController* AIController = SearchData.OwnerComp.GetAIOwner();
	return ShouldTransitionFromBlueprint(AIController);
}

#if WITH_EDITOR
bool UBTBlueprintStateTransition::UsesBlueprint() const
{
	return true;
}
#endif // WITH_EDITOR
