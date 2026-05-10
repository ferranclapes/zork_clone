#pragma once

#include <string>
#include <list>

using namespace std;

enum EntityType {
    ENTITY,
    ROOM,
    EXIT,
    ITEM,
    CREATURE,
    PLAYER
};

class Entity {
public:
    // Methods-------------
    Entity(const char* name, const char* description, Entity* parent);
    virtual ~Entity();
	void SetType(EntityType type) { this->type = type; }

    virtual void Update();

	void ChangeParent(Entity* new_parent);
	void AddContainedEntity(Entity* entity);
	void RemoveContainedEntity(Entity* entity);

    virtual void Look();

	EntityType GetType() { return type; }
    string GetName();
	string GetDescription();
	Entity* GetParent() { return parent; }
	const list<Entity*>& GetContains() { return contains; }
    // Attributes-------------
protected:
    EntityType type;
    string name;
    string description;
    Entity* parent;
    list<Entity*> contains;
};