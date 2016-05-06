#include "StudentLocalization.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {

	//Get the position of the mouth
	Feature Mouth = features.getFeature(Feature::FEATURE_MOUTH_TOP);
	Point2D<double> MouthPosition;
	
	//Initialise the chin feature
	std::vector<Point2D<double>> ChinPositions;
	Feature Chin = Feature(Feature::FEATURE_CHIN);
	Feature ChinContour = Feature(Feature::FEATURE_CHIN_CONTOUR);
	int y = 0;
	int m = 0;
	
	//Draw a half circle starting from the center of the mouth
	for (int j = HALF_CIRCLE; j > 0; j -= DEGREE_STEP){
		
		//reset the position of the mouth
		MouthPosition.set(Mouth.getX(), Mouth.getY());
		MouthPosition.set(drawLine(j, START_POSITION, MouthPosition));
	
		m = m + 1;

		
		for (int i = 0; i < MEASURE_RANGE; i++){

			MouthPosition.set(drawLine(j, MEASURE_STEP, MouthPosition));
			Intensity pixel = image.getPixel(MouthPosition.getX(), MouthPosition.getY());

			// If the intensity of the current pixel is lower than 2 (which means it is black)
			if (pixel < 2){ 
				
				// If the current angle is within the bounds of the half circle
				if (j < RIGHT_HALF && j > LEFT_HALF){
					ChinContour.addPoint(drawLine(j, 2, MouthPosition));
				}
				else{
					//Draw a point on the mouth position, to indicate the detection failed.
					ChinContour.addPoint(MouthPosition);
				}
				break;
			}
		}	
	}	
	features.putFeature(ChinContour);
	return true;
}

//Draw a line from a given position, with given length and angle
Point2D<double> StudentLocalization::drawLine(double angle, int len, Point2D<double> point) const{
	angle = angle * M_PI / HALF_CIRCLE; // Convert degrees to radians
	Point2D<double> point1;
	point1.setX(point.getX() + len * cos(angle)); 
	point1.setY(point.getY() + len * sin(angle));
	return point1;
}
bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}