// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Base/GlobalHUD.h"
#include "ClientPlayHUD.generated.h"

/**
 * Playlevel���� ������ HUD Ŭ����
 */
class UClientPlayMainWidget;
UCLASS()
class UNREALCLIENT_API AClientPlayHUD : public AGlobalHUD
{
	GENERATED_BODY()
	
public:
	
	/// <summary>
	/// MainWidget�� ������ �������� ���
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
	/// HUD�� ��� ����Ʈ ������ �󿡼� UUserWidget�� ��ӹ޴� Ŭ������ ������ �������� ����
	/// </summary>
	UPROPERTY(Editanywhere, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MainWidgetClass = nullptr;
};
