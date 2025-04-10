// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	// 기본값 설정.
	Contents = TEXT("기본 학사 정보");
}

void UCourseInfo::FChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	// 콘텐츠 업데이트.
	Contents = InNewContents;

	// 발행.
	UE_LOG(LogTemp, Log, TEXT("[CourseInfo] 학사 정보가 변경되어 알림을 발송합니다."));
	OnChanged.Broadcast(InSchoolName, InNewContents);
}
