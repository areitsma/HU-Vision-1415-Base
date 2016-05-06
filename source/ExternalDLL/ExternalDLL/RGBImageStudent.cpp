#include "RGBImageStudent.h"

//Default constructor
RGBImageStudent::RGBImageStudent() : RGBImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

//Constructor with given RGBImageStudent
RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object
	
	RGBImageStudent cpy = RGBImageStudent(other.getWidth(), other.getHeight());
	//delete[] pixelStorage;
	
	//pixelStorage = new RGB[other.getWidth() * other.getHeight()];
	cpy.setAllPixels(pixelStorage);
	/*for (int i = 0; i < cpy.getHeight()*cpy.getWidth(); i++){
		RGB RGB_pix = cpy.getPixel(i);
		pixelStorage[i] = RGB_pix;
	}*/
}

//Constructor with given width and height
RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	//delete[] pixelStorage;
	pixelStorage = new RGB[width * height];
}

RGBImageStudent::~RGBImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
	//delete[] pixelStorage;
}

//Set the RGBImageStudent to given width and height
void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	delete[] pixelStorage;
	pixelStorage = new RGB[width * height];
}

//Set the RGBImageStudent to given RGMImageStudent
void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)

	//delete[] pixelStorage;
	set(other.getWidth(), other.getHeight());
/*	for (int i = 0; i < cpy.getHeight()*cpy.getWidth(); i++){
		RGB RGB_pix = cpy.getPixel(i);
		pixelStorage[i] = RGB_pix;
	}*/
}

//Set the pixel of RGBImageStudent with given x and y coordinate
void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = x + (y * getWidth());
	setPixel(i,pixel);
}

//Set the pixel of RGBImageStudent with given x and y coordinate
void RGBImageStudent::setPixel(int i, RGB pixel) {
	pixelStorage[i] = pixel;
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

//Get pixel of RGBImageStudent with given x and y coordinates
RGB RGBImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = x + (y * getWidth());
	return getPixel(i);
}

//Get pixel of RGBImageStudent with given number
RGB RGBImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	return pixelStorage[i];
}

//Apply all given pixels to the RGBImageStudent
void RGBImageStudent::setAllPixels(RGB* pS){
	pixelStorage = pS;
}