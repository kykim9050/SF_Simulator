// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalHUD.h"
#include "ClientPlayHUD.generated.h"

/**
 * Playlevel에서 설정될 HUD 클래스
 */
class UClientPlayMainWidget;
UCLASS()
class UNREALCLIENT_API AClientPlayHUD : public AGlobalHUD
{
	GENERATED_BODY()
	
public:
	
	/// <summary>
	/// MainWidget의 정보를 가져오는 기능
	/// </summary>
	/// <returns></returns>
	UClientPlayMainWidget* GetMainWidget() const
	{
		return MainWidget;
	}

protected:
	void BeginPlay() override;

private:
	TObjectPtr<UClientPlayMainWidget> MainWidget = nullptr;

	/// <summary>
	/// HUD의 블루 프린트 에디터 상에서 UUserWidget을 상속받는 클래스의 정보를 가져오는 수단
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MainWidgetClass = nullptr;
};
