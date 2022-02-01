#include "Framework.h"
#include "Device.h"

Device* Device::instance = nullptr;

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
}

Device::~Device()
{
	device->Release();
	context->Release();
	swapChain->Release();
	renderTargetView->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    /*RECT rc;
    GetClientRect(hWnd, &rc);*/
    UINT width = WIN_WIDTH;
    UINT height = WIN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferCount = 1;//후면버퍼 갯수
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//unsigned normal, 8bit
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    //RefreshRate : 디스플레이 모드 갱신율(주사율 : Numerator / Denominator)
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hWnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &desc,
        &swapChain,
        &device,
        nullptr,
        &context
    );
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();
}

void Device::Clear()
{
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);

    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, clearColor);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}