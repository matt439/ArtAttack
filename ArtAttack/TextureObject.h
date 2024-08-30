#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include "SpriteSheetObject.h"

class TextureObject : public SpriteSheetObject
{
protected:
	virtual void draw(const MattMath::RectangleI& destination_rectangle) const;
	virtual void draw(const MattMath::RectangleF& destination_rectangle) const;
	virtual void draw(const MattMath::Vector2F& position, float scale = 1.0f) const;

	virtual void draw(const MattMath::RectangleF& destination_rectangle,
		const MattMath::Camera& camera) const;
	virtual void draw(const MattMath::Vector2F& position,
		const MattMath::Camera& camera, float scale = 1.0f) const;
public:
	TextureObject() = default;
	TextureObject(const std::string& sheet_name,
				const std::string& frame_name,
				DirectX::SpriteBatch* sprite_batch,
				ResourceManager* resource_manager,
				const MattMath::Colour& color = colour_consts::WHITE,
				float rotation = 0.0f,
				const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
				DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
				float layer_depth = 0.0f) :
		SpriteSheetObject(sheet_name, frame_name, sprite_batch, resource_manager,
				color, rotation, origin, effects, layer_depth) {}

};
#endif // !TEXTUREOBJECT_H
