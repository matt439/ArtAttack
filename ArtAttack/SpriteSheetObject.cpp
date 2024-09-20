#include "pch.h"
#include "SpriteSheetObject.h"

using namespace DirectX;
using namespace MattMath;

SpriteSheetObject::SpriteSheetObject(const std::string& sheet_name,
	const std::string& element_name,
	//SpriteBatch* sprite_batch,
	ResourceManager* resource_manager,
	const Colour& color,
	float rotation,
	const Vector2F& origin,
	SpriteEffects effects,
	float layer_depth) :
	DrawObject(resource_manager, color, rotation, origin,
		effects, layer_depth),
	_sheet_name(sheet_name),
	_element_name(element_name)
{
}

const std::string& SpriteSheetObject::get_sprite_sheet_name() const
{
	return this->_sheet_name;
}
const std::string& SpriteSheetObject::get_element_name() const
{
	return this->_element_name;
}
SpriteSheet* SpriteSheetObject::get_sprite_sheet() const
{
	return this->get_resource_manager()->get_sprite_sheet(
		this->get_sprite_sheet_name());
}
void SpriteSheetObject::set_sprite_sheet_name(const std::string& sheet_name)
{
	this->_sheet_name = sheet_name;
}
void SpriteSheetObject::set_element_name(const std::string& frame_name)
{
	this->_element_name = frame_name;
}