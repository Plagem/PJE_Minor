

#include "PJE_ButtonBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APJE_ButtonBase::APJE_ButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Button Component 생성
	ButtonBorderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = ButtonBorderMesh;
	ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	ButtonTrigger->SetupAttachment(RootComponent);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(RootComponent);

}

void APJE_ButtonBase::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = ButtonMesh->GetRelativeLocation();

	// 버튼 작동 테스트를 위해 APawn* Character를 생성하여 적용시킴
	// 실제 게임에서는 Cast를 통해 PlayerDuck & Cat 판별해야 함
	Character = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Event Binding
	// Warning : 캐릭터에 Generate Overlap Event가 적용된 Component가 여러 개 있다면 해당 수 만큼 실행된다.
	// 해결법 반드시 찾을 것
	ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &APJE_ButtonBase::ButtonBeginOverlap);
	ButtonTrigger->OnComponentEndOverlap.AddDynamic(this, &APJE_ButtonBase::ButtonEndOverlap);
}

void APJE_ButtonBase::MoveButton(float DeltaTime)
{
	FVector CurrentLocation = ButtonMesh->GetRelativeLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;

	// Interactive 여부에 따라 버튼을 임계점이나 원 위치로 움직이게 한다
	if(bButtonInteract)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}

	// Button이 임계점까지 움직이면 bButtonActive를 true로 변경
	if(FVector::Distance(CurrentLocation, TargetLocation) < 5.f)
	{
		bButtonActive = true;
	}
	else
	{
		bButtonActive = false;
	}
}

void APJE_ButtonBase::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if(Character) // Nullptr Check
	{
		if(OtherActor != Character) return;
	}
}

void APJE_ButtonBase::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Character) // Nullptr Check
	{
		if(OtherActor != Character) return;
	}
}

// Called every frame
void APJE_ButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

