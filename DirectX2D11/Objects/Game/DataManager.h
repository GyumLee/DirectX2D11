#pragma once

struct ItemData
{
	UINT key;
	string name;
	UINT attack;
	UINT type;
	UINT price;
	string imageFile;
};

class DataManager : public Singleton<DataManager>
{
private:
	friend class Singleton;

	map<UINT, ItemData> itemDatas;

	DataManager();
	~DataManager();

public:
	map<UINT, ItemData> GetItemData() { return itemDatas; }

private:
	void LoadItemData();
};