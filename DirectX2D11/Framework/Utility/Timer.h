#pragma once

class Timer : public Singleton<Timer>
{
private:
	friend class Singleton;

	float timeScale;
	float timeElapsed;

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	int frameRate;
	int frameCount;

	float oneSecCount;
	float runTime;

	float scale;

	Timer();

public:
	void Update();

	void SetScale(float value) { scale = value; }

	int GetFPS() { return frameRate; }
	float GetDeltaTime() { return timeElapsed * scale; }
	float GetElapsed() { return timeElapsed; }
	float GetRunTime() { return runTime; }
};