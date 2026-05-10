#include "entity.h"
#include "exit.h"

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
	if (parent != nullptr) {
		parent->RemoveContainedEntity(this);
	}
	while (!contains.empty()) {
		Entity* e = contains.front();
		contains.pop_front();
		if (e->GetType() == EXIT) {
			Exit* exit = (Exit*)e;
			if (exit->GetParent() == this) {
				exit->ChangeParent(nullptr);
			}
			else {
				exit->RemoveDestination();
			}
		}
		else {
			e->ChangeParent(nullptr);
		}
	}
	contains.clear();
}

//--------------------------------------
void Entity::Update() {}

//--------------------------------------
string Entity::GetName() {
	return name;
}

//--------------------------------------
string Entity::GetDescription() {
	return description;
}

//--------------------------------------
void Entity::AddContainedEntity(Entity* entity) {
	contains.push_back(entity);
}

//--------------------------------------
void Entity::RemoveContainedEntity(Entity* entity) {
	contains.remove(entity);
}

//--------------------------------------
void Entity::ChangeParent(Entity* new_parent) {
	if (parent != nullptr) {
		parent->RemoveContainedEntity(this);
	}
	parent = new_parent;
	if (new_parent != nullptr) {
		new_parent->AddContainedEntity(this);
	}
}

//--------------------------------------
void Entity::Look() {}