#pragma once
#include "../structure/Component.h"

#include "../utils/checkML.h"

using namespace std;

template<typename Comp>
class Manager : public Component {
	friend Comp;
private:
	static Comp* instance;
protected:
	Manager(GameObject* parent) : Component(parent, Comp::id) { }
public:
	template<typename ...Ts >
	static Comp* init(GameObject* parent, Ts&& ...args) {
		if(instance == nullptr) {
			instance = new Comp(parent, forward<Ts>(args)...);
		}
		return instance;
	}
	inline static Comp* get() { return instance; }

	Manager(Manager const&) = delete;
	virtual ~Manager() { }
};

template<typename Comp>
Comp* Manager<Comp>::instance = nullptr;