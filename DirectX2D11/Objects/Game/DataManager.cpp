#include "Framework.h"

DataManager::DataManager()
{
	LoadItemData();
}

DataManager::~DataManager()
{
}

void DataManager::LoadItemData()
{
	ifstream load("TextData/ItemTable.txt", ios::in);

	UINT dataCount = 6;

	string str;

	int count = 0;
	while (true)
	{
		if (count < dataCount)
		{
			load >> str;
			count++;
			continue;
		}

		ItemData data;
		data.key = 0;
		load >> data.key;

		if (data.key == 0) return;

		load >> data.name >> data.attack >> data.type
			>> data.price >> data.imageFile;

		itemDatas[data.key] = data;
	}
}
