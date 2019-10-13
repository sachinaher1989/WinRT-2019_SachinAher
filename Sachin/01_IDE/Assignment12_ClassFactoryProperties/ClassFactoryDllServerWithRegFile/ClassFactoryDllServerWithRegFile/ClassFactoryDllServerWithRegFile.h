#include <Unknwnbase.h>

class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};


class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

class IMultiplication : public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

//{FDC1323B - D2EE - 4441 - BA92 - B825F62578BE}
const CLSID CLSID_SumSubtract = { 0xfdc1323b, 0xd2ee, 0x4441, 0xba, 0x92, 0xb8, 0x25, 0xf6, 0x25, 0x78, 0xbe };


// {2286350F-2C12-4D64-933C-EB0D0E4225E1}
const IID IID_ISum = { 0x2286350f, 0x2c12, 0x4d64, 0x93, 0x3c, 0xeb, 0xd, 0xe, 0x42, 0x25, 0xe1 };

// {100D4A23-C1C2-4BF7-9C71-7B274D1A8499}
const IID IID_ISubtract = { 0x100d4a23, 0xc1c2, 0x4bf7, 0x9c, 0x71, 0x7b, 0x27, 0x4d, 0x1a, 0x84, 0x99 };

// {F3B2B4F3-E600-43CB-8C46-2C18617FA35B}
const IID IID_IMultiplication = { 0xf3b2b4f3, 0xe600, 0x43cb, 0x8c, 0x46, 0x2c, 0x18, 0x61, 0x7f, 0xa3, 0x5b };

