#pragma once

class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);

	Vector2 operator+ (const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator- (const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator* (const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/ (const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}
	Vector2 operator* (const float& value) const //½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/ (const float& value) const //½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		return Vector2(x / value, y / value);
	}

	void operator+= (const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-= (const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator+= (const float& value) // ½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		x += value;
		y += value;
	}
	void operator-= (const float& value) // ½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		x -= value;
		y -= value;
	}
	void operator*= (const float& value) // ½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		x *= value;
		y *= value;
	}
	void operator/= (const float& value) // ½ºÄ®¶ó °ª °öÇØÁÖ±â
	{
		x /= value;
		y /= value;
	}

	float Length() const;

	void Normalize();
	Vector2 Normalized() const;

	float Angle() const;

	static float Dot(const Vector2& v1, const Vector2& v2);
	static float Cross(const Vector2& v1, const Vector2& v2);

	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mat);
};