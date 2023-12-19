#include "pch.h"
#include "EricsonMath.h"

using namespace MattMath;
using namespace EricsonMath;

////Vector::Vector(float x, float y) :
////	x(x), y(y)
////{
////}
////Vector::Vector(float f) :
////	x(f), y(f)
////{
////}
//
//AABB::AABB(Point min, Point max) :
//	min(min), max(max)
//{
//}
//AABB::AABB(float min_x, float min_y, float max_x, float max_y) :
//	min(min_x, min_y), max(max_x, max_y)
//{
//}
//
////float AABB::mina(int index) const
////{
////	if (index == 0)
////	{
////		return this->min.x;
////	}
////	else if (index == 1)
////	{
////		return this->min.y;
////	}
////	else
////	{
////		throw std::exception("Index out of range");
////	}
////
////}
////float AABB::maxa(int index) const
////{
////	if (index == 0)
////	{
////		return this->max.x;
////	}
////	else if (index == 1)
////	{
////		return this->max.y;
////	}
////	else
////	{
////		throw std::exception("Index out of range");
////	}
////}
//
//Vector Vector::operator+(const Vector& rhs) const
//{
//	return Vector(x + rhs.x, y + rhs.y);
//}
//Vector Vector::operator-(const Vector & rhs) const
//{
//	return Vector(x - rhs.x, y - rhs.y);
//}
//Vector Vector::operator*(float rhs) const
//{
//	return Vector(x * rhs, y * rhs);
//}
//Vector Vector::operator/(float rhs) const
//{
//	return Vector(x / rhs, y / rhs);
//}
//Vector& Vector::operator+=(const Vector& rhs)
//{
//	x += rhs.x;
//	y += rhs.y;
//	return *this;
//}
//Vector& Vector::operator-=(const Vector& rhs)
//{
//	x -= rhs.x;
//	y -= rhs.y;
//	return *this;
//}
//Vector& Vector::operator*=(float rhs)
//{
//	x *= rhs;
//	y *= rhs;
//	return *this;
//}
//Vector& Vector::operator/=(float rhs)
//{
//	x /= rhs;
//	y /= rhs;
//	return *this;
//}
//Vector& Vector::operator*=(const Vector& rhs)
//{
//	x *= rhs.x;
//	y *= rhs.y;
//	return *this;
//}
//Vector& Vector::operator/=(const Vector& rhs)
//{
//	x /= rhs.x;
//	y /= rhs.y;
//	return *this;
//}
//Vector Vector::operator=(float rhs[2])
//{
//	return Vector(rhs[0], rhs[1]);
//}
//Vector EricsonMath::operator*(float lhs, const Vector& rhs)
//{
//	return Vector(lhs * rhs.x, lhs * rhs.y);
//}
//
//
//Sphere::Sphere(Point c, float r) :
//	c(c), r(r)
//{
//}
//Sphere::Sphere(float center_x, float center_y, float radius) :
//	c(center_x, center_y), r(radius)
//{
//}


