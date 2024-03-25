#pragma once

namespace CyberEngine {
	struct SceneEntity : public Entity {
	private:
		Transform transform;
		std::vector<std::shared_ptr<Component>> components;
	public:	

SceneEntity() {
			transform = Transform();
		}

		SceneEntity(Transform transform) {
			this->transform = transform;
		}

		SceneEntity(Transform transform, std::vector<std::shared_ptr<Component>> components) {
			this->transform = transform;
			this->components = components;
		}

		void AddComponent(std::shared_ptr<Component> component) {
			components.push_back(component);
		}

		void Update() {
			for (auto& component : components) {
				component->OnUpdate();
			}
		}

		void Render() {
			for (auto& component : components) {
				component->OnRender();
			}
		}

		void SetTransform(Transform transform) {
			this->transform = transform;
		}

		Transform GetTransform() {
			return transform;
		}

		std::vector<std::shared_ptr<Component>> GetComponents() {
			return components;
		}
	};
}