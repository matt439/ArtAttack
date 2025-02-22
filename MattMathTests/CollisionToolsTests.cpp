#include "pch.h"
#include "CppUnitTest.h"
#include "..\ArtAttack\CollisionTools.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MattMath;

namespace CollisionToolsTests
{
	constexpr float EPSILON_F = 0.000001f;

	TEST_CLASS(CollisionToolsTests)
	{
	public:
		TEST_METHOD(test_rectangle_rectangle_collision)
		{
			// 1st test. Collision to the bottom right
			RectangleF rect1 = RectangleF(0.0f, 0.0f, 10.0f, 10.0f);
			RectangleF rect2 = RectangleF(5.0f, 5.0f, 10.0f, 10.0f);
			
			Vector2F direction =
				CollisionTools::calculate_object_collision_direction(&rect1, &rect2);

			Vector2F direction_expected = Vector2F::unit_vector(
				rect2.get_center() - rect1.get_center());

			Assert::AreEqual(direction.x, direction_expected.x, EPSILON_F);
			Assert::AreEqual(direction.y, direction_expected.y, EPSILON_F);

			Vector2F amount = Vector2F(0.0f, 0.0f);
			bool resolved = CollisionTools::resolve_object_collision(&rect1, &rect2, direction, amount);

			Assert::IsTrue(resolved);
			Assert::AreEqual(amount.x, -5.0f, EPSILON_F);
			Assert::AreEqual(amount.y, -5.0f, EPSILON_F);

			// 2nd test. Collision to the left

			RectangleF rect3 = RectangleF(0.0f, 0.0f, 10.0f, 10.0f);
			RectangleF rect4 = RectangleF(-5.0f, 0.0f, 10.0f, 10.0f);

			direction = CollisionTools::calculate_object_collision_direction(&rect3, &rect4);

			direction_expected = Vector2F::unit_vector(
				rect4.get_center() - rect3.get_center());

			Assert::AreEqual(direction.x, direction_expected.x, EPSILON_F);
			Assert::AreEqual(direction.y, direction_expected.y, EPSILON_F);

			amount = Vector2F(0.0f, 0.0f);
			resolved = CollisionTools::resolve_object_collision(&rect3, &rect4, direction, amount);

			Assert::IsTrue(resolved);
			Assert::AreEqual(amount.x, 5.0f, EPSILON_F);
			Assert::AreEqual(amount.y, 0.0f, EPSILON_F);
		}

		TEST_METHOD(test_rectagle_triangle_collision)
		{
			RectangleF rect1 = RectangleF(0.0f, 0.0f, 10.0f, 10.0f);
			Triangle tri1 = Triangle(Vector2F(5.0f, 5.0f),
				Vector2F(15.0f, 5.0f),
				Vector2F(5.0f, 15.0f));

			Vector2F direction = CollisionTools::calculate_object_collision_direction(&rect1, &tri1);

			Vector2F direction_expected = Vector2F::unit_vector(
				tri1.get_center() - rect1.get_center());

			Assert::AreEqual(direction.x, direction_expected.x, EPSILON_F);
			Assert::AreEqual(direction.y, direction_expected.y, EPSILON_F);

			Vector2F amount = Vector2F(0.0f, 0.0f);
			bool resolved = CollisionTools::resolve_object_collision(&rect1, &tri1, direction, amount);

			Assert::IsTrue(resolved);
			Assert::AreEqual(amount.x, -5.0f, EPSILON_F);
			Assert::AreEqual(amount.y, -5.0f, EPSILON_F);
			
			
			
			//RectangleF rect = RectangleF(220.0f, 5878.0f, 52.0f, 120.0f);
			//Triangle tri = Triangle(Vector2F(200.0f, 6000.0f),
			//						Vector2F(400.0f, 6000.0f),
			//						Vector2F(400.0f, 5800.0f));

			//Vector2F direction =
			//	CollisionTools::calculate_object_collision_direction(&rect, &tri);

			//Assert::AreEqual(direction.x, Vector2F::DIRECTION_DOWN_RIGHT.x, EPSILON_F);
			//Assert::AreEqual(direction.y, Vector2F::DIRECTION_DOWN_RIGHT.y, EPSILON_F);

			//Vector2F amount = Vector2F(0.0f, 0.0f);
			//bool resolved = CollisionTools::resolve_object_collision(&rect, &tri, direction, amount);

			//Assert::IsTrue(resolved);
			//Assert::AreEqual(-1.0f, amount.x, EPSILON_F);
			//Assert::AreEqual(-1.0f, amount.y, EPSILON_F);
		}
	};
}