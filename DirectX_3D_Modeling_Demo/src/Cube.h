#pragma once

#include "Model.h"
#include "ConstantBuffer.h"

class Cube : public Model {
public:
	Cube(class Shader* shader);
	//Cube() = default;
	void Make(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* context);
private:
};