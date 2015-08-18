// 
// Name: Emily Puth
// ID: 28239807
//

#include "image.h"
#include <fstream>
#include <iostream>


// Constructors
Image::Image() {
	width = 0; height = 0;
	maxGrayValue = 0;
}

Image::Image(std::string filename) {
	readImage(filename);
}

Image::Image(int width, int height) {
	this->width = width;
	this->height = height;
	this->picture = new int* [this->height];
	for (int i=0; i<this->height; i++)
		this->picture[i] = new int[width];
}

Image::Image(const Image& other) {
	width = other.getWidth();
	height = other.getHeight();
	maxGrayValue = other.getMaxGrayValue();
	picture = new int*[height];
	for (int i=0; i<height; i++)
		picture[i] = new int [width];
	setPicture(other.getPicture(), other.getWidth(), other.getHeight());
}

Image::~Image() {
	// delete picture array
	// delete each row
	for (int i=0; i<height; i++)
		delete[] picture[i];
	// delete the "spine" of the array
	delete[] picture;
}


// Accessors/Mutators
void Image::setPicture(int** pictureArray, int width, int height) {
	for(int r=0; r<height; r++)
		for(int c=0; c<width; c++)
			picture[r][c] = pictureArray[r][c];
}


// Other Functions
// Assignment Operator Overload
Image& Image::operator=(const Image& other) {
	if (this == &other)
		return *this;
	width = other.getWidth();
	height = other.getHeight();
	maxGrayValue = other.getMaxGrayValue();
	picture = new int*[height];
	for (int i=0; i<height; i++)
		picture[i] = new int [width];
	setPicture(other.getPicture(), other.getWidth(), other.getHeight());
	return *this;
}

bool Image::readImage(std::string filename) {
	std::ifstream infile(filename);
	std::string p2;
	infile >> p2 >> width >> height >> maxGrayValue;
	if (infile.is_open()) {
		picture = new int* [height];
		for (int r=0; r<height; r++) {
			picture[r] = new int[width]; 
			for (int c=0; c<width; c++) 
				infile >> picture[r][c]; 
		}
		return true;
	}
	return false;
}

bool Image::writeImage(std::string filename) {
	std::ofstream outfile(filename);
	if(outfile.is_open()) {
		outfile << "P2\n" << width << " " << height << "\n" << maxGrayValue << std::endl;
		for(int r=0; r<height; r++) {
			for(int c=0; c<width; c++)
				outfile << picture[r][c] << " ";
			outfile << "\n";
		}
		return true;
	}
	return false;
}

Image Image::getQuadrant(int whichQuadrant) {
	Image quadrant(width/2, height/2); 
	quadrant.setMaxGrayValue(maxGrayValue);
	int** tempPicture = new int*[height/2];
	for(int i=0; i<height/2; i++) tempPicture[i] = new int[width/2];
	if (whichQuadrant == 1) {
		for (int r=0; r<(height/2); r++)
			for (int c=0; c<(width/2); c++)
				tempPicture[r][c] = picture[r][c];
	}
	else if (whichQuadrant == 2) {
		for (int r=0; r<height/2; r++) {
			int quadrantWidth = 0;
			for (int c=width/2; c<width; c++) {
				tempPicture[r][quadrantWidth] = picture[r][c];
				quadrantWidth++;
			}
		}
	}
	else if (whichQuadrant == 3) {
		int quadrantHeight = 0;
		for (int r=height/2; r<height; r++) {
			for (int c=0; c<width/2; c++) 
				tempPicture[quadrantHeight][c] = picture[r][c];
			quadrantHeight++;
		}
	}
	else if (whichQuadrant == 4) {
		int quadrantHeight = 0;
		for (int r=height/2; r<height; r++) {
			int quadrantWidth = 0;
			for (int c=width/2; c<width; c++) {
				tempPicture[quadrantHeight][quadrantWidth] = picture[r][c];
				quadrantWidth++;
			}
			quadrantHeight++;
		}
	} 
	quadrant.setPicture(tempPicture, width/2, height/2);
	return quadrant;
}

void Image::setQuadrant(int whichQuadrant, const Image* newQuadrant) {
	if(whichQuadrant == 1) {
		for (int r=0; r<height/2; r++)
			for (int c=0; c<width/2; c++)
				picture[r][c] = newQuadrant->getPicture()[r][c];
	}
	else if (whichQuadrant == 2) {
		for (int r=0; r<height/2; r++) {
			int quadrantWidth = 0;
			for (int c=width/2; c<width; c++) {
				picture[r][c] = newQuadrant->getPicture()[r][quadrantWidth];
				quadrantWidth++;
			}
		}
	}
	else if (whichQuadrant == 3) {
		int quadrantHeight = 0;
		for (int r=height/2; r<height; r++) {
			for (int c=0; c<width/2; c++)
				picture[r][c] = newQuadrant->getPicture()[quadrantHeight][c];
			quadrantHeight++;
		}
	}
	else if (whichQuadrant == 4) {
		int quadrantHeight = 0;
		for (int r=height/2; r<height; r++) {
			int quadrantWidth = 0;
			for (int c=width/2; c<width; c++) {
				picture[r][c] = newQuadrant->getPicture()[quadrantHeight][quadrantWidth];
				quadrantWidth++;
			}
		quadrantHeight++;
		}
	}
}

/*
int main() {
	Image mountain("picture1.pgm");
	Image img(mountain);
	Image mountainQuadrant = mountain.getQuadrant(1);
	mountainQuadrant.writeImage("mountain-quadrant1.pgm");
	Image mountainQuadrant2 = mountain.getQuadrant(2);
	mountainQuadrant2.writeImage("mountain-quadrant2.pgm");
	Image mountainQuadrant3 = mountain.getQuadrant(3);
	mountainQuadrant3.writeImage("mountain-quadrant3.pgm");
	Image mountainQuadrant4 = mountain.getQuadrant(4);
	mountainQuadrant4.writeImage("mountain-quadrant4.pgm");
	
	img.setQuadrant(1, &mountainQuadrant4);
	img.setQuadrant(2, &mountainQuadrant3);
	img.setQuadrant(3, &mountainQuadrant2);
	img.setQuadrant(4, &mountainQuadrant);
	for (int r=0; r<10; r++) for (int c=0; c<10; c++) std::cout << img.getPicture()[r][c] << " ";
	std::cout << "\n";
	img.writeImage("changed-mountain.pgm");
	return 0;
}*/
