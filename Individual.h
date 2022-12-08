#pragma once
#include <vector>
#include <array>

class Food;
class NeuralNetwork;
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

	static void SetFood(Food* pFood);
	void Reset();

	Point2f GetPosition() const { return m_Position; }
	NeuralNetwork* GetBrain() const { return m_pBrain; }
	bool IsDead() const;

	void CalculateFitness();
	int GetFitness() const;

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
	void CheckIfFoodHasBeenEaten();
	void CheckForEndlessMovement();

	NeuralNetwork* m_pBrain;
	std::vector<float> m_Inputs;
	float m_Fitness{ 0 };

	Point2f m_Position;
	Rectf m_Shape;
	float m_MoveSpeed{ 800.f };
	Vector2f m_Velocity{ 0.f, 0.f };
	MovementDirection m_MovementDirection{ MovementDirection::Up };
	bool m_IsDead{ false };

	Rectf m_MapBounds;
	static Food* m_pFood;

	float m_EndlessMovementTimer{ 0 };
	float m_EndlessMovementValue{ 10 };

	int m_AmountOfFoodsEaten{ 0 };
	int m_AmountOfDeaths{ 0 };
	int m_AmountOfEndlessMovement{ 0 };
};

