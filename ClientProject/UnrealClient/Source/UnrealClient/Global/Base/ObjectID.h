// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Object의 ID관련 클래스
 */
class UNREALCLIENT_API ObjectID
{
public:
	FORCEINLINE int GetID() const
	{
		return ID;
	}

	virtual FORCEINLINE void SetID(int _ID)
	{
		ID = _ID;
	}

	ObjectID();
	virtual ~ObjectID();

protected:

private:
	/// <summary>
	/// Object ID
	/// </summary>
	int ID = -1;
};
