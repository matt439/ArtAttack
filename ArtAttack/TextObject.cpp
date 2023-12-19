#include "pch.h"
#include "TextObject.h"

using namespace DirectX;
using namespace MattMath;

TextObject::TextObject(const std::string& text,
	const std::string& font_name,
	const Vector2F& position,
	 SpriteBatch* sprite_batch,
	ResourceManager* resource_manager,
	const Colour& color,
	float scale,
	float rotation,
	const Vector2F& origin,
	SpriteEffects effects,
	float layer_depth) :
	DrawObject(sprite_batch, resource_manager, color,
		rotation, origin, effects, layer_depth),
	_text(text),
	_font_name(font_name),
	_position(position),
	_scale(scale)
{

}

void TextObject::draw(const Camera& camera) const
{
	SpriteFont* sprite_font =
		this->get_resource_manager()->get_sprite_font(this->_font_name);

	Vector2F view_pos = camera.calculate_view_position(this->_position);
	float view_scale = camera.calculate_view_scale(this->_scale);

	sprite_font->DrawString(
		this->get_sprite_batch(),
		this->_text.c_str(),
		view_pos.get_xm_vector(),
		this->get_colour().get_xm_vector(),
		this->get_draw_rotation(),
		this->get_origin().get_xm_vector(),
		view_scale,
		this->get_effects(),
		this->get_layer_depth());
}

void TextObject::draw() const
{
	SpriteFont* sprite_font =
		this->get_resource_manager()->get_sprite_font(this->_font_name);

	sprite_font->DrawString(
		this->get_sprite_batch(),
		this->_text.c_str(),
		this->_position.get_xm_vector(),
		this->get_colour().get_xm_vector(),
		this->get_draw_rotation(),
		this->get_origin().get_xm_vector(),
		this->_scale,
		this->get_effects(),
		this->get_layer_depth());
}

const std::string& TextObject::get_text() const
{
	return this->_text;
}
const std::string& TextObject::get_font_name() const
{
	return this->_font_name;

}
const Vector2F& TextObject::get_position() const
{
	return this->_position;
}
float TextObject::get_scale() const
{
	return this->_scale;
}
void TextObject::set_text(const std::string& text)
{
	this->_text = text;
}
void TextObject::set_font_name(const std::string& font_name)
{
	this->_font_name = font_name;
}
void TextObject::set_position(const Vector2F& position)
{
	this->_position = position;
}
void TextObject::set_scale(float scale)
{
	this->_scale = scale;
}