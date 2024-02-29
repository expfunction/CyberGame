#pragma once

namespace CyberEngine {

	// ECS component
	class Component
	{
	public:
		CUID id;
		cString name;

		Component() {
			id = UUIDv4::UUIDGenerator<std::mt19937_64>().getUUID();
			name = "Default Component";
			OnCreate();
		};

		~Component() = default;

		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};

	// Entity class for ECS
	class Entity
	{
	public:
		CUID id;
		cString name;

		Entity() {
			id = UUIDv4::UUIDGenerator<std::mt19937_64>().getUUID();
			name = "Default Entity";
			OnCreate();
		}

		~Entity() = default;

		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};

	// ECS system for updating entities and components
	class System
	{
	private:
		// ECS system for updating entities and components
		entt::registry registry;

	public:
		System() = default;
		~System() = default;

		// Update system
		void Update() {
			registry.view<Component>().each([](auto& component) {
				component.OnUpdate();
			});
		}

		// Render system
		void Render() {
			registry.view<Component>().each([](auto& component) {
				component.OnRender();
			});
		}

		// Add entity to system
		template<typename T>
		void AddEntity(T& entity) {
			registry.emplace<T>(entity);
		}

		// Get entity from system
		template<typename T>
		void GetEntity(T& entity) {
			registry.get<T>(entity);
		}

		// Remove entity from system
		template<typename T>
		void RemoveEntity(T& entity) {
			registry.remove<T>(entity);
		}

		// Add component to entity
		template<typename T>
		void AddComponent(Entity& entity, T& component) {
			registry.emplace<T>(entity, component);
		}

		// Remove component from entity
		template<typename T>
		void RemoveComponent(Entity& entity) {
			registry.remove<T>(entity);
		}

		// Get component from entity
		template<typename T>
		T& GetComponent(Entity& entity) {
			return registry.get<T>(entity);
		}

		// Get all entities with component
		template<typename T>
		std::vector<Entity> GetEntities() {
			std::vector<Entity> entities;
			for (auto entity : registry.view<T>()) {
				entities.push_back(entity);
			}
			return entities;
		}

		// Get all entities with component
		template<typename T>
		std::vector<Component> GetComponents() {
			std::vector<Component> components;
			for (auto component : registry.view<T>()) {
				components.push_back(component);
			}
			return components;
		}
	};
}