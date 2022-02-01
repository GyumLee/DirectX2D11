#pragma once

class IndexBuffer
{
private:
	ID3D11Buffer* buffer; //VRAM에 저장된 메모리 공간 객체

public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void Set();
};