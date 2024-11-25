// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "ClientPlayMainWidget.generated.h"

/**
 * Playlevel �c�鿡 ǥ���� ���� ��ҵ��� �����ϴ� ���� ����
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
	/// �����κ��� �α� �ؽ�Ʈ�� ����ϱ� ���� �Լ�
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
