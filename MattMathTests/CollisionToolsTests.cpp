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
			RectangleF rect1 = RectangleF(0.0f, 0.0f, 10.0f, 10.0f);
			RectangleF rect2 = RectangleF(5.0f, 5.0f, 10.0f, 10.0f);
			
			collision_direction direction =
				CollisionTools::calculate_object_collision_direction(&rect1, &rect2);

			Assert::AreEqual(static_cast<int>(collision_direction::BOTTOM_RIGHT),
				static_cast<int>(direction));

			Vector2F amount = Vector2F(0.0f, 0.0f);
			bool resolved = CollisionTools::resolve_object_collision(&rect1, &rect2, direction, amount);

			Assert::IsTrue(resolved);
			Assert::AreEqual(-5.0f, amount.x, EPSILON_F);
			Assert::AreEqual(-5.0f, amount.y, EPSILON_F);
		}

		TEST_METHOD(test_rectagle_triangle_collision)
		{
			RectangleF rect = RectangleF(220.0f, 5878.0f, 52.0f, 120.0f);
			Triangle tri = Triangle(Vector2F(200.0f, 6000.0f), Vector2F(400.0f, 6000.0f), Vector2F(400.0f, 5800.0f));

			collision_direction direction =
				CollisionTools::calculate_object_collision_direction(&rect, &tri);

			Assert::AreEqual(static_cast<int>(collision_direction::BOTTOM_RIGHT), 
				static_cast<int>(direction));

			Vector2F amount = Vector2F(0.0f, 0.0f);
			bool resolved = CollisionTools::resolve_object_collision(&rect, &tri, direction, amount);

			Assert::IsTrue(resolved);
			Assert::AreEqual(-1.0f, amount.x, EPSILON_F);
			Assert::AreEqual(-1.0f, amount.y, EPSILON_F);
		}
	};
}