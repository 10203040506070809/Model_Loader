# Model_Loader

This project is a model loader created in C++ using the OpenGL framework. It aims to provide the ability to load simple .obj files
and render them within an OpenGL window. 

## Getting Started
You can either:
* Open the x64 folder
  * Open the debug folder
  * Find Model_Loader.exe and run it
 
* Open Model_Loader.sln
  * Set the Model Loader as the current working project
  * Run the local debugger
  
* From here you'll be required to input the path to your model. 
* This includes the file name itself, E.G
* Media/Models/Model.obj
## Requirements
FreeGLUT, GLFW and GLEW are used within this project. To easily download these, in Visual Studio:
* Tool
* Nuget Package Manage
* PM Console
* Type Install-Package nupengl.core

## Developed using
Developed using Visual Studio on the  Windows SDK Version 10.0.17763.0 with the platform toolset v141.

# How does it work?

## SplitString

Parameters:
Const &string, char delimiter
Const &string - the string you're splitting
Char delimiter - the delimiter you're splitting by
Splits a string by a delimiter and returns a vector string. 
## LoadObj
Not implemented yet
## ParseObj

Parameters: Ifstream file, string path
Ifstream file - the file stream that should already be open
String path - the path of the object to load
Read through an obj file line by line and checks for the first word of each line. 
Depending on what the word is, it'll split the following values and add them to a vector. 

## ParseDAE
Not implemented yet
## OpenFile
Takes in a path as a console input and splits it at the last .
Everything after and including the dot is taken as a file extension
Which is then used to decide which method to run, I.E if the file extension is OBJ, it runs ParseOBJ.

## loadTexture

Loads the texture of the model.

## checkForInput

Checks for user input within the OpenGL window

## Display

Clears the background colour to a predefined colour, then renders the model/
## init

Generates the VAOs and VBO's for the model and sets the shaders of the model.
## GLFWInit

Initialises GLFW and glew, creates a window and allows for user input.
Contains a while loop that functions as an update loop, until the application is closed.
## Main

The main function of the CPP, takes an input as a string and sends that as a parameter to OpenFile,
then initialises GLFW.




