// Implementation file for the CRoutingTable.

#include "RoutingTable.h"
#include <iostream>

using namespace std;

CRoutingTable::CRoutingTable ( )
{

	RoutingTablePTR = new CLinkedList;
	NoOfEntries = 0;
	
}

int CRoutingTable::AddEntry ( int Destination, int NextHop, int Cost )
{

	int SearchIndex = 0;
	if ( ( SearchIndex = SearchEntry ( Destination ) ) != -1 )
	{
		
		if ( (*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).Destination == Destination  && (*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).NextHop == NextHop && (*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).Cost == Cost )
		{
		
//			cout << "Dupe addition detected." << endl;
			return -1;
				
		}
		else
		{
		
			(*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).Destination = Destination;
			(*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).NextHop = NextHop;
			(*(RoutingTableEntry *)(*RoutingTablePTR)[SearchIndex]).Cost = Cost;
			cout << "Routing Table updated." << endl;
			return 1;
			
		}		

	}

	RoutingTableEntry * SingleRoutingTableEntry = new RoutingTableEntry;
	(*SingleRoutingTableEntry).Destination = Destination;
	(*SingleRoutingTableEntry).NextHop = NextHop;
	(*SingleRoutingTableEntry).Cost = Cost;

	(*RoutingTablePTR).Add ( (void *)SingleRoutingTableEntry );

	NoOfEntries++;
	
	return 0;

}
/*
CLinkedList CGraph::AddLinkedList ( CLinkedList *PassedLinkedList )
{

	for ( int i=0; i<NoOfNode; i++ )
	{

		( *(*GraphPTR)[i] ).IndexReset ( );
		if ( 1 )
		{
		}

	}

}
*/
RoutingTableEntry CRoutingTable::GetEntry ( int EntryNumber )
{

	RoutingTableEntry ToReturn;
	ToReturn.Destination = -1;
	ToReturn.NextHop = -1;
	ToReturn.Cost = -1;

	if ( EntryNumber >= NoOfEntries || EntryNumber < 0 )
	{

		return ToReturn;

	}
	return *(RoutingTableEntry *)(*RoutingTablePTR)[EntryNumber];

}

void CRoutingTable::DisplayRoutingTable ( )
{

	cout << "*** Displaying RoutingTable... ***" << endl;
	cout << "No of Entries = " << NoOfEntries;
	for ( int i=0; i<NoOfEntries; i++ )
	{
		
		cout << endl << (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).Destination;
		cout << " "  << (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).NextHop;
		cout << " "  << (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).Cost;
		
	}
	cout << endl << "***********************" << endl;
	
}

int CRoutingTable::SearchEntry ( int NodeID )
{

	for ( int i=0; i<NoOfEntries; i++ )
	{

		if ( (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).Destination == NodeID )
		{
			return i;
		}

	}
	
	return -1;

}

RoutingTableEntry * CRoutingTable::operator [] ( int Index )
{

	if ( NoOfEntries == 0 || Index < 0 || Index >= NoOfEntries )
	{
		return NULL;
	}
	
	return (RoutingTableEntry *)(*RoutingTablePTR)[Index];

}
 
int CRoutingTable::GetNextHop ( int Destination )
{

	for ( int i=0; i<NoOfEntries; i++ )
	{

		if ( (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).Destination == Destination )
		{
			return (*(RoutingTableEntry *)(*RoutingTablePTR)[i]).NextHop;
		}

	}	
	
	return -1;

}

