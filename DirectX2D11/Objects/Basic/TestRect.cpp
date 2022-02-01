#include "Framework.h"

TestRect::TestRect(Float2 pos, Float2 size)
{
    vertexShader = new VertexShader(L"Shaders/ColorShader.hlsl");
    pixelShader = new PixelShader(L"Shaders/ColorShader.hlsl");

    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y - size.y * 0.5f;
    float bottom = pos.y + size.y * 0.5f;

    //Polygon : ���� 3�� �̻����� �̷���� 3D ���������� �ﰢ��
    //������ ���� ������ ���� �ð������ �ո�, �ݽð������ �޸����� �Ѵ�.
    //�������� �ո鸸 ����Ѵ�.
    vertices =
    {
        Vertex(left, bottom, 1, 1, 1),
        Vertex(left, top, 1, 1, 1),
        Vertex(right, bottom, 1, 1, 1),
        Vertex(right, top, 1, 1, 1),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer;
    colorBuffer = new ColorBuffer;
}

TestRect::~TestRect()
{
    delete vertexShader;
    delete pixelShader;

    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
    delete colorBuffer;
}

void TestRect::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
