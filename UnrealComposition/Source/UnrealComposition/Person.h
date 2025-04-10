// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	// Getter/Setter.
	const FString& GetName() const;
	void SetName(const FString& InName);

	class UCard* GetCard() const;
	void SetCard(class UCard* InCard);

protected:

	UPROPERTY()
	FString Name;

	UPROPERTY()
	TObjectPtr<class UCard> Card;

};
