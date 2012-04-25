#include "../LinkedList/LinkedList.h"

#define MAXNODES    100

struct NeighbourInfo
{

	int Address;
	int Cost;

};

class CGraph
{

	public:

	CGraph ( );
	int AddNode ( int, int, NeighbourInfo * );
	CLinkedList GetNode ( int );
	void DisplayGraph ( );
	void DisplayDist ( );
	int  SearchNode ( int );

	void CalculateTranslation ( );
	void CalculateDist ( );
	// * Index Operator.
	CLinkedList * operator [] ( int );
	
	int GetID ( int );
	int GetIndex ( int );
	
	// THIS IS IT. Dijkstra's Algorithm.
	int shortest_path ( int, int, int * );
	
	int GetNextHopIndex ( int );
	int GetNextHop ( int, int );
	
	int GetNoOfEntries ( ) { return NoOfNodes; }
	private:

	int NoOfNodes;
	CLinkedList *GraphPTR;
	
	int *Translation;	
	int dist[MAXNODES][MAXNODES];
	
};
