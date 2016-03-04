#include <iostream>
#include <thread>

void foo1() {
	std::cout << "Hello" << std::endl;
}

void foo2() {
	std::cout << "Yo" << std::endl;
}

int main() {
	std::thread first(foo1);
	std::thread sec(foo2);
	
	std::cout << "LOL" << std::endl;

	first.join();
	sec.join();

	return 0;
	
}
