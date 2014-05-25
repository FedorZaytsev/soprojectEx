/*
*	S.T.A.L.K.E.R.- IPureClient class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

#include "NET_Packet.h"

class __declspec(dllimport) IPureClient
{
public:
	IPureClient();
	~IPureClient();

	void ClearStatistic(void);
	int Connect(char *Src);
	void Disconnect(void);
	void EndProcessQueue(void);
	virtual void Flush_Send_Buffer(void);
	//const ClientID& GetClientID(void);
	virtual char const * GetMsgId2Name(unsigned short);
	bool GetServerAddress(struct ip_address &, unsigned long *);
	// IClientStatistic & GetStatistic(void);
	virtual void Send(class NET_Packet &, unsigned int, unsigned int);
	virtual void SendTo_LL(void *, unsigned int, unsigned int, unsigned int);
	char const* net_SessionName(void);
	unsigned int timeServer(void);
};