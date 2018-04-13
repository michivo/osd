// nested class Pin_handle
#include "PinHandle.h"
#include <functional>
#include <utility>

Pin_handle::Pin_handle(Pin pin, std::function<void(Pin)> releaser) : pin_{ pin }, is_active_{ true }, releaser_{
	std::move(releaser)
}
{
}

Pin_handle::~Pin_handle()
{
	if (is_active_)
	{
		releaser_(pin_);
	}
}

Pin_handle::Pin_handle(Pin_handle&& other) noexcept : pin_{ other.pin_ }, is_active_{ other.is_active_ }
{
	releaser_.swap(other.releaser_);
	other.is_active_ = false;
}

Pin_handle& Pin_handle::operator=(Pin_handle&& other) noexcept
{
	is_active_ = other.is_active_;
	pin_ = other.pin_;
	other.is_active_ = false;

	return *this;
}

void Pin_handle::release()
{
	releaser_(pin_);
	is_active_ = false;
}

Pin Pin_handle::get_pin() const
{
	return pin_;
}
