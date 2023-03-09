#include <string>
#include <ostream>

using namespace std;

struct Vector2Int
{
	Vector2Int(int x, int y)
		: X(x)
		, Y(y)
	{}

	Vector2Int operator+(const Vector2Int& other)
	{
		X += other.X;
		Y += other.Y;
	}

	//TODO: operators overload for vector structs and print functions

	friend ostream& operator<< (ostream& os, const Vector2Int& other)    //Overloaded operator for '<<'{                                                                                    //for struct output
	{
		os << other.X << other.Y;
		return os;
	}

	int X;
	int Y;

	string ToString()
	{
		return "(" + to_string(X) + ", " + to_string(Y) + ")";
	}
};