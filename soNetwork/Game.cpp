/*
*	S.T.A.L.K.E.R. Online - Game controll
*	Developers:
*		009 (Михайлов Алексей)
*/

#include <windows.h>

#include "Game.h"
#include "../shared/hook.h"
#include "../shared/log.h"

extern CLog* LogHandle;
extern CHook* HookHandle;

void GameThread(void*)
{
	LogHandle->Write("Game controll thread started");
	// loop
	while(true)
	{
		while(!HookHandle->IsServer()) Sleep(100);

		/*
		if(GetAsyncKeyState(VK_NUMPAD1))
		{
			while(GetAsyncKeyState(VK_NUMPAD1)) Sleep(10);
			
			LogHandle->Write("try create my own [bloodsucker_strong]");
			
			unsigned short objectid = HookHandle->CreateObject("bloodsucker_strong","bloodsucker",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD2))
		{
			while(GetAsyncKeyState(VK_NUMPAD2)) Sleep(10);
			
			LogHandle->Write("try create my own [burer_online]");
			
			unsigned short objectid = HookHandle->CreateObject("burer_online","burer",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD3))
		{
			while(GetAsyncKeyState(VK_NUMPAD3)) Sleep(10);
			
			LogHandle->Write("try create my own [gigant_online]");
			
			unsigned short objectid = HookHandle->CreateObject("gigant_online","gigant",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD4))
		{
			while(GetAsyncKeyState(VK_NUMPAD4)) Sleep(10);
			
			LogHandle->Write("try create my own [controller_online]");
			
			unsigned short objectid = HookHandle->CreateObject("controller_online","controller",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD5))
		{
			while(GetAsyncKeyState(VK_NUMPAD5)) Sleep(10);
			
			LogHandle->Write("try create my own [snork_online]");
			
			unsigned short objectid = HookHandle->CreateObject("snork_online","snork",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD6))
		{
			while(GetAsyncKeyState(VK_NUMPAD6)) Sleep(10);
			
			LogHandle->Write("try create my own [poltergeist_online_tele]");
			
			unsigned short objectid = HookHandle->CreateObject("poltergeist_online_tele","poltergeist_tele",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState(VK_NUMPAD7))
		{
			while(GetAsyncKeyState(VK_NUMPAD7)) Sleep(10);
			
			LogHandle->Write("try create my own [poltergeist_online_flame]");
			
			unsigned short objectid = HookHandle->CreateObject("poltergeist_online_flame","poltergeist_flame",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		
		if(GetAsyncKeyState(VK_NUMPAD8))
		{
			while(GetAsyncKeyState(VK_NUMPAD8)) Sleep(10);
			
			LogHandle->Write("try create my own [stalker_online]");
			
			unsigned short objectid = HookHandle->CreateObject("stalker_online","stalker",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
			
			unsigned short wobjectid = HookHandle->CreateObject("mp_wpn_ak74","stalker_wpn",128.488358f,-0.583647f,372.461487f,objectid);
			LogHandle->Write("wobjectid %d",wobjectid);
			
			unsigned short aobjectid = HookHandle->CreateObject("mp_ammo_5.45x39_ap","stalker_ammo",128.488358f,-0.583647f,372.461487f,objectid);
			LogHandle->Write("wobjectid %d",aobjectid);
		}
		// not work
		if(GetAsyncKeyState('1'))
		{
			while(GetAsyncKeyState('1')) Sleep(10);
			
			LogHandle->Write("try create my own [boar_online]");
			
			unsigned short objectid = HookHandle->CreateObject("boar_online","boar",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('2'))
		{
			while(GetAsyncKeyState('2')) Sleep(10);
			
			LogHandle->Write("try create my own [chimera_online]");
			
			unsigned short objectid = HookHandle->CreateObject("chimera_online","chimera",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('3'))
		{
			while(GetAsyncKeyState('3')) Sleep(10);
			
			LogHandle->Write("try create my own [crow_online]");
			
			unsigned short objectid = HookHandle->CreateObject("crow_online","crow",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('4'))
		{
			while(GetAsyncKeyState('4')) Sleep(10);
			
			LogHandle->Write("try create my own [dog_online]");
			
			unsigned short objectid = HookHandle->CreateObject("dog_online","dog",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('5'))
		{
			while(GetAsyncKeyState('5')) Sleep(10);
			
			LogHandle->Write("try create my own [flesh_online]");
			
			unsigned short objectid = HookHandle->CreateObject("flesh_online","flesh",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		
		if(GetAsyncKeyState('6'))
		{
			while(GetAsyncKeyState('6')) Sleep(10);
			
			LogHandle->Write("try create my own [pseudodog_online]");
			
			unsigned short objectid = HookHandle->CreateObject("pseudodog_online","pseudodog",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		
		if(GetAsyncKeyState('7'))
		{
			while(GetAsyncKeyState('7')) Sleep(10);
			
			LogHandle->Write("try create my own [tushkano_online]");
			
			unsigned short objectid = HookHandle->CreateObject("tushkano_online","tushkano",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('8'))
		{
			while(GetAsyncKeyState('8')) Sleep(10);
			
			LogHandle->Write("try create my own [car_online]");
			
			unsigned short objectid = HookHandle->CreateObject("car_online","car",128.488358f,-0.583647f,372.461487f,-1);
			LogHandle->Write("object %d",objectid);
		}
		if(GetAsyncKeyState('9'))
		{
			while(GetAsyncKeyState('9')) Sleep(10);
			
			LogHandle->Write("===========================================");
			for(int i = 0;i < 65535;i++)
			{
				if((int)HookHandle->g_pGameLevel->ObjectList.objects[i] > 0x400000)
				{
					CObject * obj = HookHandle->g_pGameLevel->ObjectList.objects[i];

					if(!strcmp("mp_actor",obj->cNameSect_str()))
					{
						_vector3<float> pos = obj->Position();

						LogHandle->Write("Position take [%f,%f,%f]",pos.x,pos.y,pos.z);
					}
				}
			}
		}
		*/
		/*
		if(GetAsyncKeyState(VK_SPACE))
		{
			if(GetAsyncKeyState(VK_NUMPAD8))
			{
				while(GetAsyncKeyState(VK_NUMPAD8)) Sleep(10);
			
				LogHandle->Write("try create my own [stalker_online]");
			
#define SPAWN_POS	128.488358f,-0.583647f,372.461487f
//#define SPAWN_POS	282.99f,21.66f,565.22f

				unsigned short objectid = HookHandle->CreateCustomSyncObject("stalker_online","stalker",SPAWN_POS,-1);
				LogHandle->Write("created %d",objectid);
				unsigned short wobjectid = HookHandle->CreateObject("mp_wpn_ak74","stalker_wpn",SPAWN_POS,objectid);
				LogHandle->Write("wobjectid %d",wobjectid);
				wobjectid = HookHandle->CreateObject("mp_ammo_5.45x39_ap","stalker_ammo",SPAWN_POS,objectid);
				LogHandle->Write("wobjectid %d",wobjectid);
			}
		}\*/
		/*
		if(GetAsyncKeyState('6'))
		{
			while(GetAsyncKeyState('6')) Sleep(10);
			
			LogHandle->Write("objects list (client):");
			
			for(int i = 0;i < 65535;i++)
			{
				if((int)HookHandle->g_pGameLevel->ObjectList.objects[i] > 0x400000)
				{
					LogHandle->Write("object id %d exist.addr 0x%X",i,(int)HookHandle->g_pGameLevel->ObjectList.objects[i]);
					CObject * obj = HookHandle->g_pGameLevel->ObjectList.objects[i];
					//LogHandle->Write("CObject handle 0x%x",(DWORD)(obj));
					LogHandle->Write("Name [%s]",obj->cNameSect_str());
					_vector3<float> pos = obj->Position();
					_vector3<float> dir = obj->Direction();

					LogHandle->Write("Position take [%f,%f,%f]",pos.x,pos.y,pos.z);
					LogHandle->Write("Direction take [%f,%f,%f]",dir.x,dir.y,dir.z);
					LogHandle->Write("getDestroy [%d]",obj->getDestroy());
					LogHandle->Write("getEnabled [%d]",obj->getEnabled());
					LogHandle->Write("getLocal [%d]",obj->getLocal());
					LogHandle->Write("getReady [%d]",obj->getReady());
					LogHandle->Write("getSVU [%d]",obj->getSVU());
					LogHandle->Write("getVisible [%d]",obj->getVisible());
					LogHandle->Write("processing_enabled [%d]",obj->processing_enabled());
					LogHandle->Write("shedule_Needed [%d]",obj->shedule_Needed());
					//LogHandle->Write("shedule_Scale [%f]",obj->shedule_Scale());
					//LogHandle->Write("Radius [%f]",obj->Radius());
					LogHandle->Write("AmICrow [%d]",obj->AmICrow());
					
					//LogHandle->Write("[0x%X] - [%s] - [%f,%f,%f]",(int)HookHandle->g_pGameLevel->ObjectList.objects[i],obj->cNameSect_str(),pos.x,pos.y,pos.z);
				}
			}
		}
/*
		if(GetAsyncKeyState(VK_NUMPAD8))
		{
			while(GetAsyncKeyState(VK_NUMPAD8)) Sleep(10);
			
			LogHandle->Write("try create my own [stalker_online] 2");

			unsigned short objectid = HookHandle->CreateObject("stalker_online","111",128.488358f,-0.583647f,372.461487f);
			stalkers[0] = (DWORD)HookHandle->GetObjectHandle(objectid);
			
			objectid = HookHandle->CreateObject("stalker_online","111",128.488358f,-0.583647f,372.461487f);
			stalkers[1] = (DWORD)HookHandle->GetObjectHandle(objectid);
			
			LogHandle->Write("created");
		}
		if(GetAsyncKeyState(VK_NUMPAD1))
		{
			while(GetAsyncKeyState(VK_NUMPAD1)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 1");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0x7C) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0x7C);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD2))
		{
			while(GetAsyncKeyState(VK_NUMPAD2)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 2");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0x80) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0x80);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD3))
		{
			while(GetAsyncKeyState(VK_NUMPAD3)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 3");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0x88) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0x88);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD4))
		{
			while(GetAsyncKeyState(VK_NUMPAD4)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 4");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0x8C) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0x8C);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD5))
		{
			while(GetAsyncKeyState(VK_NUMPAD5)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 5");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0xB8) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0xB8);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD6))
		{
			while(GetAsyncKeyState(VK_NUMPAD6)) Sleep(10);
			
			LogHandle->Write("reset visual pointer 6");

			*(DWORD*)(*(DWORD*)(stalkers[0] + 0x90) + 0xC8) = *(DWORD*)(*(DWORD*)(stalkers[1] + 0x90) + 0xC8);
			
			LogHandle->Write("completed");
		}
		if(GetAsyncKeyState(VK_NUMPAD7))
		{
			while(GetAsyncKeyState(VK_NUMPAD7)) Sleep(10);
			
			LogHandle->Write("IsApplyAnim");

			if(IsApplyAnim) IsApplyAnim = false;
			else IsApplyAnim = true;
			
			LogHandle->Write("completed");
		}
		*/

		/*
		if(GetAsyncKeyState(VK_NUMPAD9))
		{
			while(GetAsyncKeyState(VK_NUMPAD9)) Sleep(10);
			
			LogHandle->Write("try create my own [burer_online]");
			
			unsigned short objectid = HookHandle->CreateObject("burer_online","111",128.488358f,-0.583647f,372.461487f);
			CObject* obj = HookHandle->GetObjectHandle(objectid);
			LogHandle->Write("Object [%d] spawned, handle [0x%X], name [%s] local [%d]",objectid,obj,obj->cNameSect_str(),obj->getLocal());
			
			LogHandle->Write("getDestroy [%d]",obj->getDestroy());
			LogHandle->Write("getEnabled [%d]",obj->getEnabled());
			LogHandle->Write("getLocal [%d]",obj->getLocal());
			LogHandle->Write("getReady [%d]",obj->getReady());
			LogHandle->Write("getSVU [%d]",obj->getSVU());
		}

		if(GetAsyncKeyState(VK_F12))
		{
			while(GetAsyncKeyState(VK_F12)) Sleep(10);
			
			LogHandle->Write("try create my own [car_online]");
			
			unsigned short objectid = HookHandle->CreateObject("car_online","vehicle",130.488358f,-0.583647f,372.461487f);
			CObject* obj = HookHandle->GetObjectHandle(objectid);
			LogHandle->Write("Object [%d] spawned, handle [0x%X], name [%s] local [%d]",objectid,obj,obj->cNameSect_str(),obj->getLocal());
		}

		if(GetAsyncKeyState('5'))
		{
			while(GetAsyncKeyState('5')) Sleep(10);
			
			LogHandle->Write("objects list (server):");
			
			DWORD GameLevel = (DWORD)HookHandle->g_pGameLevel;
			DWORD xrServerHandle = *(DWORD*)(GameLevel + 0x48728);
			DWORD EntityHandle = *(DWORD*)(xrServerHandle + 0xA0);

			LogHandle->Write("GameLevel 0x%X",GameLevel);
			LogHandle->Write("xrServerHandle 0x%X",xrServerHandle);
			LogHandle->Write("EntityHandle 0x%X",EntityHandle);

			while(EntityHandle)
			{
				//LogHandle->Write("finded entity on addr: 0x%X",EntityHandle);
				DWORD CSE_Abstract_Handle = *(DWORD*)(EntityHandle + 0x8);
				//LogHandle->Write("CSE_Abstract_Handle 0x%X",CSE_Abstract_Handle);
				DWORD CSE_Abstract_Funclist = *(DWORD*)CSE_Abstract_Handle;
				//LogHandle->Write("CSE_Abstract_Funclist 0x%X",CSE_Abstract_Funclist);
				char* (_cdecl * CSE_Abstract_cNameSect_str)(DWORD) = reinterpret_cast<char* (_cdecl *)(DWORD)>( *(DWORD*)(CSE_Abstract_Funclist + 0x8));
				//LogHandle->Write("CSE_Abstract_cNameSect_str [%s]",CSE_Abstract_cNameSect_str(CSE_Abstract_Handle));
				
				//LogHandle->Write("EntityHandle 0x%X",EntityHandle);
				//LogHandle->Write("CSE_Abstract_Handle 0x%X",CSE_Abstract_Handle);
				//DWORD name_string = *(DWORD*)(CSE_Abstract_Handle + 0x3C);
				//LogHandle->Write("section: %s",(char*)(name_string + 0x10));
				//LogHandle->Write("name: %s",*(char**)(CSE_Abstract_Handle + 0x20));

				LogHandle->Write("[0x%X] - [%f,%f,%f] - [%s]",EntityHandle,*(FLOAT*)(CSE_Abstract_Handle + 0x54),*(FLOAT*)(CSE_Abstract_Handle + 0x58),*(FLOAT*)(CSE_Abstract_Handle + 0x5C),CSE_Abstract_cNameSect_str(CSE_Abstract_Handle));

				EntityHandle = *(DWORD*)EntityHandle;
			}
		}
		*/
		Sleep(10);
	}
	LogHandle->Write("Game controll thread completed");
}