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
void Entity::ChangeParent(Entity* new_parent) {
	if (parent != nullptr) {
		parent->contains.remove(this);
	}
	parent = new_parent;
	if (new_parent != nullptr) {
		new_parent->contains.push_back(this);
	}
}

//--------------------------------------
void Entity::Look() {}