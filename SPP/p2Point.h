// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include <math.h>

template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point& p) : x(p.x), y(p.y)
	{}

	p2Point(TYPE x, TYPE y) : x(x), y(y)
	{}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Point<TYPE> r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point<TYPE> r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (TYPE) sqrtf(float((fx*fx) + (fy*fy)));
	}
};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;

template<class TYPE>
class p2Vector : public p2Point<TYPE>
{
public:

	p2Vector() : p2Point()
	{}

	p2Vector(const p2Point& p) : p2Point(p)
	{}

	p2Vector(TYPE x, TYPE y) : p2Point(x,y)
	{}

	void Normalize()
	{
		float m = x * x + y * y;
		if(m > 0.0f)
		{
			float inv_m = 1 / sqrtf(m);
			x *= inv_m;
			y *= inv_m;
		}
	}

	float Length() const
	{
		return sqrtf(float((x*x) + (y*y)));
	}

	p2Vector operator -(const TYPE v) const
	{
		p2Vector<TYPE> r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Vector& operator*=(float a)
	{
		x *= a;
		y *= a;
		return(*this);
	}

	p2Vector& operator*(float a)
	{
		p2Vector<TYPE> r;

		r.x = x * a;
		r.y = y * a;

		return r;
	}

	p2Vector& operator/=(float a)
	{
		float f = 1.0f / a;
		x *= f;
		y *= f;
		return(*this);
	}

	TYPE dot(const p2Vector<TYPE>& v) const
	{
		return(x * v.x + y * v.y);
	}
};

typedef p2Vector<int> iVector;
typedef p2Vector<float> fVector;

#endif // __P2POINT_H__