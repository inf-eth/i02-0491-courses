// Linked List's Implementation.

#include "LinkedList.h"
#include <iostream>
#include <string.h>

using namespace std;

bool IsMatch( char *, char * );

// Standard Constructor.
CLinkedList::CLinkedList ( )
{

	FirstNode = LastNode = Index = NULL;

	NoOfEntries = 0;

}

// Standard Destructor.
CLinkedList::~CLinkedList ( )
{

	Node *Temp1;
	Node *Temp2;

	Temp1 = Temp2 = FirstNode;

	while ( Temp1 != NULL )
	{

		Temp2 = (*Temp1).NextNode;
		delete Temp1;
		Temp1 = Temp2;

	}

}

// Add a Node.
void CLinkedList::Add ( void *PassedEntry )
{

	Node *Temp;
	Temp = new Node;

	// If this is the first entry.
	if ( FirstNode == NULL )
	{

		FirstNode = Temp;
		LastNode  = Temp;

		(*Temp).PreviousNode = NULL;
		(*Temp).NextNode = NULL;
		(*Temp).Payload = PassedEntry;

		Index = FirstNode;

	}
	else
	{

		(*LastNode).NextNode = Temp;
		(*Temp).PreviousNode = LastNode;
		(*Temp).NextNode = NULL;
		(*Temp).Payload = PassedEntry;

		LastNode = Temp;

		Index = LastNode;

	}

	NoOfEntries++;

}

// Add without duping
int CLinkedList::AddNoDupe ( void *PassedEntry, int DupeCode )
{

	// If an int is being added.
	if ( DupeCode == 0 )
	{
		// Checking the addition of duped entry.
		Node *CurrentNode = FirstNode;
		while ( CurrentNode != NULL )
		{

			if ( *( (int *)(*CurrentNode).Payload ) == *( (int *)(PassedEntry) ) )
			{

				cout << "Duplicate addition detected. Aborting." << endl;
				return -1;

			}
			CurrentNode = (*CurrentNode).NextNode;

		}
	}

	// Dupe check complete.

	// If a string is being added.
	if ( DupeCode == 1 )
	{

		if ( (*this).ExactSearch ( (char *)PassedEntry ) != -1 )
		{
			return -2;
		}

	}

	if ( DupeCode == 2 )
	{

	}

    // If an unsigned int is being added.
	if ( DupeCode == 3 )
	{
		// Checking the addition of duped entry.
		Node *CurrentNode = FirstNode;
		while ( CurrentNode != NULL )
		{

			if ( *( (unsigned int *)(*CurrentNode).Payload ) == *( (unsigned int *)(PassedEntry) ) )
			{

				cout << "Duplicate addition detected. Aborting." << endl;
				return -1;

			}
			CurrentNode = (*CurrentNode).NextNode;

		}
	}

	Node *Temp;
	Temp = new Node;

	// If this is the first entry.
	if ( FirstNode == NULL )
	{

		FirstNode = Temp;
		LastNode  = Temp;

		(*Temp).PreviousNode = NULL;
		(*Temp).NextNode = NULL;
		(*Temp).Payload = PassedEntry;

		Index = FirstNode;

	}
	else
	{

		(*LastNode).NextNode = Temp;
		(*Temp).PreviousNode = LastNode;
		(*Temp).NextNode = NULL;
		(*Temp).Payload = PassedEntry;

		LastNode = Temp;

		Index = LastNode;

	}

	NoOfEntries++;
	return 0;

}

// Empty the linked list.
void CLinkedList::Empty ( )
{

	Node *Temp1;
	Node *Temp2;

	Temp1 = Temp2 = FirstNode;

	while ( Temp1 != NULL )
	{

		Temp2 = (*Temp1).NextNode;
		delete Temp1;
		Temp1 = Temp2;

	}

	FirstNode = LastNode = Index = NULL;
	NoOfEntries = 0;

}
void * CLinkedList::GetCurrent ( )
{

	return (*Index).Payload;

}

// Index Functions.
void CLinkedList::IndexReset ( )
{

	Index = FirstNode;

}

void CLinkedList::IndexForward ( )
{

	if ( (*Index).NextNode != NULL )
	{
		Index = (*Index).NextNode;
	}

}

void CLinkedList::IndexReverse ( )
{

	if ( (*Index).PreviousNode != NULL )
	{
		Index = (*Index).PreviousNode;
	}

}

void * CLinkedList::operator [] ( int Index )
{

	if ( NoOfEntries == 0 || Index < 0 || Index >= NoOfEntries )
	{
		return NULL;
	}

	Node *Temp;
	Temp = FirstNode;

	for ( int i=0; i<Index; i++ )
	{

		Temp = (*Temp).NextNode;

	}

	return (*Temp).Payload;

}

