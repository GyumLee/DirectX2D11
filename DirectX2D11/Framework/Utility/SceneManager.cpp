#include "Framework.h"

SceneManager::SceneManager() : curScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	//for (pair<string, Scene*> scene : scenes)
	for (auto scene : scenes)
		delete scene.second;
}

void SceneManager::Update()
{
	if (curScene == nullptr) return;

	curScene->Update();
}

void SceneManager::PreRender()
{
	if (curScene == nullptr) return;

	curScene->PreRender();
}

void SceneManager::Render()
{
	if (curScene == nullptr) return;

	curScene->Render();
}

void SceneManager::PostRender()
{
	if (curScene == nullptr) return;

	curScene->PostRender();
}

Scene* SceneManager::Add(string key, Scene* scene)
{
	if (scenes.count(key) > 0)
		return scenes[key];

	scenes[key] = scene;

	return scene;
}

void SceneManager::Change(string key)
{
	if (scenes.count(key) == 0) return;
	if (scenes[key] == curScene) return;

	if (curScene != nullptr)
		curScene->End();

	curScene = scenes[key];
	curScene->Start();
}
