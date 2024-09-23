#ifndef TEXTDROPSHADOW_H
#define TEXTDROPSHADOW_H

#include "Text.h"

class TextDropShadow final : public Text
{
public:
	TextDropShadow() = default;
	TextDropShadow(const std::string& text,
				const std::string& font_name,
				const MattMath::Vector2F& position,
				ResourceManager* resource_manager,
				const MattMath::Colour& color = colour_consts::WHITE,
				const MattMath::Colour& shadow_color = colour_consts::BLACK,
				const MattMath::Vector2F& shadow_offset = { 2.0f, 2.0f },
				float scale = 1.0f,
				float shadow_scale = 1.0f,
				float rotation = 0.0f,
				const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
				DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
				float layer_depth = 0.0f);

	void draw(DirectX::SpriteBatch* sprite_batch, const MattMath::Camera& camera);
	void draw(DirectX::SpriteBatch* sprite_batch);

	MattMath::Vector2F get_shadow_offset() const;
	MattMath::Colour get_shadow_color() const;
	float get_shadow_scale() const;

	void set_shadow_offset(const MattMath::Vector2F& offset);
	void set_shadow_color(const MattMath::Colour& color);
	void set_shadow_scale(float scale);

private:
	MattMath::Vector2F _shadow_offset = { 2.0f, 2.0f };
	MattMath::Colour _shadow_color = colour_consts::BLACK;
	float _shadow_scale = 1.0f;
};
#endif // !TEXTDROPSHADOW_H
