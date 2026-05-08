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

	string GetName();
	void ChangeParent(Entity* new_parent);

    virtual void Look();

    // Attributes-------------
    EntityType type;
    string name;
    string description;
    Entity* parent;
    list<Entity*> contains;
};