// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	// Call parent class's function.
	Super::Init();

	// Test Log.
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));
}
