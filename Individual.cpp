#include "pch.h"
#include "Individual.h"

Individual::Individual(const Point2f& position, const Rectf& mapBounds, float width, float height)
	:m_pBrain{ new NeuralNetwork<10, 4, 20>{2} }
	, m_Shape{ position.x - width, position.y + height, width, height }
	, m_Position{ position }
	, m_MapBounds{ mapBounds }
	, m_Inputs{}
{

}

Individual::~Individual()
{
	delete m_pBrain;
	m_pBrain = nullptr;
}

void Individual::Draw() const
{
	utils::SetColor(0, 1, 0);
	utils::FillRect(m_Shape);
}

void Individual::Update(float deltaTime)
{
	UpdateInputs();
	HandleMovement(deltaTime);
	CheckIfInBounds();
}

void Individual::HandleMovement(float deltaTime)
{
	// Get the outputs from the brain
	m_pBrain->Forward(m_Inputs);
	auto output = m_pBrain->Output();
	auto index = std::distance(output.begin(), std::max_element(output.begin(), output.end()));

	// Excecute the right thing according to the output
	switch (index)
	{
	case 0:
		m_MovementDirection = MovementDirection::Left;
		m_Velocity = Vector2f{ -m_MoveSpeed, 0 };
		break;
	case 1:
		m_MovementDirection = MovementDirection::Right;
		m_Velocity = Vector2f{ m_MoveSpeed, 0 };
		break;
	case 2:
		m_MovementDirection = MovementDirection::Up;
		m_Velocity = Vector2f{ 0, m_MoveSpeed };
		break;
	case 3:
		m_MovementDirection = MovementDirection::Down;
		m_Velocity = Vector2f{ 0, -m_MoveSpeed };
		break;
	}

	// Update the position
	m_Position += m_Velocity * deltaTime;

	// Update the shape to the position
	m_Shape.left = m_Position.x;
	m_Shape.bottom = m_Position.y;
}

void Individual::CheckIfInBounds()
{
	// Reset the individual when it hits the wall
	if (utils::IsPointInRect(m_Position, m_MapBounds) == false)
	{
		m_IsDead = true;
	}
}

void Individual::UpdateInputs()
{
	// Which direction is he moving?
	m_Inputs[0] = 0;
	m_Inputs[1] = 0;
	m_Inputs[2] = 0;
	m_Inputs[3] = 0;

	switch (m_MovementDirection)
	{
	case Individual::MovementDirection::Left:
		m_Inputs[0] = 1;
		break;
	case Individual::MovementDirection::Right:
		m_Inputs[1] = 1;
		break;
	case Individual::MovementDirection::Up:
		m_Inputs[2] = 1;
		break;
	case Individual::MovementDirection::Down:
		m_Inputs[3] = 1;
		break;
	}

	// x and y position of the food (FOR NOW JUST POSITION (0, 0))
	m_Inputs[4] = m_Position.x / m_MapBounds.width;
	m_Inputs[5] = m_Position.y / m_MapBounds.height;

	// distance to all 4 walls
	m_Inputs[6] = m_Position.x / m_MapBounds.width;
	m_Inputs[7] = (m_MapBounds.width - m_Position.x) / m_MapBounds.width;
	m_Inputs[8] = m_Position.y / m_MapBounds.height;
	m_Inputs[9] = (m_MapBounds.height - m_Position.y) / m_MapBounds.height;

	/*std::cout << "Inputs: [";
	for (int i{ 0 }; i < m_Inputs.size() - 1; ++i)
	{
		std::cout << m_Inputs[i] << ", ";
	}
	std::cout << m_Inputs[m_Inputs.size() - 1] << "]\n\n";*/
}

int Individual::GetFitness() const
{
	// TODO calculate fitness
	return 0;
}

bool Individual::IsDead() const
{
	return m_IsDead;
}

//void Individual::SetBrain(NeuralNetwork* pNetwork)
//{
//	m_pBrain = pNetwork;
//}
