#ifndef RECTANGLETEXTURE_H
#define RECTANGLETEXTURE_H

#include "TextureObject.h"
#include "RectangleObject.h"

class RectangleTexture : public TextureObject, public RectangleObject
{
public:
	RectangleTexture() = default;
	RectangleTexture(const std::string& sheet_name,
				const std::string& frame_name,
				const MattMath::RectangleF& rectangle,
				DirectX::SpriteBatch* sprite_batch,
				ResourceManager* resource_manager,
				const MattMath::Colour& color = colour_consts::WHITE,
				const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
				DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
				float layer_depth = 0.0f) :
		TextureObject(sheet_name, frame_name, sprite_batch, resource_manager,
						color, 0.0f, origin, effects, layer_depth),
		RectangleObject(rectangle) {}

	virtual void draw();
};

#endif // !RECTANGLETEXTURE_H
