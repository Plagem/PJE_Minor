

#include "PJE_PressButton.h"

#include "Components/BoxComponent.h"

void APJE_PressButton::BeginPlay()
{
	Super::BeginPlay();

	
}

void APJE_PressButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Super::ButtonBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Hit);

	bButtonInteract = true;
}

void APJE_PressButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ButtonEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	bButtonInteract = false;
}
