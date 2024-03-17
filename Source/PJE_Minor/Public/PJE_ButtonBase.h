
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJE_ButtonBase.generated.h"

class APJE_Platform;
class UBoxComponent;

UCLASS()
class PJE_MINOR_API APJE_ButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APJE_ButtonBase();

protected:
	virtual void BeginPlay() override;

	void MoveButton(float DeltaTime);

	UFUNCTION()
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void NotifyActiveToPlatform(bool ButtonActive);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool bButtonActive = false;
	
protected:
	// Button Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonBorderMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UPROPERTY(VisibleAnywhere)
	bool bButtonInteract = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<APJE_Platform>> Platforms;
	
	// 나중에 없앨 것
	APawn* Character;
};
