/*
*	S.T.A.L.K.E.R.- IConsole_Command class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

class __declspec(dllimport) IConsole_Command
{
public:
	IConsole_Command(char const *);
	~IConsole_Command();

	void InvalidSyntax(void);
	/*
	virtual void Status(char (&)[256]);
	virtual void Info(char (&)[256]);
	virtual void Save(class IWriter *);
	*/

	void* ftable;
	char* cmd_name;
	unsigned char flag1;
	unsigned char flag2;
	unsigned char is_custom;
	unsigned char unknown[0x10];
};