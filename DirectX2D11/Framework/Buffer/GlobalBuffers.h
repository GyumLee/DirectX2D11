#pragma once

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	}data;

public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);//전치행렬 GPU에서는 전치행렬로 바꿔야 연산이 된다.
	}
};

class ColorBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Float4 color;
	}data;

public:
	ColorBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.color = Float4(1, 1, 1, 1);
	}

	void Set(float r, float g, float b)
	{
		data.color = Float4(r, g, b, 1);
	}
	void Set(float r, float g, float b, float a)
	{
		data.color = Float4(r, g, b, a);
	}
	void Set(Float4 color)
	{
		data.color = color;
	}
};

class FrameBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Vector2 maxFrame;
		Vector2 curFrame;
	}data;

public:
	FrameBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}

	void SetMaxFrame(float x, float y)
	{
		data.maxFrame = { x, y };
	}

	void SetCurFrame(float x, float y)
	{
		data.curFrame = { x, y };
	}
};

class ValueBuffer : public ConstBuffer
{
public:
	struct Data
	{
		float values[4] = {};
	}data;

	ValueBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}
};

class IntBuffer : public ConstBuffer
{
public:
	struct Data
	{
		int values[4] = {};
	}data;

	IntBuffer() : ConstBuffer(&data, sizeof(Data))
	{
	}
};