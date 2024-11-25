// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "ClientPlayMainWidget.generated.h"

/**
 * Playlevel 홤면에 표시할 위젯 요소들을 관리하는 메인 위젯
 */
class UCanvasPanel;
class UWidgetSwitcher;
class UScrollBox;
UCLASS()
class UNREALCLIENT_API UClientPlayMainWidget : public UClientPlayBaseUserWidget
{
	GENERATED_BODY()
public:

	/// <summary>
	/// 서버로부터 로그 텍스트를 출력하기 위한 함수
	/// </summary>
	/// <param name="_Log"></param>
	void AddLogText(const FString& _Log);

protected:

private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UWidgetSwitcher* WidgetSwitcher = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UScrollBox* LoggingBox = nullptr;
	
};
