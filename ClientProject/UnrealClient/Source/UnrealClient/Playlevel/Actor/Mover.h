// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/Base/ObjectID.h"
#include "Mover.generated.h"

/*
* 이동체 클레스
*/
class UStaticMeshComponent;
class UArrowComponent;
class ASimulatorManager;
class ABaseMoverAIController;
class AAIController;
class UWidgetComponent;
class UMoverData;
struct FMoverDataRow;
struct FCourseInfo;
UCLASS()
class UNREALCLIENT_API AMover : public ACharacter, public ObjectID
{
	GENERATED_BODY()

	friend ASimulatorManager;

public:
	// Sets default values for this pawn's properties
	AMover();

	FORCEINLINE FVector GetTargetPos() const
	{
		return TargetPos;
	}

	FORCEINLINE void SetTargetPos(FVector _TargetPos)
	{
		TargetPos = _TargetPos;
	}

	/// <summary>
	/// WayPoint의 정보를 Mover에 입력한다.
	/// </summary>
	/// <param name="_WayPointsInfo"></param>
	void SetWayPoints(const TArray<FVector2D>& _WayPointsInfo);

	FORCEINLINE ABaseMoverAIController* GetAIController() const
	{
		return AIController;
	}

	/// <summary>
	/// ID를 입력하는 동시에 자신의 컴포넌트 아이디도 초기화 한다.
	/// </summary>
	/// <param name="_ID"></param>
	void SetID(int _ID) override;

	UMoverData* GetSettingData() const
	{
		return SettingData;
	}

	/// <summary>
	/// SimulatorManager에게 자신의 Destroy를 허용한다는 시그널을 보내는 역할
	/// </summary>
	void AllowDestroy()
	{
		bIsAllowDestroy = true;
	}

	/// <summary>
	/// 위젯 컴포넌트에 표시할 좌표데이터 최신화 함수
	/// </summary>
	/// <param name="_InfoIdx"></param>
	void UpdateWidgetPosInfo(FVector _Pos, EMoverInfoIdx _InfoIdx);

	/// <summary>
	/// 위젯 컴포넌트에 표시할 시간 기록 함수
	/// </summary>
	/// <param name="_InfoIdx"></param>
	void UpdateWidgetTimeInfo(FDateTime _CurTime, EMoverInfoIdx _InfoIdx);

	/// <summary>
	/// Path 세팅 완료후 해당 함수 호출해야 Mover의 상태 변환이 이루어짐
	/// </summary>
	void SetIsPathRecv();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

private:
	/// <summary>
	/// Mover의 외형 매시용 컴포넌트
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MoverMeshComponent = nullptr;

	/// <summary>
	/// ID를 나타낼 수 있는 위젯 컴포넌트
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> IDComponent = nullptr;

	UPROPERTY()
	FVector TargetPos = FVector();

	/// <summary>
	/// 매칭할 ID위젯 관련 클래스 정보
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> IDComponentWidgetClass = nullptr;

	/// <summary>
	/// 매칭할 AICOntroller 클래스 정보
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAIController> MatchingAIControllerClass = nullptr;

	/// <summary>
	/// Mover를 제어할 AIController 포인터
	/// </summary>
	UPROPERTY()
	TObjectPtr<ABaseMoverAIController> AIController = nullptr;

	/// <summary>
	/// Mover의 모든 데이터를 저장
	/// </summary>
	UPROPERTY()
	UMoverData* SettingData;

	/// <summary>
	/// 데이터 테이블 중 어떤 이름의 테이블을 선택할 것인지 식별자
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Setting Data Name", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName StatusName;

	/// <summary>
	/// 고정 데이터 값들에 대한 포인터
	/// </summary>
	const FMoverDataRow* BaseData;

	/// <summary>
	/// 본인을 삭제해도 된다는 의미의 boo값
	/// </summary>
	bool bIsAllowDestroy = false;
};
