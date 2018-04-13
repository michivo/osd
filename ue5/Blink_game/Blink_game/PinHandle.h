#pragma once

#include "Pin.h"
#include <functional>

class Pin_handle
{
public:
	Pin_handle(Pin pin, std::function<void(Pin)> releaser);
	~Pin_handle();
	Pin_handle(Pin_handle &&other) noexcept;
	Pin_handle& operator=(Pin_handle &&other) noexcept;

	void release();
	Pin get_pin() const;

private:
	Pin pin_;
	bool is_active_;
	std::function<void(Pin)> releaser_;
};
