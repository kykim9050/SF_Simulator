// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Object�� ID���� Ŭ����
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
