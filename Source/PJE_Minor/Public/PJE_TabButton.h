// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJE_ButtonBase.h"
#include "PJE_InteractionInterface.h"
#include "PJE_TabButton.generated.h"

UCLASS()
class PJE_MINOR_API APJE_TabButton : public APJE_ButtonBase, public IPJE_InteractionInterface
{
	GENERATED_BODY()

public:
	APJE_TabButton();

	/** Button Interface */
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;
	/** end Button Interface */
	
protected:
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
