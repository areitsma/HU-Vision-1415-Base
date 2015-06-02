#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <algorithm>
#include <iostream>
#include <vector>


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

//Bilinear scaling
IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	int dest_width = 200;
	int dest_height = 200;
	IntensityImageStudent * outImage = new IntensityImageStudent{ dest_width, dest_height };

	int topLeft, topRight, bottomLeft, bottomRight, x, y, intensityValue;

	//Berekening van ratio's
	float xRatio = ((float)(image.getWidth() - 1)) / dest_width;
	float yRatio = ((float)(image.getHeight() - 1)) / dest_height;

	float xDiff, yDiff;

	for (int i = 0; i<dest_height; i++) {
		for (int j = 0; j<dest_width; j++) {
			x = (int)(xRatio * j);
			y = (int)(yRatio * i);
			xDiff = (xRatio * j) - x;
			yDiff = (yRatio * i) - y;
			
			topLeft = image.getPixel(x, y);
			topRight = image.getPixel(x + 1, y);
			bottomLeft = image.getPixel(x, y + 1);
			bottomRight = image.getPixel(x + 1, y + 1);

			// gray amount = topLeft(1-w)(1-h) + topRight(w)(1-h) + bottomLeft(h)(1-w) + bottomRightwh
			intensityValue = (int)(
				topLeft * (1 - xDiff) * (1 - yDiff) + topRight*(xDiff) * (1 - yDiff) +
				bottomLeft * (yDiff) * (1 - xDiff) + bottomRight * (xDiff * yDiff)
				);

			outImage->setPixel(j, i, intensityValue);
		}
	}
	return outImage;

}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {

	//kernels:
	const int kernel5x5[5][5] =
	{ { 2, 4, 5, 4, 2 },
	{ 4, 9, 12, 9, 4 },
	{ 5, 12, 15, 12, 5 },
	{ 4, 9, 12, 9, 4 },
	{ 2, 4, 5, 4, 2 } };

	//Gausian
	const int kernel5x51[5][5] =
	{ { 1, 2, 3, 2, 1 },
	{ 2, 7, 11, 7, 2 },
	{ 3, 11, 17, 11, 3 },
	{ 2, 7, 11, 7, 2 },
	{ 1, 2, 3, 2, 1 } };

	const int LKernel5x5[5][5] =
	{ { -1, -1, -1, -1, -1, },
	{ -1, -1, -1, -1, -1, },
	{ -1, -1, 24, -1, -1, },
	{ -1, -1, -1, -1, -1, },
	{ -1, -1, -1, -1, -1 } };

	const int LapKernel9x9[9][9] =
	{ { 0, 0, 0, 1, 1, 1, 0, 0, 0 },	
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 } };

	const int Sobel9x9[9][9] =
	{ { 4, 3, 2, 1, 0, -1, -2, -3, -4 },
	{ 5, 4, 3, 2, 0, -2, -3, -4, -5 },
	{ 6, 5, 4, 3, 0, -3, -4, -5, -6 },
	{ 7, 6, 5, 4, 0, -4, -5, -6, -7 },
	{ 8, 7, 6, 5, 0, -5, -6, -7, -8 },
	{ 7, 6, 5, 4, 0, -4, -5, -6, -7 },
	{ 6, 5, 4, 3, 0, -3, -4, -5, -6 },
	{ 5, 4, 3, 2, 0, -2, -3, -4, -5 },
	{ 4, 3, 2, 1, 0, -1, -2, -3, -4 } };

	const int Kernel9x9drie[9][9] =
	{ { 0, 0, 3, 2, 2, 2, 3, 0, 0 },
	{ 0, 2, 3, 5, 5, 5, 3, 2, 0 },
	{ 3, 3, 5, 3, 0, 3, 5, 3, 3 },
	{ 2, 5, 3, -12, -23, -12, 3, 5, 2 },
	{ 2, 5, 0, -23, -40, -23, 0, 5, 2 },
	{ 2, 5, 3, -12, -23, -12, 3, 5, 2 },
	{ 3, 3, 5, 3, 0, 3, 5, 3, 3 },
	{ 0, 2, 3, 5, 5, 5, 3, 2, 0 },
	{ 0, 0, 3, 2, 2, 2, 3, 0, 0 } };


	int kernel3[3][3] = 
	{ { 0, 3, 0 }, 
	{ 3, -12, 3 }, 
	{ 0, 3, 0 } };

	int kernel2[3][3] = 
	{ { 1, 2,1},
	{ 2, 4, 2 },
	{ 1, 2, 1 } };

	int Sobelkernel[3][3] =
	{ { -1, -1, -1 },
	{ -1, 8, -1 },
	{ -1, -1, -1 } };


	IntensityImageStudent *  valueImage = new IntensityImageStudent(image.getWidth() - 4, image.getHeight() - 4);
	IntensityImageStudent * newIntensityImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	
	int newIntensity;

	//maak image wit
	for (int x = 0; x < newIntensityImage->getWidth(); x++) {
		for (int y = 0; y < newIntensityImage->getHeight(); y++) {
			newIntensityImage->setPixel(x, y, 0);
		}
	}

	//uitvoeren van de kernel op de image
	for (int x = 4; x < image.getWidth() - 4; x++){
		for (int y = 4; y < image.getHeight() - 4; y++){
			newIntensity = 0;

			for (int g = -4; g <= 4; g++){
				for (int q = -4; q <= 4; q++){
					newIntensity += (image.getPixel(x + g, y + q) * (LapKernel9x9[g + 4][q + 4]));
				}
			}
			if (newIntensity > 255){
				newIntensity = 255;
			}
			else if (newIntensity < 0){
				newIntensity = 0;
			}
			newIntensityImage->setPixel(x, y, static_cast<unsigned char>(newIntensity));
		}
	}
	return newIntensityImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImageStudent *  newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	// met threshold waarde van 210 kregen we de besten afbeeldingen. 
	int threshold = 210;

	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){
			int intensityValue = 0;
			intensityValue = image.getPixel(x, y);

			if (intensityValue > threshold){
				intensityValue = 0;
			}
			else {
				intensityValue = 255;
			}
			newImage->setPixel(x, y, static_cast<unsigned char>(intensityValue));
		}
	}
	return newImage;
}