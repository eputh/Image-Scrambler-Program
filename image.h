//
// Name: Emily Puth
// ID: 28239807
//
// The Image class provides utilities for
// reading, writing, and getting fourths of 
// the PGM image

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>


class Image{
	private:
		int width;
		int height;
		int maxGrayValue;
		int** picture;

	public:
		// Constructors
		// Default COnstructor
		Image();
		// Initialize an image by reading in the picture
		// contained in filename
		Image(std::string filename);
		// Initialize an image with dimensions width and height
		Image(int width, int height);
		// copy Constructor
		Image(const Image& other);
		// Destructor
		~Image();

		// Accessors/Mutators
		int getHeight() const {return height;}
		int getWidth() const {return width;}
		int getMaxGrayValue() const {return maxGrayValue;}
		void setMaxGrayValue(int max) {maxGrayValue = max;}
		int** getPicture() const{return picture;}
		void setPicture(int** pictureArray, int width, int height);

		// Other Functions
		//Assignment Operator Overload
		Image& operator=(const Image& other);

		// Reads in the image file contained in filename
		// Sets this picture to the image contained in the file
		// returns true if read successfully, false otherwise
		bool readImage(std::string filename);

		//Writes the current picture to file
		// filename: name of the file to write to
		// returns true if successful
		// returns fase if unsuccessful or if this Image doesn't have
		// a picture to write to file
		bool writeImage(std::string filename);

		// returns the specified quadrant (1,2,3, or 4) of the picture as an image
		// whichQuadrant: 1 - top left fourth, 2 - top right fourth,
		// 3 - bottom left fourth, 4 - bottom right fourth,
		Image getQuadrant (int whichQuadrant);

		// sets the quadrant to the new values contained in newQuadrant
		void setQuadrant(int whichQuadrant, const Image* newQuadrant);
};


#endif
