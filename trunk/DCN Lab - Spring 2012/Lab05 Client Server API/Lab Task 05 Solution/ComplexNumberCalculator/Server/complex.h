class complex
{
	float real;
	float img;
	public:
	complex();	// Default contructor.
	complex(float, float); // Parameterized constructor.
	// setter functions.
	void setreal(float);
	void setimg(float);
	// getter functions.
	float getreal();
	float getimg();
	// Display.
	void display();
	// Operators.
	complex operator + (complex &);
	complex operator - (complex &);
	complex operator * (complex &);
	complex operator / (complex &);
};
