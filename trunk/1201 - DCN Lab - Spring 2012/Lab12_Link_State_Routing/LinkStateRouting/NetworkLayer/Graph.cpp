// Implementation file for the CGraph.

#include "Graph.h"
#include <iostream>

using namespace std;

int Infinity = 10000;

CGraph::CGraph ( )
{

	GraphPTR = new CLinkedList;
	NoOfNodes = 0;

	for ( int i=0; i<MAXNODES; i++ )
	{
		for ( int j=0; j<MAXNODES; j++ )
		{

			dist[i][j] = Infinity;
			if ( i == j )
			{
				dist[i][j] = 0;
			}

		}

	}

	Translation = NULL;

}

int CGraph::AddNode ( int NodeNumber, int NoOfNeighbours, NeighbourInfo *Neighbour )
{

	int SearchIndex;
	int *IntPTR;
	bool DupeFlag = true;
	NeighbourInfo *NeighbourInfoPTR;

	if ( ( SearchIndex = SearchNode ( NodeNumber ) ) != -1 )
	{

		if ( NoOfNeighbours == *(int *)( *(CLinkedList *)(*GraphPTR)[SearchIndex] )[1] )
		{
			for ( int i=0; i<NoOfNeighbours; i++ )
			{

				if ( Neighbour[i].Address != (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[SearchIndex] )[i+2]).Address || Neighbour[i].Cost != (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[SearchIndex] )[i+2]).Cost )
				{
					DupeFlag = false;
				}

			}

			if ( DupeFlag == true )
			{

//				cout << "WARNING: Dupe entry in graph detected." << endl;
				return -1;

			}

		}

		(*(CLinkedList *)(*GraphPTR)[SearchIndex]).Empty ( );

		IntPTR = new int;
		*IntPTR = NodeNumber;
		(*(CLinkedList *)(*GraphPTR)[SearchIndex]).AddNoDupe ( (void *)IntPTR, 0 );

		IntPTR = new int;
		*IntPTR = NoOfNeighbours;
		(*(CLinkedList *)(*GraphPTR)[SearchIndex]).AddNoDupe ( (void *)IntPTR, 0 );

		for ( int i=0; i<NoOfNeighbours; i++ )
		{

			NeighbourInfoPTR = new NeighbourInfo;
			*NeighbourInfoPTR = Neighbour[i];
			(*(CLinkedList *)(*GraphPTR)[SearchIndex]).AddNoDupe ( (void *)NeighbourInfoPTR, 2 );

		}

		cout << "MESSAGE: Graph updated." << endl;

		return 1;

	}

	CLinkedList *SingleNodePTR = new CLinkedList;

	IntPTR = new int;
	*IntPTR = NodeNumber;
	(*SingleNodePTR).AddNoDupe ( (void *)IntPTR, 0 );

	IntPTR = new int;
	*IntPTR = NoOfNeighbours;
	(*SingleNodePTR).AddNoDupe ( (void *)IntPTR, 0 );

	for ( int i=0; i<NoOfNeighbours; i++ )
	{

		NeighbourInfoPTR = new NeighbourInfo;
		*NeighbourInfoPTR = Neighbour[i];
		(*SingleNodePTR).AddNoDupe ( (void *)NeighbourInfoPTR, 2 );

	}

	(*GraphPTR).Add ( (void *)SingleNodePTR );

	NoOfNodes++;

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
CLinkedList CGraph::GetNode ( int NodeNumber )
{

	CLinkedList ToReturn;

	if ( NodeNumber >= NoOfNodes || NodeNumber < 0 )
	{

		return ToReturn;

	}
	return *(CLinkedList *)(*GraphPTR)[NodeNumber];

}

void CGraph::DisplayGraph ( )
{

	cout << "*** Displaying graph... ***" << endl;
	cout << "No of Nodes = " << NoOfNodes;
	for ( int i=0; i<NoOfNodes; i++ )
	{

		cout << endl << *(int *)( *(CLinkedList *)(*GraphPTR)[i] )[0];

		cout << " " << *(int *)( *(CLinkedList *)(*GraphPTR)[i] )[1];

		for ( int j=2; j<( *(CLinkedList *)(*GraphPTR)[i] ).GetNoOfEntries ( ); j++ )
		{

			cout << " " << (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[i] )[j]).Address;
			cout << " " << (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[i] )[j]).Cost;

		}

	}
	cout << endl << "***********************" << endl;

}

