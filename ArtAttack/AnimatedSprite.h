#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SpriteSheet.h"

class AnimatedSprite
{
public:
	AnimatedSprite(SpriteSheet* sprite_sheet,
		const std::string& animation_strip_name,
		const float* dt);

	void draw(DirectX::SpriteBatch* sprite_batch,
		const MattMath::RectangleI& destination_rectangle,
		const MattMath::Colour& color = colour_consts::WHITE,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f) const;

	void draw(DirectX::SpriteBatch* sprite_batch,
		const MattMath::Vector2F& position,
		const MattMath::Colour& color = colour_consts::WHITE,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		float scale = 1.0f,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f) const;
	void update();
	void reset();
	void stop();
	void play();
	void pause();

	bool is_paused() const;

	void set_animation_strip(SpriteSheet* sprite_sheet,
		const std::string& animation_strip_name);
	void set_frame_index(int frame_index);

private:
	const float* _dt = nullptr;
	SpriteSheet* _sprite_sheet = nullptr;
	const AnimationStrip* _animation_strip = nullptr;
	int _frame_index = 0;
	bool _paused = false;
	float _time_elapsed = 0.0f;
};
#endif // !ANIMATEDSPRITE_H
