#ifndef PROJECTILEJET_H
#define PROJECTILEJET_H

#include "Projectile.h"

class ProjectileJet final : public Projectile
{
public:
	ProjectileJet() = default;
	ProjectileJet(const MattMath::RectangleF& rectangle,
		const MattMath::Vector2F& velocity,
		player_team team,
		int player_num,
		const MattMath::Colour& team_colour,
		const float* dt,
		ResourceManager* resource_manager,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f);

	void update() override;
	void draw(DirectX::SpriteBatch* sprite_batch, const MattMath::Camera& camera) override;
	void draw(DirectX::SpriteBatch* sprite_batch) override;
	bool is_visible_in_viewport(const MattMath::RectangleF& view) const override;

	bool is_colliding(const ICollisionGameObject* other) const override;
	const MattMath::Shape* get_shape() const override;

private:
	MattMath::RectangleF _rectangle = MattMath::RectangleF::ZERO;
	MattMath::RectangleF get_draw_rectangle() const;
};
#endif // !PROJECTILEJET_H
