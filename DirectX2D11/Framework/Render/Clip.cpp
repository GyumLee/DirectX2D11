#include "Framework.h"

Clip::Clip(vector<Frame*> frames, Type type, float delayTime)
	: frames(frames), repeatType(type), delayTime(delayTime),
	curFrameNum(0), isPlay(true), isReverse(false), time(0.0f),
	EndEvent(nullptr)
{

}

Clip::~Clip()
{
	for (Frame* frame : frames)
		delete frame;
}

void Clip::Update()
{
	if (!isPlay) return;

	time += DELTA;

	if (time < delayTime) return;

	switch (repeatType)
	{
	case Clip::END:
		curFrameNum++;
		if (curFrameNum >= frames.size())
		{
			curFrameNum--;
			Stop();
		}
		break;
	case Clip::LOOP:
		++curFrameNum %= frames.size();
		break;
	case Clip::PINGPONG:
		if (isReverse)
		{
			curFrameNum--;
			if (curFrameNum <= 0)
				isReverse = false;
		}
		else
		{
			curFrameNum++;
			if (curFrameNum >= frames.size() - 1)
				isReverse = true;
		}
		break;
	default:
		break;
	}

	time -= delayTime;
}

void Clip::Render()
{
	frames[curFrameNum]->Render();
}

void Clip::Play()
{
	isPlay = true;
	isReverse = false;
	time = 0.0f;
	curFrameNum = 0;
}

void Clip::Stop()
{
	isPlay = false;

	if (EndEvent != nullptr)
		EndEvent();
}
