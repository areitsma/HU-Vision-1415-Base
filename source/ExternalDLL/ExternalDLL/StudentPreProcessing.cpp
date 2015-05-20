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
	int kernel[3][3] = { { 0, 1, 0 }, { 1, -4, 1 }, { 0, 1, 0 } };
	IntensityImage * newIntensityImage;
	Intensity newIntensity;
	for (int i; i < image.getWidth(); i++){
		for (int j; j < image.getHeight(); j++){
			if ((i == 0) || (i == image.getWidth() - 1) || (j == 0) || (j == image.getHeight() - 1)){
				newIntensity = 0;
			}
			else{
				for (int x = -1; x <= 1; x++){
					for (int y = -1; y <= 1; y++){
						newIntensity += image.getPixel(x + (i - 1), y + (j - 1)) * kernel[i][j];
					}
				}
				IntensityImage::newIntensityImage.setPixel(i, j, newIntensity);
		}
	}
	
	return newIntensityImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}