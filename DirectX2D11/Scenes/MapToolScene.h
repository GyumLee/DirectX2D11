#pragma once

class MapToolScene : public Scene
{
private:
	vector<Button*> sampleBtns;

	Button* selectSampleBtn;

	TileMap* tileMap;

	Tile::Type selectType;

	string projectPath;
public:
	MapToolScene();
	~MapToolScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	void CreateSample();
	void CreateSampleObj();

	void ClickSampleBtn(void* btn);
};