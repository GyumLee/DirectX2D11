#pragma once

class Scene;

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton;

	map<string, Scene*> scenes;
	Scene* curScene;

	SceneManager();
	~SceneManager();

public:
	void Update();

	void PreRender();
	void Render();
	void PostRender();

	Scene* Add(string key, Scene* scene);

	void Change(string key);
};