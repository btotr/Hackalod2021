#include "geo.h"
#include <math.h>
#include <string>
#include <stdio.h>
#include <iostream>


float round6(float var)
{
    float value = (int)(var * 1000000 + .5);
    return (float)value / 1000000;
}

std::string locationToWGS84(int x, int y) {

    int referenceRdX = 155000;
    int referenceRdY = 463000;

    double dX = (x - referenceRdX) * (pow(10, -5));
    double dY = (y - referenceRdY) * (pow(10,-5));

    double sumN =
      (3235.65389 * dY) +
      (-32.58297 * (pow(dX, 2))) +
      (-0.2475 * (pow(dY, 2))) +
      (-0.84978 * (pow(dX, 2)) * dY) +
      (-0.0655 * (pow(dY, 3))) +
      (-0.01709 * (pow(dX, 2)) * (pow(dY, 2))) +
      (-0.00738 * dX) ; // +
      (0.0053 * (pow(dX, 4))) +
      (-0.00039 * (pow(dX,2)) * (pow(dY,3))) +
      (0.00033 * (pow(dX,4)) * dY) +
      (-0.00012 * dX * dY);

    double sumE =
      (5260.52916 * dX) +
      (105.94684 * dX * dY) +
      (2.45656 * dX * (pow(dY,2))) +
      (-0.81885 * pow(dX, 3)) +
      (0.05594 * dX * (pow(dY, 3))) +
      (-0.05607 * (pow(dX,3)) * dY) +
      (0.01199 * dY) +
      (-0.00256 * (pow(dX, 3)) * (pow(dY,2))) +
      (0.00128 * dX * (pow(dY,4))) +
      (0.00022 * (pow(dY,2))) +
      (-0.00022 * (pow(dX,2))) +
      (0.00026 * (pow(dX,5)));

    double referenceWgs84X = 52.15517;
    double referenceWgs84Y = 5.387206;

    double latitude = referenceWgs84X + (sumN / 3600);
    double longitude = referenceWgs84Y + (sumE / 3600);
    
    std::string latlong = std::to_string(round6(latitude)) + " " +  std::to_string(round6(longitude));

    return latlong;
}

int main ( void )
{
    std::string wgs84 = locationToWGS84(121687,487484);
    std::cout << wgs84;
    return 0;
}

