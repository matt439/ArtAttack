#include "pch.h"
#include "State.h"

void State::set_context(StateContext* context)
{
	this->_context = context;
}
StateContext* State::get_context() const
{
	return this->_context;
}