// WildCard Search in the linked list.
bool CLinkedList::WildCardSearch ( CLinkedList *MatchedIndices, char *Pattern )
{

	bool Found = false;
	int *IntPTR;

	for ( int i=0; i<NoOfEntries; i++ )
	{

		char *Temp = new char [ strlen ( (char *)(*this)[i] ) + 1 ];
		strcpy ( Temp, (char *)(*this)[i] );
		Temp[ strlen ( (char *)(*this)[i] ) - 1 ] = '\0';

		if ( IsMatch ( Pattern, Temp ) )
		{

			IntPTR = new int;
			*IntPTR = i;
			(*MatchedIndices).Add ( (void *)IntPTR );
			Found = true;

		}
		//delete Temp;

	}

	return Found;

}

// Exact string search in the linked list.
int CLinkedList::ExactSearch ( char *String )
{

	for ( int i=0; i<NoOfEntries; i++ )
	{

		if ( !strcmp ( String, (char *)(*this)[i] ) )
		{
			return i;
		}

	}

	return -1;

}

// WildCard Search
bool IsMatch( char *pattern, char *string )
{
	while( *string )
	{
		switch( *pattern )
		{
			// If question mark then do nothing
			case '?':
				break;

			// If asterisk
			case '*':
				// Remove adjacent asterisks
				do{

					++pattern;

				} while( *pattern == '*' );

				// If the asterisk(s) were the last characters in the pattern
				// return true
				if( !*pattern )
				{
					return true;
				}

				while( *string )
				{
					// Compare all possible combinations of remaining pattern
					// with string
					if( IsMatch( pattern, string++) )
					{
						return true;
					}
				}

				// At this point we know there is no match
				return false;

			default:
				// If individual characters do not match then return false
				if( *pattern != *string )
				{
					return false;
				}

				break;
		}

		// Increment pointers
		++pattern, ++string;
	}

	// Used to remove trailing asterisk(s)
	while( *pattern == '*' )
	{
		++pattern;
	}

	// If we have reached the end of pattern and no false has been returned
	// the value !*pattern will be true and false for the opposite case i.e.
	// the string has finished but there is still pattern remaining
	return !*pattern;

}

// Search something in the linked list.
int CLinkedList::Search ( void *SearchKey, int Code )
{

	Node *CurrentNode = FirstNode;
	int  Index = 0;

	// Matching the code for datatype.
	switch ( Code )
	{

		// Integer search.
    	case 0:
		{

			while ( CurrentNode != NULL )
			{

				if ( *( (int *)(*CurrentNode).Payload ) == *( (int *)(SearchKey) ) )
				{

					return Index;

				}
				CurrentNode = (*CurrentNode).NextNode;
				Index++;

			}
			return -1;

		}

        // Unsigned Integer search.
    	case 3:
		{

			while ( CurrentNode != NULL )
			{

				if ( *( (unsigned int *)(*CurrentNode).Payload ) == *( (unsigned int *)(SearchKey) ) )
				{

					return Index;

				}
				CurrentNode = (*CurrentNode).NextNode;
				Index++;

			}
			return -1;

		}

		default:
		{
        	return -1;
		}

	}
	return -1;

}

// Modify something in the linked list at the specified index.
int CLinkedList::Modify ( int Index, void *Entry, int Code )
{

	Node *CurrentNode = FirstNode;
	if ( CurrentNode == NULL )
	{
		return -1;
	}
	if ( Index < 0 )
	{
		return -1;
	}
	int Counter = 0;

	// Matching the code for datatype.
	switch ( Code )
	{

		// Integer search.
    	case 0:
		{

			for ( Counter = 0; Counter < Index; Counter++ )
			{

				CurrentNode = (*CurrentNode).NextNode;
				if ( CurrentNode == NULL )
				{
                	return -1;
				}


			}
			delete (int *)(*CurrentNode).Payload;
			(*CurrentNode).Payload = Entry;
			return 0;

		}

        // Unsigned Integer search.
    	case 3:
		{

			for ( Counter = 0; Counter < Index; Counter++ )
			{

				CurrentNode = (*CurrentNode).NextNode;
				if ( CurrentNode == NULL )
				{
                	return -1;
				}


			}
			delete (unsigned int *)(*CurrentNode).Payload;
			(*CurrentNode).Payload = Entry;
			return 0;

		}

		default:
		{
        	return -1;
		}

	}
	return -1;

}


