// Copyright 2024, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputAbilitySystemDataAsset.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct FAbilityInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;
};

UCLASS()
class ABILITYSYSTEMCORE_API UInputAbilitySystemDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<FAbilityInputAction> AbilityInputs;
};
