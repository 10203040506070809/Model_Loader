#include "Utilities.h"

//This cpp contains utility methods that can be utilized in various classes.

//Splits strings into a vector of strings and returns it.
vector<string> SplitString(const string &s, char delimiter)
{
	vector<string> words;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delimiter)) {
		words.push_back(item);
	}
	return words;
}

//Takes r,g,b,a values and converts them to float values between 0 and 1 for use with GLFW.
//Allows me to input rgb values for colour and not have to think about rgb to float
Colour RGBtoFloat(float r, float g, float b, float a)
{
	Colour col;
	col.r = r / 255;
	col.g = g / 255;
	col.b = b / 255;
	col.a = a / 255;

	return col;
}

