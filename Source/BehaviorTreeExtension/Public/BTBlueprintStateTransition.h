// // Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTStateTransitionDecorator.h"
#include "BTBlueprintStateTransition.generated.h"

/**
 * A State Transition that is defined in blueprints
 */
UCLASS(Abstract, Blueprintable)
class BEHAVIORTREEEXTENSION_API UBTBlueprintStateTransition : public UBTStateTransitionDecorator
{
	GENERATED_UCLASS_BODY()
	virtual bool ShouldTransition_Execute(FBehaviorTreeSearchData& SearchData) override;

	/** Has transition activated*/
	UFUNCTION(BlueprintImplementableEvent)
	bool ShouldTransitionFromBlueprint(AAIController* AIController) const;

#if WITH_EDITOR
	virtual bool UsesBlueprint() const override;
#endif
};
