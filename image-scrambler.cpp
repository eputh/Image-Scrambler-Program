//
// Name: Emily Puth
// ID: 28239807
//

#include "image-scrambler.h"
#include <fstream>
#include <iostream>


// Constructors
ImageScrambler::ImageScrambler() {}

ImageScrambler::ImageScrambler(Image startingImage) {
	myImage = startingImage;
	setQuadrants();
}


// Prive Helper Functions
void ImageScrambler::setQuadrants() {
	quadrant1 = myImage.getQuadrant(1);
	quadrant2 = myImage.getQuadrant(2);
	quadrant3 = myImage.getQuadrant(3);
	quadrant4 = myImage.getQuadrant(4);
}


// Accessors/Mutators
void ImageScrambler::changeImage(Image newImage) {
	myImage = newImage;
	setQuadrants();
}


// Other Functions
void ImageScrambler::moveQuadrantsClockwise() {
	myImage.setQuadrant(1, &quadrant3);
	myImage.setQuadrant(2, &quadrant1);
	myImage.setQuadrant(3, &quadrant4);
	myImage.setQuadrant(4, &quadrant2);
}

void ImageScrambler::moveQuadrantsCounterClockwise() {
	myImage.setQuadrant(1, &quadrant2);
	myImage.setQuadrant(2, &quadrant4);
	myImage.setQuadrant(3, &quadrant1);
	myImage.setQuadrant(4, &quadrant3);
}

void ImageScrambler::writeImage(std::string outfileName) {
	std::ofstream outfile(outfileName);
	if(outfile.is_open()) {
		outfile << "P2\n" << myImage.getWidth() << " " << myImage.getHeight() << "\n" << myImage.getMaxGrayValue() << std::endl;
		for (int r=0; r<myImage.getHeight(); r++) {
			for (int c=0; c<myImage.getWidth(); c++)
				outfile << myImage.getPicture()[r][c] << " ";
			outfile << "\n";
		}
	}
}


int main() {
	// Rotate picture1.pgm (mountain) once clockwise
	Image mountain("picture1.pgm");
	ImageScrambler picture1Scrambled (mountain);
	picture1Scrambled.moveQuadrantsClockwise();
	picture1Scrambled.writeImage("picture1_scrambled.pgm");

	// Rotate picture2.pgm (totem) once counterclockwise
	Image totem("picture2.pgm");
	ImageScrambler picture2Scrambled (totem);
	picture2Scrambled.moveQuadrantsCounterClockwise();
	picture2Scrambled.writeImage("picture2_scrambled.pgm");

	// Changes the Image for picture1Scrambled to picture3.pgm (airplanes)
	// and rotates twice clockwise
	Image airplanes("picture3.pgm");
	picture1Scrambled.changeImage(airplanes);
	picture1Scrambled.moveQuadrantsClockwise();
	picture1Scrambled.moveQuadrantsClockwise();
	picture1Scrambled.writeImage("picture3_scrambled.pgm");
	
	return 0;
}
