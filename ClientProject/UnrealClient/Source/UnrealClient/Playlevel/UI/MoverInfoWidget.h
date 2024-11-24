// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Playlevel/Base/ClientPlayBaseUserWidget.h"
#include "Playlevel/UI/IDMainWidget.h"
#include "Components/VerticalBox.h"
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
	void InfoUpdate(const FString& _NewPos, EnumType _Type)
	{
		InfoUpdate(_NewPos, static_cast<int32>(_Type));
	}

	void InfoUpdate(const FString& _NewPos, int32 _Type);

protected:
	virtual void NativeConstruct() override;

	/// <summary>
	/// Widget의 초기 세팅
	/// </summary>
	void WidgetInitSetting();
private:

	/// <summary>
	/// InfoList에서 Child중에 원하는 EnumType에서 원하는 형태의 위젯으로 가져오는 함수
	/// </summary>
	/// <typeparam name="WidgetType"></typeparam>
	/// <typeparam name="EnumType"></typeparam>
	/// <param name="_Type"></param>
	/// <returns></returns>
	template<typename WidgetType, typename EnumType>
	WidgetType* GetInfoListChildAt(EnumType _Type)
	{
		return GetInfoListChildAt<WidgetType>(static_cast<int32>(_Type));
	}

	/// <summary>
	/// InfoList에서 Child중에 원하는 인덱스에서 원하는 형태의 위젯으로 가져오는 템플릿 함수
	/// </summary>
	/// <typeparam name="WidgetType"></typeparam>
	/// <param name="_Idx"></param>
	/// <returns></returns>
	template<typename WidgetType>
	WidgetType* GetInfoListChildAt(int32 _Type)
	{
		UWidget* Widget = InfoList->GetChildAt(_Type);

		WidgetType* CastWidget = Cast<WidgetType>(Widget);

		if (nullptr != CastWidget)
		{
			return CastWidget;
		}

		return nullptr;
	}


private:
	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> RootWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIDMainWidget> IDWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget", meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVerticalBox> InfoList = nullptr;
};
