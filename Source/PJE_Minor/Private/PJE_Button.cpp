
#include "PJE_Button.h"

#include "PJE_Platform.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APJE_Button::APJE_Button()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	ButtonBorderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = ButtonBorderMesh;
	ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	ButtonTrigger->SetupAttachment(RootComponent);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(RootComponent);
	
}

void APJE_Button::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = ButtonMesh->GetRelativeLocation();

	// 일시적 테스트를 위해 APawn* Character를 생성하여 적용시킨 모습
	// 실제 게임에서는 Cast를 통해 UPJE_PlayerDuck & UPJE_PlayerCat인지 확인해야 할 것임
	Character = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	UE_LOG(LogTemp, Warning, TEXT("Actor Name : %s"), *Character->GetName());

	// Event Binding
	// Warning : 캐릭터에 Generate Overlap Event가 여러개 있다면 여러번 실행된다. 해결법 찾을 것
	ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &APJE_Button::ButtonBeginOverlap);
	ButtonTrigger->OnComponentEndOverlap.AddDynamic(this, &APJE_Button::ButtonEndOverlap);
}

void APJE_Button::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	// Overlap된 Actor가 Player인지 확인
	// 실제 게임에서는 Cast를 통해 UPJE_PlayerDuck & UPJE_PlayerCat인지 확인한다
	if(OtherActor == Character && Character)
	{
		bOnButton = true;
	}
}

void APJE_Button::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == Character && Character)
	{
		bOnButton = false;
		if(Platform)
		{
			Platform->SetbPlatformActive(false);
		}
	}
}

void APJE_Button::MoveButton(float DeltaTime)
{
	FVector CurrentLocation = ButtonMesh->GetRelativeLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;
	
	if(bOnButton)
	{
		// Move Button to TargetLocation
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);

		// 임계점까지 움직이면 bButtonActive을 true로 변경
		if(FVector::Distance(NewLocation, TargetLocation) < 10.f)
		{
			if(Platform)
			{
				Platform->SetbPlatformActive(true);
				UE_LOG(LogTemp, Warning, TEXT("Platform Actived"));
			}
		}
	}
	else
	{
		// Move Button to OriginLocation
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}
}

// Called every frame
void APJE_Button::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveButton(DeltaTime);
}


