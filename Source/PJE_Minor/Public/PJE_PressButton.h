

#pragma once

#include "CoreMinimal.h"
#include "PJE_ButtonBase.h"
#include "PJE_PressButton.generated.h"

UCLASS()
class PJE_MINOR_API APJE_PressButton : public APJE_ButtonBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
