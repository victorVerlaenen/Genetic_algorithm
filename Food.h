#pragma once

class Food
{
public:
	Food(const Point2f& position, const Rectf& mapBounds, float width = 20.f, float height = 20.f);
	~Food() = default;

	Food(const Food& other) = delete;
	Food(Food&& other) = delete;
	Food& operator=(const Food& other) = delete;
	Food& operator=(Food&& other) = delete;

	void Update(float deltaTime);
	void Draw() const;

	void Reset();
	Rectf GetShape() const;
	void SetPosition(const Point2f& position);
private:
	Point2f m_Position;
	Rectf m_Shape;

	Rectf m_MapBounds;
};