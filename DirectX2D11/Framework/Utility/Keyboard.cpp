#include "Framework.h"

Keyboard::Keyboard()
	: curState{}, oldState{}, mapState{}
{
}

void Keyboard::Update()
{
	memcpy(oldState, curState, sizeof(oldState));

	//키보드가 눌러졌을 때 128, 129가 토글형식으로 반환(128, 129가 번갈아가며 호출)
	//키보드가 떼졌을 때 0, 1이 토글형식으로 반환
	GetKeyboardState(curState);

	for (int i = 0; i < KEY_MAX; i++)
	{
		BYTE key = curState[i] & 0x80;;//128, 0
		curState[i] = key ? 1 : 0;//삼항연산자, left=>return true / right=>return false

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
