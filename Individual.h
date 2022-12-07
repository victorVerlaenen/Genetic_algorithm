#pragma once
#include <vector>
#include <array>
#include "NeuralNetwork.h"

class Individual
{
public:
	Individual(const Point2f& position, const Rectf& mapBounds, float width = 20.f, float height = 20.f);
	~Individual();

	Individual(const Individual& other) = delete;
	Individual(Individual&& other) = delete;
	Individual& operator=(const Individual& other) = delete;
	Individual& operator=(Individual&& other) = delete;

	void Draw() const;
	void Update(float deltaTime);

	Point2f GetPosition() const { return m_Position; }
	bool IsDead() const;

	int GetFitness() const;

	template<typename Typename>
	void SetBrain(Typename* pNetwork)
	{
		m_pBrain = pNetwork;
	}

private:
	enum class MovementDirection
	{
		Left,
		Right,
		Up,
		Down
	};

	void UpdateInputs();
	void HandleMovement(float deltaTime);
	void CheckIfInBounds();


	NeuralNetwork<10, 4, 20>* m_pBrain;
	std::array<float, 10> m_Inputs;

	Point2f m_Position;
	float m_MoveSpeed{ 300.f };
	Vector2f m_Velocity{ 0.f, 0.f };
	MovementDirection m_MovementDirection{ MovementDirection::Up };
	bool m_IsDead{ false };

	Rectf m_MapBounds;

	// Visuals
	Rectf m_Shape;
};

