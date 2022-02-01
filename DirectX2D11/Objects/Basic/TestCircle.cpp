#include "Framework.h"

TestCircle::TestCircle(Float2 pos, float radius)
{
    vertexShader = new VertexShader(L"Shaders/ColorShader.hlsl");
    pixelShader = new PixelShader(L"Shaders/ColorShader.hlsl");

    vertices.emplace_back(pos.x, pos.y, 1, 1, 1);
    for (UINT i = 0; i < N; i++)
    {
        float angle = XM_2PI / N * i;

        float x = cos(angle) * radius + pos.x;
        float y = -sin(angle) * radius + pos.y;

        vertices.emplace_back(x, y, 1, 1, 1);
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    for (UINT i = 1; i < N; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 0);
    }

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(N);

    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

TestCircle::~TestCircle()
{
    delete vertexShader;
    delete pixelShader;

    delete vertexBuffer;
    delete indexBuffer;
}

void TestCircle::Render()
{
    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
