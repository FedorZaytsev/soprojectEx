/*
*	S.T.A.L.K.E.R.- CApplication class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "CEvent.h"
#include "IEventReceiver.h"
#include "pureFrame.h"
#include "CGameFont.h"

class __declspec(dllimport) CApplication:
	IEventReceiver,
	pureFrame
{
public:
	CApplication();
	~CApplication();

	int GetArchiveHeader(char const *,char const *);
	void Level_Append(char const *);
	int Level_ID(char const *,char const *,bool);
	void Level_Scan(void);
	void Level_Set(unsigned int);
	void LoadAllArchives(void);
	void LoadBegin(void);
	void LoadDraw(void);
	void LoadEnd(void);
	void LoadStage(void);
	void LoadSwitch(void);
	void LoadTitleInt(char const *,char const *,char const *);
	int OnEvent(CEvent *,unsigned __int64,unsigned __int64);
	virtual void OnFrame(void);
	void destroy_loading_shaders(void);
	void load_draw_internal(void);

	char unknown[0x1829]; // 0x0
	CGameFont* pFont; // 0x1830
};