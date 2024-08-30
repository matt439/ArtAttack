#include "pch.h"
#include "RectangleObject.h"

using namespace MattMath;

const RectangleF* RectangleObject::get_rectangle_ptr() const
{
	return this->_rectangle.get();
}
const RectangleF& RectangleObject::get_rectangle() const
{
	return *this->_rectangle;
}
void RectangleObject::set_rectangle(const RectangleF& rectangle)
{
	this->_rectangle = std::make_unique<RectangleF>(rectangle);
}
void RectangleObject::inflate(float horizontal_amount, float vertical_amount)
{
	this->_rectangle->inflate(horizontal_amount, vertical_amount);
}
void RectangleObject::inflate(const Vector2F& amount)
{
	this->_rectangle->inflate(amount);
}
void RectangleObject::scale_at_center(float scale)
{
	this->_rectangle->scale_at_center(scale);
}
void RectangleObject::scale_at_center(float horizontal_scale,
	float vertical_scale)
{
	this->_rectangle->scale_at_center(horizontal_scale, vertical_scale);
}
void RectangleObject::scale_at_center(const Vector2F& scale)
{
	this->_rectangle->scale_at_center(scale);
}
void RectangleObject::offset(float horizontal_amount, float vertical_amount)
{
	this->_rectangle->offset(horizontal_amount, vertical_amount);
}
void RectangleObject::offset(const Vector2F& amount)
{
	this->_rectangle->offset(amount);
}
void RectangleObject::scale(float horizontal_amount, float vertical_amount)
{
	this->_rectangle->scale(horizontal_amount, vertical_amount);
}
void RectangleObject::scale(const Vector2F& amount)
{
	this->_rectangle->scale(amount);
}
void RectangleObject::set_position(const Vector2F& position)
{
	this->_rectangle->set_position(position);
}
void RectangleObject::set_size(const Vector2F& size)
{
	this->_rectangle->set_size(size);
}
