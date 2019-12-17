/**
* Copyright (C) 2007-2010 SlimDX Group
*
* Permission is hereby granted, free  of charge, to any person obtaining a copy of this software  and
* associated  documentation  files (the  "Software"), to deal  in the Software  without  restriction,
* including  without  limitation  the  rights  to use,  copy,  modify,  merge,  publish,  distribute,
* sublicense, and/or sell  copies of the  Software,  and to permit  persons to whom  the Software  is
* furnished to do so, subject to the following conditions:
*
* The  above  copyright  notice  and this  permission  notice shall  be included  in  all  copies  or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF  ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
* NOT  LIMITED  TO  THE  WARRANTIES  OF  MERCHANTABILITY,  FITNESS  FOR  A   PARTICULAR  PURPOSE  AND
* NONINFRINGEMENT.  IN  NO  EVENT SHALL THE  AUTHORS  OR COPYRIGHT HOLDERS  BE LIABLE FOR  ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  OUT
* OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
* ALTERED SOURCE
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*/
#include "GTAmath.h"

#include <math.h>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


#pragma region Vector3
Vector3::Vector3(float X, float Y, float Z)
	: x(X), y(Y), z(Z)
{
}

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}

Vector3::Vector3(Vector3_t& xyz)
	: x(xyz.x), y(xyz.y), z(xyz.z)
{
}

void Vector3::clear()
{
	*this = Vector3();
}

Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::One()
{
	return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::WorldUp()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}
Vector3 Vector3::WorldDown()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}
Vector3 Vector3::WorldNorth()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}
Vector3 Vector3::WorldSouth()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}
Vector3 Vector3::WorldEast()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}
Vector3 Vector3::WorldWest()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::RelativeRight()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}
Vector3 Vector3::RelativeLeft()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}
Vector3 Vector3::RelativeFront()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}
Vector3 Vector3::RelativeBack()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}
Vector3 Vector3::RelativeTop()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}
Vector3 Vector3::RelativeBottom()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

float Vector3::Length() const
{
	return static_cast<float>(sqrt((x*x) + (y*y) + (z*z)));
}
float Vector3::LengthSquared() const
{
	return (x * x) + (y * y) + (z * z);
}

void Vector3::Normalize()
{
	float length = this->Length();
	if (length == 0.0f)
		return;
	float num = 1.0f / length;
	x *= num;
	y *= num;
	z *= num;
}

float Vector3::DistanceTo(const Vector3& position) const
{
	return (position - *this).Length();
}

Vector3 Vector3::Around(float distance) const
{
	return *this + Vector3::RandomXY() * distance;
}

Vector3 Vector3::PointOnCircle(float radius, float angleInDegrees) const
{
	Vector3 point;
	point.x = radius * cos(DegreeToRadian(angleInDegrees)) + this->x;
	point.y = radius * sin(DegreeToRadian(angleInDegrees)) + this->y;
	point.z = this->z;

	return point;
}

void Vector3::PointsOnCircle(std::vector<Vector3>& results, float fullRadius, float angleDifference, float intervalDistance, bool includeCentre) const
{
	//results.clear();

	auto& origin = *this;
	Vector3 current;
	float u, d;

	if (includeCentre)
		results.push_back(origin);
	if (intervalDistance == 0.0f)
		return;

	for (u = 0.0f; u < 360.0f; u += angleDifference)
	{
		for (d = intervalDistance; d < fullRadius; d += intervalDistance)
		{
			current.x = d * cos(DegreeToRadian(u)) + origin.x;
			current.y = d * sin(DegreeToRadian(u)) + origin.y;
			//current.z = origin.z; // this will stay uniform as we're only considering the circle
			results.push_back(current);
		}
	}

}

Vector3 Vector3::PointOnSphere(float radius, float longitude, float latitude) const
{
	float u = DegreeToRadian(longitude);
	float v = DegreeToRadian(latitude);
	Vector3 point;
	point.x = radius * sin(u) * cos(v) + this->x;
	point.y = radius * cos(u) * cos(v) + this->y;
	point.z = radius * sin(v) + this->z;

	return point;
}

Vector3_t Vector3::ToTypeStruct() const
{
	Vector3_t Return;
	Return.x = this->x;
	Return.y = this->y;
	Return.z = this->z;
	return Return;
}

void Vector3::ToArray(float* out) const
{
	out[0] = this->x;
	out[1] = this->y;
	out[2] = this->z;
}

std::array<float,3> Vector3::ToArray() const
{
	return{ { this->x, this->y, this->z } };
}

