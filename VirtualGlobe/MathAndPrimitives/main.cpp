#include <iostream>
#include "Vector3D.h"
#include "Ellipsoid.h"
using namespace std;

int main()
{
    Vector3D<double> v(6378250.0,6378260.0,6356752.314245);

    Vector3D<double> w = v;
    Vector3D<double> a = w+v;
	Vector3D<double> b = w-v;
	//Ellipsoid WGS84(6378137.0,6378137.0,6356752.314245);
	//WGS84.surfaceNormalGeodetic(v);

	a = w+v;
	double rhs[3] = {20,30,40};
	a = rhs; 
	a.x(500);
	a = (3.3*w);
	a= v*4.5;
	std::cout<<a.x();
	a.normalize();
    bool test;
    test = (v==w)?true:false;

    std::cout << "Hello World!" << endl;
    return 0;
}

