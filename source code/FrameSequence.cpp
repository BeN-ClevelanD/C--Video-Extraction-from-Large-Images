#include "FrameSequence.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>



//default constructor

bnjcle001::FrameSequence::FrameSequence(void)
{}

//destructor deletes all memory spaces held by pointers for each 1D array within each 2D array, as well as the 2D arrays themselves (each array being held by the imageSequence vector)

bnjcle001::FrameSequence::~FrameSequence()
			{
				
				for(int x = 0; x < imageSequence.size(); ++x)
				{
					
					for (int y = 0; y < frameHeight; ++y)
					{
						delete imageSequence[x][y];
					}
					
					delete imageSequence[x];
				}
				
				
				
			}
			
			
//creates frames based on original image, y and x start points, and the width and height specified by the user			
unsigned char** bnjcle001::FrameSequence::CreateFrame(int startX, int startY, int Width, int Height, char ** largeImage){
						
			frameHeight = Height;
			frameWidth = Width;
			//dynamically allocates space for array to hold 1D array of char pointers
			unsigned char ** numrows = new unsigned char *[frameHeight];

			int ycount = 0;
			int y = startY;
			//checks to see that our memory request was successful
			if(numrows != nullptr)
			{
			for( y ; y < frameHeight+startY; ++y)
			{
				//dynamically allocates space for array to hold char pointers
				unsigned char * cols = new unsigned char [frameWidth];
				int x = startX;
				int xcount = 0;
				//checks to see that our memory request was successful
				if(cols != nullptr)
				{
				for ( x; x < frameWidth+startX; ++x)
					{
						//assigns content of the larger image from the correct coord to the correct coord in our 2D array
						cols[xcount] = largeImage[y][x];
						
				
						++xcount;
			
					}
				}
					numrows[ycount] = cols;
					ycount++;
				
		
			}
			}
			
		
				//returns the frame object to be pushed back to the imageSequence vector (this is done in the executor file)
				return numrows;
			
			
		}


//function that makes the sequence when "none" is specified, uses input from the user for naming the sequence
//it then writes the header information to the pgms, and writes out the frames from each of the vector items that holds frames

void bnjcle001::FrameSequence::make_default_sequence(std::string filepath)
	{
		for(int y = 0; y < imageSequence.size() ; ++y)
		{
			std::ofstream pgmfileOut (filepath+std::to_string(y+1)+".pgm", std::ofstream::binary);
	
			pgmfileOut << "P5" << "\n";
			pgmfileOut << frameWidth << " " << frameHeight << "\n";
			pgmfileOut << 255 << "\n" ;
	
			for(int x = 0; x < frameHeight; ++x)
			{
				pgmfileOut.write((const char*)imageSequence[y][x], frameWidth);
			}
		
		}
	}


//function that makes the sequence when "reverse" is specified, uses input from the user for naming the sequence
//it then writes the header information to the pgms, and writes out the frames from each of the vector items that holds frames but in reverse order
void bnjcle001::FrameSequence::make_reverse_sequence(std::string filepath)
	{
		int end = imageSequence.size()-1;
		int framenum = 0;
		
		for (end; end != -1; --end)
		{
			std::ofstream pgmfileOut (filepath+std::to_string(framenum)+".pgm", std::ofstream::binary);
	
			pgmfileOut << "P5" << "\n";
			pgmfileOut << frameWidth << " " << frameHeight << "\n";
			pgmfileOut << 255 << "\n" ;
	
			for(int x = 0; x < frameHeight; ++x)
			{
				pgmfileOut.write((const char*)imageSequence[end][x], frameWidth);
			}
			++framenum;
		
		}
	}
	
//function that makes the sequence when "reinvert" is specified, uses input from the user for naming the sequence
//it then writes the header information to the pgms, places each pixel into a temporary
//1D array buffer (and inverts it using 255-original value while assigning to temp buffer) and writes them out to file
void bnjcle001::FrameSequence::make_reinverse_sequence(std::string filepath)
	{
		int end = imageSequence.size()-1;
		int framenum = 1;

		for (end; end != -1; --end)
		{
			std::ofstream pgmfileOut (filepath+std::to_string(framenum)+".pgm", std::ofstream::binary);
	
			pgmfileOut << "P5" << "\n";
			pgmfileOut << frameWidth << " " << frameHeight << "\n";
			pgmfileOut << 255 << "\n" ;
	
			for(int x = 0; x < frameHeight; ++x)
			{
				
				char * tempBuffer = new char [frameWidth];
				for(int i = 0; i < frameWidth; ++i)
				{
					
				tempBuffer[i] = 255 - (char)imageSequence[end][x][i];
				}
				
				
				
				
				pgmfileOut.write((const char*)tempBuffer, frameWidth);
				delete tempBuffer;
			}
			++framenum;
		
		}
	}
	
//function that makes the sequence when "invert" is specified, uses input from the user for naming the sequence
//it then writes the header information to the pgms, places each pixel into a temporary
//1D array buffer (and inverts it using 255-original value while assigning to temp buffer) and writes them out to file
void bnjcle001::FrameSequence::make_inverse_sequence(std::string filepath)
	{
		
		int framenum = 1;
		
		for(int y = 0; y < imageSequence.size() ; ++y)
		{
			std::ofstream pgmfileOut (filepath+std::to_string(framenum)+".pgm", std::ofstream::binary);
	
			pgmfileOut << "P5" << "\n";
			pgmfileOut << frameWidth << " " << frameHeight << "\n";
			pgmfileOut << 255 << "\n" ;
	
			for(int x = 0; x < frameHeight; ++x)
			{
				
				char * tempBuffer = new char [frameWidth];
				for(int i = 0; i < frameWidth; ++i)
				{
					
				tempBuffer[i] = 255 - (char)imageSequence[y][x][i];
				}
				
				
				
				
				pgmfileOut.write((const char*)tempBuffer, frameWidth);
				delete tempBuffer;
			}
			++framenum;
		
		}
	}
