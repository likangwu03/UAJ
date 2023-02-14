#pragma once
#include "../structure/Component.h"

template<typename Comp>
class Manager : public Component {
private:
	static Comp* instance;
protected:
	Manager(GameObject* parent) : Component(parent, Comp::id) { }
public:
	static Comp* init(GameObject* parent) {
		if(instance == nullptr) {
			instance = new Comp(parent);
		}
		return instance;
	}
	inline static Comp* get() { return instance; }

	Manager(Manager const&) = delete;
	virtual ~Manager() { }
};

template<typename Comp>
Comp* Manager<Comp>::instance = nullptr;