bool Vector3::IsZero() const
{
	return (this->x == 0 && this->y == 0 && this->z == 0);
}

Vector3 Vector3::RandomXY()
{
	Vector3 v;
	v.x = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.y = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.z = 0.0f;
	v.Normalize();
	return v;
}
Vector3 Vector3::RandomXYZ()
{
	Vector3 v;
	v.x = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.y = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.z = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.Normalize();
	return v;
}

Vector3 Vector3::Add(Vector3 left, Vector3 right)
{
	return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3 Vector3::Subtract(Vector3 left, Vector3 right)
{
	return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3 Vector3::Multiply(Vector3 value, float scale)
{
	return Vector3(value.x * scale, value.y * scale, value.z * scale);
}

Vector3 Vector3::Modulate(Vector3 left, Vector3 right)
{
	return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3 Vector3::Divide(Vector3 value, float scale)
{
	return Vector3(value.x / scale, value.y / scale, value.z / scale);
}

Vector3 Vector3::Negate(Vector3 value)
{
	return Vector3(-value.x, -value.y, -value.z);
}

Vector3 Vector3::Clamp(Vector3 value, Vector3 min, Vector3 max)
{
	float x = value.x;
	x = (x > max.x) ? max.x : x;
	x = (x < min.x) ? min.x : x;

	float y = value.y;
	y = (y > max.y) ? max.y : y;
	y = (y < min.y) ? min.y : y;

	float z = value.z;
	z = (z > max.z) ? max.z : z;
	z = (z < min.z) ? min.z : z;

	return Vector3(x, y, z);
}

Vector3 Vector3::Lerp(Vector3 start, Vector3 end, float amount)
{
	Vector3 vector;

	vector.x = start.x + ((end.x - start.x) * amount);
	vector.y = start.y + ((end.y - start.y) * amount);
	vector.z = start.z + ((end.z - start.z) * amount);

	return vector;
}

Vector3 Vector3::Normalize(Vector3 vector)
{
	vector.Normalize();
	return vector;
}

float Vector3::Dot(Vector3 left, Vector3 right)
{
	return (left.x * right.x + left.y * right.y + left.z * right.z);
}

Vector3 Vector3::Cross(Vector3 left, Vector3 right)
{
	Vector3 result;
	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;
	return result;
}

Vector3 Vector3::Reflect(Vector3 vector, Vector3 normal)
{
	Vector3 result;
	float dot = ((vector.x * normal.x) + (vector.y * normal.y)) + (vector.z * normal.z);

	result.x = vector.x - ((2.0f * dot) * normal.x);
	result.y = vector.y - ((2.0f * dot) * normal.y);
	result.z = vector.z - ((2.0f * dot) * normal.z);

	return result;
}

Vector3 Vector3::Minimize(Vector3 value1, Vector3 value2)
{
	Vector3 vector;
	vector.x = (value1.x < value2.x) ? value1.x : value2.x;
	vector.y = (value1.y < value2.y) ? value1.y : value2.y;
	vector.z = (value1.z < value2.z) ? value1.z : value2.z;
	return vector;
}

Vector3 Vector3::Maximize(Vector3 value1, Vector3 value2)
{
	Vector3 vector;
	vector.x = (value1.x > value2.x) ? value1.x : value2.x;
	vector.y = (value1.y > value2.y) ? value1.y : value2.y;
	vector.z = (value1.z > value2.z) ? value1.z : value2.z;
	return vector;
}

Vector3 operator + (Vector3 const& left, Vector3 const& right)
{
	return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3 operator - (Vector3 const& left, Vector3 const& right)
{
	return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3 operator - (Vector3 const& value)
{
	return Vector3(-value.x, -value.y, -value.z);
}

Vector3 operator * (Vector3 const& left, Vector3 const& right)
{
	return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3 operator * (Vector3 const& value, float const& scale)
{
	return Vector3(value.x * scale, value.y * scale, value.z * scale);
}

Vector3 operator * (float const& scale, Vector3 const& value)
{
	return Vector3(value.x * scale, value.y * scale, value.z * scale);
}

Vector3 operator *= (Vector3& value, float const& scale)
{
	value.x *= scale;
	value.y *= scale;
	value.z *= scale;
	return value;
}

Vector3 operator / (Vector3 const& left, Vector3 const& right)
{
	return Vector3(left.x / right.x, left.y / right.y, left.z / right.z);
}

Vector3 operator / (Vector3 const& value, float const& scale)
{
	return Vector3(value.x / scale, value.y / scale, value.z / scale);
}

Vector3 operator /= (Vector3& value, float const& scale)
{
	value.x /= scale;
	value.y /= scale;
	value.z /= scale;
	return value;
}

bool operator == (Vector3 const& left, Vector3 const& right)
{
	return Vector3::Equals(left, right);
}

bool operator != (Vector3 const& left, Vector3 const& right)
{
	return !Vector3::Equals(left, right);
}


std::string Vector3::ToString() const
{
	std::stringstream ss;
	ss << "X:" << std::setprecision(4) << std::fixed << this->x;
	ss << " Y:" << std::setprecision(4) << std::fixed << this->y;
	ss << " Z:" << std::setprecision(4) << std::fixed << this->z;
	return ss.str();
}

bool Vector3::Equals(const Vector3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::Equals(const Vector3_t& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::Equals(const Vector3& value1, const Vector3& value2)
{
	return (value1.x == value2.x && value1.y == value2.y && value1.z == value2.z);
}


float Vector3::DistanceBetween(const Vector3& value1, const Vector3& value2)
{
	return (value1 - value2).Length();
}

Vector3 Vector3::RotationToDirection(const Vector3& rotation)
{
	float retz = rotation.z * 0.0174532924F; // Degree to radian
	float retx = rotation.x * 0.0174532924F;
	float absx = abs(cos(retx));
	return Vector3(-sin(retz) * absx, cos(retz) * absx, sin(retx));
}
Vector3 Vector3::DirectionToRotation(Vector3 direction)
{
	direction.Normalize();
	float xx = atan2(direction.z, direction.y) / 0.0174532924F; // Radian to degree
	float yy = 0;
	float zz = -atan2(direction.x, direction.y) / 0.0174532924F;
	return Vector3(xx, yy, zz);
}

#pragma endregion

#pragma region Vector2
Vector2::Vector2(float X, float Y)
	: x(X), y(Y)
{
}

Vector2::Vector2()
	: x(0), y(0)
{
}

void Vector2::clear()
{
	*this = Vector2(0.0f, 0.0f);
}

Vector2 Vector2::Zero()
{
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::One()
{
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::Up()
{
	return Vector2(0.0f, 1.0);
}

Vector2 Vector2::Down()
{
	return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::Right()
{
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::Left()
{
	return Vector2(-1.0f, 0.0f);
}

float Vector2::Length() const
{
	return sqrt((x*x) + (y*y));
}

Vector2 Vector2::PointOnCircle(float radius, float angleInDegrees) const
{
	Vector2 point;
	point.x = radius * cos(DegreeToRadian(angleInDegrees)) + this->x;
	point.y = radius * sin(DegreeToRadian(angleInDegrees)) + this->y;

	return point;
}

void Vector2::PointsOnCircle(std::vector<Vector2>& results, float fullRadius, float angleInDegrees, float intervalDistance, bool includeCentre) const
{
	//results.clear();

	auto& origin = *this;
	Vector2 current;
	float u, d;

	if (includeCentre) results.push_back(origin);
	if (intervalDistance == 0.0f) return;

	for (u = 0.0f; u < 360.0f; u += angleInDegrees)
	{
		for (d = intervalDistance; d < fullRadius; d += intervalDistance)
		{
			current.x = d * cos(DegreeToRadian(u)) + origin.x;
			current.y = d * sin(DegreeToRadian(u)) + origin.y;
			results.push_back(current);
		}
	}
}

float Vector2::LengthSquared() const
{
	return (x * x) + (y * y);
}

void Vector2::Normalize()
{
	float length = Length();
	if (length == 0.0f)
		return;
	float num = 1.0f / length;
	x *= num;
	y *= num;
}

float Vector2::DistanceTo(const Vector2& position) const
{
	return (position - *this).Length();
}

std::array<float,2> Vector2::ToArray() const
{
	return{ {this->x, this->y} };
}

bool Vector2::IsZero() const
{
	return (this->x == 0 && this->y == 0);
}

Vector2 Vector2::RandomXY()
{
	Vector2 v;
	v.x = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.y = get_random_float_in_range(0.0f, 1.0f) - 0.5f;
	v.Normalize();
	return v;
}

Vector2 Vector2::Add(Vector2 const& left, Vector2 const& right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

Vector2 Vector2::Subtract(Vector2 const& left, Vector2 const& right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

Vector2 Vector2::Multiply(Vector2 const& value, float const& scale)
{
	return Vector2(value.x * scale, value.y * scale);
}

Vector2 Vector2::Modulate(Vector2 const& left, Vector2 const& right)
{
	return Vector2(left.x * right.x, left.y * right.y);
}

Vector2 Vector2::Divide(Vector2 const& value, float const& scale)
{
	return Vector2(value.x / scale, value.y / scale);
}

Vector2 Vector2::Negate(Vector2 const& value)
{
	return Vector2(-value.x, -value.y);
}

Vector2 Vector2::Clamp(Vector2 const& value, Vector2 const& min, Vector2 const& max)
{
	float ex = value.x;
	ex = (ex > max.x) ? max.x : ex;
	ex = (ex < min.x) ? min.x : ex;

	float why = value.y;
	why = (why > max.y) ? max.y : why;
	why = (why < min.y) ? min.y : why;

	return Vector2(ex, why);
}

Vector2 Vector2::Lerp(Vector2 const& start, Vector2 const& end, float const& amount)
{
	Vector2 vector;

	vector.x = start.x + ((end.x - start.x) * amount);
	vector.y = start.y + ((end.y - start.y) * amount);

	return vector;
}

Vector2 Vector2::Normalize(Vector2 value)
{
	value.Normalize();
	return value;
}

float Vector2::Dot(Vector2 const& left, Vector2 const& right)
{
	return (left.x * right.x + left.y * right.y);
}

Vector2 Vector2::Reflect(Vector2 const& vector, Vector2 const& normal)
{
	Vector2 result;
	float dot = ((vector.x * normal.x) + (vector.y * normal.y));

	result.x = vector.x - ((2.0f * dot) * normal.x);
	result.y = vector.y - ((2.0f * dot) * normal.y);

	return result;
}

Vector2 Vector2::Minimize(Vector2 const& value1, Vector2 const& value2)
{
	Vector2 vector;
	vector.x = (value1.x < value2.x) ? value1.x : value2.x;
	vector.y = (value1.y < value2.y) ? value1.y : value2.y;
	return vector;
}

Vector2 Vector2::Maximize(Vector2 value1, Vector2 value2)
{
	Vector2 vector;
	vector.x = (value1.x > value2.x) ? value1.x : value2.x;
	vector.y = (value1.y > value2.y) ? value1.y : value2.y;
	return vector;
}

Vector2 operator + (Vector2 const& left, Vector2 const& right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

Vector2 operator - (Vector2 const& left, Vector2 const& right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

Vector2 operator - (Vector2 const& value)
{
	return Vector2(-value.x, -value.y);
}

Vector2 operator * (Vector2 const& vec, float const& scale)
{
	return Vector2(vec.x * scale, vec.y * scale);
}

Vector2 operator * (float const& scale, Vector2 const& vec)
{
	return vec * scale;
}

Vector2 operator / (Vector2 const& vec, float const& scale)
{
	return Vector2(vec.x / scale, vec.y / scale);
}

bool operator == (Vector2 const& left, Vector2 const& right)
{
	return Vector2::Equals(left, right);
}

bool operator != (Vector2 const& left, Vector2 const& right)
{
	return !Vector2::Equals(left, right);
}


std::string Vector2::ToString() const
{
	//return "X:" + std::to_string(x) + " Y:" + std::to_string(y);
	std::stringstream ss;
	ss << "X:" << std::setprecision(4) << std::fixed << this->x;
	ss << " Y:" << std::setprecision(4) << std::fixed << this->y;
	return ss.str();
}


bool Vector2::Equals(const Vector2& other) const
{
	return (x == other.x && y == other.y);
}

bool Vector2::Equals(Vector2 value1, Vector2 value2)
{
	return (value1.x == value2.x && value1.y == value2.y);
}
#pragma endregion


int get_random_int_in_range(int min, int max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> u(min, max); // inclusive
	return u(rng);
}
float get_random_float_in_range(float min, float max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	//boost::uniform_real<float> u(min, max);
	std::uniform_real_distribution<float> u(min, max); // inclusive
	//boost::variate_generator< boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
	return u(rng);
	//return gen();
}

float DegreeToRadian(float angle)
{
	return angle * 0.0174532925199433F;
}
float RadianToDegree(float angle)
{
	return angle / 0.0174532925199433F;
}

Vector3 DegreeToRadian(const Vector3& angles)
{
	return Vector3(angles.x * 0.0174532925199433F, angles.y * 0.0174532925199433F, angles.z * 0.0174532925199433F);
}
float GetHeadingFromCoords(const Vector3& source, const Vector3& target)
{
	return atan2((target.y - source.y), (target.x - source.x));
}

