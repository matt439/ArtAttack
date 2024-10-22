#include "pch.h"
#include "Drawer.h"

using namespace DirectX;
using namespace MattMath;

RectangleI Drawer::calculate_draw_rectangle(const RectangleI& rec,
    const Vector3F& camera)
{
    return calculate_draw_rectangle(
		Vector2F(static_cast<float>(rec.x), static_cast<float>(rec.y)),
		Vector2F(static_cast<float>(rec.width), static_cast<float>(rec.height)),
		camera);
}

RectangleI Drawer::calculate_draw_rectangle(const Vector2F& position,
    const Vector2F& size, const Vector3F& camera)
{
    Vector2F draw_pos = (position - Vector2F(camera.x, camera.y)) * camera.z;
    Vector2F draw_size = Vector2F(size) * camera.z;
    return {
	    static_cast<int>(draw_pos.x),
        static_cast<int>(draw_pos.y),
        static_cast<int>(draw_size.x),
        static_cast<int>(draw_size.y)
    };
}

Vector2F Drawer::calculate_sprite_origin(
    const Vector2F& size, rotation_origin origin)
{
    switch (origin)
    {
    case rotation_origin::CENTER:
        return Vector2F(size) / 2.0f;
    case rotation_origin::LEFT_CENTER:
        return {0.0f, size.y / 2.0f};
    case rotation_origin::TOP_LEFT:
        return Vector2F::ZERO;
    default:
		return Vector2F::ZERO;
    }
}