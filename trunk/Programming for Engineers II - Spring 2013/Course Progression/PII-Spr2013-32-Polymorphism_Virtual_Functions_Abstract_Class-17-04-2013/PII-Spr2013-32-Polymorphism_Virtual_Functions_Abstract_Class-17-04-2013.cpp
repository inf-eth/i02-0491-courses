\documentclass[12pt,a4paper]{article}

% Margins.
\setlength{\oddsidemargin}{0in}
\setlength{\evensidemargin}{0in}
\setlength{\headheight}{12pt}
\setlength{\headsep}{42pt}
\setlength{\topmargin}{-54pt}
\setlength{\textwidth}{6.5in}
\setlength{\textheight}{10in}

\usepackage{amsmath}
\usepackage{float}
\usepackage{graphicx}
\usepackage[hyphens]{url}
\usepackage{hyperref}	% Clickable links to figures, references and urls.
\usepackage{enumerate}
\usepackage{datetime}

% Drawing.
\usepackage{pgf}
\usepackage{tikz}

% Listings for formatting code.
\usepackage{listings}
\usepackage{textcomp}
% General options.
\lstset{breaklines=true, basicstyle=\small\ttfamily, tabsize=4, numbers=left, stepnumber=1, frame=single, showstringspaces=false, upquote=true}
% C++ specific high-lighting. Comments are 50/50 shades of green/black and strings coloured with 60/40 red/black mixture.
\lstset{language=[ISO]C++, commentstyle=\color{green!50!black}, keywordstyle=\color{blue}, stringstyle=\color{red!60!black}}

%opening
\title{\vspace{-2cm}Programming for Engineers II\\Class 32\\Polymorphism\\Virtual Functions\\Abstract Class}
\author{Attique Dawood}
\date{April 17, 2013\\[0.2cm] Last Modified: \today, \currenttime}
\begin{document}
\maketitle
\section{Announcements}
\begin{itemize}
\item Reminder: Quiz on Friday, 19-04-2013. Topics are linked list and polymorphism.
\item Next ABQ is based on linked list and polymorphism. Detailed implementation may be required.
\item You may be required to modify list functions, like, instead of adding a node at end, insert node at beginning.
\item Practice with linked lists.
\end{itemize}
\section{Revision}
\subsection{Overloading the Subscript Operator for Linked List}
\begin{itemize}
\item What if we want to get and set the entries in our list like an array? \verb|GetAt()| and \verb|SetAt()| functions. An elegant solution is to overload subscript operator\verb|[]|.
\item We need to keep track of number of entries in our list so we keep a count variable.
\item Remember we still need to call the add node function to increase the size of our linked list.
\end{itemize}
\subsection{Advanced Linked List Concepts}
\begin{itemize}
\item \textbf{Doubly--linked list:} Can traverse in both directions. Electronic quiz; can skip questions and then come back again later.
\item \textbf{Circular--linked list:} First and last nodes are joined together.
\item \textbf{Indexing:} Index in a book? Helps you remember where you left off. Just a pointer to some node just like first and last. Can move forward or backward. Get the value at current index. Can reset index at 
\end{itemize}
\subsection{Adding a node at Beginning, Middle or End: Sorted Insertion?}
\begin{itemize}
\item Why do we need to insert at some random location? Insertion sort.
\item Creates a sorted list.
\item Easier to search a sorted list. Don't have to go through all the list.
\end{itemize}
\section{Polymorphism and Virtual Functions}
\begin{itemize}
\item A pointer of base class can point to (and access) derived class object(s).
\item In the following code we derive Triangle and Circle from Shape. A pointer of Shape class can access Triangle and Circle objects.
\item Calling the draw function will invoke Shape's draw.
\item Now a base class pointer can point to any derived class object and we may not know what object it is.
\item How can we call the respective draw function? Make draw function \verb|virtual|.
\item Using \verb|virtual| is an effective means of telling the compiler: ``Don't look at the \textcolor{red}{type of pointer}, look at the \textcolor{red}{type of object it points}''.
\end{itemize}
\begin{lstlisting}[caption={Using base class pointer to manipulate derived class objects}, escapechar=$]
#include <iostream>
using namespace std;

class Shape
{
	public:
	void Draw()
	{
		cout << "Shape." << endl;
	}
};

class Circle: public Shape
{
	public:
	void Draw()
	{
		cout << "Circle." << endl;
	}
};

