#include "pch.h"
#include "CppUnitTest.h"
//#include "..\packages\directxtk_desktop_2019.2023.10.31.1\include\SimpleMath.h"
//#include "..\ArtAttack\MattMath.h"
#include "..\ArtAttack\MattMath.cpp"
#include "..\ArtAttack\EricsonMath.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MattMath;
using namespace EricsonMath;

namespace MattMathTests
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
			Segment s2(Point2F(5.0f, -5.0f), Point2F(5.0f, 5.0f));

			// s1 and s2 intersect
			Assert::IsTrue(test_2D_segment_segment(s1.point_0, s1.point_1,
				s2.point_0, s2.point_1, t, p));
			Assert::IsTrue(p == Point2F(5.0f, 5.0f));
			Assert::IsTrue(t == 0.5f);

		}
		TEST_METHOD(test_test_segment_AABB)
		{

		}
	};

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
			s = Segment(Point2F(10.0f + EPSILON_F, 10.0f), Point2F(20.0f, 10.0f));
			Assert::IsFalse(rectangle_segment_intersect(a, s));
		}
	};

} // namespace MattMathTests