#pragma once

class Device : public Singleton<Device>
{
private:
	friend class Singleton;

	ID3D11Device* device;// CPU (resource load, operation, etc..)
	ID3D11DeviceContext* context;// GPU output

	IDXGISwapChain* swapChain;// backbuffer management (swap: front <=> back)
	ID3D11RenderTargetView* renderTargetView;// GPU memory management

	Device();
	~Device();

public:
	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetContext() { return context; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }
};