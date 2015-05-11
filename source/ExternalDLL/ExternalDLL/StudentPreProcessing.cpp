#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <algorithm>
#include <iostream>
IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {

	std::cout << "Step to Intensity image " << std::endl;
	IntensityImageStudent * IntImage = new IntensityImageStudent{ image.getWidth(), image.getHeight() };
	for (int i = 0; i < image.getHeight()* image.getWidth(); i++){
			RGB rgbPix = image.getPixel(i); 
			//convert RGB values to gray/intensity value
			//int Gray = (rgbPix.r + rgbPix.g + rgbPix.b) / 3; //Method Average
			//int Gray = (rgbPix.r * 0.299 + rgbPix.g  * 0.587 + rgbPix.b  * 0.114); //Method Luma
			int Gray = (std::max({ rgbPix.r, rgbPix.g, rgbPix.b }) + std::min({ rgbPix.r, rgbPix.g, rgbPix.b})) / 2; // Method Desaturation
			IntImage->setPixel(i, Gray);
		}
	return IntImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}