#include "Framework.h"

Timer::Timer()
	: frameRate(0), frameCount(0), timeElapsed(0),
	oneSecCount(0), runTime(0), scale(1.0f)
{
	//1�ʵ��� CPU�������� ��ȯ�ϴ� �Լ�
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	//���� CPU������
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

	timeScale = 1.0f / (float)periodFrequency;
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	timeElapsed = (float)(curTime - lastTime) * timeScale;

	lastTime = curTime;

	frameCount++;

	oneSecCount += timeElapsed;

	if (oneSecCount >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;
		oneSecCount = 0.0f;
	}

	runTime += timeElapsed;
}