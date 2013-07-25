\begin{lstlisting}[caption={Linked List Destructor}]
~LinkedList()
{
	Node* temp1;
	Node* temp2;
	temp1 = temp2 = First;
	if (First == NULL)
		return;
	else
	{
		temp2 = temp2->Next;
		while(true)
		{
			cout << "Deleting " << temp1->Data << endl;
			delete temp1;
			temp1 = temp2;
			if (temp1 == NULL)
				break;
			temp2 = temp2->Next;
		}
	}
}
\end{lstlisting}
