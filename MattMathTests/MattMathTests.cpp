#include "pch.h"
#include "CppUnitTest.h"
#include "..\packages\directxtk_desktop_2019.2023.10.31.1\include\SimpleMath.h"
#include "..\ArtAttack\MattMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MattMath;

TEST_CLASS(MattMathTests)
{
public:
		
	TEST_METHOD(TestRectanglesIntersect)
	{
		RectangleF a(0.0f, 0.0f, 10.0f, 10.0f);
		RectangleF b(5.0f, 5.0f, 10.0f, 10.0f);
		Assert::IsTrue(rectangles_intersect(a, b));
	}
};
