#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include "Colour.h"
#include "ResourceManager.h"

class DrawObject
{
private:
	DirectX::SpriteBatch* _sprite_batch = nullptr;
	ResourceManager* _resource_manager = nullptr;
	MattMath::Colour _colour = colour_consts::WHITE;
	float _draw_rotation = 0.0f;
	MattMath::Vector2F _origin = MattMath::Vector2F::ZERO;
	DirectX::SpriteEffects _effects = DirectX::SpriteEffects_None;
	float _layer_depth = 0.0f;
protected:
	virtual DirectX::SpriteBatch* get_sprite_batch() const;
	virtual ResourceManager* get_resource_manager() const;
	virtual const MattMath::Colour& get_colour() const;
	virtual float get_draw_rotation() const;
	virtual const MattMath::Vector2F& get_origin() const;
	virtual DirectX::SpriteEffects get_effects() const;
	virtual float get_layer_depth() const;

	virtual void set_colour(const MattMath::Colour& colour);
	virtual void set_draw_rotation(float rotation);
	virtual void set_origin(const MattMath::Vector2F& origin);
	virtual void set_effects(DirectX::SpriteEffects effects);
	virtual void set_layer_depth(float layer_depth);
public:
	DrawObject() = default;
	DrawObject(DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		const MattMath::Colour& color = colour_consts::WHITE,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f) :
		_sprite_batch(sprite_batch),
		_resource_manager(resource_manager),
		_colour(color),
		_draw_rotation(rotation),
		_origin(origin),
		_effects(effects),
		_layer_depth(layer_depth) {}

};
#endif // !DRAWOBJECT_H
