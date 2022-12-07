#include "pch.h"
#include "Food.h"

Food::Food(const Point2f& position, const Rectf& mapBounds, float width, float height)
	:m_Position{ position }
	, m_MapBounds{ mapBounds }
	, m_Shape{ 0,0,width, height }
{
	Reset();
}
void Food::Update(float deltaTime)
{
	// Update the shape to the position
	m_Shape.left = m_Position.x - m_Shape.width / 2;
	m_Shape.bottom = m_Position.y - m_Shape.height / 2;
}

void Food::Draw() const
{
	utils::SetColor(1, 0, 0);
	utils::FillRect(m_Shape);
}

void Food::Reset()
{
	m_Position.x = static_cast<float>(rand() % static_cast<int>(m_MapBounds.width));
	m_Position.y = static_cast<float>(rand() % static_cast<int>(m_MapBounds.height));
}

Rectf Food::GetShape() const
{
	return m_Shape;
}

void Food::SetPosition(const Point2f& position)
{
	m_Position = position;
}