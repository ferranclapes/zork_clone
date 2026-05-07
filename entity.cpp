#include "entity.h"

//--------------------------------------
Entity::Entity(const char* name, const char* description, Entity* parent = nullptr) {
	this->name = name;
	this->description = description;
	this->parent = parent;
	
	type = ENTITY;

	if (parent != nullptr) {
		parent->contains.push_back(this);
	}
}

//--------------------------------------
Entity:: ~Entity() {
}

//--------------------------------------
string Entity::GetName() {
	return name;
}

//--------------------------------------
void Entity::Look() {}