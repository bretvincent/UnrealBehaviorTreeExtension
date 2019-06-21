# UnrealBehaviorTreeExtension

## Overview

An extension of Unreal Engine's Behavior Tree adding the following nodes:
* A State Machine Selector that will run whichever child state is currently active and transition to a new child state depending on the transitions set.
* A Utility Selector that will choose whichever child has the highest utility score.
* A Weighted Random Selector that will do a weighted random roll over it's children and run that child.
* An Inverter Decorator that will invert the result of it's attached task eg. Success -> Fail or Fail -> Success.

## Usage Guide

### State Machine Selector

This will allow a Selector to serve as a State Machine as long as each of it's children has a State Decorator attached to it.

< Insert picture of usage in Unreal; graph with a state machine selector and its children with blueprint state transition decorators>

* InitialStateId: This is the Id of the child to execute when first entering the selector.
* ExitStateMachineId: This is the Id reserved to allow exiting the state machine when a state sets it as its transition Id.   Otherwise, the state machine will continue running it's current state until it fails.

<insert picture of Details Panel for State Machine Selector>
  
#### State Transition Decorator

<insert picture of Details Panel for State Decorator>
  
* StateId: Every State Decorator will need to set this to a unique number amongst all the other states.
* StateToTransitionId: Each State Decorator will set which state it wants to transition to when it's transition is activated.

To create a new State Transition Decorator:
* You can either inherit from StateTransitionDecorator in C++ and override the ShouldTransition_Execute() function
```C++
/**
 * It will allow execution of it's child node if no transition has activated;
 *  if transition activated; it will transition to child node set
 */
UCLASS(Abstract)
class BEHAVIORTREEEXTENSION_API UBTStateTransitionDecorator : public UBTDecorator
{
	GENERATED_UCLASS_BODY()
public:
	/** The Id of the state to transition to when activated*/
	UPROPERTY(EditAnywhere)
	int32 StateToTransitionId;

	/* The id of this state must be unique among all children of StateMachineSelector */
	UPROPERTY(EditAnywhere)
	int32 StateId;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	bool ShouldTransition(FBehaviorTreeSearchData& SearchData);
protected:
	virtual bool ShouldTransition_Execute(FBehaviorTreeSearchData& SearchData);
private:
	virtual uint16 GetInstanceMemorySize() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;

};
 ```
* You can also inherit from StateTransitionBlueprint in the Editor and define the ShouldTransitionFromBlueprint() function in blueprint editor.
  
 ### Utility Selector
 
 This will make it so that a Selector will choose which child to execute next based off each child's utility score as long as each of it's children has a Utility Decorator.
 
 < Insert picture of usage in Unreal; graph with a Utility selector and its children with a mix of Utility Decorators>
 
 To create a new Utility Decorator you can either:
   * Inherit from Utility Decorator or any of it's derived classes in C++ and override the CalculateUtility() function which should return a number between 0 and 1.
   ```C++
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
   ```
   * Inherit from UtilityBlueprintDecorator in the Editor and define the CalculateUtilityFromBlueprint() function in blueprint editor which should return a number between 0 and 1.
 
 #### Selection Types
 
 The decision of which child gets selected depends upon the selection type chosen.
 
 <insert picture of Details Panel for Utility Selector>
  
  ##### PickHighestValue
  This will choose the child with the highest utility score.
  
  ##### SubsetWeightedRandom
  This will choose among the n highest scoring children based off the value set in SubsetChosenForWeightedRandom. Eg. SubsetChosenForWeightedRandom: 0.9; this means that only the top 90% of children will be considered, afterwards, a weighted random roll based off the remaining children's utility score will determine which child will be chosen.
  
  ##### BucketedWeightedRandom
  
  Each Utility Decorator has a BucketPriorityValue property.
  
  <insert picture of Details Panel for Utility Decorator>
  
  This value is used to place each child in different priority buckets. After each child calculates their utility score only    those among the highest bucket will be chosen to execute based off a weighted random of the children from that bucket.
  
   #### Utility Decorators

  ##### LinearUtilityDecorator
  It will calculate its utility score based off a linear function given a current value and a max value.
  
  ##### QuadraticUtilityDecorator
  It will calculate its utility score based off a quadratic function given a current value, a max value and a power value.
  
  ##### LogisticUtilityDecorator
  It will calculate its utility score based off the logistic function < insert link to logistic function in wikipedia>.
  
  ### WeightedRandomSelector
  
  This is a selector that will do a weighted random of its children depending upon the weights defined in the Selector.
  
  < Insert picture of details panel of WeightedRandomSelector>
  
  ## License
  
  This software is licensed under MIT License.
 
    
  

  
  

