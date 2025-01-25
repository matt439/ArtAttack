#include "pch.h"
#include "CppUnitTest.h"
//#include "..\packages\directxtk_desktop_2019.2023.10.31.1\include\SimpleMath.h"
//#include "..\ArtAttack\MattMath.h"
#include "..\ArtAttack\MattMath.cpp"
#include "..\ArtAttack\EricsonMath.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MattMath;
using namespace EricsonMath;

namespace EricsonMathTests
{
	constexpr float EPSILON_F = 0.000001f;

	TEST_CLASS(EricsonMathTests)
	{
	public:
		TEST_METHOD(test_closest_pt_point_AABB)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);
			Point2F p, closest;

			// p is inside a
			p = Point2F(5.0f, 5.0f);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == p);

			// p is outside a
			p = Point2F(15.0f, 15.0f);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == Point2F(10.0f, 10.0f));

			// p is outside a
			p = Point2F(-5.0f, -5.0f);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == Point2F(0.0f, 0.0f));

			// p is outside a
			p = Point2F(5.0f, 15.0f);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == Point2F(5.0f, 10.0f));

			// p is just inside a
			p = Point2F(10.0f - FLT_EPSILON, 10.0f - FLT_EPSILON);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == p);

			// p is just outside a
			p = Point2F(10.0f + FLT_EPSILON, 10.0f + FLT_EPSILON);
			closest_pt_point_AABB(p, a, closest);
			Assert::IsTrue(closest == Point2F(10.0f, 10.0f));
		}
		TEST_METHOD(test_signed_2D_tri_area)
		{
			Point2F a(0.0f, 0.0f);
			Point2F b(10.0f, 0.0f);
			Point2F c(0.0f, 10.0f);

			// a, b, c are in counter-clockwise order
			Assert::IsTrue(signed_2D_tri_area(a, b, c) == 100.0f);

			// a, b, c are in clockwise order
			Assert::IsTrue(signed_2D_tri_area(a, c, b) == -100.0f);

			// a, b, c are collinear
			Assert::IsTrue(signed_2D_tri_area(a, b, Point2F(20.0f, 0.0f)) == 0.0f);
		}
		TEST_METHOD(test_test_2D_segment_segment)
		{
			float t;
			Point2F p;
			Segment s1(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f));

			// s1 and s2 intersect
			Segment s2(Point2F(5.0f, -5.0f), Point2F(5.0f, 5.0f));
			Assert::IsTrue(test_2D_segment_segment(s1.point_0, s1.point_1,
				s2.point_0, s2.point_1, t, p));
			Assert::IsTrue(p == Point2F(5.0f, 0.0f));
			Assert::IsTrue(t == 0.5f);

			// s1 and s2 not intersecting
			s2 = Segment(Point2F(15.0f, -5.0f), Point2F(15.0f, 5.0f));
			Assert::IsFalse(test_2D_segment_segment(s1.point_0, s1.point_1,
				s2.point_0, s2.point_1, t, p));
		}
		TEST_METHOD(test_test_segment_AABB)
		{
			// tested below with rectangle_segment_intersect
		}
		TEST_METHOD(test_closest_pt_point_triangle)
		{
			Triangle t(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f), Point2F(0.0f, 10.0f));
			Point2F t0 = t.get_point_0();
			Point2F t1 = t.get_point_1();
			Point2F t2 = t.get_point_2();
			Point2F closest;

			Point2F p = Point2F(5.0f, 5.0f);
			Assert::IsTrue(closest_pt_point_triangle(p, t0, t1, t2) == p);

			p = Point2F(15.0f, 15.0f);
			closest = closest_pt_point_triangle(p, t0, t1, t2);
			Assert::IsTrue(closest == Point2F(5.0f, 5.0f));

			p = Point2F(-5.0f, -5.0f);
			closest = closest_pt_point_triangle(p, t0, t1, t2);
			Assert::IsTrue(closest == Point2F(0.0f, 0.0f));

			p = Point2F(5.0f, -5.0f);
			closest = closest_pt_point_triangle(p, t0, t1, t2);
			Assert::IsTrue(closest == Point2F(5.0f, 0.0f));
		}
		TEST_METHOD(test_closest_pt_point_segment)
		{
			Segment s(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f));
			Point2F s0 = s.point_0;
			Point2F s1 = s.point_1;
			Point2F closest;
			float t;

			Point2F p = Point2F(5.0f, 5.0f);
			closest_pt_point_segment(p, s0, s1, t, closest);
			Assert::IsTrue(closest == Point2F(5.0f, 0.0f));
			Assert::IsTrue(t == 0.5f);

			p = Point2F(15.0f, 5.0f);
			closest_pt_point_segment(p, s0, s1, t, closest);
			Assert::IsTrue(closest == Point2F(10.0f, 0.0f));
			Assert::IsTrue(t == 1.0f);

			p = Point2F(-5.0f, 5.0f);
			closest_pt_point_segment(p, s0, s1, t, closest);
			Assert::IsTrue(closest == Point2F(0.0f, 0.0f));
			Assert::IsTrue(t == 0.0f);

			p = Point2F(5.0f, -5.0f);
			closest_pt_point_segment(p, s0, s1, t, closest);
			Assert::IsTrue(closest == Point2F(5.0f, 0.0f));
			Assert::IsTrue(t == 0.5f);
		}
	};
} // namespace EricsonMathTests