int CGraph::SearchNode ( int NodeID )
{

	for ( int i=0; i<NoOfNodes; i++ )
	{

		if ( *(int *)(*(CLinkedList *)(*GraphPTR)[i])[0] == NodeID )
		{
			return i;
		}

	}

	return -1;

}

CLinkedList * CGraph::operator [] ( int Index )
{

	if ( NoOfNodes == 0 || Index < 0 || Index >= NoOfNodes )
	{
		return NULL;
	}

	return (CLinkedList *)(*GraphPTR)[Index];

}

void CGraph::CalculateTranslation ( )
{

	if ( Translation != NULL )
	{
		delete Translation;
	}

	Translation = new int[NoOfNodes];

	for ( int i=0; i<NoOfNodes; i++ )
	{
		Translation[i] = *(int *)(*(CLinkedList *)(*GraphPTR)[i])[0];
	}

}

int CGraph::GetID ( int Index )
{

	if ( NoOfNodes == 0 || Index < 0 || Index >= NoOfNodes )
	{
		return -1;
	}

	return Translation[Index];

}

int CGraph::GetIndex ( int ID )
{

	for ( int i=0; i<NoOfNodes; i++ )
	{

		if ( ID == Translation[i] )
		{
			return i;
		}

	}
	return -1;
}

void CGraph::CalculateDist ( )
{

	int NoOfNeighbours;

	for ( int i=0; i<NoOfNodes; i++ )
	{

		NoOfNeighbours = *(int *)(*(CLinkedList *)(*GraphPTR)[i])[1];
		NeighbourInfo Neighbour[NoOfNeighbours];

		for ( int j=0; j<NoOfNeighbours; j++ )
		{

			int Index = GetIndex( (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[i] )[j+2]).Address );
			if ( Index != -1 )
			{
				dist[i][ Index ] = (*(NeighbourInfo *)( *(CLinkedList *)(*GraphPTR)[i] )[j+2]).Cost;
			}

		}

	}

}

void CGraph::DisplayDist ( )
{

	cout << "******* Displaying Distances *********";
	for ( int i=0; i<NoOfNodes; i++ )
	{
		cout << endl;
		for ( int j=0; j<NoOfNodes; j++ )
		{

			cout << dist[i][j];
			cout << " ";

		}
	}
	cout << endl;

}

int CGraph::shortest_path ( int s, int t, int * path )
{

//  cout << "MESSAGE: Calculating shortest path from source " << GetID(s) << " to destination " << GetID(t) << endl;
	int n = NoOfNodes;

	struct state
	{

		int predecessor;
		int length;
		int label;

	} state[MAXNODES];

	int i, k, min;

	struct state *p;

	for ( p = &state[0]; p < &state[n]; p++ )
	{

		(*p).predecessor = -1;
		(*p).length = Infinity;
		(*p).label = 0;

	}

	state[t].length = 0; state[t].label = 1;
	k = t;

	do
	{

		for ( i=0; i<n; i++ )
		{

			if ( dist[k][i] != 0 && state[i].label == 0 )
			{

				if ( state[k].length + dist[k][i] < state[i].length )
				{

					state[i].predecessor = k;
					state[i].length = state[k].length + dist[k][i];

				}

			}

		}

        k = 0; min = Infinity;

        for ( i=0; i<n; i++ )
        {

            if ( state[i].label == 0 && state[i].length < min )
            {

                min = state[i].length;
                k = i;

            }

        }
		state[k].label = 1;
	}
	while ( k != s );

	i = 0; k = s;
	do
	{
	    path[i++] = k;
	    k = state[k].predecessor;
    }
    while ( k>=0 );

    cout << endl;

	return state[s].predecessor;

}

int CGraph::GetNextHop  ( int Source, int Destination )
{

	int s = GetIndex ( Source );
	int t = GetIndex ( Destination );
	int *path = new int[MAXNODES];

	int Index = shortest_path ( s, t, path );

	int NextHopIndex = path[Index-1];
	cout << "Source       = " << Source << endl;
	cout << "Dest         = " << Destination << endl;
	//cout << "Source Index = " << s << endl;
	//cout << "Dest   Index = " << t << endl;
	cout << "Path   = ";
	for (int i=0; i<MAXNODES; i++)
	{
		cout << GetID(path[i]) << " ";
		if (path[i] == t)
			break;
	}
	cout << endl;

	return GetID ( Index );

}

