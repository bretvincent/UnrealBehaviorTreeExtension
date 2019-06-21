# UnrealBehaviorTreeExtension

## Overview

An extension of Unreal Engine's Behavior Tree adding the following nodes:
* An State Machine Selector that will run whichever child state is currently active and transition to new child state depending on the transitions set.
* A Utility Selector that will choose whichever child has the greatest utility at that moment.
* A Weighted Random Selector that will do a weighted random roll over it's children and run that child
* An Inverter Decorator that will invert the result of it's attached task eg. Success -> Fail or Fail -> Success.

## Usage Guide

### State Machine Selector

This will allow a Selector to serve as a State Machine as long as each of it's children has a State Decorator attached to it.

< Insert picture of usage in Unreal; graph with a state machine selector and its children with blueprint state transition decorators>
* InitialStateId: This will be the Id of the child to execute when first entering the selector
* ExitStateMachineId: This will be an Id reserved to allow exiting the state machine when a state sets it as its transition
<insert picture of Details Panel for State Machine Selector>
  
#### State Transition Decorator

<insert picture of Details Panel for State Decorator>
  
* StateId: Every State Decorator will need to set this to a unique number among all the other states.
* StateToTransitionId: Each State Decorator will set which state it wants to transition to when it's transition is activated.

To create a new State Transition Decorator:
* You can either inherit from StateTransitionDecorator in C++ and override the ShouldTransition_Execute() function
<insert header file of StateTransitionDecorator>
*  You can also inherit from StateTransitionBlueprint in Blueprints and define the ShouldTransitionFromBlueprint() function in blueprint editor.
  
 ### Utility Selector
 
 This will make it so that a Selector will choose which child to execute next based off each child's utility score as long as each of it's children has a Utility Decorator attached.
 
 < Insert picture of usage in Unreal; graph with a Utility selector and its children with a mix of Utility Decorators>
 
 To create a new Utility Decorator you can either:
   * Inherit from Utility Decorator or any of it's derived classes in C++ and override the CalculateUtility function.
   <insert header file of UtilityDecorator>
   * Inherit from UtilityBlueprintDecorator in Blueprints and define the CalculateUtilityFromBlueprint() function in blueprint editor.
 
 #### Selection Types
 
 The choice of how each child gets selected depending upon the selection type chosen under SelectionType:
 
 <insert picture of Details Panel for Utility Selector>
  
  * PickHighestValue
  This will just return the child with the highest utility score.
  
  * SubsetWeightedRandom
  This will choose among the n highest scoring children based off the value set in SubsetChosenForWeightedRandom. Eg. SubsetChosenForWeightedRandom: 0.9; this means that only the top 90% of actions will be considered and then a weighted random roll based off their utility score will determine which child will be selected
  
  * BucketedWeightedRandom
  
  Each Utility Decorator has a BucketPriorityValue property.
  
  <insert picture of Details Panel for Utility Decorator>
  
  This value is used to place each child in different priority buckets. After each child calculates their utility score only    those among the highest bucket will be chosen to execute based off a weighted random of the children from that bucket.
  
   #### Utility Decorators
    
    You can also choose from among the following Utility Decorator classes that will apply a mathematical function to determine your utility score.
  * LinearUtilityDecorator: this will calculate utility score based off a linear function given a current value and a max value.
  * QuadraticUtilityDecorator: this will calculate utility score based off a quadratic function given a current value, a max value and a power value.
  * LogisticUtilityDecorator: this will calculate utility score based off the logistic function < insert link to logistic function in wikipedia>.
  
  ### WeightedRandomSelector
  
  This is a selector that will do a weighted random of its children depending upon the weights defined in the Selector.
  
  < Insert picture of details panel of WeightedRandomSelector>
  
  ## License
  
  This software is licensed under MIT License.
 
    
  

  
  

