/*
*	S.T.A.L.K.E.R.- CConsole class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "IConsole_Command.h"

class __declspec(dllimport) CConsole
{
public:
	CConsole();
	~CConsole();

	virtual void Initialize(void);
	virtual void Destroy(void);
	void AddCommand(IConsole_Command *);
	void RemoveCommand(IConsole_Command *);
	void OutFont(char const *, float &);
	void ExecuteCommand(char const *, bool);
	void Show(void);
	void Hide(void);
	void SelectCommand(void);
	void Execute(char const *);
	void ExecuteScript(char const *);
	IConsole_Command* find_next_cmd(char const *, class shared_str &);
};