// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GOAPer.h"

class AGOAPAIController;

UENUM()
enum class EGOAPFSMState : uint8
{
	Idle 	 UMETA(DisplayName = "Idle"),
	MoveTo   UMETA(DisplayName = "MoveTo"),
	DoAction UMETA(DisplayName = "DoAction")
};

class GOAPFSMState
{
public:
	GOAPFSMState() {};
	~GOAPFSMState() {};
	EGOAPFSMState eState;
	virtual TSharedPtr<GOAPFSMState> Tick(AGOAPAIController& controller, float DeltaTime) = 0;
	virtual void Enter(AGOAPAIController& controller) = 0;
	virtual FString ToString() = 0;
};

