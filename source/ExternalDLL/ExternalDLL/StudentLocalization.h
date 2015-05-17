/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "Localization.h"
class StudentLocalization :
	public Localization {
public:
	bool stepFindHead(const IntensityImage &image, FeatureMap &features) const;
	bool stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const;
	bool stepFindChinContours(const IntensityImage &image, FeatureMap &features) const;
	bool stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const;
	bool stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const;
	Point2D<double> drawLine(double angle, int len, Point2D<double> point) const;

	const int DEGREE_STEP = 10;
	const int HALF_CIRCLE = 180;
	const int START_POSITION = 27;
	const int MEASURE_RANGE = 30;
	const int MEASURE_STEP = 1;
	const int LEFT_HALF = 140;
	const int RIGHT_HALF = 40;
}; 