//// Returns true if sphere s intersects AABB b, false otherwise
//int EricsonMath::TestAABBAABB(AABB a, AABB b)
//{
//	// Exit with no intersection if separated along an axis
//	if (a.max.x < b.min.x || a.min.x > b.max.x) return 0;
//	if (a.max.y < b.min.y || a.min.y > b.max.y) return 0;
//	//if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return 0;
//	// Overlapping on all axes means AABBs are intersecting
//	return 1;
//}
//
//int EricsonMath::TestSphereSphere(Sphere a, Sphere b)
//{
//	// Calculate squared distance between centers
//	Vector d = a.c - b.c;
//	float dist2 = Dot(d, d);
//	// Spheres intersect if squared distance is less than squared sum of radii
//	float radiusSum = a.r + b.r;
//	return dist2 <= radiusSum * radiusSum;
//}
//
//Point EricsonMath::ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
//{
//	// Check if P in vertex region outside A
//	Vector ab = b - a;
//	Vector ac = c - a;
//	Vector ap = p - a;
//	float d1 = Dot(ab, ap);
//	float d2 = Dot(ac, ap);
//	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
//	// Check if P in vertex region outside B
//	Vector bp = p - b;
//	float d3 = Dot(ab, bp);
//	float d4 = Dot(ac, bp);
//	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
//	// Check if P in edge region of AB, if so return projection of P onto AB
//	float vc = d1 * d4 - d3 * d2;
//	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
//		float v = d1 / (d1 - d3);
//		return a + v * ab; // barycentric coordinates (1-v,v,0)
//	}
//	// Check if P in vertex region outside C
//	Vector cp = p - c;
//	float d5 = Dot(ab, cp);
//	float d6 = Dot(ac, cp);
//	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)
//
//	// Check if P in edge region of AC, if so return projection of P onto AC
//	float vb = d5 * d2 - d1 * d6;
//	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
//		float w = d2 / (d2 - d6);
//		return a + w * ac; // barycentric coordinates (1-w,0,w)
//	}
//	// Check if P in edge region of BC, if so return projection of P onto BC
//	float va = d3 * d6 - d5 * d4;
//	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
//		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
//		return b + w * (c - b); // barycentric coordinates (0,1-w,w)
//	}
//	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
//	float denom = 1.0f / (va + vb + vc);
//	float v = vb * denom;
//	float w = vc * denom;
//	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f - v - w
//}
//
//float EricsonMath::Clamp(float n, float min, float max)
//{
//	if (n < min) return min;
//	if (n > max) return max;
//	return n;
//}
//
//// Returns true if sphere s intersects AABB b, false otherwise
//int EricsonMath::TestSphereAABB(Sphere s, AABB b)
//{
//	// Compute squared distance between sphere center and AABB
//	float sqDist = SqDistPointAABB(s.c, b);
//	// Sphere and AABB intersect if the (squared) distance
//	// between them is less than the (squared) sphere radius
//	return sqDist <= s.r * s.r;
//}
//
//// Returns true if sphere s intersects AABB b, false otherwise.
//// The point p on the AABB closest to the sphere center is also returned
//int TestSphereAABB(Sphere s, AABB b, Point& p)
//{
//	// Find point p on AABB closest to sphere center
//	ClosestPtPointAABB(s.c, b, p);
//	// Sphere and AABB intersect if the (squared) distance from sphere
//	// center to point p is less than the (squared) sphere radius
//	Vector v = p - s.c;
//	return Dot(v, v) <= s.r * s.r;
//}
//
//// Computes the square distance between a point p and an AABB b
//float EricsonMath::SqDistPointAABB(Point p, AABB b)
//{
//	float sqDist = 0.0f;
//
//	// For each axis count any excess distance outside box extents
//	float v = p.x;
//	if (v < b.min.x)
//	{
//		sqDist += (b.min.x - v) * (b.min.x - v);
//	}
//	if (v > b.max.x)
//	{
//		sqDist += (v - b.max.x) * (v - b.max.x);
//	}
//
//	v = p.y;
//	if (v < b.min.y)
//	{
//		sqDist += (b.min.y - v) * (b.min.y - v);
//	}
//	if (v > b.max.y)
//	{
//		sqDist += (v - b.max.y) * (v - b.max.y);
//	}
//	return sqDist;
//}
//
//// Given point p, return the point q on or in AABB b that is closest to p
//void EricsonMath::ClosestPtPointAABB(Point p, AABB b, Point& q)
//{
//	// For each coordinate axis, if the point coordinate value is
//	// outside box, clamp it to the box, else keep it as is
//	for (int i = 0; i < 3; i++) {
//		float v = p[i];
//		if (v < b.min[i]) v = b.min[i]; // v = max(v, b.min[i])
//		if (v > b.max[i]) v = b.max[i]; // v = min(v, b.max[i])
//		q[i] = v;
//	}
//}
//
//// Computes the square distance between a point p and an AABB b
//float EricsonMath::SqDistPointAABB(Point p, AABB b)
//{
//	float sqDist = 0.0f;
//	for (int i = 0; i < 3; i++) {
//		// For each axis count any excess distance outside box extents
//		float v = p[i];
//		if (v < b.min[i]) sqDist += (b.min[i] - v) * (b.min[i] - v);
//		if (v > b.max[i]) sqDist += (v - b.max[i]) * (v - b.max[i]);
//	}
//	return sqDist;
//}
//float EricsonMath::Dot(Vector a, Vector b)
//{
//	return a.x * b.x + a.y * b.y;
//}

