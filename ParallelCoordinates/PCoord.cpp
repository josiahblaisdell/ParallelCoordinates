#include "PCoord.h"

using namespace System;
using namespace System::Windows::Forms;
#include<iostream>
#include<math.h>
#include<typeinfo>
#include<ctime>

double f(array<double, 2>^);
[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ParallelCoordinates::PCoordWindow Window;
	Application::Run(%Window);
	array<double, 2>^ a = gcnew array<double, 2>(10, 10);
	a[0, 0] = 5;
	std::cout << f(a);
	int x = 0;
}
double f(array<double, 2>^ b) {
	return b[0, 0] + 1;
}