#include <Windows.h>
#include <sstream>
#include <string>

#include "detours.h"
#include "Helpers.h"
#include "Signature.h"
#include "toml.hpp"

int rnd;
int rnd2;
char rorn = 'r';

int randomLoading = -1;
int loadingStyle = -1;
toml::table config;

//1.0.2 0x140CC2138
SIG_SCAN ( sigLoadingBg, "\x6C\x6F\x61\x64\x69\x6E\x67\x5F\x62\x67\x00\x00\x00\x00\x00\x00", "xxxxxxxxxx??????" )

//1.0.2 0x140CC2198
SIG_SCAN(sigNowLoading, "\x6E\x6F\x77\x5F\x6C\x6F\x61\x64\x69\x6E\x67\x00\x00\x00\x00\x00", "xxxxxxxxxxx?????")

//1.0.2 0x140653FC0
SIG_SCAN(sigLoadingScreen, "\x48\x89\x5C\x24\x00\x48\x89\x7C\x24\x00\x55\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\xF9\x45\x33\xC0\x41\x8D\x50\x04\x33\xC9\xE8\x00\x00\x00\x00\x8B\xD8\x48\x8D\x15\x00\x00\x00\x00", "xxxx?xxxx?xxxxx????xxx????xxx????xxxxxx????xxxxxxxxxxxxx????xxxxx????")

void load_bg(unsigned char v1, unsigned char v2, unsigned char v3, unsigned char v4)
{
	unsigned char zeroX = '0x0';
	std::stringstream sstream;
	sstream << std::hex << v1;
	sstream << std::hex << v2;
	sstream << std::hex << v3;
	sstream << std::hex << v4;
	std::string result = sstream.str();
	unsigned char V1 = zeroX + v1;
	unsigned char V2 = zeroX + v2;
	unsigned char V3 = zeroX + v3;
	unsigned char V4 = zeroX + v4;
	WRITE_MEMORY((char*)sigLoadingBg()+0x04, uint8_t, 'b', 'g', V1, V2, V3, V4);
}

void random_bg()
{
	switch (randomLoading)
	{
		case 0: //M39 (0-4)
		{
			rnd = rand() % 5;
			break;
		}
		case 1: //X (5-238)
		{
			rnd = 5 + rand() % 234;
			break;
		}
		case 2: //FT (239-241)
		{
			rnd = 239 + rand() % 3;
			break;
		}
		case 3: //Fnd (242-398)
		{
			rnd = 242 + rand() % 157;
			break;
		}
		case 4: //F (399-567)
		{
			rnd = 399 + rand() % 169;
			break;
		}
		case 5: //EX (568-601)
		{
			rnd = 568 + rand() % 34;
			break;
		}
		case 6: //2nd (602-806)
		{
			rnd = 602 + rand() % 205;
			break;
		}
		case 7: //1st (807-1002)
		{
			rnd = 807 + rand() % 196;
			break;
		}
		case 8: //SteamCards (1003-1014)
		{
			rnd = 1003 + rand() % 12;
			break;
		}
		case 9: //MikuFlick1&2 (1015-1017)
		{
			rnd = 1015 + rand() % 3;
			break;
		}
		default: //All
		{
			rnd = rand() % 1018;
			break;
		}
	}
	
	int first = rnd / 1000;
	rnd = rnd % 1000;
	int second = rnd / 100;
	rnd = rnd % 100;
	int third = rnd / 10;
	rnd = rnd % 10;
	int fourth = rnd;
	load_bg(first, second, third, fourth);
}

void set_load_style(int x1)
{
	switch (x1) 
	{
	case 1: //X
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'p', 'j', 'x');
		break;

	case 2: //FT
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'p', 'f', 't');
		break;

	case 3: //F2nd
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'd', 'f', '2');
		break;

	case 4: //F
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'p', 'j', 'f');
		break;

	case 5: //EX
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'p', 'e', 'x');
		break;

	case 6: //2nd
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'p', 'j', 'd');
		break;

	default: //M39's
		rorn = 'r';
		WRITE_MEMORY(sigNowLoading(), uint8_t, 'n', 'o', 'w');
		break;
	}

	if (x1 != 0)
	{
		rorn = 'n';
	}

	//1.0.0 0x140CC9008
	//1.0.1 0x140CC3178
	WRITE_MEMORY(0x140CC21D8, uint8_t, rorn); //rights_list

	//1.0.0 0x140CC9028
	//1.0.1 0x140CC3108
	WRITE_MEMORY(0x140CC2168, uint8_t, rorn); //rights_bg01

	//1.0.0 0x140CC9018
	//1.0.1 0x140CC30F8
	WRITE_MEMORY(0x140CC21E8, uint8_t, rorn); //rights_bg02

	//1.0.0 0x140CC90B8
	//1.0.1 0x140CC3198
	WRITE_MEMORY(0x140CC21F8, uint8_t, rorn); //rights_base_man

	//1.0.0 0x140CC90C8
	//1.0.1 0x140CC31A8
	WRITE_MEMORY(0x140CC2208, uint8_t, rorn); //rights_base_arr

	//1.0.0 0x140CC9048
	//1.0.1 0x140CC31B8
	WRITE_MEMORY(0x140CC2218, uint8_t, rorn); //rights_base_lyr

	//1.0.0 0x140CC9058
	//1.0.1 0x140CC3138
	WRITE_MEMORY(0x140CC2228, uint8_t, rorn); //rights_base_mus

	//1.0.0 0x140CC9098
	//1.0.1 0x140CC31E0
	WRITE_MEMORY(0x140CC2250, uint8_t, rorn); //rights_base_pv

	//1.0.0 0x140CC90A8
	//1.0.1 0x140CC3188
	WRITE_MEMORY(0x140CC2260, uint8_t, rorn); //rights_base_gui

	//1.0.0 0x140CC9080
	//1.0.1 0x140CC31C8
	WRITE_MEMORY((char*)0x140CC2238+0x02, uint8_t, rorn); //p_rights_name%02d_lt

	//1.0.0 0x140CC915A
	//1.0.1 0x140CC3160
	WRITE_MEMORY((char*)0x140CC21C0+0x02, uint8_t, rorn); //p_rights_song_lt
}

void random_load()
{
	rnd2 = (rand() % 7);
	set_load_style(rnd2);
}

HOOK(__int64, __fastcall, _LoadingScreen, sigLoadingScreen(), int a1)
{
	original_LoadingScreen(a1);
	random_bg();
	if (loadingStyle == -1) //Set to Random
	{
		random_load();
	}
	return 0;
}

extern "C" __declspec(dllexport) void Init()
{
	printf("[Complete Loading Screen Collection for MM+] Initializing...\n");
	try
	{
		config = toml::parse_file("config.toml");
		try
		{
			randomLoading = config["Random_Loading"].value_or(0);
			loadingStyle = config["Loading_Style"].value_or(0);
		}
		catch (std::exception& exception)
		{
			char text[1024];
			sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
			MessageBoxA(nullptr, text, "Complete Loading Screen Collection for MM+", MB_OK | MB_ICONERROR);
		}
	}
	catch (std::exception& exception)
	{
		char text[1024];
		sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
		MessageBoxA(nullptr, text, "Complete Loading Screen Collection for MM+", MB_OK | MB_ICONERROR);
	}

	srand(time(NULL));
		
	random_bg();

	if (loadingStyle != -1)
	{
		set_load_style(loadingStyle);
	}

	INSTALL_HOOK(_LoadingScreen);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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
