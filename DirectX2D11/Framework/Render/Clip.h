#pragma once

class Clip
{
public:
	enum Type
	{
		END, LOOP, PINGPONG
	};

private:
	vector<Frame*> frames;

	Type repeatType;
	bool isPlay;

	UINT curFrameNum;

	float time;
	float delayTime;

	bool isReverse;

	function<void()> EndEvent;

public:
	Clip(vector<Frame*> frames, Type type = LOOP, float delayTime = 0.1f);
	~Clip();

	void Update();
	void Render();

	void Play();
	void Stop();

	void SetEndEvent(function<void()> Event) { EndEvent = Event; }

	Frame* GetFrame() { return frames[curFrameNum]; }
};