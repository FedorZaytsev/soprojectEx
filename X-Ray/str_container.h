/*
*	S.T.A.L.K.E.R.- str_container class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

struct str_value
{
	unsigned long	ref;
	unsigned long	len;
	unsigned long	crc;
	unsigned long	Unknown;
	char	string;
};

class __declspec(dllimport) str_container
{
public:
	str_container();
	~str_container();

	str_value* dock(char const*);
	void clean(void);
	void verify(void);
	void dump(void);
	unsigned int stat_economy(void);
};