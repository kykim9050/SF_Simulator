// Fill out your copyright notice in the Description page of Project Settings.


#include "Playlevel/Actor/DestSign.h"
#include "Components/WidgetComponent.h"
#include "Playlevel/UI/IDMainWidget.h"
#include "Components/TextBlock.h"

// Sets default values
ADestSign::ADestSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IDComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("IDComponent"));
	IDComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestSign::BeginPlay()
{
	Super::BeginPlay();
	
	// id 컴포넌트 세팅
	if (nullptr != IDComponentWidgetClass)
	{
		// RotateVal을 Radian으로 변경
		double RotateVal = 90.;
		RotateVal = FMath::DegreesToRadians(RotateVal);

		IDComponent->SetWidgetClass(IDComponentWidgetClass);
		IDComponent->SetDrawSize(FVector2D(150.0f, 50.0f));
		IDComponent->SetRelativeLocation(FVector(0.0, 0.0, 200.0));
		IDComponent->SetRelativeRotation(FRotator(RotateVal, .0, .0));
		IDComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

// Called every frame
void ADestSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestSign::SetID(int _ID)
{
	ObjectID::SetID(_ID);

	UUserWidget* Widget = IDComponent->GetWidget();
	if (nullptr != Widget)
	{
		UIDMainWidget* IdWidget = Cast<UIDMainWidget>(Widget);

		if (nullptr != IdWidget)
		{
			int MyID = GetID();
			FString PrintString = FString(TEXT("T")) + FString::FromInt(MyID);
			FText Text = FText::FromString(PrintString);
			IdWidget->GetIDTextBlock()->SetText(Text);
		}
	}
}

