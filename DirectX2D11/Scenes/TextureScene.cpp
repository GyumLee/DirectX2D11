#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    vertexShader = new VertexShader(L"Shaders/Texture.hlsl");
    pixelShader = new PixelShader(L"Shaders/Texture.hlsl");

    float left = -50.0f;
    float right = 50.0f;
    float top = -50.0f;
    float bottom = 50.0f;

    vertices =
    {
        Vertex(left, bottom, 0, 1),
        Vertex(left, top, 0, 0),
        Vertex(right, bottom, 1, 1),
        Vertex(right, top, 1, 0),
    };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };

    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer;
    colorBuffer = new ColorBuffer;

    transform = new Transform();
    transform->position = { CENTER_X, CENTER_Y };

    ScratchImage image;
    LoadFromWICFile(L"Textures/player.png", WIC_FLAGS_NONE, nullptr, image);

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    D3D11_SAMPLER_DESC desc = {};
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    DEVICE->CreateSamplerState(&desc, &samplerState);
    DC->PSSetSamplers(0, 1, &samplerState);
}

TextureScene::~TextureScene()
{
    delete vertexShader;
    delete pixelShader;

    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
    delete colorBuffer;

    delete transform;

    srv->Release();
}

void TextureScene::Update()
{
    if (KEY_PRESS('A'))
        transform->position.x -= speed * DELTA;
    if (KEY_PRESS('D'))
        transform->position.x += speed * DELTA;
    if (KEY_PRESS('W'))
        transform->position.y -= speed * DELTA;
    if (KEY_PRESS('S'))
        transform->position.y += speed * DELTA;

    transform->UpdateWorld();
}

void TextureScene::Render()
{
    worldBuffer->Set(transform->GetWorld());
    worldBuffer->SetVS(0);

    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    DC->PSSetShaderResources(0, 1, &srv);

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
