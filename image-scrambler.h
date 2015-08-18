// 
// Name: Emily Puth
// ID: 28239807
//
// The ImageScrambler class will provide functions
// to move around fourths of the picture

#ifndef IMAGE_SCRAMBLER_H
#define IMAGE_SCRAMBLER_H

#include "image.h"
#include <fstream>
#include <iostream>


class ImageScrambler{
	private:
		Image myImage;
		Image quadrant1, quadrant2, quadrant3, quadrant4;

		void setQuadrants();
	public:
		// Constructor
		// Default Constructor
		ImageScrambler();
		// Initialize with the given image
		ImageScrambler(Image startingImage);

		// Destructor
		// doesn't need one

		// Accessors/Mutators
		void changeImage(Image newImage);

		// Other Functions
		// move quadrants of the image clockwise
		// will permanently modify myImage
		void moveQuadrantsClockwise();
		// move the quadrants of the image counterclockwise
		// will permanently modify myImage
		void moveQuadrantsCounterClockwise();
		// write the image to file
		void writeImage(std::string outfileName);
};


#endif
