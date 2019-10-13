// ClassFactoryDllServerwithRegFile.cpp : Defines the exported functions for the DLL application.
//

#include <windows.h>
#include "stdafx.h"
#include "ClassFactoryDllServerWithRegFile.h"

#define MESSAGE_MACRO 0 
class CSumSubtract : public ISum, ISubtract, IMultiplication
{
private:
	long m_cRef;
public:
	//constructor
	CSumSubtract(void);
	//Destructor
	~CSumSubtract(void);

	//IUnknown specific mthods declaration
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum Specific method declaration(inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
};


class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor
	CSumSubtractClassFactory(void);
	//destructor
	~CSumSubtractClassFactory(void);

	//IUnknown specific method declaration
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassSpecific Methods declaration
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//Implementations of CSumSubtract's constructor
CSumSubtract::CSumSubtract(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("inside CSumSubtract::CSumSubtract"), TEXT("Message"), MB_OK);
#endif
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Implementations of CSumSubtract's destructor
CSumSubtract::~CSumSubtract(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT(" inside CSumSubtract::~CSumSubtract"), TEXT("Message"), MB_OK);
#endif
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Implementations of CSumSubtract's IUnknown methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of CSumSubtract::QueryInterface"), TEXT("Message"), MB_OK);
#endif
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum *>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract *>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of CSumSubtract::QueryInterface"), TEXT("Message"), MB_OK);
#endif
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("CSumSubtract::AddRef"), TEXT("Message"), MB_OK);
#endif
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("CSumSubtract::Release"), TEXT("Message"), MB_OK);
#endif
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cRef);
}

// Implementation of ISum's method
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int*pSum)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("SumOfTwoIntegers"), TEXT("Message"), MB_OK);
#endif
	*pSum = num1 + num2;
	return(S_OK);
}

// Implementation of ISum's method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int*pSum)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("SubtractionOfTwoIntegers"), TEXT("Message"), MB_OK);
#endif
	*pSum = num1 - num2;
	return(S_OK);
}

// Implementation of ISum's method
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int*pSum)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("MultiplicationOfTwoIntegers"), TEXT("Message"), MB_OK);
#endif
	*pSum = num1 * num2;
	return(S_OK);
}


CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("inside CSumSubtractClassFactory"), TEXT("Message"), MB_OK);
#endif
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("inside ~CSumSubtractClassFactory"), TEXT("Message"), MB_OK);
#endif

	// NoCode
}

//Implementations of CSumSubtractClassFactory's methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of CSumSubtractClassFactory::QueryInterface"), TEXT("Message"), MB_OK);
#endif
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IUnknown *>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of CSumSubtractClassFactory::QueryInterface"), TEXT("Message"), MB_OK);
#endif
	return(S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("inside CSumSubtractClassFactory::AddRef"), TEXT("Message"), MB_OK);
#endif
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of CSumSubtractClassFactory::Release"), TEXT("Message"), MB_OK);
#endif
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of CSumSubtractClassFactory::Release"), TEXT("Message"), MB_OK);
#endif
	return(m_cRef);
}

//Implementation of CSumSubtractClassFactory
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of CSumSubtractClassFactory::CreateInstance"), TEXT("Message"), MB_OK);
#endif
	// variable declarations
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	//code
	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of CSumSubtractClassFactory::CreateInstance"), TEXT("Message"), MB_OK);
#endif
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of CSumSubtractClassFactory::LockServer"), TEXT("Message"), MB_OK);
#endif
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of CSumSubtractClassFactory::LockServer"), TEXT("Message"), MB_OK);
#endif
	return (S_OK);
}

// Implementation of exported functions from this DLL
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of DllGetClassObject"), TEXT("Message"), MB_OK);
#endif
	//code
	if (rclsid != CLSID_SumSubtract)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
	{
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of DllGetClassObject"), TEXT("Message"), MB_OK);
#endif
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("start of DllCanUnloadNow "), TEXT("Message"), MB_OK);
#endif
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
#if MESSAGE_MACRO
	MessageBox(NULL, TEXT("end of DllCanUnloadNow "), TEXT("Message"), MB_OK);
#endif
}

