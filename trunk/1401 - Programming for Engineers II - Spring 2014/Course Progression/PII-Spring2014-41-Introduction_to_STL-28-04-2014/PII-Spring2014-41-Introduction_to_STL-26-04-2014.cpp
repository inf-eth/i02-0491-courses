\begin{lstlisting}[caption={Traditional way of writing sum function}]
int sum(int a, int b)
{
	return (a+b);
}
float sum(float a, float b)
{
	return (a+b);
}
...
complex sum(complex a, complex b)
{
	return (a+b);
}
...
\end{lstlisting}

\begin{lstlisting}[caption={Sum function template}]
// Sum function template.
// Depending on type of argument passed in main, that will be substituted in place of 'MyType'.
// For example, if called as sum(2.3, 7.7), MyType would be double.
template <class MyType> MyType sum(MyType a, MyType b)
{
	return (a+b);
}
int main()
{
	sum(3.2, 7.8); // implicit instantiation with double type.
	sum(3, 8); // implicit instantiation with int type.
	sum<double> (3.2, 7.8); // explicit double instantiation.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Sum function template for mixed types}]
template <class MyType1, class MyType2> MyType1 sum(MyType1 a, MyType2 b)
{
	return (a+b);
}
int main()
{
	sum(3.2, 7.8); // implicit instantiation with both double types.
	sum(3, 8.9); // implicit instantiation for int and double types.
	sum<int, double> (3, 7.8); // explicit instantiation.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Class template}]
#include <iostream>
using namespace std;
template <class MyType> class GenericArray
{
	private:
	MyType Data[5];
	public:
	void Input()
	{
		for (int i=0; i<5; i++)
			cin >> Data[i];
	}
	void Display()
	{
		for (int i=0; i<5; i++)
			cout << Data[i] << " ";
		cout << endl;
	}
};
int main()
{
	GenericArray<int> IntArray;
	IntArray.Input();
	IntArray.Display();
	
	return 0;
}
\end{lstlisting}
