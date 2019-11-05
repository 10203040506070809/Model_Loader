// Model_Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <fstream>

int main()

{
	std::cout << "Hello World!\n";

	std::string line;
	std::ifstream myFile("media/Creeper.obj", std::ios::binary);
	if (myFile.is_open())
	{
		GLubyte byte; // is 8bit and maps to char
		while (myFile >> byte)
		{
			
			std::cout << byte;
			//check and map each byte
			// only read strings if file is in plaintext encoding
		}
		myFile.close();
	}
	
}

