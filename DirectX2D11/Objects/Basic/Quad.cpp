#include "Framework.h"

Quad::Quad(wstring textureFile, Vector2 cutStart, Vector2 cutEnd)
    : textureFile(textureFile)
{
    vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
    pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

    texture = Texture::Add(textureFile);

    size = (cutEnd - cutStart) * texture->GetSize();

    Vector2 halfSize = size * 0.5f;

    float left = -halfSize.x;
    float right = halfSize.x;
    float top = -halfSize.y;
    float bottom = halfSize.y;

    vertices = {
       Vertex(left, bottom, cutStart.x, cutEnd.y),
       Vertex(left, top, cutStart.x, cutStart.y),
       Vertex(right, bottom, cutEnd.x, cutEnd.y),
       Vertex(right, top, cutEnd.x, cutStart.y),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
}

Quad::Quad(Vector2 size)
    : texture(nullptr), size(size)
{
    vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
    pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

    Vector2 halfSize = size * 0.5f;

    float left = -halfSize.x;
    float right = halfSize.x;
    float top = -halfSize.y;
    float bottom = halfSize.y;

    vertices = {
       Vertex(left, bottom, 0, 1),
       Vertex(left, top, 0, 0),
       Vertex(right, bottom, 1, 1),
       Vertex(right, top, 1, 0),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
}

Quad::~Quad()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
    delete colorBuffer;
}

void Quad::Render()
{
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    if (texture != nullptr)
        texture->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::SetRender()
{
    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    if (texture != nullptr)
        texture->Set();

    vertexShader->Set();
    pixelShader->Set();
}

void Quad::SetPixelShader(wstring file)
{
    pixelShader = Shader::AddPS(file);
}

void Quad::SetVertexShader(wstring file)
{
    vertexShader = Shader::AddVS(file);
}

void Quad::SetTexture(wstring file)
{
    textureFile = file;
    texture = Texture::Add(file);
}
