#include "Framework.h"

Frame::Frame(wstring textureFile, Vector2 cutStart, Vector2 cutEnd)
{
    texture = Texture::Add(textureFile);

    size = (cutEnd - cutStart) * texture->GetSize();

    Vector2 halfSize = size * 0.5f;

    float left = -halfSize.x;
    float right = halfSize.x;
    float top = -halfSize.y;
    float bottom = halfSize.y;

    vertices =
    {
        Vertex(left, bottom, cutStart.x, cutEnd.y),
        Vertex(left, top, cutStart.x, cutStart.y),
        Vertex(right, bottom, cutEnd.x, cutEnd.y),
        Vertex(right, top, cutEnd.x, cutStart.y),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Frame::Frame(wstring textureFile, float x, float y, float w, float h)
{
    texture = Texture::Add(textureFile);

    size = Vector2(w, h);

    Vector2 halfSize = size * 0.5f;

    float left = -halfSize.x;
    float right = halfSize.x;
    float top = -halfSize.y;
    float bottom = halfSize.y;

    Vector2 cutStart = Vector2(x, y) / texture->GetSize();
    Vector2 cutEnd = Vector2(x + w, y + h) / texture->GetSize();

    vertices =
    {
        Vertex(left, bottom, cutStart.x, cutEnd.y),
        Vertex(left, top, cutStart.x, cutStart.y),
        Vertex(right, bottom, cutEnd.x, cutEnd.y),
        Vertex(right, top, cutEnd.x, cutStart.y),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Frame::~Frame()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void Frame::Render()
{
    vertexBuffer->Set();
    indexBuffer->Set();

    texture->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
