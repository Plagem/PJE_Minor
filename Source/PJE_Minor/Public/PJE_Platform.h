// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJE_Platform.generated.h"

UCLASS()
class PJE_MINOR_API APJE_Platform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJE_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MovePlatform(float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;

	void SetbPlatformActive(bool _bPlatformActive) { bPlatformActive = _bPlatformActive; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* PlatformMesh;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime = 4.f;
	
	float PlatformDelayTime;

	bool bPlatformActive;
};
