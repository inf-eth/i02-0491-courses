\begin{lstlisting}[caption={Ambiguity in Multiple Inheritance}]
#include <iostream>
using namespace std;

class A
{
	public:
	int Data;
};
class B: public A
{
};
class C: public A
{
};
class D: public B, public C
{
	void Display()
	{
		cout << Data << endl; // Error: which data to display? B::data or C::data
	}
};
\end{lstlisting}
\begin{lstlisting}[caption={Resolving Ambiguity in Multiple Inheritance},escapechar=$]
#include <iostream>
using namespace std;

class A
{
	public:
	int Data;
};
class B: $\textcolor{red}{virtual}$ public A
{
};
class C: $\textcolor{red}{virtual}$ public A
{
};
class D: public B, public C
{
	void Display()
	{
		cout << Data << endl; // No ambiguity, there is only one data which is A::data.
	}
};
\end{lstlisting}
