// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ClientInterpreter.generated.h"

/**
 * ��Ŷ ������ ���� ��Ŷ�� �ؼ��ϴ� Ŭ����
 */
struct FRecvBaseProtocol;
UCLASS()
class UNREALCLIENT_API UClientInterpreter : public UObject
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Ư�� ��Ŷ �����ͷ� ��ȯ
	/// </summary>
	/// <param name="_Type"></param>
	/// <param name="_ReadMem"></param>
	/// <returns></returns>
	TSharedPtr<FRecvBaseProtocol> ConvertProtocol(int32 _Type, FMemoryArchive& _ReadMem);

protected:

private:

};
