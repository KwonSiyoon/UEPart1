// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"


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

	UE_LOG(LogTemp, Log, TEXT("====================="));
	
	
	// 클래스 정보 가져오기.
	UClass* RuntimeClass = GetClass();
	UClass* StaticClass = UMyGameInstance::StaticClass();
	// 어써트(Assert).
	// check가 좀더 강력.
	check(RuntimeClass == StaticClass);
	//ensure(RuntimeClass == StaticClass);
	//ensureMsgf(RuntimeClass != StaticClass, TEXT("일부러 오류 발생시켜봄."));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름: %s"), *RuntimeClass->GetName());
	
	SchoolName = TEXT("새로 변경된 학교");

	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *RuntimeClass->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("====================="));

	// Student/Teacher 객체 생성.
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생의 이름: %s"), *Student->GetName());

	// 리플렉션을 이용한 프로퍼티 정보 설정.
	FProperty* NameProperty = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	
	FString CurrentTeacherName;
	if (NameProperty)
	{
		// 현재 저장된 값 가져오기.
		NameProperty->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *CurrentTeacherName);

		FString NewTeacherName(TEXT("장세윤"));
		NameProperty->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름: %s"), *Teacher->GetName());

		int32 value = 100;
		UTeacher::StaticClass()->FindPropertyByName(TEXT("Year"))->SetValue_InContainer(Teacher, &value);
	}
	UE_LOG(LogTemp, Log, TEXT("====================="));

	Student->DoLesson();


	// 리플렉션을 통한 함수 호출.
	UFunction* DoLessonFunction = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunction)
	{
		Teacher->ProcessEvent(DoLessonFunction, nullptr);
	}
	UE_LOG(LogTemp, Log, TEXT("====================="));



}
