// Copyright 2024, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "InputGameplayAbility.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputReleased);
UCLASS()
class ABILITYSYSTEMCORE_API UInputGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	// Setting for initial activation. If true this will useful for something such as a passive ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution")
	bool bAutoActivate {false};
	// If true, when you try to activate this ability again while already active it will end
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Execution")
	bool bEndAbilityIfInputPressedWhileActive {false};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;
	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnInputPressed();
	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void OnInputReleased();

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};
