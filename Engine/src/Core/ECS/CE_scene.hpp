#pragma once

namespace CyberEngine {
	class Scene : public System
	{
	private:
		std::vector<std::shared_ptr<SceneEntity>> entities;

	public:
		Scene() {
			entities = std::vector<std::shared_ptr<SceneEntity>>();
		}

		void AddEntity(std::shared_ptr<SceneEntity> entity) {
			entities.push_back(entity);
		}

		void Update() {
			for (auto& entity : entities) {
				entity->Update();
			}
		}

		void Render() {
			for (auto& entity : entities) {
				entity->Render();
			}
		}

		std::vector<std::shared_ptr<SceneEntity>> GetEntities() {
			return entities;
		}

		std::shared_ptr<SceneEntity> GetEntity(int index) {
			return entities[index];
		}

		void RemoveEntity(int index) {
			entities.erase(entities.begin() + index);
		}

		void RemoveEntity(std::shared_ptr<SceneEntity> entity) {
			entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		}

		void Clear() {
			entities.clear();
		}

		bool LoadScene(const cString& path);

		bool SaveScene(const cString& path);
	};
}

