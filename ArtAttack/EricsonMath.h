#ifndef ERICSONMATH_H
#define ERICSONMATH_H

// Real-Time Collision Detection
// Christer Ericson
// 2005

#include "MattMath.h"

namespace EricsonMath
{
	constexpr float EPSILON = 0.000001f;

	bool test_AABB_AABB(const MattMath::RectangleF& a,
		const MattMath::RectangleF& b);

	bool test_circle_circle(const MattMath::Circle& a,
		const MattMath::Circle& b);

	MattMath::Point2F closest_pt_point_triangle(
		const MattMath::Point2F& p,
		const MattMath::Point2F& a, const MattMath::Point2F& b,
		const MattMath::Point2F& c);

	float clamp(float n, float min, float max);

	bool test_circle_AABB(const MattMath::Circle& s,
		const MattMath::RectangleF& b);

	bool test_circle_AABB(const MattMath::Circle& s,
		const MattMath::RectangleF& b, MattMath::Point2F& p);

	float sq_dist_point_AABB(const MattMath::Point2F& p,
		const MattMath::RectangleF& b);

	void closest_pt_point_AABB(const MattMath::Point2F& p,
		const MattMath::RectangleF& b, MattMath::Point2F& q);

	bool test_circle_triangle(const MattMath::Circle& s,
		const MattMath::Point2F& a, const MattMath::Point2F& b,
		const MattMath::Point2F& c, MattMath::Point2F& p);

	bool intersect_moving_AABB_AABB(const MattMath::AABB& a,
		const MattMath::AABB& b,
		const MattMath::Vector2F& va,
		const MattMath::Vector2F& vb,
		float& tfirst, float& tlast);

	bool test_segment_AABB(const MattMath::Point2F& p0,
		const MattMath::Point2F p1, const MattMath::AABB& b);

	float signed_2D_tri_area(const MattMath::Point2F& a,
		const MattMath::Point2F& b, const MattMath::Point2F& c);

	bool test_2D_segment_segment(const MattMath::Point2F& a,
		const MattMath::Point2F& b, const MattMath::Point2F& c,
		const MattMath::Point2F& d, float& t, MattMath::Point2F& p);

	void barycentric(const MattMath::Point2F& a,
		const MattMath::Point2F& b, const MattMath::Point2F& c,
		const MattMath::Point2F& p, float& u, float& v, float& w);

	bool test_point_triangle(const MattMath::Point2F& p,
		const MattMath::Point2F& a, const MattMath::Point2F& b,
		const MattMath::Point2F& c);

}
#endif // !ERICSONMATH_H
