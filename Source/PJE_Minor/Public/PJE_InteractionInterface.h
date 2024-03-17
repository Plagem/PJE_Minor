// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PJE_InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPJE_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PJE_MINOR_API IPJE_InteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ShowInteractWidget() = 0;
	virtual void HideInteractWidget() = 0;
};
