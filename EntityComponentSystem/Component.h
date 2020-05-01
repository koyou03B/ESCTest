#pragma once
#include "ECS.h"

class PositionComponent : public Component
{
private:
	int m_xPos;
	int m_yPos;

public:
	int x() { return m_xPos; }
	int y() { return m_yPos; }

	void Init() override
	{
		m_xPos = 0;
		m_yPos = 0;
	}

	void Update() override
	{
		++m_xPos;
		++m_yPos;
	}

	void Render() override
	{
		std::cout << m_xPos << " and " << m_yPos << " point" << std::endl;
	}
	void SetPosition(int x, int y) 
	{
		m_xPos = x;
		m_yPos = y;
	}


};

class AngleComponent : public Component
{
private:
	float m_angle;

public:
	float angle() { return m_angle; }

	void Init() override
	{
		m_angle = 0;
	}

	void Update() override
	{
		m_angle = 180.0f * 0.01745f;
	}

	void Render() override
	{
		std::cout << m_angle  << std::endl;
	}
	void SetAngle(float angle)
	{
		m_angle = angle;
	}


};