#ifndef PROJECTILEBALL_H
#define PROJECTILEBALL_H

#include "Projectile.h"

class ProjectileBall : public Projectile
{
public:
	ProjectileBall() = default;
	ProjectileBall(const MattMath::RectangleF& rectangle,
		const MattMath::Vector2F& velocity,
		player_team team,
		int player_num,
		const MattMath::Colour& team_colour,
		const float* dt,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f);

	virtual void update() override;
	virtual void draw(const MattMath::Camera& camera) override;
	virtual void draw() override;
	virtual bool is_visible_in_viewport(const MattMath::RectangleF& view) const override;

	virtual bool is_colliding(const ICollisionGameObject* other) const override;
	virtual const MattMath::Shape* get_shape() const override;
private:
	MattMath::RectangleF _rectangle = MattMath::RectangleF::ZERO;
};

#endif // !PROJECTILEBALL_H
