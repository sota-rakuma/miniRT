#include "GraphicSystem.hpp"
#include <iostream>
#ifdef __cplusplus
extern "C" {
#endif
#include "mlx.h"
#include <cstdlib>
#ifdef __cplusplus
}
#endif

GraphicSystem::GraphicSystem(void) {}

GraphicSystem::~GraphicSystem(void) {
	void* tmp = const_cast<void*>(_mlx);
	mlx_destroy_display(tmp);
	free(tmp);
}

void* GraphicSystem::getMlx(void) { return (const_cast<void*>(_mlx)); }
