// Copyright 2024, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEMCORE_API UInputAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputAbilitySystemComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UAttributeSet>> StartingAttributes;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingPassiveAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartingEffects;
	
	virtual void BeginPlay() override;

public:
	void GiveStartingAttributes();
	void GiveStartingAbilities();
	void GiveStartingEffects();

	void AddAttribute(const TSubclassOf<UAttributeSet>& AttributeSet);
	void AddAttributes(const TArray<TSubclassOf<UAttributeSet>>& AttributeSets);
	
	void AddAbility(const TSubclassOf<UGameplayAbility>& Ability, bool bAutoActivateAbility = false);
	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, bool bAutoActivateAbility = false);

	void AddEffect(const TSubclassOf<UGameplayEffect>& Effect);
	void AddEffects(const TArray<TSubclassOf<UGameplayEffect>>& Effects);
	
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	void AbilityInputPressed(const FGameplayTag& Tag);
	void AbilityInputReleased(const FGameplayTag& Tag);
};
