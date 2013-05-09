#include "../Packet/Packet.h"

struct RoutingTableEntry
{

	int Destination;
	int NextHop;
	int Cost;

};

class CRoutingTable
{

	public:

	CRoutingTable ( );
	int AddEntry ( int, int, int );
	RoutingTableEntry GetEntry ( int );
	void DisplayRoutingTable ( );
	int  SearchEntry ( int );

	// * Index Operator.
	RoutingTableEntry * operator [] ( int );
	
	int GetNextHop ( int );
	
	private:

	int NoOfEntries;
	CLinkedList *RoutingTablePTR;
	
};
 
