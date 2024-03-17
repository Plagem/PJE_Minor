

#include "PJE_ButtonBase.h"

#include "PJE_Platform.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

APJE_ButtonBase::APJE_ButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Button Component
	ButtonBorderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = ButtonBorderMesh;
	ButtonBorderMesh->SetGenerateOverlapEvents(false);
	
	ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	ButtonTrigger->SetupAttachment(RootComponent);
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(RootComponent);
	ButtonMesh->SetGenerateOverlapEvents(false);

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
		//UE_LOG(LogTemp, Warning, TEXT("Button Active"));
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}

	// Button이 임계점까지 움직이면 bButtonActive를 true로 변경
	// ButtonActive 상태가 변경되면 Platform으로 Notify 보낸다
	if(FVector::Distance(CurrentLocation, TargetLocation) < 5.f)
	{
		if(bButtonActive == false)
		{
			NotifyActiveToPlatform(true);
		}
		bButtonActive = true;
	}
	else
	{
		if(bButtonActive == true)
		{
			NotifyActiveToPlatform(false);
		}
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

void APJE_ButtonBase::NotifyActiveToPlatform(bool ButtonActive)
{
	UE_LOG(LogTemp, Warning, TEXT("Now Button Active : %d"), ButtonActive);
	Platforms[0]->SetbPlatformActive(ButtonActive);
}

// Called every frame
void APJE_ButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveButton(DeltaTime);
}

