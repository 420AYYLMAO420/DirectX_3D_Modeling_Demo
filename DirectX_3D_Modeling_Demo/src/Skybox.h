#pragma once

#include <vector>
#include "Cube.h"

class Skybox {
public:
	Skybox(const std::vector<const char*> paths);

private:
	std::shared_ptr<Cube> CubeObject;
	std::vector<class Texture> textures;
};