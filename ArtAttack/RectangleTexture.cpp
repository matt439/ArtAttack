#include "pch.h"
#include "RectangleTexture.h"

using namespace DirectX;
using namespace MattMath;

void RectangleTexture::draw()
{
	TextureObject::draw(RectangleObject::get_rectangle());
}