// Returns true if sphere s intersects AABB b, false otherwise
bool EricsonMath::test_AABB_AABB(const RectangleF& a,
	const RectangleF& b)
{
	Vector2F a_min = a.get_top_left();
	Vector2F a_max = a.get_bottom_right();
	Vector2F b_min = b.get_top_left();
	Vector2F b_max = b.get_bottom_right();
	
	// Exit with no intersection if separated along an axis
	if (a_max.x < b_min.x || a_min.x > b_max.x) return 0;
	if (a_max.y < b_min.y || a_min.y > b_max.y) return 0;
	// Overlapping on all axes means AABBs are intersecting
	return 1;
}

bool EricsonMath::test_circle_circle(const Circle& a, const Circle& b)
{
	// Calculate squared distance between centers
	Vector2F d = a.center - b.center;
	float dist2 = Vector2F::dot(d, d);
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = a.radius + b.radius;
	return dist2 <= radiusSum * radiusSum;
}

Point2F EricsonMath::closest_pt_point_triangle(const Point2F& p,
	const Point2F& a, const Point2F& b, const Point2F& c)
{
	// Check if P in vertex region outside A
	Vector2F ab = b - a;
	Vector2F ac = c - a;
	Vector2F ap = p - a;
	float d1 = Vector2F::dot(ab, ap);
	float d2 = Vector2F::dot(ac, ap);
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)
	// Check if P in vertex region outside B
	Vector2F bp = p - b;
	float d3 = Vector2F::dot(ab, bp);
	float d4 = Vector2F::dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)
	// Check if P in edge region of AB, if so return projection of P onto AB
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
		float v = d1 / (d1 - d3);
		return a + v * ab; // barycentric coordinates (1-v,v,0)
	}
	// Check if P in vertex region outside C
	Vector2F cp = p - c;
	float d5 = Vector2F::dot(ab, cp);
	float d6 = Vector2F::dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)

	// Check if P in edge region of AC, if so return projection of P onto AC
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
		float w = d2 / (d2 - d6);
		return a + w * ac; // barycentric coordinates (1-w,0,w)
	}
	// Check if P in edge region of BC, if so return projection of P onto BC
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + w * (c - b); // barycentric coordinates (0,1-w,w)
	}
	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f - v - w
}

float EricsonMath::clamp(float n, float min, float max)
{
	if (n < min)
	{
		return min;
	}
	if (n > max)
	{
		return max;
	}
	return n;
}

// Returns true if sphere s intersects AABB b, false otherwise
bool EricsonMath::test_circle_AABB(const Circle& s, const RectangleF& b)
{
	// Compute squared distance between sphere center and AABB
	float sqDist = sq_dist_point_AABB(s.center, b);
	// Sphere and AABB intersect if the (squared) distance
	// between them is less than the (squared) sphere radius
	return sqDist <= s.radius * s.radius;
}

// Returns true if sphere s intersects AABB b, false otherwise.
// The point p on the AABB closest to the sphere center is also returned
bool EricsonMath::test_circle_AABB(const Circle& s,
	const RectangleF& b, Point2F& p)
{
	// Find point p on AABB closest to sphere center
	closest_pt_point_AABB(s.center, b, p);
	// Sphere and AABB intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	Vector2F v = p - s.center;
	return Vector2F::dot(v, v) <= s.radius * s.radius;
}

// Computes the square distance between a point p and an AABB b
float EricsonMath::sq_dist_point_AABB(const Point2F& p, const RectangleF& b)
{
	float sqDist = 0.0f;
	Vector2F b_min = b.get_top_left();
	Vector2F b_max = b.get_bottom_right();

	// For each axis count any excess distance outside box extents
	float v = p.x;
	if (v < b_min.x)
	{
		sqDist += (b_min.x - v) * (b_min.x - v);
	}
	if (v > b_max.x)
	{
		sqDist += (v - b_max.x) * (v - b_max.x);
	}

	v = p.y;
	if (v < b_min.y)
	{
		sqDist += (b_min.y - v) * (b_min.y - v);
	}
	if (v > b_max.y)
	{
		sqDist += (v - b_max.y) * (v - b_max.y);
	}
	return sqDist;
}

