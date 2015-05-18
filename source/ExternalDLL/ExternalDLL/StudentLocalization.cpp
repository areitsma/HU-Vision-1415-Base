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

	std::cout << "Chin Contourse" << std::endl;
	Feature Mouth = features.getFeature(Feature::FEATURE_MOUTH_TOP);
	Point2D<double> MouthPosition;
	
	std::vector<Point2D<double>> ChinPositions;
	Feature Chin = Feature(Feature::FEATURE_CHIN);
	Feature ChinContour = Feature(Feature::FEATURE_CHIN_CONTOUR);
	int y = 0;
	int m = 0;
	
	for (int j = HALF_CIRCLE; j > 0; j -= DEGREE_STEP){
		MouthPosition.set(Mouth.getX(), Mouth.getY()); //return to the mouthtop
		MouthPosition.set(drawLine(j, START_POSITION, MouthPosition));
	
		std::cout << std::endl << "line " << m << std::endl;
		m = m + 1;

		for (int i = 0; i < MEASURE_RANGE; i++){

			MouthPosition.set(drawLine(j, MEASURE_STEP, MouthPosition));

			Intensity pixel = image.getPixel(MouthPosition.getX(), MouthPosition.getY());
			std::cout << i << "  ";

			if (pixel < 2){ //detect chin contour
				std::cout << std::endl << "found pixel " << pixel << std::endl;
				if (j < RIGHT_HALF && j > LEFT_HALF){
					ChinContour.addPoint(drawLine(j, 2, MouthPosition));
				}
				else{
					ChinContour.addPoint(MouthPosition);
				}
				break;
			}
		}	
	}	
	features.putFeature(ChinContour);
	return true;
}

Point2D<double> StudentLocalization::drawLine(double angle, int len, Point2D<double> point) const{
	angle = angle * M_PI / HALF_CIRCLE; // Degrees to radians
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