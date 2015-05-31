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
	IntensityImageStudent * outImage = new IntensityImageStudent{ 200, 200 };

	int A, B, C, D, x, y, index, gray;

	float x_ratio = ((float)(image.getWidth() - 1)) / dest_width;
	float y_ratio = ((float)(image.getHeight() - 1)) / dest_height;

	float x_diff, y_diff, ya, yb;

	for (int i = 0; i<dest_height; i++) {
		for (int j = 0; j<dest_width; j++) {
			x = (int)(x_ratio * j);
			y = (int)(y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index = y*image.getWidth() + x;

			
			A = image.getPixel(index);
			B = image.getPixel(index + 1);
			C = image.getPixel(index + image.getWidth());
			D = image.getPixel(index + image.getWidth() + 1);

			// Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
			gray = (int)(
				A*(1 - x_diff)*(1 - y_diff) + B*(x_diff)*(1 - y_diff) +
				C*(y_diff)*(1 - x_diff) + D*(x_diff*y_diff)
				);

			outImage->setPixel(j,i, gray);
		}
	}
	return outImage;

}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {

	const int kernel5x5[5][5] =
	{ { 2, 4, 5, 4, 2 },
	{ 4, 9, 12, 9, 4 },
	{ 5, 12, 15, 12, 5 },
	{ 4, 9, 12, 9, 4 },
	{ 2, 4, 5, 4, 2 } };
	//159

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

	int kernel3[3][3] = { { 0, 3, 0 }, 
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

	//sobel
	char kernelX[3][3] = {
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }
	};
	char kernelY[3][3] = {
		{ -1, -2, -1 },
		{ 0, 0, 0 },
		{ 1, 2, 1 }
	};

	IntensityImageStudent *  valueImage = new IntensityImageStudent(image.getWidth() - 4, image.getHeight() - 4);
	IntensityImageStudent * newIntensityImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	
	int newIntensity;

	//first we make the image white
	for (int x = 0; x < newIntensityImage->getWidth(); x++) {
		for (int y = 0; y < newIntensityImage->getHeight(); y++) {
			newIntensityImage->setPixel(x, y, 0);
		}
	}

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
	/*
	float sumX;
	float sumY;
	for (int i = 2; i < valueImage->getWidth()-2; i++){
		for (int j = 2; j < valueImage->getHeight()-2; j++){
				newIntensity = 0;
				sumX = 0.0;
				sumY = 0.0;
				for (int x = -2; x <= 2; x++){
					for (int y = -2; y <= 2; y++){
						newIntensity += valueImage->getPixel(x + i, y + j) * LapKernel5x5[x + 2][y + 2];
					}
				}
				for (int x = -2; x <= 2; x++){
					for (int y = -2; y <= 2; y++){
						newIntensity += valueImage->getPixel(x + i, y + j) * LapKernel5x5[x + 2][y + 2];
					}
				}
				for (int x = -1; x <= 1; x++){
					for (int y = -1; y <= 1; y++){
						newIntensity += valueImage->getPixel(x + i, y + j) * kernel3[x + 1][y + 1];
						//sumX = sumX + kernelX[x + 1][y + 1] * valueImage->getPixel(x + i, y + j); 
						//sumY = sumY + kernelY[x + 1][y + 1] * valueImage->getPixel(x + i, y + j);
					}
				}
				//newIntensity = abs(sumX) + abs(sumY);
				//newIntensity = (newIntensity);
				*/
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImageStudent *  newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());

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