// Given point p, return the point q on or in AABB b that is closest to p
void EricsonMath::closest_pt_point_AABB(const Point2F& p,
	const RectangleF& b, Point2F& q)
{
	// For each coordinate axis, if the point coordinate value is
	// outside box, clamp it to the box, else keep it as is
	Vector2F b_min = b.get_top_left();
	Vector2F b_max = b.get_bottom_right();
	float v = p.x;
	if (v < b_min.x)
	{
		v = b_min.x;
	}
	if (v > b_max.x)
	{
		v = b_max.x;
	}
	q.x = v;

	v = p.y;
	if (v < b_min.y)
	{
		v = b_min.y;
	}
	if (v > b_max.y)
	{
		v = b_max.y;
	}
	q.y = v;
}

//// Computes the square distance between a point p and an AABB b
//float EricsonMath::sq_dist_point_AABB(const Point2F& p, const RectangleF& b)
//{
//	float sqDist = 0.0f;
//
//	Vector2F b_min = b.get_top_left();
//	Vector2F b_max = b.get_bottom_right();
//	float v = p.x;
//	if (v < b_min.x)
//	{
//		sqDist += (b_min.x - v) * (b_min.x - v);
//	}
//	if (v > b_max.x)
//	{
//		sqDist += (v - b_max.x) * (v - b_max.x);
//	}
//
//	v = p.y;
//	if (v < b_min.y)
//	{
//		sqDist += (b_min.y - v) * (b_min.y - v);
//	}
//	if (v > b_max.y)
//	{
//		sqDist += (v - b_max.y) * (v - b_max.y);
//	}
//
//	return sqDist;
//}

// Returns true if sphere s intersects triangle ABC, false otherwise.
// The point p on abc closest to the sphere center is also returned
bool EricsonMath::test_circle_triangle(const Circle& s, const Point2F& a,
	const Point2F& b, const Point2F& c, Point2F& p)
{
	// Find point P on triangle ABC closest to sphere center
	p = closest_pt_point_triangle(s.center, a, b, c);
	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to point p is less than the (squared) sphere radius
	Vector2F v = p - s.center;
	return Vector2F::dot(v, v) <= s.radius * s.radius;
}

//bool EricsonMath::test_triangle_AABB(const Point2F& v0,
//	const Point2F& v1, const Point2F& v2, const RectangleF& b)
//{
//	float p0, p1, p2, r;
//	// Compute box center and extents (if not already given in that format)
//	Vector2F c = (b.min + b.max) * 0.5f;
//	float e0 = (b.max.x - b.min.x) * 0.5f;
//	float e1 = (b.max.y - b.min.y) * 0.5f;
//	float e2 = (b.max.z - b.min.z) * 0.5f;
//	// Translate triangle as conceptually moving AABB to origin
//	v0 = v0 - c;
//	v1 = v1 - c;
//	v2 = v2 - c;
//	// Compute edge vectors for triangle
//	Vector2F f0 = v1 - v0, f1 = v2 - v1, f2 = v0 - v2;
//	// Test axes a00..a22 (category 3)
//	// Test axis a00
//	p0 = v0.z * v1.y - v0.y * v1.z;
//	p2 = v2.z * (v1.y - v0.y) - v2.z * (v1.z - v0.z);
//	r = e1 * Abs(f0.z) + e2 * Abs(f0.y);
//	if (Max(-Max(p0, p2), Min(p0, p2)) > r) return 0; // Axis is a separating axis
//	// Repeat similar tests for remaining axes a01..a22
//	...
//		// Test the three axes corresponding to the face normals of AABB b (category 1).
//		// Exit if...
//		// ... [-e0, e0] and [min(v0.x,v1.x,v2.x), max(v0.x,v1.x,v2.x)] do not overlap
//		if (Max(v0.x, v1.x, v2.x) < -e0 || Min(v0.x, v1.x, v2.x) > e0) return 0;
//	// ... [-e1, e1] and [min(v0.y,v1.y,v2.y), max(v0.y,v1.y,v2.y)] do not overlap
//	if (Max(v0.y, v1.y, v2.y) < -e1 || Min(v0.y, v1.y, v2.y) > e1) return 0;
//	// ... [-e2, e2] and [min(v0.z,v1.z,v2.z), max(v0.z,v1.z,v2.z)] do not overlap
//	if (Max(v0.z, v1.z, v2.z) < -e2 || Min(v0.z, v1.z, v2.z) > e2) return 0;
//	// Test separating axis corresponding to triangle face normal (category 2)
//	Plane p;
//	p.n = Cross(f0, f1);
//	p.d = Dot(p.n, v0);
//	return TestAABBPlane(b, p);
//}


