// Copyright 2024, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemReadyInterface.generated.h"

class UAbilitySystemComponent;

UINTERFACE()
class ABILITYSYSTEMCORE_API UAbilitySystemReadyInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilitySystemReady, UAbilitySystemComponent*);
class ABILITYSYSTEMCORE_API IAbilitySystemReadyInterface
{
	GENERATED_BODY()

public:
	FOnAbilitySystemReady OnAbilitySystemReady;
};
