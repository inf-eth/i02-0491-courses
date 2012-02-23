// Client Interface. Client can be TCP or UDP.
#define MAXBUFFERSIZE	512
#define TCPSOCKET		0
#define UDPSOCKET		1
#define DEFAULTPORT		6001
#include <arpa/inet.h>
class CClient
{
private:
	int Type;
	int ClientPort;
public:
	CClient (int = TCPSOCKET, int = DEFAULTPORT);
	int test;
};
