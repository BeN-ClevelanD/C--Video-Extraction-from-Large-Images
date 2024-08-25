#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "FrameSequence.h"
#include <vector>
#include <cmath>


using namespace bnjcle001;
int main(int argc, char *argv[])
{
	
	//Below are variables to collect user inputted parameters for sequence creation
	int x1; 
	int y1; 
	int x2; 
	int y2; 
	int userInWidth; 
	int userInHeight; 
	
	//Below are variables that are used to do error checking for the command line input
	
	
	bool wParam = false;
	bool sParam = false;
	bool tParam = false;
	
	
	//vector to store the variable list of operations inputted by user
	std::vector<std::string> operations;
	//looping through argv content and assigning relevant variables
	for(int x = 1; x < argc; ++x)
	{
		if(std::string(argv[x]) == "-t")
		{		
			tParam = true;
			++x;
			
			x1 = std::stoi(argv[x]);
			
			++x;
			y1 = std::stoi(argv[x]);
			
			++x;
			x2 = std::stoi(argv[x]);
			
			++x;
			y2 = std::stoi(argv[x]);
			
			
		}
		
		if(std::string(argv[x]) == "-s")
		{
			sParam = true;
			++x;
			userInWidth = std::stoi(argv[x]);
			
			++x;
			userInHeight = std::stoi(argv[x]);
			
			//error check for if the user has not specified any frames (frame size must be greater than 0)
			if(userInHeight == 0 && userInWidth == 0)
			{
				std::cout << "There are no frames" << std::endl;
				exit(1);
			}
			
		}
		
		if(std::string(argv[x]) == "-w")
		{
			wParam = true;
			++x;
			
			std::string Stored = argv[x];
			
			++x;
			Stored = Stored + " " + argv[x];
			
			
			operations.push_back(Stored);
			
		}
		
		
		
	}
	
	//error checking to make sure that all of the flags are present in the command line input
	if(!wParam || !tParam || !sParam )
	{
		std::cout << " The command line arguments you have entered do not meet the requirements, please try again" << std::endl;
		exit(1);
	}
	

	//declaring variables that will be used to store original image width and height as well as the header contents
	std::string Pwidth;
	std::string Pheight;
	int pWidth;
	int pHeight;
	int maxWhite = 0;
	//declaring the vector of FrameSequence objects
	FrameSequence frameHolder;
	std::string firstLine;
	std::string lastLine = "255";
	
	std::string inputFileName = argv[1];
	

		
	
	
	
		//Open up file with the inputFileName in binary and reading mode
		std::ifstream pgmfile (inputFileName, std::ifstream::binary);
		if(!pgmfile)
		{
			std::cout << "Invalid file name please try again" << std::endl;
			exit(1);
		}
		std::string line;
		std::getline(pgmfile, line);
		
		//read in the P5 line and assign to "firstLine"
		if(line == "P5")
		{
			firstLine = line;
		
		}
		
		//read in the comment lines while there are any and keep going until there are no more comments
		std::getline(pgmfile, line);
		while(line.starts_with("#"))
		{

	
			std::getline(pgmfile, line);
			
		}

		//read in the width and height line and assign to pWidth and pHeight
		std::stringstream is(line);
		is >> pWidth >> pHeight;

		//read in the 255 line and assign to "lastLine"
		std::getline(pgmfile, line);
		lastLine = line;
	
		//Creating 2D array for the large image and reading it in
		char ** rows = new char *[pHeight];
		for(int x = 0 ; x < pHeight; ++x)
		
		{
			
		char * restofbytes = new char [pWidth];
		
		pgmfile.read(restofbytes, pWidth);
		
		rows[x] = restofbytes;
		
		}
 
	//error checking for if the starting or ending points are invalid due to being out of bounds or being negative
	if(x1+userInWidth > pWidth || x2+userInWidth > pWidth || x1<0 || x2<0)
	{
		std::cout << "Either the starting coords or ending coords are invalid for the image size (are either out of bounds or are negative!)" << std::endl;
		exit(1);
		
	}
	//error checking for if the starting or ending points are invalid due to being out of bounds or being negative
	if(y1+userInHeight > pHeight || y2+userInHeight > pHeight || y1<0 || y2<0)
	{
		std::cout << "Either the starting coords or ending coords are invalid for the image size (are either out of bounds or are negative!)" << std::endl;
		exit(1);
	}
 

	pgmfile.close();

	
	
	
	

	

	
	  //assigning variables to work with for frames generation
	  
	  //calculate gradient and loop accordingly
	  
	int xstart = float(x1);
	int ystart = float(y1);
	int xend = float(x2);
	int yend = float(y2);
	float filmGradient = float(yend-ystart)/(xend-xstart);

	//if below is true then we are looping over x and adding gradient to y, and if not, then visa versa
	float yr;
	float xr;
	float startPoint;
	float endPoint;
	float xIncFactor;
	float yIncFactor;
	float direction;
	
	if (std::fabs(filmGradient)  < 1.0) 
	{
		
		yr = ystart;
		xr = xstart;
		startPoint = x1;
		endPoint = x2;
		//check if the frame will move positively or negatively along the x axis
		if(x1 < x2)
		{
			xIncFactor = 1;
			direction = 1;
		}
		else
		{
			xIncFactor = -1;
			direction = -1;
		}
		//check if the frame will move positively or negatively along the y axis
		if(y1 < y2)
		{
			yIncFactor = filmGradient;
		}
		else
		{
			yIncFactor = -filmGradient;
		}
			
		
		
		

	}
	//same checks are done below but for the case in which the gradient is bigger than 1
	else 
	{
		
		yr = ystart;
		xr = xstart;
		startPoint = y1;
		endPoint = y2;
		if(y1 < y2)
		{
			yIncFactor = 1;
			direction = 1;
		}
		else
		{
			yIncFactor = -1;
			direction = -1;
		}
		if(x1 < x2)
		{
			xIncFactor = 1/filmGradient;
		}
		else
		{
			xIncFactor = -(1/filmGradient);
		}
		
	}
	//uses infinite loop with the case-based definitions of iterator, incrementer values, start and end points
	for(;;){
			if(startPoint == endPoint)
			{
				break;
			}
			
			//creates frame using function from FrameSequence class
			unsigned char ** tempa = frameHolder.CreateFrame(std::round(xr),std::round(yr),userInWidth,userInHeight, rows);
			//assigns the frame to the FrameSequence object's (frameHolder) vector of FrameSequences
			frameHolder.imageSequence.push_back(tempa);
			yr += yIncFactor;
			xr += xIncFactor;
			startPoint += direction;
		}
		
		
		//Deallocating the memory for the dynamically allocated 2D array "rows"
		
	for(int x = 0; x < pHeight; ++x)
	{
		delete rows[x];
	}
	delete rows;
    
    

    
    //loops over the operations that were inputted by the user and calls the appropriate methods from the FrameSequence class for each one, naming each sequence according to the user's requests
    for(int x = 0; x < operations.size(); ++x)
    {
		int middle = operations[x].find(" ");
		std::string op = operations[x].substr(0, middle);
		std::string sequenceName = operations[x].substr(middle+1, -1);
		
		
		
		if(op == "reverse")
		{
			frameHolder.make_reverse_sequence(sequenceName);
			std::cout << "Now making  "+ op + " sequence named " + sequenceName << std::endl;
		}
		if(op == "none")
		{
			frameHolder.make_default_sequence(sequenceName);
			std::cout << "Now making "+ op +"  sequence named " + sequenceName << std::endl;
		}
		if(op == "revinvert")
		{
			frameHolder.make_reinverse_sequence(sequenceName);
			std::cout << "Now making " +op +" sequence named " + sequenceName << std::endl;
		}
		if(op == "invert")
		{
			frameHolder.make_inverse_sequence(sequenceName);
			std::cout << "Now making "+ op+" sequence named " + sequenceName << std::endl;
		}
		
	}
	


}
