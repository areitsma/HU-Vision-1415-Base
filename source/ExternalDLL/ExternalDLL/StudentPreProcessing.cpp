#include "StudentPreProcessing.h"
#include "IntensityImageStudent.h"
#include <algorithm>
#include <iostream>
#include <vector>


//Grayscale RGBImage to intensity image
IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {

	std::cout << "Step to Intensity image " << std::endl;
	
	// Create new IntensityImage with size of the image width and height
	IntensityImageStudent * IntImage = new IntensityImageStudent{ image.getWidth(), image.getHeight() };

	// Loop through every pixel of the entire image and calculate the Gray value with the selected method
	for (int i = 0; i < image.getHeight()* image.getWidth(); i++){
			//Get one pixel on position i of the image 
			RGB rgbPix = image.getPixel(i); 

			//convert RGB values to gray/intensity value
			//Source: https://en.wikipedia.org/wiki/Grayscale

			//Method Average, devide summation of r,g and b by 3
			//int Gray = (rgbPix.r + rgbPix.g + rgbPix.b) / 3; 

			//Method Luma, multiply r, g and b with specific value
			//int Gray = (rgbPix.r * 0.299 + rgbPix.g  * 0.587 + rgbPix.b  * 0.114);

			//Method Desaturation, add max value of r, g or b to min value of r, g or b
			int Gray = (std::max({ rgbPix.r, rgbPix.g, rgbPix.b }) + std::min({ rgbPix.r, rgbPix.g, rgbPix.b})) / 2;

			//Set the new pixel on position i
			IntImage->setPixel(i, Gray);
		}
	return IntImage;
}

//Bilinear scaling
IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	//Set destination width and height
	int dest_width = 200;
	int dest_height = 200;

	//Create new image what will be the output with the destination width and height
	IntensityImageStudent * outImage = new IntensityImageStudent{ dest_width, dest_height };

	int topLeft, topRight, bottomLeft, bottomRight, x, y, intensityValue;

	//Calculate the scale ratio's based on width and height of image and destination width and height
	float xRatio = ((float)(image.getWidth() - 1)) / dest_width;
	float yRatio = ((float)(image.getHeight() - 1)) / dest_height;

	float xDiff, yDiff;

	// Loop through destination image
	for (int i = 0; i<dest_height; i++) {
		for (int j = 0; j<dest_width; j++) {

			//Calculate the x and y based on the ratio and current element
			x = (int)(xRatio * j);
			y = (int)(yRatio * i);

			//Calculate the x and y difference
			xDiff = (xRatio * j) - x;
			yDiff = (yRatio * i) - y;
			
			//Get the values of every corner of the image
			topLeft = image.getPixel(x, y);
			topRight = image.getPixel(x + 1, y);
			bottomLeft = image.getPixel(x, y + 1);
			bottomRight = image.getPixel(x + 1, y + 1);

			//Calculate intensity value of the current output pixel:
			//gray amount = topLeft(1-w)(1-h) + topRight(w)(1-h) + bottomLeft(h)(1-w) + bottomRightwh
			intensityValue = (int)(
				topLeft * (1 - xDiff) * (1 - yDiff) + topRight*(xDiff) * (1 - yDiff) +
				bottomLeft * (yDiff) * (1 - xDiff) + bottomRight * (xDiff * yDiff)
				);

			//Set the pixel on the output image
			outImage->setPixel(j, i, intensityValue);
		}
	}
	return outImage;

}

//Function to create edge detected image
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

	//Create the new intensityImage 
	IntensityImageStudent * newIntensityImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	
	int newIntensity;

	// Make every pixel of the new image white (0)
	for (int x = 0; x < newIntensityImage->getWidth(); x++) {
		for (int y = 0; y < newIntensityImage->getHeight(); y++) {
			newIntensityImage->setPixel(x, y, 0);
		}
	}

	// Algorithm for convolving the image and the kernel, source https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution
	// First loop through entire image except the border (4 pixel = kernel size /2) because otherwise the kernel will be out of range
	for (int x = 4; x < image.getWidth() - 4; x++){
		for (int y = 4; y < image.getHeight() - 4; y++){

			//Reset intensity accumulator to 0
			newIntensity = 0;

			// Now loop through entire kernel, first the row then the elements in that row 
			for (int g = -4; g <= 4; g++){
				for (int q = -4; q <= 4; q++){
					//Get the pixel intensity and caluclate the accumulator intensity by multiplying the pixel value and the kernel element value, add this to the accumulator intensity
					newIntensity += (image.getPixel(x + g, y + q) * (LapKernel9x9[g + 4][q + 4]));
				}
			}
			//Threshold check, if new intensity higher then 255 pixel is black and lower then the pixel is white
			if (newIntensity > 255){
				newIntensity = 255;
			}
			else if (newIntensity < 0){
				newIntensity = 0;
			}
			//Set the new white or black pixel
			newIntensityImage->setPixel(x, y, static_cast<unsigned char>(newIntensity));
		}
	}
	return newIntensityImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImageStudent *  newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	// Threshold set to 210 for the best image
	int threshold = 210;

	// Loop through entire image, first the row then the elements in that row 
	for (int x = 0; x < image.getWidth(); x++){
		for (int y = 0; y < image.getHeight(); y++){

			int intensityValue = 0;
			//Get intensity value of pixel x, y
			intensityValue = image.getPixel(x, y);

			//Check if threshold is higher then the value if so intensity value is set to 0, else to 255
			if (intensityValue > threshold){
				intensityValue = 0;
			}
			else {
				intensityValue = 255;
			}
			//Set the new intensity value on pixel x, y of new image
			newImage->setPixel(x, y, static_cast<unsigned char>(intensityValue));
		}
	}
	return newImage;
}