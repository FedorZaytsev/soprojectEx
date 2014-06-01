#ifndef CLIENT_ID_H
#define CLIENT_ID_H
/*
*	S.T.A.L.K.E.R.
*/

class  ClientID
{
public:
	unsigned int  id;
			ClientID		():id(0)			{};
			ClientID		(unsigned int val):id(val)	{};
	
	unsigned int			value			()const							{return id;};
	void	set				(unsigned int v)							{id=v;};
	
	bool	compare			(unsigned int v) const					{ return id == v;};
	bool	operator ==		(const ClientID& other)const	{ return value() == other.value();};
	bool	operator !=		(const ClientID& other)const	{ return value() != other.value();};
	bool	operator <		(const ClientID& other)const	{ return value() < other.value();};
};

#endif
