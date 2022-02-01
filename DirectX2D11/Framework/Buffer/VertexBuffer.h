#pragma once

class VertexBuffer
{
private:
	ID3D11Buffer* buffer; //VRAM�� ����� �޸� ���� ��ü

	UINT stride;
	UINT offset;

public:
	VertexBuffer(void* data, UINT stride, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void Set(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void Update(void* data, UINT count);
};