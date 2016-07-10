#ifndef VECTOR3_HPP
#define VECTOR3_HPP

template <typename T>
class Vector3 {
public:
	Vector3<T>() : x(0), y(0), z(0) { };
	Vector3<T>(T a, T b, T c) : x(a), y(b), z(c) { };
	//~Vector3<T>();

	// Member variables:
	T x;
	T y;
	T z;

	// Assignement operators:
	Vector3<T>& operator =(const Vector3& rhs);
	Vector3<T>& operator +=(const Vector3& rhs);
	Vector3<T>& operator -=(const Vector3& rhs);

	// With scalar operators:
	template <typename S>
	Vector3<T>& operator +=(const S& scalar);
	template <typename S>
	Vector3<T>& operator -=(const S& scalar);
	template <typename S>
	Vector3<T>& operator *=(const S& scalar);
	template <typename S>
	Vector3<T>& operator /=(const S& scalar);
};

// Arithmetic operators:
template <typename T>
Vector3<T> operator +(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
Vector3<T> operator -(const Vector3<T>& lhs, const Vector3<T>& rhs);

// Inner and cross product:
template <typename T>
T operator *(const Vector3<T>& lhs, const Vector3<T>& rhs); // Inner product
template <typename T>
Vector3<T> operator %(const Vector3<T>& lhs, const Vector3<T>& rhs); // Cross product

// Equality operators:
template <typename T>
bool operator ==(const Vector3<T>& lhs, const Vector3<T>& rhs);
template <typename T>
bool operator !=(const Vector3<T>& lhs, const Vector3<T>& rhs);

// With scalar operators:
template <typename T, typename S>
Vector3<T> operator +(const Vector3<T>& lhs, const S& scalar);
template <typename T, typename S>
Vector3<T> operator +(const S& scalar, const Vector3<T>& rhs);
template <typename T, typename S>
Vector3<T> operator -(const Vector3<T>& lhs, const S& scalar);
template <typename T, typename S>
Vector3<T> operator -(const S& scalar, const Vector3<T>& rhs);
template <typename T, typename S>
Vector3<T> operator *(const Vector3<T>& lhs, const S& scalar);
template <typename T, typename S>
Vector3<T> operator *(const S& scalar, const Vector3<T>& rhs);
template <typename T, typename S>
Vector3<T> operator /(const Vector3<T>& lhs, const S& scalar);

template <typename T>
Vector3<T> operator -(const Vector3<T>& rhs);
// It makes no sense to divide a scalar by a vector so we dont have that operation.

// Definitions:
template<typename T>
Vector3<T>& Vector3<T>::operator =(const Vector3<T>& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator +=(const Vector3<T>& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator -=(const Vector3<T>& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

// Element-wise operators:
template <typename T>
template <typename S>
Vector3<T>& Vector3<T>::operator +=(const S& scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	return *this;
}

template <typename T>
template <typename S>
Vector3<T>& Vector3<T>::operator -=(const S& scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	return *this;
}

template <typename T>
template <typename S>
Vector3<T>& Vector3<T>::operator *=(const S& scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

template <typename T>
template <typename S>
Vector3<T>& Vector3<T>::operator /=(const S& scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

// Arithmetic operators:
template<typename T>
Vector3<T> operator +(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	Vector3<T> sum = lhs;
	sum += rhs;
	return sum;
}

template<typename T>
Vector3<T> operator -(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	Vector3<T> sum = lhs;
	sum -= rhs;
	return sum;
}

// Inner and cross product:
template <typename T>
T operator *(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

template <typename T>
Vector3<T> operator %(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	Vector3<T> crossProduct;
	crossProduct.x = lhs.y*rhs.z - lhs.z*rhs.y;
	crossProduct.y = lhs.z*rhs.x - lhs.x*rhs.z;
	crossProduct.z = lhs.x*rhs.y - lhs.y*rhs.x;
	return crossProduct;
}

// Equality operators:
template <typename T>
bool operator ==(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	return lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.z == rhs.z;
}

template <typename T>
bool operator !=(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
	return !(lhs == rhs);
}

// With scalar operators:
template <typename T, typename S>
Vector3<T> operator +(const Vector3<T>& lhs, const S& scalar)
{
	return Vector3<T>(lhs.x + scalar, lhs.y + scalar, lhs.z + scalar);
}

template <typename T, typename S>
Vector3<T> operator +(const S& scalar, const Vector3<T>& rhs)
{
	return operator +(rhs, scalar);
}

template <typename T, typename S>
Vector3<T> operator -(const Vector3<T>& lhs, const S& scalar)
{
	return Vector3<T>(lhs.x - scalar, lhs.y - scalar, lhs.z - scalar);
}

template <typename T, typename S>
Vector3<T> operator -(const S& scalar, const Vector3<T>& rhs)
{
	return Vector3<T>(scalar - rhs.x, scalar - rhs.y, scalar - rhs.z);
}

template<typename T, typename S>
Vector3<T> operator *(const Vector3<T>& lhs, const S& scalar)
{
	return Vector3<T>(lhs.x*scalar, lhs.y*scalar, lhs.z*scalar);
}

template <typename T, typename S>
Vector3<T> operator *(const S& scalar, const Vector3<T>& rhs)
{
	return operator *(rhs, scalar);
}

template <typename T, typename S>
Vector3<T> operator /(const Vector3<T>& lhs, const S& scalar)
{
	return Vector3<T>(lhs.x/scalar, lhs.y/scalar, lhs.z/scalar);
}

template <typename T>
Vector3<T> operator -(const Vector3<T>& rhs)
{
	return rhs*-1.0;
}

#endif /* VECTOR3_HPP */