namespace MattMathTests
{
	constexpr float EPSILON_F = 0.000001f;
	
	TEST_CLASS(MattMathTests)
	{
	public:
		TEST_METHOD(test_rectangles_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);

			RectangleF b(5.0f, 5.0f, 10.0f, 10.0f);
			Assert::IsTrue(rectangles_intersect(a, b));

			// a and b are just touching
			b = RectangleF(10.0f - EPSILON_F, 10.0f, 10.0f, 10.0f);
			Assert::IsTrue(rectangles_intersect(a, b));

			// a and b are just not touching
			b = RectangleF(10.0f + EPSILON_F, 10.0f, 10.0f, 10.0f);
			Assert::IsFalse(rectangles_intersect(a, b));

			// b is inside a
			b = RectangleF(2.0f, 2.0f, 2.0f, 2.0f);
			Assert::IsTrue(rectangles_intersect(a, b));

			// a is inside b
			b = RectangleF(-2.0f, -2.0f, 20.0f, 20.0f);
			Assert::IsTrue(rectangles_intersect(a, b));

			// 2 identical rectangles
			Assert::IsTrue(rectangles_intersect(a, a));
		}
		TEST_METHOD(test_rectangle_circle_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);
			Point2F p;

			Circle c(5.0f, 5.0f, 5.0f);
			Assert::IsTrue(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(5.0f, 5.0f));

			c = Circle(15.0f, 15.0f, 5.0f);
			Assert::IsFalse(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(10.0f, 10.0f));

			// c is inside a
			c = Circle(2.0f, 2.0f, 2.0f);
			Assert::IsTrue(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(2.0f, 2.0f));

			// a is inside c
			c = Circle(5.0f, 5.0f, 10.0f);
			Assert::IsTrue(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(5.0f, 5.0f));

			// a and c are just touching
			c = Circle(15.0f - EPSILON_F, 5.0f, 5.0f);
			Assert::IsTrue(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(10.0f, 5.0f));