class Triangle: public Shape
{
	public:
	void Draw()
	{
		cout << "Triangle." << endl;
	}
};

int main()
{
	Shape* Sp;
	Circle C;
	Triangle T;

	Sp = &C;
	Sp->Draw(); // Output: "Shape."

	Sp = &T;
	Sp->Draw(); // Output: "Shape."

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Virtual Functions}, escapechar=$]
#include <iostream>
using namespace std;

class Shape
{
	public:
	$\textcolor{red}{virtual}$ void Draw()
	{
		cout << "Shape." << endl;
	}
};

class Circle: public Shape
{
	public:
	$\textcolor{red}{virtual}$ void Draw()
	{
		cout << "Circle." << endl;
	}
};

class Triangle: public Shape
{
	public:
	$\textcolor{red}{virtual}$ void Draw()
	{
		cout << "Triangle." << endl;
	}
};

int main()
{
	Shape* Sp;
	Circle C;
	Triangle T;

	Sp = &C;
	Sp->Draw(); // Output: "Circle."

	Sp = &T;
	Sp->Draw(); // Output: "Triangle."

	return 0;
}
\end{lstlisting}
\section{A List of Random Objects}
\begin{itemize}
\item Why can't an array contain different objects/variables; like int, char, double etc? Different sizes. Array entries must have same size.
\item From previous section we can see that a base class pointer can point to any derived class object. Make an array of base class pointer and create any object! Remember, pointer size is constant!
\item Using this concept we create an array of shapes. Shapes can be triangle, circle or rectangle.
\item \textbf{We don't know which shape is stored in a particular index but still we can call the appropriate draw function!} This is called polymorphism: \textcolor{red}{Morph our pointer into whatever object it is pointing to!}
\item \underline{Polymorphism is achieved through the use of virtual functions.}
\end{itemize}
\begin{lstlisting}[caption={Creating random shapes}, escapechar=$]
#include <iostream>
#include <cstdlib>
using namespace std;

class Shape
{
	public:
	virtual void Draw()
	{
		cout << "Shape." << endl;
	}
};

class Circle: public Shape
{
	public:
	virtual void Draw()
	{
		cout << "Circle." << endl;
	}
};

class Triangle: public Shape
{
	public:
	virtual void Draw()
	{
		cout << "Triangle." << endl;
	}
};

class Rectangle: public Shape
{
	public:
	virtual void Draw()
	{
		cout << "Rectangle." << endl;
	}
};

int main()
{
	int NumberOfShapes;
	cout << "How many shapes do you want? ";
	cin >> NumberOfShapes;
	srand(NumberOfShapes); // Randomisation seed. Isn't really necessary.

	// Create an array of Shape pointers.
	Shape** Sp;
	Sp = new Shape*[NumberOfShapes];

	// Dynamically create random shapes.
	for (int i=0; i<NumberOfShapes; i++)
	{
		int Random = rand()%3;
		if (Random == 0)
			Sp[i] = new Circle;
		if (Random == 1)
			Sp[i] = new Triangle;
		if (Random == 2)
			Sp[i] = new Rectangle;
	}

	// 'Draw' shapes.
	for (int i=0; i<NumberOfShapes; i++)
		Sp[i]->Draw(); // Appropriate Draw() function is called!

	// De-allocation before exiting.
	for (int i=0; i<NumberOfShapes; i++)
		delete Sp[i];
	delete[] Sp;

	return 0;
}
\end{lstlisting}
\section{Abstract Class}
\begin{itemize}
\item A \verb|virtual| function can be made \textcolor{red}{pure} \verb|virtual| by specifying a \verb|=0| in function prototype.
\item Any class containing even a single pure virtual function becomes \textcolor{red}{abstract} class.
\item Objects of abstract class cannot be instantiated (created) but pointers can be created.
\item Abstract classes are like common nouns. They refer to a generalised concept, like shape or person.
\item An abstract class is most appropriate as a base class from which other classes can be derived.
\end{itemize}
\begin{lstlisting}[caption={Making Shape class abstract}, escapechar=$]
class Shape
{
	public:
	virtual void Draw() $\textcolor{red}{= 0}$
	{
		cout << "Shape." << endl;
	}
};
\end{lstlisting}
%\nocite{*}
%\bibliographystyle{plain}
%\bibliography{OOPref}
\end{document}
