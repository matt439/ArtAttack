#ifndef RECTANGLEANIMATION_H
#define RECTANGLEANIMATION_H

#include "AnimationObject.h"
#include "AnimatedSprite.h"
#include "RectangleObject.h"

class RectangleAnimation : public AnimationObject, public RectangleObject
{
public:
	RectangleAnimation() = default;
	RectangleAnimation(const float* dt,
		const std::string& sheet_name,
		const std::string& animation_strip_name,
		const MattMath::RectangleF& rectangle,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		const MattMath::Colour& color = colour_consts::WHITE,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f) :
	AnimationObject(dt, sheet_name, animation_strip_name, sprite_batch,
		resource_manager, color, 0.0f, origin, effects, layer_depth) {}

	virtual void draw();
};
#endif // !RECTANGLEANIMATION_H