// Intersect AABBs �a� and �b� moving with constant velocities va and vb.
// On intersection, return time of first and last contact in tfirst and tlast
bool EricsonMath::intersect_moving_AABB_AABB(const AABB& a, const AABB& b,
	const Vector2F& va, const Vector2F& vb,
	float& tfirst, float& tlast)
{
	// Exit early if �a� and �b� initially overlapping
	if (test_AABB_AABB(a, b)) {
		tfirst = tlast = 0.0f;
		return 1;
	}
	// Use relative velocity; effectively treating �a� as stationary
	Vector2F v = vb - va;
	// Initialize times of first and last contact
	tfirst = 0.0f;
	tlast = 1.0f;


	//// For each axis, determine times of first and last contact, if any
	//for (int i = 0; i < 3; i++) {
	//	if (v[i] < 0.0f) {
	//		if (b.max[i] < a.min[i]) return 0; // Nonintersecting and moving apart
	//		if (a.max[i] < b.min[i]) tfirst = Max((a.max[i] - b.min[i]) / v[i], tfirst);
	//		if (b.max[i] > a.min[i]) tlast = Min((a.min[i] - b.max[i]) / v[i], tlast);
	//	}
	//	if (v[i] > 0.0f) {
	//		if (b.min[i] > a.max[i]) return 0; // Nonintersecting and moving apart
	//		if (b.max[i] < a.min[i]) tfirst = Max((a.min[i] - b.max[i]) / v[i], tfirst);
	//		if (a.max[i] > b.min[i]) tlast = Min((a.max[i] - b.min[i]) / v[i], tlast);
	//	}
	//	// No overlap possible if time of first contact occurs after time of last contact
	//	if (tfirst > tlast) return 0;
	//}

	Vector2F a_min = a.get_top_left();
	Vector2F a_max = a.get_bottom_right();
	Vector2F b_min = b.get_top_left();
	Vector2F b_max = b.get_bottom_right();

	if (v.x < 0.0f) {
		if (b_max.x < a_min.x)
		{
			return 0; // Nonintersecting and moving apart
		}
		if (a_max.x < b_min.x)
		{
			tfirst = max((a_max.x - b_min.x) / v.x, tfirst);
		}
		if (b_max.x > a_min.x)
		{
			tlast = min((a_min.x - b_max.x) / v.x, tlast);
		}
	}
	if (v.x > 0.0f) {
		if (b_min.x > a_max.x)
		{
			return 0; // Nonintersecting and moving apart
		}
		if (b_max.x < a_min.x)
		{
			tfirst = max((a_min.x - b_max.x) / v.x, tfirst);
		}
		if (a_max.x > b_min.x)
		{
			tlast = min((a_max.x - b_min.x) / v.x, tlast);
		}
	}
	// No overlap possible if time of first contact occurs after time of last contact
	if (tfirst > tlast)
	{
		return 0;
	}

	if (v.y < 0.0f) {
		if (b_max.y < a_min.y)
		{
			return 0; // Nonintersecting and moving apart
		}
		if (a_max.y < b_min.y)
		{
			tfirst = max((a_max.y - b_min.y) / v.y, tfirst);
		}
		if (b_max.y > a_min.y)
		{
			tlast = min((a_min.y - b_max.y) / v.y, tlast);
		}
	}
	if (v.y > 0.0f) {
		if (b_min.y > a_max.y)
		{
			return 0; // Nonintersecting and moving apart
		}
		if (b_max.y < a_min.y)
		{
			tfirst = max((a_min.y - b_max.y) / v.y, tfirst);
		}
		if (a_max.y > b_min.y)
		{
			tlast = min((a_max.y - b_min.y) / v.y, tlast);
		}
	}
	// No overlap possible if time of first contact occurs after time of last contact
	if (tfirst > tlast)
	{
		return 0;
	}
	return 1;
}


