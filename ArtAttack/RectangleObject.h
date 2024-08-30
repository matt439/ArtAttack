#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "MattMath.h"

class RectangleObject
{
private:
	std::unique_ptr<MattMath::RectangleF> _rectangle = nullptr;
protected:
	virtual const MattMath::RectangleF* get_rectangle_ptr() const;
	virtual const MattMath::RectangleF& get_rectangle() const;
	virtual void set_rectangle(const MattMath::RectangleF& rectangle);

	virtual void inflate(float horizontal_amount, float vertical_amount);
	virtual void inflate(const MattMath::Vector2F& amount);
	virtual void scale_at_center(float scale);
	virtual void scale_at_center(float horizontal_scale, float vertical_scale);
	virtual void scale_at_center(const MattMath::Vector2F& scale);
	virtual void offset(float horizontal_amount, float vertical_amount);
	virtual void offset(const MattMath::Vector2F& amount);
	virtual void scale(float horizontal_amount, float vertical_amount);
	virtual void scale(const MattMath::Vector2F& amount);
	virtual void set_position(const MattMath::Vector2F& position);
	virtual void set_size(const MattMath::Vector2F& size);
public:
	RectangleObject() {}
	RectangleObject(const MattMath::RectangleF& bounds) :
		_rectangle(std::make_unique<MattMath::RectangleF>(bounds)) {}
};

#endif // !RECTANGLEOBJECT_H
