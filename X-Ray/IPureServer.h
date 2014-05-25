/*
*	S.T.A.L.K.E.R.- IPureServer class
*	Disassembly by:
*		009 (Михайлов Алексей)
*/

//class ClientID {};

class __declspec(dllimport) IPureServer
{
public:
	IPureServer();
	~IPureServer();

	virtual void GetServerInfo(class CServerInfo *);
	virtual void BanAddress(struct ip_address const &, unsigned int);
	virtual void BanClient(class IClient *, unsigned int);
	void BannedList_Load(void);
	void BannedList_Save(void);
	virtual bool Check_ServerAccess(class IClient *, char (&)[512]);
	void ClearStatistic(void);
	int Connect(char *Src, int);
	virtual void Disconnect(void);
	virtual bool DisconnectAddress(struct ip_address const &, char const *);
	virtual bool DisconnectClient(class IClient *, char const *);
	virtual void Flush_Clients_Buffers(void);
	class IBannedClient * GetBannedClient(struct ip_address const &);
	char const * GetBannedListName(void);
	bool GetClientAddress(class ClientID, struct ip_address &, unsigned long *);
	bool GetClientAddress(struct IDirectPlay8Address *, struct ip_address &, unsigned long *);
	class IClient * GetClientByID(class ClientID);
	unsigned int GetClientsCount(void);
	class shared_str const & GetConnectOptions(void) const;
	int GetPort(void);
	class IClient * GetServerClient(void);
	class IServerStatistic const * GetStatistic(void);
	int HasBandwidth(class IClient *);
	class IClient * ID_to_client(class ClientID, bool);
	void IpList_Load(void);
	void IpList_Unload(void);
	bool IsPlayerIPDenied(unsigned int);
	void Print_Banned_Addreses(void);
	virtual void SendBroadcast(class ClientID, class NET_Packet &, unsigned int);
	void SendBroadcast_LL(class ClientID, void *, unsigned int, unsigned int);
	void SendTo(class ClientID, class NET_Packet &, unsigned int, unsigned int);
	virtual void SendTo_Buf(class ClientID, void *, unsigned int, unsigned int, unsigned int);
	virtual void SendTo_LL(class ClientID, void *, unsigned int, unsigned int, unsigned int);
	virtual void UnBanAddress(struct ip_address const &);
	void UpdateBannedList(void);
	void UpdateClientStatistic(class IClient *);
	int Recieve(void *Src, size_t Size, int, int);
	long net_Handler(unsigned int, void *);
};