// Test if segment specified by points p0 and p1 intersects AABB b
bool EricsonMath::test_segment_AABB(const Point2F& p0,
	const Point2F p1, const AABB& b)
{
	Vector2F b_min = b.get_top_left();
	Vector2F b_max = b.get_bottom_right();
	
	Point2F c = (b_min + b_max) * 0.5f; // Box center-point
	Vector2F e = b_max - c; // Box halflength extents
	Point2F m = (p0 + p1) * 0.5f; // Segment midpoint
	Vector2F d = p1 - m; // Segment halflength vector
	m = m - c; // Translate box and segment to origin
	// Try world coordinate axes as separating axes
	float adx = std::abs(d.x);
	if (std::abs(m.x) > e.x + adx) return 0;
	float ady = std::abs(d.y);
	if (std::abs(m.y) > e.y + ady) return 0;
	//float adz = std::abs(d.z);
	//if (std::abs(m.z) > e.z + adz) return 0;

	// Add in an epsilon term to counteract arithmetic errors when segment is
	// (near) parallel to a coordinate axis (see text for detail)
	adx += EPSILON;
	ady += EPSILON;
	//adz += EPSILON;

	// Try cross products of segment direction vector with coordinate axes
	//if (std::abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady)
	//{
	//	return 0;
	//}
	//if (std::abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx)
	//{
	//	return 0;
	//}
	if (std::abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx)
	{
		return 0;
	}
	// No separating axis found; segment must be overlapping AABB
	return 1;
}

// Returns 2 times the signed triangle area. The result is positive if
// abc is ccw, negative if abc is cw, zero if abc is degenerate.
float EricsonMath::signed_2D_tri_area(const Point2F& a,
	const Point2F& b, const Point2F& c)
{
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}


// Test if segments ab and cd overlap. If they do, compute and return
// intersection t value along ab and intersection position p
bool EricsonMath::test_2D_segment_segment(const Point2F& a,
	const Point2F& b, const Point2F& c,
	const Point2F& d, float& t, Point2F& p)
{
	// Sign of areas correspond to which side of ab points c and d are
	float a1 = signed_2D_tri_area(a, b, d); // Compute winding of abd (+ or -)
	float a2 = signed_2D_tri_area(a, b, c); // To intersect, must have sign opposite of a1
	// If c and d are on different sides of ab, areas have different signs
	if (a1 * a2 < 0.0f) {
		// Compute signs for a and b with respect to segment cd
		float a3 = signed_2D_tri_area(c, d, a); // Compute winding of cda (+ or -)
		// Since area is constant a1 - a2 = a3 - a4, or a4 = a3 + a2 - a1
		// float a4 = Signed2DTriArea(c, d, b); // Must have opposite sign of a3
		float a4 = a3 + a2 - a1;
		// Points a and b on different sides of cd if areas have different signs
		if (a3 * a4 < 0.0f) {
			// Segments intersect. Find intersection point along L(t) = a + t * (b - a).
			// Given height h1 of an over cd and height h2 of b over cd,
			// t = h1 / (h1 - h2) = (b*h1/2) / (b*h1/2 - b*h2/2) = a3 / (a3 - a4),
			// where b (the base of the triangles cda and cdb, i.e., the length
			// of cd) cancels out.
			t = a3 / (a3 - a4);
			p = a + t * (b - a);
			return 1;
		}
	}
	// Segments not intersecting (or collinear)
	return 0;
}

// Compute barycentric coordinates (u, v, w) for
// point p with respect to triangle (a, b, c)
void EricsonMath::barycentric(const Point2F& a,
	const Point2F& b, const Point2F& c,
	const Point2F& p, float& u, float& v, float& w)
{
	Vector2F v0 = b - a, v1 = c - a, v2 = p - a;
	float d00 = Vector2F::dot(v0, v0);
	float d01 = Vector2F::dot(v0, v1);
	float d11 = Vector2F::dot(v1, v1);
	float d20 = Vector2F::dot(v2, v0);
	float d21 = Vector2F::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}

// Test if point p is contained in triangle (a, b, c)
bool  EricsonMath::test_point_triangle(const Point2F& p,
	const Point2F& a, const Point2F& b, const Point2F& c)
{
	float u, v, w;
	barycentric(a, b, c, p, u, v, w);
	return v >= 0.0f && w >= 0.0f && (v + w) <= 1.0f;
}