			// a and c are just not touching
			c = Circle(15.0f + EPSILON_F, 5.0f, 5.0f);
			Assert::IsFalse(rectangle_circle_intersect(a, c, p));
			Assert::IsTrue(p == Point2F(10.0f, 5.0f));
		}
		TEST_METHOD(test_rectangle_triangle_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);

			Triangle t(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f), Point2F(5.0f, 15.0f));
			Assert::IsTrue(rectangle_triangle_intersect(a, t));

			t = Triangle(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f), Point2F(1500.0f, 1500.0f));
			Assert::IsFalse(rectangle_triangle_intersect(a, t));

			// t is inside a
			t = Triangle(Point2F(2.0f, 2.0f), Point2F(2.0f, 8.0f), Point2F(8.0f, 2.0f));
			Assert::IsTrue(rectangle_triangle_intersect(a, t));

			// a is inside t
			t = Triangle(Point2F(-2.0f, -2.0f), Point2F(12.0f, -2.0f), Point2F(-2.0f, 12.0f));
			Assert::IsTrue(rectangle_triangle_intersect(a, t));

			// a and t are just touching
			t = Triangle(Point2F(10.0f - FLT_EPSILON, 10.0f), Point2F(20.0f, 10.0f),
				Point2F(10.0f - FLT_EPSILON, 20.0f));
			Assert::IsTrue(rectangle_triangle_intersect(a, t));

			// a and t are just not touching
			t = Triangle(Point2F(10.0f + FLT_EPSILON, 10.0f), Point2F(20.0f, 10.0f),
				Point2F(10.0f + FLT_EPSILON, 20.0f));
		}
		TEST_METHOD(test_rectangle_quad_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);

			Quad q(RectangleF(5.0f, 5.0f, 10.0f, 10.0f));
			Assert::IsTrue(rectangle_quad_intersect(a, q));

			q = Quad(RectangleF(500.0f, 500.0f, 10.0f, 10.0f));
			Assert::IsFalse(rectangle_quad_intersect(a, q));

			// q is inside a
			q = Quad(RectangleF(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(rectangle_quad_intersect(a, q));

			// a is inside q
			q = Quad(RectangleF(-2.0f, -2.0f, 20.0f, 20.0f));
			Assert::IsTrue(rectangle_quad_intersect(a, q));

			// a and q are just touching
			q = Quad(RectangleF(10.0f - EPSILON_F, 10.0f, 10.0f, 10.0f));
			Assert::IsTrue(rectangle_quad_intersect(a, q));

			// a and q are just not touching
			q = Quad(RectangleF(10.0f + EPSILON_F, 10.0f, 10.0f, 10.0f));
			Assert::IsFalse(rectangle_quad_intersect(a, q));

			// 2 identical rectangles
			q = Quad(a);
			Assert::IsTrue(rectangle_quad_intersect(a, q));
		}
		TEST_METHOD(test_rectangle_segment_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);

			Segment s(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f));
			Assert::IsTrue(rectangle_segment_intersect(a, s));

			s = Segment(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f));
			Assert::IsFalse(rectangle_segment_intersect(a, s));

			// s is inside a
			s = Segment(Point2F(2.0f, 2.0f), Point2F(8.0f, 8.0f));
			Assert::IsTrue(rectangle_segment_intersect(a, s));

			// a is inside s
			s = Segment(Point2F(-2.0f, -2.0f), Point2F(12.0f, 12.0f));
			Assert::IsTrue(rectangle_segment_intersect(a, s));

			// a and s are just touching
			s = Segment(Point2F(10.0f - EPSILON_F, 10.0f), Point2F(20.0f, 10.0f));
			Assert::IsTrue(rectangle_segment_intersect(a, s));

			// a and s are just not touching
			s = Segment(Point2F(10.0f + EPSILON_F * 2, 10.0f), Point2F(20.0f, 10.0f));
			Assert::IsFalse(rectangle_segment_intersect(a, s));
		}
		TEST_METHOD(test_rectangle_point_intersect)
		{
			RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);

			Point2F p(5.0f, 5.0f);
			Assert::IsTrue(rectangle_point_intersect(a, p));

			p = Point2F(15.0f, 15.0f);
			Assert::IsFalse(rectangle_point_intersect(a, p));

			// p is on the edge of a
			p = Point2F(10.0f, 10.0f);
			Assert::IsTrue(rectangle_point_intersect(a, p));

			// p is on the corner of a
			p = Point2F(0.0f, 0.0f);
			Assert::IsTrue(rectangle_point_intersect(a, p));
		}
		TEST_METHOD(test_circles_intersect)
		{
			Circle a(0.0f, 0.0f, 10.0f);

			Circle b(5.0f, 5.0f, 5.0f);
			Assert::IsTrue(circles_intersect(a, b));

			// a and b are just touching
			b = Circle(10.0f - EPSILON_F, 5.0f, 5.0f);
			Assert::IsTrue(circles_intersect(a, b));

			// a and b are just not touching
			b = Circle(15.0f + EPSILON_F, 0.0f, 5.0f);
			Assert::IsFalse(circles_intersect(a, b));

			// b is inside a
			b = Circle(2.0f, 2.0f, 2.0f);
			Assert::IsTrue(circles_intersect(a, b));

			// a is inside b
			b = Circle(0.0f, 0.0f, 20.0f);
			Assert::IsTrue(circles_intersect(a, b));

			// 2 identical circles
			Assert::IsTrue(circles_intersect(a, a));
		}
		TEST_METHOD(test_circle_triangle_intersect)
		{
			Circle a(0.0f, 0.0f, 10.0f);
			Point2F p;

			Triangle t(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f), Point2F(5.0f, 15.0f));
			Assert::IsTrue(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(p == Point2F(5.0f, 5.0f));

			t = Triangle(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f), Point2F(1500.0f, 1500.0f));
			Assert::IsFalse(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(p == Point2F(500.0f, 500.0f));

			// t is inside a
			t = Triangle(Point2F(2.0f, 2.0f), Point2F(2.0f, 8.0f), Point2F(8.0f, 2.0f));
			Assert::IsTrue(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(p == Point2F(2.0f, 2.0f));

			// a is inside t
			t = Triangle(Point2F(-2.0f, -2.0f), Point2F(12.0f, -2.0f), Point2F(-2.0f, 12.0f));
			Assert::IsTrue(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(p == Point2F(0.0f, 0.0f));

			// a and t are just touching
			t = Triangle(Point2F(10.0f - EPSILON_F, 0.0f), Point2F(20.0f, 0.0f),
				Point2F(10.0f - EPSILON_F, 20.0f));
			Assert::IsTrue(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(are_equal(p, Point2F(10.0f - EPSILON_F, 0.0f), 0.1f));

			// a and t are just not touching
			t = Triangle(Point2F(10.0f + EPSILON_F, 10.0f), Point2F(20.0f, 10.0f),
				Point2F(10.0f + EPSILON_F, 20.0f));
			Assert::IsFalse(circle_triangle_intersect(a, t, p));
			Assert::IsTrue(p == Point2F(10.0f + EPSILON_F, 10.0f));
		}
		TEST_METHOD(test_circle_quad_intersect)
		{
			Circle a(0.0f, 0.0f, 10.0f);

			Quad q(RectangleF(5.0f, 5.0f, 10.0f, 10.0f));
			Assert::IsTrue(circle_quad_intersect(a, q));

			q = Quad(RectangleF(500.0f, 500.0f, 10.0f, 10.0f));
			Assert::IsFalse(circle_quad_intersect(a, q));

			// q is inside a
			q = Quad(RectangleF(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(circle_quad_intersect(a, q));

			// a is inside q
			q = Quad(RectangleF(-2.0f, -2.0f, 20.0f, 20.0f));
			Assert::IsTrue(circle_quad_intersect(a, q));

			// a and q are just touching
			q = Quad(RectangleF(10.0f - EPSILON_F, 0.0f, 10.0f, 10.0f));
			Assert::IsTrue(circle_quad_intersect(a, q));

			// a and q are just not touching
			q = Quad(RectangleF(10.0f + EPSILON_F, 10.0f, 10.0f, 10.0f));
			Assert::IsFalse(circle_quad_intersect(a, q));
		}
		TEST_METHOD(test_circle_segment_intersect)
		{
			Circle c(0.0f, 0.0f, 10.0f);
			Point2F p;

			Segment s(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f));
			Assert::IsTrue(circle_segment_intersect(c, s, p));
			Assert::IsTrue(p == Point2F(5.0f, 5.0f));

			s = Segment(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f));
			Assert::IsFalse(circle_segment_intersect(c, s, p));
			Assert::IsTrue(p == Point2F(500.0f, 500.0f));

			// s is inside c
			s = Segment(Point2F(2.0f, 2.0f), Point2F(8.0f, 8.0f));
			Assert::IsTrue(circle_segment_intersect(c, s, p));
			Assert::IsTrue(p == Point2F(2.0f, 2.0f));

			// c is inside s
			s = Segment(Point2F(-2.0f, -2.0f), Point2F(12.0f, 12.0f));
			Assert::IsTrue(circle_segment_intersect(c, s, p));
			Assert::IsTrue(p == Point2F(0.0f, 0.0f));

			// c and s are just touching
			s = Segment(Point2F(10.0f - EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsTrue(circle_segment_intersect(c, s, p));
			Assert::IsTrue(are_equal(p, Point2F(10.0f - EPSILON_F, 0.0f), 0.1f));

			// c and s are just not touching
			s = Segment(Point2F(10.0f + EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsFalse(circle_segment_intersect(c, s, p));
			Assert::IsTrue(p == Point2F(10.0f + EPSILON_F, 0.0f));
		}
		TEST_METHOD(test_triangles_intersect)
		{
			Triangle a(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f), Point2F(0.0f, 10.0f));

			Triangle b(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f), Point2F(5.0f, 15.0f));
			Assert::IsTrue(triangles_intersect(a, b));

			b = Triangle(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f), Point2F(1500.0f, 1500.0f));
			Assert::IsFalse(triangles_intersect(a, b));

			// b is inside a
			b = Triangle(Point2F(2.0f, 2.0f), Point2F(2.0f, 8.0f), Point2F(8.0f, 2.0f));
			Assert::IsTrue(triangles_intersect(a, b));

			// a is inside b
			b = Triangle(Point2F(-2.0f, -2.0f), Point2F(12.0f, -2.0f), Point2F(-2.0f, 12.0f));
			Assert::IsTrue(triangles_intersect(a, b));

			// a and b are just touching
			b = Triangle(Point2F(10.0f - EPSILON_F, 0.0f), Point2F(20.0f, 0.0f),
				Point2F(10.0f - EPSILON_F, 10.0f));
			Assert::IsTrue(triangles_intersect(a, b));

			// a and b are just not touching
			b = Triangle(Point2F(10.0f + EPSILON_F, 00.0f), Point2F(20.0f, 00.0f),
				Point2F(10.0f + EPSILON_F, 10.0f));
			Assert::IsFalse(triangles_intersect(a, b));
		}
		TEST_METHOD(test_triangle_quad_intersect)
		{
			Triangle a(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f), Point2F(0.0f, 10.0f));

			Quad q(RectangleF(5.0f, 5.0f, 10.0f, 10.0f));
			Assert::IsTrue(triangle_quad_intersect(a, q));

			q = Quad(RectangleF(500.0f, 500.0f, 10.0f, 10.0f));
			Assert::IsFalse(triangle_quad_intersect(a, q));

			// q is inside a
			q = Quad(RectangleF(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(triangle_quad_intersect(a, q));

			// a is inside q
			q = Quad(RectangleF(-2.0f, -2.0f, 20.0f, 20.0f));
			Assert::IsTrue(triangle_quad_intersect(a, q));

			// a and q are just touching
			q = Quad(RectangleF(10.0f - EPSILON_F, 0.0f, 10.0f, 10.0f));
			Assert::IsTrue(triangle_quad_intersect(a, q));

			// a and q are just not touching
			q = Quad(RectangleF(10.0f + EPSILON_F, 0.0f, 10.0f, 10.0f));
			Assert::IsFalse(triangle_quad_intersect(a, q));
		}
		TEST_METHOD(test_triangle_segment_intersect)
		{
			Triangle a(Point2F(0.0f, 0.0f), Point2F(10.0f, 0.0f), Point2F(0.0f, 10.0f));

			Segment s(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f));
			Assert::IsTrue(triangle_segment_intersect(a, s));

			s = Segment(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f));
			Assert::IsFalse(triangle_segment_intersect(a, s));

			// s is inside a
			s = Segment(Point2F(2.0f, 2.0f), Point2F(8.0f, 8.0f));
			Assert::IsTrue(triangle_segment_intersect(a, s));

			// a is inside s
			s = Segment(Point2F(-2.0f, -2.0f), Point2F(12.0f, 12.0f));
			Assert::IsTrue(triangle_segment_intersect(a, s));

			// a and s are just touching
			s = Segment(Point2F(10.0f - EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsTrue(triangle_segment_intersect(a, s));

			// a and s are just not touching
			s = Segment(Point2F(10.0f + EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsFalse(triangle_segment_intersect(a, s));
		}
		TEST_METHOD(test_quads_intersect)
		{
			Quad a(RectangleF(0.0f, 0.0f, 10.0f, 10.0f));

			Quad b(RectangleF(5.0f, 5.0f, 10.0f, 10.0f));
			Assert::IsTrue(quads_intersect(a, b));

			b = Quad(RectangleF(500.0f, 500.0f, 10.0f, 10.0f));
			Assert::IsFalse(quads_intersect(a, b));

			// b is inside a
			b = Quad(RectangleF(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(quads_intersect(a, b));

			// a is inside b
			b = Quad(RectangleF(-2.0f, -2.0f, 20.0f, 20.0f));
			Assert::IsTrue(quads_intersect(a, b));

			// a and b are just touching
			b = Quad(RectangleF(10.0f - EPSILON_F, 0.0f, 10.0f, 10.0f));
			Assert::IsTrue(quads_intersect(a, b));

			// a and b are just not touching
			b = Quad(RectangleF(10.0f + EPSILON_F * 2, 0.0f, 10.0f, 10.0f));
			Assert::IsFalse(quads_intersect(a, b));

			// 2 identical quads
			Assert::IsTrue(quads_intersect(a, a));
		}
		TEST_METHOD(test_quad_segment_intersect)
		{
			Quad a(RectangleF(0.0f, 0.0f, 10.0f, 10.0f));

			Segment s(Point2F(5.0f, 5.0f), Point2F(15.0f, 5.0f));
			Assert::IsTrue(quad_segment_intersect(a, s));

			s = Segment(Point2F(500.0f, 500.0f), Point2F(1500.0f, 500.0f));
			Assert::IsFalse(quad_segment_intersect(a, s));

			// s is inside a
			s = Segment(Point2F(2.0f, 2.0f), Point2F(8.0f, 8.0f));
			Assert::IsTrue(quad_segment_intersect(a, s));

			// a is inside s
			s = Segment(Point2F(-5.0f, 5.0f), Point2F(15.0f, 5.0f));
			Assert::IsTrue(quad_segment_intersect(a, s));

			// a and s are just touching
			s = Segment(Point2F(10.0f - EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsTrue(quad_segment_intersect(a, s));

			// a and s are just not touching
			s = Segment(Point2F(10.0f + EPSILON_F, 0.0f), Point2F(20.0f, 0.0f));
			Assert::IsFalse(quad_segment_intersect(a, s));
		}
		TEST_METHOD(test_quad_point_intersect)
		{
			Quad a(RectangleF(0.0f, 0.0f, 10.0f, 10.0f));

			Point2F p(5.0f, 5.0f);
			Assert::IsTrue(quad_point_intersect(a, p));

			p = Point2F(15.0f, 15.0f);
			Assert::IsFalse(quad_point_intersect(a, p));

			// p is on the edge of a
			p = Point2F(10.0f, 10.0f);
			Assert::IsTrue(quad_point_intersect(a, p));

			// p is on the corner of a
			p = Point2F(0.0f, 0.0f);
			Assert::IsTrue(quad_point_intersect(a, p));
		}
	};

} // namespace MattMathTests