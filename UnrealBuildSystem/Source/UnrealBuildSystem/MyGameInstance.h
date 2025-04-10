// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Person.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBUILDSYSTEM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void virtual Init() override;

private:
	UPROPERTY()
	TObjectPtr<UPerson> Person;
	
};
