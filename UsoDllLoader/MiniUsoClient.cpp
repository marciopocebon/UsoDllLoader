
#include "MiniUsoClient.h"

#pragma comment(lib, "rpcrt4.lib")

MiniUsoClient::MiniUsoClient()
{
	HRESULT hResult;

	hResult = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hResult))
	{
		wprintf_s(L"    |__ CoInitializeEx() failed. Error code = 0x%08X\n", hResult);
		_ready = false;
	}
	else
	{
		_ready = true;
	}
}

MiniUsoClient::~MiniUsoClient()
{
	CoUninitialize();
}

void MiniUsoClient::ThrowOnError(HRESULT hResult)
{
	if (hResult != 0)
	{
		throw _com_error(hResult);
	}
}

bool MiniUsoClient::Run(UsoAction action)
{
	HRESULT hResult;

	if (this->_ready)
	{
		wprintf_s(L"    |__ Lets run Usoclient... ");


		try
		{
			wprintf_s(L"    |__ Creating a new Update Session... ");

			switch (action)
			{
			case USO_STARTSCAN:
				wprintf(L"    |__ Calling 'StartScan'... ");
				system("cmd.exe /C usoclient StartScan");
				wprintf(L"Done.\n");
				break;
			case USO_STARTDOWNLOAD:
				wprintf(L"    |__ Calling 'StartDownload'... ");
				system("cmd.exe /C usoclient StartDownload");
				wprintf(L"Done.\n");
				break;
			case USO_STARTINTERACTIVESCAN:
				wprintf(L"    |__ Calling 'StartInteractiveScan'... ");
				system("cmd.exe /C usoclient StartInteractiveScan");
				wprintf(L"Done.\n");
				break;
			}

		}
		catch (const _com_error& error)
		{
			wprintf_s(L"\n    |__ Something went wrong.\n", error.Error(), error.ErrorMessage());
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
