#pragma once

class GlobalValue
{
public:
	static GlobalValue& GetInst()
	{
		static GlobalValue Inst = GlobalValue();
		return Inst;
	}

	inline void SetNValue(int _Value)
	{
		NValue = _Value;
	}

	inline int GetNValue() const
	{
		return NValue;
	}

private:
	GlobalValue() {}
	~GlobalValue() {}

private:
	int NValue = -1;
};
