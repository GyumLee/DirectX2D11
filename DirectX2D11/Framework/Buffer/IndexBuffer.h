#pragma once

class IndexBuffer
{
private:
	ID3D11Buffer* buffer; //VRAM�� ����� �޸� ���� ��ü

public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void Set();
};