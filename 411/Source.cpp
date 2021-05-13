#include "Application.h"
#include <iostream>

int main() {
	Application app;
	app.BuildTree();
	return app.Execute();
}
