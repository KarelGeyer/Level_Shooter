// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ClearPlayerPosition.generated.h"

/**
 *
 */
UCLASS()
class LEVELSHOOTER_API UMyBTTask_ClearPlayerPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_ClearPlayerPosition();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
