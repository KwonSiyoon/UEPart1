// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"




UMyGameInstance::UMyGameInstance()
{
	// 기본 값 설정.
	// CDO(Class Default Object).
	// 엔진이 켜지기 전에 정보를 저장함.
	// 엔진을 키고 정보를 바꿨다면 다시 껐다켜야 CDO정보가 업데이트 되고 적용됨.
	// 템플릿 클래스 객체.
	SchoolName = TEXT("원티드스쿨");
}




void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("============================="));

	//// 객체 생성.
	//TArray<UPerson*> Persons =
	//{
	//	NewObject<UStudent>(),
	//	NewObject<UTeacher>(),
	//	NewObject<UStaff>()
	//};
	//// 이름 출력.
	//for (const auto Person : Persons)
	//{
	//	// 인터페이스 구현 영부 확인.
	//	ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
	//	if (LessonInterface)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여 가능합니다."), *Person->GetName());
	//		LessonInterface->DoLesson();
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여 불가능합니다."), *Person->GetName());
	//	}
	//	
	//	// 카드 정보 출력.
	//	const UCard* OwnCard = Person->GetCard();
	//	ensure(OwnCard);
	//	UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류: %d"), *Person->GetName(), OwnCard->GetCardType());
	//	
	//	const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType"));
	//	if (CardEnumType)
	//	{
	//		FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)OwnCard->GetCardType()).ToString();
	//		UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류: %s"), *Person->GetName(), *CardMetaData);
	//		
	//	}
	//}
	

	// 학사 정보 객체 생성.
	CourseInfo = NewObject<UCourseInfo>(this);

	// 학생 객체 생성.
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));
	
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// 구독할 함수 등록.
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	// 발행.
	CourseInfo->FChangeCourseInfo(SchoolName, TEXT("새로운 학사 정보"));

	
	UE_LOG(LogTemp, Log, TEXT("============================="));
}
