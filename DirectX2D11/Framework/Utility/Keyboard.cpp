#include "Framework.h"

Keyboard::Keyboard()
	: curState{}, oldState{}, mapState{}
{
}

void Keyboard::Update()
{
	memcpy(oldState, curState, sizeof(oldState));

	//Ű���尡 �������� �� 128, 129�� ����������� ��ȯ(128, 129�� �����ư��� ȣ��)
	//Ű���尡 ������ �� 0, 1�� ����������� ��ȯ
	GetKeyboardState(curState);

	for (int i = 0; i < KEY_MAX; i++)
	{
		BYTE key = curState[i] & 0x80;;//128, 0
		curState[i] = key ? 1 : 0;//���׿�����, left=>return true / right=>return false

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)
			mapState[i] = UP;
		else if (old == 1 && cur == 1)
			mapState[i] = PRESS;
		else
			mapState[i] = NONE;
	}
}

bool Keyboard::AnyKey()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		//if (mapState[i] == DOWN)
		if (i != 21 && mapState[i] == DOWN)
			return true;
	}

	return false;
}
