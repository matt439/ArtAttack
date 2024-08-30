#include "pch.h"
#include "StateContext.h"

void StateContext::update() const
{
	if (this->_state == nullptr)
	{
		return;
	}
	this->_state->update();
}
void StateContext::draw()
{
	if (this->_state == nullptr)
	{
		return;
	}
	this->_state->draw();
}
void StateContext::transition_to(std::unique_ptr<State> state)
{
	this->_state = std::move(state);
	this->_state->set_context(this);
	this->_state->init();
}