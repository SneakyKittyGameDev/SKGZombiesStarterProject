// Copyright 2024, Dakota Dawe, All rights reserved


#include "Components/InputAbilitySystemComponent.h"
#include "Abilities/InputGameplayAbility.h"


UInputAbilitySystemComponent::UInputAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInputAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInputAbilitySystemComponent::GiveStartingAttributes()
{
	AddAttributes(StartingAttributes);
}

void UInputAbilitySystemComponent::GiveStartingAbilities()
{
	if (IsOwnerActorAuthoritative())
	{
		AddAbilities(StartingAbilities);
		AddAbilities(StartingPassiveAbilities, true);
	}
}

void UInputAbilitySystemComponent::GiveStartingEffects()
{
	if (IsOwnerActorAuthoritative())
	{
		AddEffects(StartingEffects);
	}
}

void UInputAbilitySystemComponent::AddAttribute(const TSubclassOf<UAttributeSet>& AttributeSet)
{
	AddSpawnedAttribute(NewObject<UAttributeSet>(GetOwner(), AttributeSet));
}

void UInputAbilitySystemComponent::AddAttributes(const TArray<TSubclassOf<UAttributeSet>>& AttributeSets)
{
	for (const TSubclassOf<UAttributeSet>& AttributeSet : AttributeSets)
	{
		AddAttribute(AttributeSet);
	}
}

void UInputAbilitySystemComponent::AddAbility(const TSubclassOf<UGameplayAbility>& Ability, bool bAutoActivateAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Ability: %s"), *Ability->GetName());
	FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability);
	if (bAutoActivateAbility)
	{
		GiveAbilityAndActivateOnce(Spec);
	}
	else
	{
		GiveAbility(Spec);
	}
}

void UInputAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities, bool bAutoActivateAbility)
{
	for (const TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		AddAbility(Ability, bAutoActivateAbility);
	}
}

void UInputAbilitySystemComponent::AddEffect(const TSubclassOf<UGameplayEffect>& Effect)
{
	FGameplayEffectContextHandle ContextHandle;
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(Effect, 1.0f, ContextHandle);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

void UInputAbilitySystemComponent::AddEffects(const TArray<TSubclassOf<UGameplayEffect>>& Effects)
{
	for (const TSubclassOf<UGameplayEffect> Effect : Effects)
	{
		AddEffect(Effect);
	}
}

void UInputAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	if (const UInputGameplayAbility* Ability = Cast<UInputGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(Ability->InputTag);
	}
}

void UInputAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& Tag)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
			else if (const UInputGameplayAbility* InputGameplayAbility = Cast<UInputGameplayAbility>(AbilitySpec.GetPrimaryInstance()); InputGameplayAbility && InputGameplayAbility->bEndAbilityIfInputPressedWhileActive)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cacleing Ability: %d"), InputGameplayAbility->bEndAbilityIfInputPressedWhileActive);
				CancelAbilitySpec(AbilitySpec, nullptr);
				break;
			}
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
			{
				ServerSetInputPressed(AbilitySpec.Handle);
			}
		}
	}
}

void UInputAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& Tag)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.IsActive() && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(Tag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			if (AbilitySpec.Ability->bReplicateInputDirectly && !IsOwnerActorAuthoritative())
			{
				ServerSetInputReleased(AbilitySpec.Handle);
			}
		}
	}
}
