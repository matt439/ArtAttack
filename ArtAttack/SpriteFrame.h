#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include "MattMath.h"
#include <string>

class SpriteFrame
{
private:
	RECT _source_rectangle = { 0, 0, 0, 0 };

	MattMath::RectangleI _source_rectangle2 = MattMath::RectangleI::ZERO;
	MattMath::Vector2F _origin = MattMath::Vector2F::ZERO;
	bool _rotated = false;

	void set_source_rectangle(
		const MattMath::RectangleI& source_rectangle);
	void set_source_rectangle(const MattMath::Vector2F& position,
		const MattMath::Vector2F& size);
public:
	SpriteFrame() {}
	SpriteFrame(const MattMath::RectangleI& source_rectangle,
		const MattMath::Vector2F& origin =
			MattMath::Vector2F::ZERO,
		bool rotated = false);
	SpriteFrame(const MattMath::Vector2F& position,
		const MattMath::Vector2F& size,
		const MattMath::Vector2F& origin =
			MattMath::Vector2F::ZERO,
		bool rotated = false);
	const RECT* get_source_rectangle() const;
};

#endif // !SPRITEFRAME_H
