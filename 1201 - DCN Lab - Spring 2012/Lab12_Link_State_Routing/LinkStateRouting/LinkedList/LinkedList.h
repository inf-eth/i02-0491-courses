// Another linked list.



struct Node
{

	Node *NextNode;
	Node *PreviousNode;
	
	void *Payload;

};

class CLinkedList
{

	// Public Access Functions;
	public:
	
	CLinkedList ( );
	~CLinkedList ( );
	
	// * Generic Linked List functions.	
	void  Add ( void * );
	int   AddNoDupe ( void *, int );
	void  Empty ( );
	int   GetNoOfEntries ( ) { return NoOfEntries; }
	
	void * GetCurrent ( );
	
	// * Index Functions.
	void IndexReset   ( );
	void IndexForward ( );
	void IndexReverse ( );	
		
	// * Index Operator.
	void * operator [] ( int );
	
	// * Wildcard Search.
	bool WildCardSearch ( CLinkedList *, char * );
	
	// * Search for exact match of a string in the linked list. Returns the index in the linked list or -1 if not found.
	int  ExactSearch ( char * );
	int  Search ( void *, int );
	int  Modify ( int, void *, int );
	
	// Private Data.
	private:

	Node *FirstNode;
	Node *LastNode;
	Node *Index;
		
	int  NoOfEntries;
	
};
