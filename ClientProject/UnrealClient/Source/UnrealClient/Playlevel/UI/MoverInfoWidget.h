// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "Playlevel/UI/IDMainWidget.h"

#include "MoverInfoWidget.generated.h"

/**
 * Mover Info 표시를 위한 전용 위젯
 */
class UCanvasPanel;
class UVerticalBox;
UCLASS()
class UNREALCLIENT_API UMoverInfoWidget : public UClientPlayBaseUserWidget
{
	GENERATED_BODY()
public:

	UIDMainWidget* GetIDWidget()
	{
		return IDWidget;
	}

	/// <summary>
	/// Pos 데이터(현재 Pos, ,목적지 Pos) 업데이트 함수
	/// </summary>
	/// <typeparam name="EnumType"></typeparam>
	/// <param name="_NewPos"></param>
	/// <param name="_Type"></param>
	template<typename EnumType>
	void PosUpdate(const FString& _NewPos, EnumType _Type)
	{
		PosUpdate(_NewPos, static_cast<int32>(_Type));
	}

	void PosUpdate(const FString& _NewPos, int32 _Type);

protected:

private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIDMainWidget> IDWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVerticalBox> InfoList = nullptr;
};
