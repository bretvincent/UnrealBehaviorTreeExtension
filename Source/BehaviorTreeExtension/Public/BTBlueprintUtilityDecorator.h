// Copyright 2019 Vincent Breton Kochanowski. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUtilityDecorator.h"
#include "BTBlueprintUtilityDecorator.generated.h"

/**
 * Utility Decorator allowing one to implement your own Utility function in Blueprints
 */
UCLASS(Abstract, Blueprintable)
class BEHAVIORTREEEXTENSION_API UBTBlueprintUtilityDecorator : public UBTUtilityDecorator
{
public:
	GENERATED_UCLASS_BODY()
	virtual float CalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

#if WITH_EDITOR
	virtual bool UsesBlueprint() const override;
#endif

	/** Value returned must be between 0 and 1*/
	UFUNCTION(BlueprintImplementableEvent)
	float CalculateUtilityFromBlueprint(AAIController* AIController) const;
};
