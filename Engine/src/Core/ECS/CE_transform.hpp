#pragma once

namespace CyberEngine
{
class Transform : public Component
    {
	private:
		cVec3 position;
		cVec3 rotation;
		cVec3 scale;

    public:
		Transform();
		Transform(const Transform& other);
		~Transform() = default;

		void SetPosition(const cVec3& position) { this->position = position;}
		void SetRotation(const cVec3& rotation) { this->rotation = rotation;}
		void SetScale(const cVec3& scale)		{ this->scale = scale;		}
		const cVec3& GetPosition() const		{ return position; }
		const cVec3& GetRotation() const		{ return rotation; }
		const cVec3& GetScale() const			{ return scale;	}

		// Operators
		Transform& operator=(const Transform& other) {
			position = other.position;
			rotation = other.rotation;
			scale = other.scale;
			return *this;
		}

		Transform operator=(const Transform& other) const {
			Transform temp;
			temp.position = other.position;
			temp.rotation = other.rotation;
			temp.scale = other.scale;
			return temp;
		}
    };
}