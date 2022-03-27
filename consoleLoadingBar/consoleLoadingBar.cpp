#include <iostream>
#include "../loadingBarConsole/loadingBarConsole.h"
#include <thread>
#include <chrono>

void rengine(CloadingBarConsole* c, bool* ok) {
	while (*ok){
		c->render();//RENDER THE BAR
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

int main()
{
	std::cout << "LOADING SOMETHING" << std::endl;
	CloadingBarConsole l;
	bool sok = true;
	std::thread renderer(rengine, &l, &sok);
	for (int x = 0; x <= 100; x++) {
		if (x <= 40)
			l.setColorCode(//SET COLOR CODE
				x < 20 ?
				colorcode::CANCEL : x == 40 ?
				colorcode::OK : colorcode::SUSPEND
			);
		l.setPercent(x);//SET PERCENT VALUE
		std::this_thread::sleep_for(std::chrono::milliseconds(x < 40 ? 1500 : 900));
	}
	sok = false;
	renderer.join();
}
