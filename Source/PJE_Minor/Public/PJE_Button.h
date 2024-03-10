
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PJE_Button.generated.h"

UCLASS()
class PJE_MINOR_API APJE_Button : public APawn
{
	GENERATED_BODY()

public:
	APJE_Button();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void MoveButton(float DeltaTime);
	
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform", meta=(AllowPrivateAccess = true))
	class APJE_Platform* Platform;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = true))
	class UBoxComponent* ButtonTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* ButtonBorderMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* ButtonMesh;
	
	bool bOnButton = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime = 0.3f;

	APawn* Character;
};
