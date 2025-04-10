// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

// 이름을 랜덤으로 생성해주는 함수.
FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	// 랜덤 이름 생성을 위한 배열.
	TArray<TCHAR> RandArray;
	// 초기 크기 확보.
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();

}


void UMyGameInstance::Init()
{
	Super::Init();

	// TArray.
	TArray<int32> IntArray;

	// 동적 배열에 자료 추가.
	for (int ix = 0; ix < 10; ++ix)
	{
		IntArray.Add(ix + 1);
	}

	// 출력.
	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT("배열 값: %d"), Item);
	}

	// 조건 설정해서 삭제.
	IntArray.RemoveAll([](int32 Val) {return Val % 2 == 0; });

	// 출력.
	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT("삭제 후 배열 값: %d"), Item);
	}
	IntArray += {2, 4, 6, 8, 10};
	// 출력.
	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT("추가 후 배열 값: %d"), Item);
	}

	// 배열 통복사.
	int32 CArray[10];
	FMemory::Memcpy(CArray, IntArray.GetData(), sizeof(int32)*IntArray.Num());

	// 출력.
	for (const auto& Item : CArray)
	{
		UE_LOG(LogTemp, Log, TEXT("복사 후 배열 값: %d"), Item);
	}

	// 합계.
	int32 SumByAlgo = Algo::Accumulate(IntArray, 0);
	UE_LOG(LogTemp, Log, TEXT("SumByAlgo: %d"), SumByAlgo);

	// TSet
	TSet<int32> IntSet;
	for (int ix = 0; ix < 10; ++ix)
	{
		IntSet.Add(ix + 1);
	}

	IntSet.Remove(2);

	//StudentData.Add(FStudentData(1, TEXT("장세윤")));

	// 학생 데이터 생성.
	const int32 StudentCount = 300;
	for (int32 ix = 0; ix < StudentCount; ++ix)
	{
		// 배열을 순회하면서 랜덤으로 이름을 생성 후 배열에 추가.
		StudentData.Emplace(FStudentData(ix +1, MakeRandomName()));
	}

	// 학생 데이터를 TArray로 변환.
	TArray<FString> AllStudentNames;
	Algo::Transform(StudentData, AllStudentNames, 
		[](const FStudentData& Val)	{return Val.Name;});

	for (const auto name : AllStudentNames)
	{
		UE_LOG(LogTemp, Log, TEXT("이름: %s"), *name);
	}

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentNames.Num());


	// 학생 데이터를 TSet으로 변환.
	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentData, AllUniqueNames,
		[](const FStudentData& Val) {return Val.Name; });

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수: %d"), AllUniqueNames.Num());

	// 학생 데이터를 Map으로 변환.
	TMap<FString, int32> StudentMapByName;
	Algo::Transform(StudentData, StudentMapByName,
		[](const FStudentData& Val) {return TPair<FString, int32>(Val.Name, Val.Order); });

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수: %d"), StudentMapByName.Num());

	// 구조체를 TSet에 저장해보기.
	TSet<FStudentData> StudentsSet;
	for (int32 ix = 0; ix < StudentCount; ++ix)
	{
		StudentsSet.Emplace(FStudentData(ix + 1, MakeRandomName()));
	}

	UE_LOG(LogTemp, Log, TEXT("모든 학생 정보의 수: %d"), StudentsSet.Num());



















}
