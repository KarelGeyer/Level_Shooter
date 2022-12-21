// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BT_Tasks/MyBTTask_ClearPlayerPosition.h"
#include "BehaviorTree/BlackboardComponent.h"


UMyBTTask_ClearPlayerPosition::UMyBTTask_ClearPlayerPosition()
{
	NodeName = TEXT("Clear Player Position");
}

EBTNodeResult::Type UMyBTTask_ClearPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
