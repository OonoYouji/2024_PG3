#include <stdio.h>
#include <vector>
#include <functional>

class A {
public:
	void Show() {
		printf("A::Show()\n");
	}
};

class B {
public:
	void Demo() {
		printf("B::Demo()\n");
	}
};

class C {
public:
	void Show() {
		printf("C::Show()\n");
	}
};

template<class T>
concept Showable = requires(T t) {
	t.Show();
};

class ShowManager {
	std::vector<std::function<void()>> funcs_;

public:
	void Add(Showable auto* obj) {
		funcs_.push_back([obj]() { obj->Show(); });
	}

	void CallAll() {
		for (auto& f : funcs_) f();
	}
};


int main() {
	ShowManager manager;

	A a;
	B b;
	C c;

	manager.Add(&a);
	manager.Add(&b);
	manager.Add(&c);

	manager.CallAll();

	return 0;
}


