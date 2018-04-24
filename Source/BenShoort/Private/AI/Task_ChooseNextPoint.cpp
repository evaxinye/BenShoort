// Fill out your copyright notice in the Description page of Project Settings.

#include "Task_ChooseNextPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "GameFramework/Character.h"
#include "PatrolRouteComponent.h"


EBTNodeResult::Type UTask_ChooseNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//得到 下一个地点的下标

	auto OwnerBlackBoard=OwnerComp.GetBlackboardComponent();

	auto Index=OwnerBlackBoard->GetValueAsInt(IndexKey.SelectedKeyName);
	
	//通过Index 设置下一个地点
	auto OwnerCharacter=OwnerComp.GetAIOwner()->GetCharacter();
		if (!ensure(OwnerCharacter)) { return EBTNodeResult::Failed; }

	auto patrolComp=OwnerCharacter->FindComponentByClass<UPatrolRouteComponent>();
		if (!ensure(patrolComp)) { return EBTNodeResult::Failed; }

	auto nextPoint = patrolComp->PatrolPoints[Index];
		if (!ensure(nextPoint)) { return EBTNodeResult::Failed; }
	
	OwnerBlackBoard->SetValueAsObject(WaypointKey.SelectedKeyName, nextPoint);

	//设置下一个地点的下标 , 在数组的长度内循环
	auto length=patrolComp->PatrolPoints.Num();
	auto nextIndex = (Index + 1) % length;
	OwnerBlackBoard->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	return EBTNodeResult::Succeeded;
}
