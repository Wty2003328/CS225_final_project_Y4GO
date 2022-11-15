#pragma once
#include "math.h"
#define pi 3.1415926535897932384626433832795
#define EARTH_RAD 6378.137 //unit: km
double cal_dist(double longitude1, double latitude1, double longitude2, double latitude2)
{
	double rad_longtitude1 = pi * longitude1 / 180;
	double rad_latitude1 = pi * latitude1 / 180;
	double rad_longtitude2 = pi * longitude2 / 180;
	double rad_latitude2 = pi * latitude2 / 180;
	double rad_diff_longtitude =rad_longtitude1 - rad_longtitude2;
	double rad_diff_latitude = rad_latitude1 - rad_latitude2;
	double dist = 2 * asin(sqrt(pow(sin(rad_diff_latitude / 2), 2) + cos(rad_latitude1) * cos(rad_latitude2) * pow(sin(rad_diff_longtitude / 2), 2)));
	dist = dist * EARTH_RAD;
	return dist;
}