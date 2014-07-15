#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace VirtualGlobe
{
	namespace Core
	{

		template <typename DATA_TYPE>
		class Vector3D
		{
		public:
			//Constructors
			Vector3D();
			Vector3D(DATA_TYPE x, DATA_TYPE y, DATA_TYPE z);
			Vector3D(DATA_TYPE tuple[3]);
			// Utility fuctions
			Vector3D& operator=(Vector3D rhs);
			Vector3D& operator=(const DATA_TYPE rhs[3]);
			Vector3D operator+(const Vector3D& rhs);
			Vector3D operator+(const Vector3D& rhs) const;
			Vector3D operator-(const Vector3D& rhs);
			Vector3D operator-(const Vector3D& rhs) const;
			Vector3D operator*(const Vector3D& rhs);
			Vector3D operator*(const Vector3D& rhs) const;
			friend Vector3D operator*(const DATA_TYPE scale, const Vector3D<DATA_TYPE>& rhs)
			{
				return Vector3D(scale * rhs.mVector3D[0], scale * rhs.mVector3D[1], scale * rhs.mVector3D[2]);
			}
			friend Vector3D operator*(const Vector3D& lhs  , const DATA_TYPE scale)
			{
				return Vector3D<DATA_TYPE>(scale * lhs.mVector3D[0], scale * lhs.mVector3D[1], scale * lhs.mVector3D[2]);
			}
			bool operator==(const Vector3D& rhs);
			Vector3D normalize();
			DATA_TYPE dotProduct(const Vector3D& rhs);
			Vector3D crossProduct(const Vector3D& rhs);
			void vectorSwap(Vector3D& rhs);
			//Getter setter
			inline DATA_TYPE x() {return mVector3D[0];}
			inline DATA_TYPE x() const {return mVector3D[0];}
			inline DATA_TYPE y() {return mVector3D[1];}
			inline DATA_TYPE y() const {return mVector3D[0];}
			inline DATA_TYPE z() {return mVector3D[2];}
			inline DATA_TYPE z() const {return mVector3D[0];}
			inline void x(DATA_TYPE _x) { mVector3D[0] = _x; }
			inline void y(DATA_TYPE _y) { mVector3D[1] = _y; }
			inline void z(DATA_TYPE _z) { mVector3D[2] = _z; }

		protected:
			void assign(DATA_TYPE x, DATA_TYPE y, DATA_TYPE z);
		private :
			DATA_TYPE mVector3D[3];
		};
		template<typename DATA_TYPE>
		void Vector3D<DATA_TYPE>::assign(DATA_TYPE x, DATA_TYPE y, DATA_TYPE z)
		{ 
			mVector3D[0] = x;
			mVector3D[1] = y;
			mVector3D[2] = z;
		}
		//Constructors
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE>::Vector3D()
		{
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE>::Vector3D(DATA_TYPE x, DATA_TYPE y, DATA_TYPE z)
		{ 
			assign(x,y,z);
		}

		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE>::Vector3D(DATA_TYPE tuple[3])
		{
			assign(tuple[0], tuple[1], tuple[2]);
		}

		// Utility fuctions

		template<typename DATA_TYPE>
		void Vector3D<DATA_TYPE>::vectorSwap(Vector3D& rhs)
		{
			using std::swap;
			swap<DATA_TYPE>(mVector3D,rhs.mVector3D);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE>& Vector3D<DATA_TYPE>::operator=(Vector3D<DATA_TYPE> rhs)
		{
			vectorSwap(rhs);
			return *this;
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE>& Vector3D<DATA_TYPE>::operator=(const DATA_TYPE rhs[3])
		{  
			assign(rhs[0],rhs[1],rhs[2]);
			return *this;
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator+(const Vector3D<DATA_TYPE>& rhs)
		{
			return Vector3D(mVector3D[0] + rhs.mVector3D[0], mVector3D[1] + rhs.mVector3D[1], mVector3D[2] + rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator+(const Vector3D<DATA_TYPE>& rhs) const
		{
			return Vector3D(mVector3D[0] + rhs.mVector3D[0], mVector3D[1] + rhs.mVector3D[1], mVector3D[2] + rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator-(const Vector3D<DATA_TYPE>& rhs)
		{
			return Vector3D(mVector3D[0] - rhs.mVector3D[0], mVector3D[1] - rhs.mVector3D[1], mVector3D[2] - rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator-(const Vector3D<DATA_TYPE>& rhs) const
		{
			return Vector3D(mVector3D[0] - rhs.mVector3D[0], mVector3D[1] - rhs.mVector3D[1], mVector3D[2] - rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator*(const Vector3D<DATA_TYPE>& rhs)
		{
			return Vector3D(mVector3D[0] * rhs.mVector3D[0], mVector3D[1] * rhs.mVector3D[1], mVector3D[2] * rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::operator*(const Vector3D<DATA_TYPE>& rhs) const
		{
			return Vector3D(mVector3D[0] * rhs.mVector3D[0], mVector3D[1] * rhs.mVector3D[1], mVector3D[2] * rhs.mVector3D[2]);
		}
		template<typename DATA_TYPE>
		bool Vector3D<DATA_TYPE>::operator==(const Vector3D<DATA_TYPE>& rhs)
		{
			return ((mVector3D[0] == rhs.mVector3D[0]) && (mVector3D[1] == rhs.mVector3D[1]) && (mVector3D[2] == rhs.mVector3D[2]) );
		}
		template<typename DATA_TYPE>
		DATA_TYPE Vector3D<DATA_TYPE>::dotProduct(const Vector3D<DATA_TYPE>& rhs)
		{
			return ((mVector3D[0]*rhs.mVector3D[0]) + (mVector3D[1]*rhs.mVector3D[1]) + (mVector3D[2]*rhs.mVector3D[2]));
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::crossProduct(const Vector3D<DATA_TYPE>& rhs)
		{
			return Vector3D(mVector3D[1]*rhs.mVector3D[2] - mVector3D[2]*rhs.mVector3D[1],mVector3D[2]*rhs.mVector3D[0] - mVector3D[0]*rhs.mVector3D[2], mVector3D[0]*rhs.mVector3D[1] - mVector3D[1]*rhs.mVector3D[0]);
		}
		template<typename DATA_TYPE>
		Vector3D<DATA_TYPE> Vector3D<DATA_TYPE>::normalize()
		{
			DATA_TYPE invMagnitude = 1/sqrt((mVector3D[0] * mVector3D[0]) + (mVector3D[1] * mVector3D[1]) + (mVector3D[2] * mVector3D[2]));
			return Vector3D(mVector3D[0]*invMagnitude , mVector3D[1]*invMagnitude , mVector3D[2]*invMagnitude);
		}
	}
}
#endif // VECTOR3D_H
