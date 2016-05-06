#include "IntensityImageStudent.h"

//Constructor of new intenisityimage
IntensityImageStudent::IntensityImageStudent() : IntensityImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

//Copy Constructor of new intenisityimage 
IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object
	IntensityImageStudent(other.getWidth(), other.getHeight());
	/*IntensityImageStudent cpy = other;
	delete[] pixel_storage; 
	for (int i = 0; i < cpy.getHeight()*cpy.getWidth(); i++){
		Intensity intensity_pix = cpy.getPixel(i);
		pixel_storage[i] = intensity_pix;
	}*/
}

//Constructor of new intenisityimage with given width and height
IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	//delete[] pixel_storage;
	pixel_storage = new Intensity[width * height];

}

//Destrutor
IntensityImageStudent::~IntensityImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
	delete[] pixel_storage;
}

//Set width and height of intensityImage
void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	//delete[] pixel_storage;
	pixel_storage = new Intensity[width * height];
}

//Set width and height of other intensityImage
void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	//delete[] pixel_storage;
	IntensityImageStudent cpy = other;
	for (int i = 0; i < cpy.getHeight()*cpy.getWidth(); i++){
		Intensity intensity_pix = cpy.getPixel(i);
		pixel_storage[i] = intensity_pix;
	}
		
}

//Set pixel of intenistyImage with the given intensity
void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = x + (y * this->getWidth());
	setPixel(i, pixel);
}

//Set pixel of intenistyImage with the given intensity
void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	//int throwError = 0, e = 1 / throwError;
	pixel_storage[i] = pixel;

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

//Get intensity pixel
Intensity IntensityImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = x + (y * this->getWidth());
	return pixel_storage[i];
	
}

//Get intensity pixel
Intensity IntensityImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	return pixel_storage[i];

}