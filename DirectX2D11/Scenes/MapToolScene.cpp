#include "Framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
	: selectSampleBtn(nullptr), selectType(Tile::BG)
{
	CreateSample();
	CreateSampleObj();

	tileMap = new TileMap(10, 10);
	tileMap->position = { 70, 70 };

	char path[128];
	GetCurrentDirectoryA(128, path);
	projectPath = path;
}

MapToolScene::~MapToolScene()
{
	for (Button* btn : sampleBtns)
		delete btn;

	delete tileMap;
}

void MapToolScene::Update()
{
	if (KEY_PRESS(VK_LBUTTON) && selectSampleBtn != nullptr && !ImGui::GetIO().WantCaptureMouse)
	{
		tileMap->ClickTile(selectSampleBtn->GetTextureFile(), selectType);
	}

	if (KEY_PRESS(VK_RBUTTON) && selectSampleBtn != nullptr && !ImGui::GetIO().WantCaptureMouse)
	{
		tileMap->DeleteObjTile(CAM->ScreenToWorld(mousePos));
	}

	for (Button* btn : sampleBtns)
		btn->Update();

	tileMap->Update();
}

void MapToolScene::Render()
{
	for (Button* btn : sampleBtns)
		btn->Render();

	tileMap->Render();
}

void MapToolScene::PostRender()
{
	const char* list[] = { "BG", "OBJ" };
	ImGui::ListBox("Type", (int*)&selectType, list, 2);

	Save();
	Load();
}

void MapToolScene::Save()
{
	if (ImGui::Button("Save"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("SaveKey", "SaveFile",
			".map", ".");
	}

	if (ImGuiFileDialog::Instance()->Display("SaveKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			string file = ImGuiFileDialog::Instance()->GetFilePathName();
			//file = file.substr(projectPath.size() + 1, file.size());
			file = file.substr(2, file.size());

			tileMap->Save(file);
		}

		ImGuiFileDialog::Instance()->Close();
	}
}

void MapToolScene::Load()
{
	if (ImGui::Button("Load"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("LoadKey", "LoadFile",
			".map", ".");
	}

	if (ImGuiFileDialog::Instance()->Display("LoadKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			string file = ImGuiFileDialog::Instance()->GetFilePathName();
			//file = file.substr(projectPath.size() + 1, file.size());
			file = file.substr(2, file.size());

			tileMap->Load(file);
		}

		ImGuiFileDialog::Instance()->Close();
	}
}

void MapToolScene::CreateSample()
{
	//_wfinddata_t findData;
	_wfinddatai64_t findData;

	//long handle;
	long long handle;
	int result = 1;

	//handle = _wfindfirst(L"Textures/TileMap\\*.png", &findData);
	handle = _wfindfirsti64(L"Textures/TileMap\\*.png", &findData);

	wstring fileName;

	UINT width = 8;

	Vector2 startPos(750, 50);

	while (result != -1)
	{
		fileName = L"Textures/TileMap/";
		fileName += findData.name;

		//result = _wfindnext(handle, &findData);
		result = _wfindnexti64(handle, &findData);

		Button* button = new Button(fileName);
		UINT index = sampleBtns.size();
		Vector2 pos(index % width, index / width);

		button->position = startPos + (pos * button->Size());

		button->SetVoidEvent(bind(&MapToolScene::ClickSampleBtn, this, placeholders::_1));
		button->SetVoidParam(button);

		sampleBtns.push_back(button);
	}
}

void MapToolScene::CreateSampleObj()
{
	_wfinddatai64_t findData;

	long long handle;
	int result = 1;
	handle = _wfindfirsti64(L"Textures/TileObject\\*.png", &findData);

	wstring fileName;

	UINT width = 8;

	Vector2 startPos(750, 50);
	Vector2 size(64, 64);

	while (result != -1)
	{
		fileName = L"Textures/TileObject/";
		fileName += findData.name;

		result = _wfindnexti64(handle, &findData);

		Button* button = new Button(fileName);
		UINT index = sampleBtns.size();
		Vector2 pos(index % width, index / width);

		button->position = startPos + (pos * size);

		button->SetVoidEvent(bind(&MapToolScene::ClickSampleBtn, this, placeholders::_1));
		button->SetVoidParam(button);

		sampleBtns.push_back(button);
	}
}

void MapToolScene::ClickSampleBtn(void* btn)
{
	selectSampleBtn = (Button*)btn;
}
