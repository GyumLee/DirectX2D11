#pragma once

class ConstBuffer
{
private:
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;

public:
	ConstBuffer(void* data, UINT dataSize);
	~ConstBuffer();

	void SetVS(UINT slot);
	void SetPS(UINT slot);
};