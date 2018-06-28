#pragma once
#include<Windows.h>
#include "MainWindow.h"
using namespace System;
using namespace System::Windows::Forms;
#include<iostream>
#include<math.h>
#include<typeinfo>
#include<ctime>
[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ParallelCoordinates::MainWindow Window;
	Application::Run(%Window);
}