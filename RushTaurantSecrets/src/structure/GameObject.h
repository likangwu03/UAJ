#pragma once
#include <list>

class Component;

class GameObject {
protected:
	std::list<Component*> components;
public:
	GameObject();
	virtual ~GameObject() { }

	void addComponent(Component* comp);
	
	template<typename Comp>
	Comp* getComponent() {
		auto i = components.begin();
		bool encontrado = false;
		while(i != components.end()) {
			// Si se encuentra el componente del tipo, se devuelve.
		}
	}
};