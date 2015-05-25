#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <algorithm>
#include <iostream>

const int kernel5x5[5][5] =
{ { 2, 4, 5, 4, 2 }, 
{ 4, 9, 12, 9, 4 },
{ 5, 12, 15, 12, 5 },
{ 4, 9, 12, 9, 4 },
{ 2, 4, 5, 4, 2 }, }; 

//Gausian
const int kernel5x51[5][5] =
{ { 1, 2, 3, 2, 1 },
{ 2, 7, 11, 7, 2 },
{ 3, 11, 17, 11, 3 },
{ 2, 7, 11, 7, 2 },
{ 1, 2, 3, 2, 1 }, };

const int LapKernel5x5[5][5] =
{ { -1, -1, -1, -1, -1, },
{ -1, -1, -1, -1, -1, },
{ -1, -1, 24, -1, -1, },
{ -1, -1, -1, -1, -1, },
{ -1, -1, -1, -1, -1 } };

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
	int kernel[3][3] = { { 0, 1, 0 }, 
						{ 1, -4, 1 }, 
						{ 0, 1, 0 } };

	IntensityImageStudent *  valueImage = new IntensityImageStudent(image.getWidth() - 4, image.getHeight() - 4);
	IntensityImageStudent * newIntensityImage = new IntensityImageStudent(valueImage->getWidth(), valueImage->getHeight());

	Intensity newIntensity;

	for (int x = 2; x < image.getWidth() - 2; x++){
		for (int y = 2; y < image.getHeight() - 2; y++){
			int newIntensity = 0;

			for (int g = -2; g < 3; g++){
				for (int q = -2; q < 3; q++){
					newIntensity += image.getPixel(x + g, y + q) * (kernel5x51[g + 2][q + 2]);
				}
			}
			valueImage->setPixel(x - 2, y - 2, static_cast<unsigned char>(newIntensity / 159.0));
		}
	}

	for (int i = 0; i < valueImage->getWidth(); i++){
		for (int j = 0; j < valueImage->getHeight(); j++){
			if ((i == 0) || (i == valueImage->getWidth() - 2) || (j == 0) || (j == valueImage->getHeight() - 2)){
				newIntensity = 0;
			}
			else{
				newIntensity = 0;
				for (int x = -2; x <= 2; x++){
					for (int y = -2; y <= 2; y++){
						newIntensity += valueImage->getPixel(x + i, y + j) * LapKernel5x5[x + 2][y + 2];
					}
				}
				if (newIntensity > 255){
					newIntensity = 255;
				}
				else if (newIntensity < 0){
					newIntensity = 0;
				}
				newIntensityImage->setPixel(i, j, newIntensity);
			}
		}
	}
	return newIntensityImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}