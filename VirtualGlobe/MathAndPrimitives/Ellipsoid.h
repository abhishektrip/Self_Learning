#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Typedefs.h"
#include "ErrorsAndExceptions.h"
namespace VirtualGlobe
{
	namespace Core
	{

		class Ellipsoid
		{
		public:
			//Constructors	
			Ellipsoid(double x, double y, double z);
			Ellipsoid(const double radii[3]);
			Ellipsoid(const double3D radii); 
			// Utility Functions
			double3D surfaceNormalGeodetic ( double3D pointOnEllipsoid );
			double3D surfaceNormalGeometric( double3D pointOnEllipsoid );
			double minimumRadius();
			double maximumRadius();
			//Getters
			double3D Radii() const {return mRadii; } 
			double3D RadiiSquared() const { return mRadiiSquared; }
			double3D RadiiToTheFourth() const { return mRadiiToTheFourth; }
			double3D OneOverRadiiSquared() const { return mOneOverRadiiSquared; }
			
		private :
			//Setters for constants. 
			double3D Radii(double3D radii);
			double3D RadiiSquared(double3D radii);
			double3D RadiiToTheFourth(double3D radii);
			double3D OneOverRadiiSquared(double3D radii);
			// Read Only Constants
			const double3D mRadiiToTheFourth;
			const double3D mRadiiSquared;
			const double3D mOneOverRadiiSquared;
			const double3D mRadii;
		};
		double3D Ellipsoid::Radii(double3D radii)
		{
			if((radii.x() <=0.0 ||radii.y() <= 0.0 || radii.z() <= 0.0 ))
				throw _VG_OUTOFRANGE_EXCEPTION_;
			return radii; 			
		}
		double3D Ellipsoid::RadiiSquared(double3D radii)
		{
			if((radii.x() <=0.0 ||radii.y() <= 0.0 || radii.z() <= 0.0 ))
				throw _VG_OUTOFRANGE_EXCEPTION_;
			return double3D(radii.x()*radii.x(), radii.y()*radii.y(), radii.z()*radii.z());			
		}
		double3D Ellipsoid::RadiiToTheFourth(double3D radii)
		{
			if((radii.x() <=0.0 ||radii.y() <= 0.0 || radii.z() <= 0.0 ))
				throw _VG_OUTOFRANGE_EXCEPTION_;
			return double3D(radii.x()*radii.x()*radii.x()*radii.x(), radii.y()*radii.y()*radii.y()*radii.y(), radii.z()*radii.z()*radii.z()*radii.z());			
		}
		double3D Ellipsoid::OneOverRadiiSquared(double3D radii)
		{
			if((radii.x() <=0.0 ||radii.y() <= 0.0 || radii.z() <= 0.0 ))
				throw _VG_OUTOFRANGE_EXCEPTION_;		
			return double3D(1.0/(radii.x()*radii.x()), 1.0/(radii.y()*radii.y()), 1.0/(radii.z()*radii.z()));
		}
		Ellipsoid::Ellipsoid(double x, double y, double z)
			:mRadii(Radii(double3D(x,y,z))), 
			 mRadiiSquared(RadiiSquared(double3D(x,y,z))) , 
			 mRadiiToTheFourth(RadiiToTheFourth(double3D(x,y,z))) , 
			 mOneOverRadiiSquared(OneOverRadiiSquared(double3D(x,y,z)))
		{
		}
		Ellipsoid::Ellipsoid(const double radii[3])
			:mRadii(Radii(double3D(radii[0], radii[2], radii[2]))), 
			 mRadiiSquared(RadiiSquared(double3D(radii[0], radii[2], radii[2]))) , 
			 mRadiiToTheFourth(RadiiToTheFourth(double3D(radii[0], radii[2], radii[2]))) , 
			 mOneOverRadiiSquared(OneOverRadiiSquared(double3D(radii[0], radii[2], radii[2])))
		{
		}
		Ellipsoid::Ellipsoid(const double3D radii)
			:mRadii(Radii(radii)) , 
			 mRadiiSquared(RadiiSquared(radii)) , 
			 mRadiiToTheFourth(RadiiToTheFourth(radii)) , 
			 mOneOverRadiiSquared(OneOverRadiiSquared(radii))
		{	
		}
		double3D Ellipsoid::surfaceNormalGeometric( double3D pointOnEllipsoid )
		{
			return pointOnEllipsoid.normalize();
		}
		double3D Ellipsoid::surfaceNormalGeodetic( double3D pointOnEllipsoid)
		{
			return (pointOnEllipsoid * mOneOverRadiiSquared).normalize();
		}
		double Ellipsoid::minimumRadius()
		{
			return min<double>( mRadii.x() , min<double>(mRadii.y() , mRadii.z()));
		}
		double Ellipsoid::maximumRadius()
		{
			return max<double>(mRadii.x(), max<double>(mRadii.y(), mRadii.z()));
		}
	}
}

#endif //ELLIPSOID_H