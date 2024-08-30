#ifndef STATECONTEXT_H
#define STATECONTEXT_H

#include "State.h"
#include <memory>

class StateContext
{
private:
	std::unique_ptr<State> _state = nullptr;
public:
	virtual ~StateContext() = default;
	StateContext() = default;
	void update() const;
	void draw() const;
	void transition_to(std::unique_ptr<State> state);
};

#endif // !STATECONTEXTGENERIC_H
