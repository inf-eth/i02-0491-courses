\begin{lstlisting}[caption={Local Variable in a Function}]
#include <iostream>
using namespace std;

int Simple()
{
	int x = 0;
	x++;
	return x;
}
int main()
{
	cout << x << endl;

	cout << Simple() << endl;
	cout << Simple() << endl;
	cout << Simple() << endl;
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={\texttt{static} Local Variable in a Function}]
#include <iostream>
using namespace std;

int Simple()
{
	static int x = 0;
	x++;
	return x;
}
int main()
{
	cout << x << endl;

	cout << Simple() << endl;
	cout << Simple() << endl;
	cout << Simple() << endl;
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={\texttt{static} Data Member}]
#include <iostream>
using namespace std;

class Complex
{
	private:
	static int count; // Declaration.
	public:
	Complex()
	{
		count++;
	}
	int GetCount()
	{
		return count;
	}
	~Complex()
	{
		count--;
	}
};
int Complex::count = 0; // Initialisation (think of definition).

int main()
{
	Complex A, B, C;
	cout << A.GetCount() << endl;
	Complex* Ap;
	Ap = new Complex;
	cout << A.GetCount() << endl;
	delete Ap;
	cout << A.GetCount() << endl;
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={\texttt{static} Member Function}]
#include <iostream>
using namespace std;

class Complex
{
	private:
	static int count; // Declaration.
	public:
	Complex()
	{
		count++;
	}
	static int GetCount()
	{
		return count;
	}
	~Complex()
	{
		count--;
	}
};
int Complex::count = 0; // Initialisation (think of definition).

int main()
{
	Complex A, B, C;
	cout << Complex::GetCount() << endl;
	Complex* Ap;
	Ap = new Complex;
	cout << Complex::GetCount() << endl;
	delete Ap;
	cout << Complex::GetCount() << endl;
	
	return 0;
}
\end{lstlisting}
%\nocite{*}
\bibliographystyle{plain}
\bibliography{OOPref}
\end{document}
