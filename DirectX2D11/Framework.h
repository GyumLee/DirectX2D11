#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH (1240) // Window Screen Width
#define WIN_HEIGHT (720) // Window Screen Height

#define WIN_START_X (100) // Window Screen StartX (LEFT)
#define WIN_START_Y (100) // Window Screen StartY (TOP)

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define GRAVITY (980.0f)

#define DEVICE (Device::Get()->GetDevice()) // Device
#define DC (Device::Get()->GetContext()) // DeviceContext

#define KEY_DOWN(k) (Keyboard::Get()->Down(k))
#define KEY_UP(k) (Keyboard::Get()->Up(k))
#define KEY_PRESS(k) (Keyboard::Get()->Press(k))

#define DELTA (Timer::Get()->GetDeltaTime())

#define CAM (Environment::Get()->GetMainCamera())

#define AUDIO (Audio::Get())

#define FONT (Font::Get())

#define LERP(s, e, t) (s + (e - s) * t)

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <algorithm>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
//#include "../DirectXTex/DirectXTex.h"
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

//ImGui
//#include "../ImGui/imgui.h"
//#include "../ImGui/imgui_impl_dx11.h"
//#include "../ImGui/imgui_impl_win32.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <ImGuiFileDialog.h>

#pragma comment(lib, "ImGui.lib")

//FMOD
//#include "Library/FMOD/inc/fmod.hpp"
//#pragma comment(lib, "Library/FMOD/fmod_vc.lib")
#include <inc/fmod.hpp>
#pragma comment(lib, "fmod_vc.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace DirectX;
using namespace std;
using namespace FMOD;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

//Framework Header
#include "Framework/Math/Math.h"
using namespace GameMath;
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Xml.h"
#include "Framework/Utility/Audio.h"
#include "Framework/Utility/SceneManager.h"
#include "Framework/Utility/Font.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"

#include "Framework/System/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffers.h"
#include "Framework/Buffer/VertexLayouts.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/LineCollider.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

#include "Algorithm/DNode.h"
#include "Algorithm/Dijkstra.h"
#include "Algorithm/Node.h"
#include "Algorithm/Heap.h"
#include "Algorithm/AStar.h"

//Object Header
#include "Objects/Basic/TestRect.h"
#include "Objects/Basic/TestCircle.h"

#include "Objects/Basic/Quad.h"
#include "Objects/Basic/AnimObject.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/EffectManager.h"
#include "Objects/Basic/Bar.h"
#include "Objects/Basic/ImageFont.h"
#include "Objects/Basic/Button.h"

#include "Objects/Game/Bullet.h"
#include "Objects/Game/BulletManager.h"
#include "Objects/Game/Plane.h"
#include "Objects/Game/Enemy.h"
#include "Objects/Game/EnemyManager.h"
#include "Objects/Game/Mario.h"
#include "Objects/Game/Knight.h"
#include "Objects/Game/KnightPlayer.h"
#include "Objects/Game/KnightMonster.h"
#include "Objects/Game/DataManager.h"
#include "Objects/Game/Item.h"
#include "Objects/Game/UIPanel.h"
#include "Objects/Game/Inventory.h"
#include "Objects/Game/Store.h"
#include "Objects/Game/Tile.h"
#include "Objects/Game/TileMap.h"
#include "Objects/Game/Tank.h"
#include "Objects/Game/GameMap.h"

#include "Objects/Game/BreakOut/Stick.h"
#include "Objects/Game/BreakOut/Brick.h"
#include "Objects/Game/BreakOut/BrickManager.h"
#include "Objects/Game/BreakOut/Ball.h"

//Scene Header
#include "Scenes/Scene.h""
#include "Program/Program.h"

extern HWND hWnd;
extern Vector2 mousePos;