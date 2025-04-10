// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"
#include "AssetRegistry/AssetRegistryModule.h"


UMyGameInstance::UMyGameInstance()
{
	// 강참조 로딩.
	FString ObjectPath = TEXT("/Script/UnrealSerialization.Student'/Game/Student.Student'");

	// 에셋 로드.
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_Student(*ObjectPath);

	// 성공 확인.
	if (UASSET_Student.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("[Constructor] 이름: %s, 순번: %d"), *UASSET_Student.Object->GetName(), UASSET_Student.Object->GetOrder());
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 데이터 생성.
	FStudentData RawDataSource(23, TEXT("장세윤"));

	// 경로.
	const FString SavedPath = FPaths::Combine(
		FPlatformMisc::ProjectDir(),
		TEXT("Saved")
	);

	// 테스트 출력.
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더: %s"), *SavedPath);

	{
		// 파일 이름.
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 전체 경로 설정 후 절대경로로 변경.
		FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 폴더: %s"), *RawDataAbsolutePath);

		// 절대 경로로 변경.
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 폴더: %s"), *RawDataAbsolutePath);

		// 구조체 데이터 직렬화.
		// CreateFileWriter 함수는 new로 생성 후 반환하기 때문에 delete로 메모리 정리해야함.
		// 파일 생성 및 여는 행위
		FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);

		if (RawFileWriteAr)
		{
			// 데이터 넣기.
			/**RawFileWriteAr << RawDataSource.Order;
			*RawFileWriteAr << RawDataSource.Name;*/
			*RawFileWriteAr << RawDataSource;

			// 아카이브 닫기.
			RawFileWriteAr->Close();

			// 메모리 해제.
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}
		// 역직렬화(읽기).
		FStudentData RawDataDeserialized;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);

		if (RawFileReaderAr)
		{
			// 데이터 읽기.
			/**RawFileReaderAr << RawDataDeserialized.Order;
			*RawFileReaderAr << RawDataDeserialized.Name;*/
			*RawFileReaderAr << RawDataDeserialized;


			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			// 출력.
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름: %s, 순번: %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);
		}

	}

	// UObject 직렬화.
	StudentSource = NewObject<UStudent>();
	StudentSource->SetOrder(40);
	StudentSource->SetName(TEXT("장세윤"));

	{
		// 파일 이름.
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));

		// 폴더 경로.
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedPath, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		// 직렬화.
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSource->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FileWriterAr << BufferArray;

			//StudentSource->Serialize(*FileWriterAr);
			FileWriterAr->Close();
		}

		// 역직렬화.
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			// File -> ByteArray -> Memory Buffer(FArchive) -> Student Object.
			TArray<uint8> BufferArrayFromFile;
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();

			FMemoryReader MemoryReaderAr(BufferArrayFromFile);

			UStudent* StudentDes = NewObject<UStudent>();
			StudentDes->Serialize(MemoryReaderAr);
			//StudentDes->Serialize(*FileReaderAr);

			UE_LOG(LogTemp, Log, TEXT("이름: %s, 순번: %d"), *StudentDes->GetName(), StudentDes->GetOrder());
		}
		
	}


#pragma region Json직렬화 저장 및 읽기.

	// JSON 직렬화.
	const FString JsonDataFileName(TEXT("StudentJsonData.txt"));

	// 경로.
	FString JsonDataAbsolutePath = FPaths::Combine(*SavedPath, *JsonDataFileName);
	FPaths::MakeStandardFilename(JsonDataAbsolutePath);
	
	// Json 객체 생성.
	TSharedRef<FJsonObject> JsonObjectSource = MakeShared<FJsonObject>();
	
	// UObject -> Json 객체 변환.
	FJsonObjectConverter::UStructToJsonObject(StudentSource->GetClass(), StudentSource, JsonObjectSource);

	// Json 객체 -> Json 문자열.
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonString);

	// Json 문자열에 직렬화 진행.
	if (FJsonSerializer::Serialize(JsonObjectSource, JsonWriterAr))
	{
		// 파일에 저장.
		FFileHelper::SaveStringToFile(JsonString, *JsonDataAbsolutePath);
	}

	// Json Read
	FString JsonFromFile;
	FFileHelper::LoadFileToString(JsonFromFile, *JsonDataAbsolutePath);

	// Json String -> Json Object.
	TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonFromFile);

	TSharedPtr<FJsonObject> JsonObjectResult;
	if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectResult))
	{
		// Json Object -> UObject.
		UStudent* JsonStudent = NewObject<UStudent>();
		if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectResult.ToSharedRef(), JsonStudent->GetClass(), JsonStudent))
		{
			// Test Print.
			UE_LOG(LogTemp, Log, TEXT("[JsonData] 이름: %s, 순번: %d"), *JsonStudent->GetName(), JsonStudent->GetOrder());
		}
	}
#pragma endregion


	// 패키지 저장 함수 호출.
	SaveStudentPackage();

	// 에셋 로드 함수 호출.
	//LoadStudentPackage();

	// 비동기 에셋 로드.
	// 비동기 -> 콜백(Callback) 함수가 필요함.
	// /Script/UnrealSerialization.Student'/Game/Student.Student'
	FString ObjectPath = FString::Printf(TEXT("%s.%s"), TEXT("/Game/Student"), TEXT("Student"));

	// 핸들 생성.
	Handle = StreamableManager.RequestAsyncLoad(ObjectPath,
		[&]() {

			// 값 출력.
			UStudent* Student = Cast<UStudent>(Handle->GetLoadedAsset());
			if (Student)
			{
				UE_LOG(LogTemp, Log, TEXT("[AsyncLoad] 이름: %s, 순번: %d"), *Student->GetName(), Student->GetOrder());
			}

			// 핸들 해제.
			Handle->ReleaseHandle();
			Handle.Reset();
		}
	);


}

void UMyGameInstance::SaveStudentPackage()
{
	// 에셋을 저장하기 전에 완전히 로드되도록 처리.
	UPackage* StudentPackage = LoadPackage(nullptr, TEXT("/Game/Student"), LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	// 패키지 생성.
	StudentPackage = CreatePackage(TEXT("/Game/Student"));
	// 패키지 구성을 위한 플래그 지정.
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	// UObject 생성.
	UStudent* TopStudent = NewObject<UStudent>(StudentPackage, UStudent::StaticClass(), TEXT("Student"), ObjectFlag);

	// 데이터 설정.
	TopStudent->SetOrder(40);
	TopStudent->SetName(TEXT("장세윤"));

	// 패키지 저장.
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(TEXT("/Game/Student"), FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;
	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지가 성공적으로 저장되었습니다."));
	}

}

void UMyGameInstance::LoadStudentPackage()
{
	// 패키지 경로 설정.
	UPackage* StudentPackage = LoadPackage(nullptr, TEXT("/Game/Student"), LOAD_None);
	// 패키지 로드 실패.
	if (!StudentPackage)
	{
		UE_LOG(LogTemp, Log, TEXT("패키지를 찾을 수 없습니다."));
		return;
	}

	// 패키지 완전히 로드 처리
	StudentPackage->FullyLoad();

	// 에셋 로드.
	UStudent* Student = FindObject<UStudent>(StudentPackage, TEXT("Student"));
	if (Student)
	{
		UE_LOG(LogTemp, Log, TEXT("[FindObject Asset] 이름: %s, 순번: %d"), *Student->GetName(), Student->GetOrder());
	}




}
