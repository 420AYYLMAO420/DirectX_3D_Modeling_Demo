#include "Graphics.h"
#include <DirectXMath.h>
#include "GraphicsCard.h"
#include "GUI.h"
#include "Time.h"
#include "Camera.h"
#include "imgui/imgui_impl_dx11.h"


//Resources
#include "View.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "Cube.h"
#include "Sampler.h"

#pragma comment(lib, "d3d11.lib")


struct {
    DirectX::XMVECTOR Color;
    DirectX::XMFLOAT3 Position;
} Light;

struct {
    DirectX::XMMATRIX Transform;
    DirectX::XMMATRIX ModelView;
} Transform;

template<class T>
T* Graphics::GetResource(const char* name) const
{
    return std::dynamic_pointer_cast<T>(Resources.at(name)).get();
}

Graphics::Graphics(HWND hwnd, unsigned int width, unsigned int height)
    :Width(width), Height(height)
{
    GPU = std::make_unique<GraphicsCard>(hwnd);
    GUI::InitDX11(GPU->GetDevice(), GPU->GetDeviceContext());

    Resources.insert({ "View", std::make_shared<View>(GPU->GetSwapChain(),width, height) });
    GPU->Make(GetResource<View>("View"));
    GPU->Bind(GetResource<View>("View"));

    Resources.insert({ "Transform", std::make_shared<ConstantBuffer>(&Transform, sizeof(Transform), SHADER::VERTEX, 0) });
    GPU->Make(GetResource<ConstantBuffer>("Transform"));
    GPU->Bind(GetResource<ConstantBuffer>("Transform"));

    Light = { DirectX::XMVectorSet(1.f, 1.f, 1.f, 1.f), {0.f, 10.f, 10.f} };
    Resources.insert({ "Light Properties", std::make_shared<ConstantBuffer>(&Light, sizeof(Light), SHADER::PIXEL, 0) });
    GPU->Make(GetResource<ConstantBuffer>("Light Properties"));
    GPU->Bind(GetResource<ConstantBuffer>("Light Properties"));

    Resources.insert({ "Nanosuit Shader", std::make_shared<Shader>(L"shaders/ModelVShader.cso", L"shaders/ModelPShader.cso") });
    GPU->Make(GetResource<Shader>("Nanosuit Shader"));
    GPU->Bind(GetResource<Shader>("Nanosuit Shader"));

    Resources.insert({ "Nanosuit", std::make_shared<Model>("res/Models/nano_textured/nanosuit.obj", GetResource<Shader>("Nanosuit Shader"))});
    GPU->Make(GetResource<Model>("Nanosuit"));

    Resources.insert({ "Light Shader", std::make_shared<Shader>(L"shaders/CubeVShader.cso", L"shaders/CubePShader.cso") });
    GPU->Make(GetResource<Shader>("Light Shader"));

    Resources.insert({ "Light", std::make_shared<Cube>( GetResource<Shader>("Light Shader")) });
    GPU->Make(GetResource<Cube>("Light"));

    Resources.insert({ "Sampler", std::make_shared<Sampler>() });
    GPU->Make(GetResource<Sampler>("Sampler"));
    GPU->Bind(GetResource<Sampler>("Sampler"));

    Timer = std::make_unique<Time>();
    Timer->Start();

    CameraObject = std::make_unique<Camera>();

    GPU->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


Graphics::~Graphics()
{
   
}

void Graphics::Render(const UINT key, float x, float y)
{
    using namespace DirectX;
   
    GPU->Clear(GetResource<View>("View"));

    GUI::NewFrame();
    CameraObject->ShowControls();
    ImGui::Begin("Light");
    ImGui::SliderFloat("X", &Light.Position.x, -20, 20);
    ImGui::SliderFloat("Y", &Light.Position.y, -20, 20);
    ImGui::SliderFloat("Z", &Light.Position.z, -20, 20);
    ImGui::End();
    GUI::Render();

    CameraObject->Move(key, Timer->GetDeltaTime());
    GetResource<ConstantBuffer>("Light Properties")->Update(GPU->GetDeviceContext(), &Light, sizeof(Light));

    XMMATRIX projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(45.f, (float)Width / (float)Height, 0.1f, 100.f));
    XMMATRIX view = XMMatrixTranspose(CameraObject->GetLookAt());
    XMMATRIX lightModel = XMMatrixTranspose(XMMatrixTranslation(Light.Position.x, Light.Position.y, Light.Position.z));
    XMMATRIX nanosuitModel = XMMatrixTranspose(XMMatrixRotationY(Timer->GetTimeSinceStart()) * XMMatrixTranslation(0.f, 0.f, 5.f));

    Transform.Transform = projection * view * lightModel;
    Transform.ModelView = view * lightModel;
    GetResource<ConstantBuffer>("Transform")->Update(GPU->GetDeviceContext(), &Transform, sizeof(Transform));
    GPU->Render(GetResource<Cube>("Light"));

    Transform.Transform = projection * view * nanosuitModel;
    Transform.ModelView = view * nanosuitModel;
    GetResource<ConstantBuffer>("Transform")->Update(GPU->GetDeviceContext(), &Transform, sizeof(Transform));
    GPU->Render(GetResource<Model>("Nanosuit"));

    GPU->SwapBuffers();
}

