// Copyright 2024, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/InputAbilitySystemDataAsset.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEMCORE_API UAbilitySystemEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilitySystemEnhancedInputComponent();

	template <class UserClass, typename PressedFunction, typename ReleasedFunction>
	void BindAbilityInputs(UInputAbilitySystemDataAsset* InputDataAsset, UserClass* Object, PressedFunction PressedFunctionCallback, ReleasedFunction ReleasedFunctionCallback);
};

template <class UserClass, typename PressedFunction, typename ReleasedFunction>
void UAbilitySystemEnhancedInputComponent::BindAbilityInputs(UInputAbilitySystemDataAsset* InputDataAsset, UserClass* Object, PressedFunction PressedFunctionCallback, ReleasedFunction ReleasedFunctionCallback)
{
	for (const FAbilityInputAction& AbilityInputAction : InputDataAsset->AbilityInputs)
	{
		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunctionCallback, AbilityInputAction.InputTag);
		BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunctionCallback, AbilityInputAction.InputTag);
	}
}
