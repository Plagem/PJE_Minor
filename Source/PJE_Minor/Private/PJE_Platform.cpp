// Fill out your copyright notice in the Description page of Project Settings.


#include "PJE_Platform.h"


APJE_Platform::APJE_Platform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = PlatformMesh;
}

// Called when the game starts or when spawned
void APJE_Platform::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
}

void APJE_Platform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;
	
	if(bPlatformActive)
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		SetActorLocation(NewLocation);
	}
}

// Called every frame
void APJE_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}