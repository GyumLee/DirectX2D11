#pragma once

class Program
{
private:
	MatrixBuffer* viewBuffer;

public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	void Create();
	void Release();
};