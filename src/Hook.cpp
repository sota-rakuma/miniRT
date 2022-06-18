#include "Win.hpp"
#include "Hook.hpp"

int	Hook::close(void *param)
{
	((Win *)param)->~Win();
	std::exit(0);
}

int	Hook::close(int keycode, void *param)
{
	((Win *)param)->~Win();
	std::exit(0);
}
