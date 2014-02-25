class Complex
{
	private:
	float real;
	float img;
	public:
	Complex();
	Complex(float, float);

	void RandomInput(); // Random input.
	// Input/output. TODO: Replace with overloaded stream operators (<< and >>)
	void Input();
	void Display();

	// Math operations. TODO: Replace with operators.
	Complex Add(const Complex&);
	Complex Subtract(const Complex&);
	Complex Multiply(const Complex&);
	Complex Divide(const Complex&);

	// TODO: Overload operators here.

};
