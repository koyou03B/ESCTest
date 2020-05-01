#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return ++lastID;
}

template <typename T> 
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t g_maxComponents = 32;

using ComponentBitSet = std::bitset<g_maxComponents>;
using ComponentArray = std::array<Component*, g_maxComponents>;

class Component
{
public:
	Entity* _entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {}

	virtual ~Component() = default;

};

class Entity
{
private:
	bool m_isActivate = true;
	std::vector<std::unique_ptr<Component>> m_component;

	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
public:
	void Update()
	{
		for (auto& c : m_component)
		{
			c->Update();
		}
	}

	void Render()
	{
		for (auto& c : m_component)
		{
			c->Render();
		}
	}

	bool IsActive() { return m_isActivate; }
	void Destroy() { m_isActivate = false; }

	template <typename T>
	bool HasComponent()const
	{
		return m_componentBitSet[GetComponentTypeID<T>];
	}

	template <typename T,typename...TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->_entity = this;
		std::unique_ptr<Component> uPtr{ c };
		m_component.emplace_back(std::move(uPtr));

		m_componentArray[GetComponentTypeID<T>()] = c;
		m_componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T>
	T& GetComponent() const
	{
		auto ptr(m_componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> m_entities;

public:
	void Update()
	{
		for (auto& e : m_entities)
		{
			e->Update();
		}
	}

	void Render()
	{
		for (auto& e : m_entities)
		{
			e->Render();
		}
	}

	void Relese()
	{
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->IsActive();
			}),
			std::end(m_entities));
	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{e};
		m_entities.emplace_back(std::move(uPtr));
		return *e;
	}
};