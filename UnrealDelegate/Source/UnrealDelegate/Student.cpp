// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("장학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s님이 수업을 듣습니다."), *Name);
}

// 딜리게이트에 등록할 함수.
void UStudent::GetNotification(const FString& InSchool, const FString& InNewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s님이 %s로부터 받은 메시지: %s"), *Name, *InSchool, *InNewCourseInfo);
}
