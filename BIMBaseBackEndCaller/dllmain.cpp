// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <mscoree.h>
#include <metahost.h>
#include <assert.h>

#pragma comment(lib, "mscoree.lib")

#define BUFFER_SIZE 500


void StartTheDotNetRuntime(LPCWSTR runtimeVersion, LPCWSTR dllPath, LPCWSTR startClass, LPCWSTR startMethod, LPCWSTR startArgument)
{
    ICLRMetaHost* pMetaHost = NULL;
    ICLRMetaHostPolicy* pMetaHostPolicy = NULL;
    ICLRDebugging* pCLRDebugging = NULL;

    CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost);
    CLRCreateInstance(CLSID_CLRMetaHostPolicy, IID_ICLRMetaHostPolicy, (LPVOID*)&pMetaHostPolicy);
    CLRCreateInstance(CLSID_CLRDebugging, IID_ICLRDebugging, (LPVOID*)&pCLRDebugging);

    DWORD dwVersion = 0;
    DWORD dwImageVersion = 0;
    ICLRRuntimeInfo* pRuntimeInfo;
    HRESULT result;
    result = pMetaHost->GetRuntime(runtimeVersion, IID_ICLRRuntimeInfo, (LPVOID*)&pRuntimeInfo);
    assert(SUCCEEDED(result));

    ICLRRuntimeHost* pRuntimeHost = NULL;
    result = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&pRuntimeHost);
    assert(SUCCEEDED(result));

    result = pRuntimeHost->Start();
    assert(SUCCEEDED(result));

    DWORD dwRetCode = 0;
    result = pRuntimeHost->ExecuteInDefaultAppDomain(dllPath, startClass, startMethod, startArgument, &dwRetCode);
    if (!SUCCEEDED(result))
    {
        FILE* fp;
        fopen_s(&fp,"c:\\xx1.txt", "w");
        fprintf(fp,"123");
        fclose(fp);
    }
    assert(SUCCEEDED(result));
    //pRuntimeHost->Stop();
    //pRuntimeHost->Release();
    //pRuntimeInfo->Release();
    //pCLRDebugging->Release();
    //pMetaHostPolicy->Release();
    //pMetaHost->Release();
}
#pragma comment(lib,"BIMBaseBackEndCSharp.lib")
_declspec(dllimport) void registerFuncs();
void Loader()
{
    wchar_t* runtimeVersionSpace = new wchar_t[BUFFER_SIZE];
    wchar_t* dllPathSpace = new wchar_t[BUFFER_SIZE];
    wchar_t* currentDir = new wchar_t[BUFFER_SIZE];

    GetCurrentDirectoryW(BUFFER_SIZE, currentDir);

    StartTheDotNetRuntime(L"v4.0.30319", L"ClassLibrary1.dll", L"testBackEndCsharp.Class1", L"EntryPoint", L"");

    //free(runtimeVersionSpace);
    //free(dllPathSpace);
    //free(currentDir);
    registerFuncs();
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loader, NULL, 0, NULL);

        //for (size_t i = 0; i < 10; i++)
        //{
        //    Sleep(100);
        //}

        //TerminateThread(handle, 0);

    }
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}



