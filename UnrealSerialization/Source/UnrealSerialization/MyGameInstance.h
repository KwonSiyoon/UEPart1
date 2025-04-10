// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

struct FStudentData
{
	FStudentData()
	{
	}
	FStudentData(int32 InOrder, const FString& InName)
		: Order(InOrder), Name(InName)
	{
	}

	// ������ �����ε�.
	friend FArchive& operator<<(FArchive& Archive, FStudentData& InStudentData)
	{
		Archive << InStudentData.Order;
		Archive << InStudentData.Name;

		return Archive;
	}


	int32 Order = -1;
	FString Name = TEXT("ȫ�浿");
};

/**
 * 
 */
UCLASS()
class UNREALSERIALIZATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	// ��Ű�� ���� �Լ�.
	void SaveStudentPackage();

	void LoadStudentPackage();

private:
	UPROPERTY()
	TObjectPtr<class UStudent> StudentSource;
	
	// ���� �ε��� ����� FStreamableManager.
	FStreamableManager StreamableManager;

	// ���� �ε� ó���� ���� �ڵ�.
	TSharedPtr<FStreamableHandle> Handle;
};
