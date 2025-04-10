// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

// Declare Delegate.
DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChanged, const FString&, const FString&);


/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	FCourseInfoOnChanged OnChanged;

	void FChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	UPROPERTY()
	FString Contents;

};
