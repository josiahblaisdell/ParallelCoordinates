#pragma once
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include "DataManager.h"
#include "Axis.h"

namespace ParallelCoordinates {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DrawingForm
	/// </summary>
	public ref class DrawingForm : public System::Windows::Forms::Form
	{
	public:
		DrawingForm(DataManager ^datamanager, Form ^parentform, GLsizei iWidth, GLsizei iHeight)
		{
			InitializeComponent();
			_DataManager = datamanager;
			datamanager->DataChanged += gcnew System::EventHandler(this, &ParallelCoordinates::VisualizationWindow::OnDataChanged);
			// Set the position on the form
			this->CreateParams->X = iWidth;
			this->CreateParams->Y = iHeight;
			this->CreateParams->Height = iWidth;
			this->CreateParams->Width = iHeight;
			// Specify the form as the parent.
			this->CreateParams->Parent = parentform->Handle;
			// Create as a child of the specified parent and make OpenGL compliant (no clipping)
			this->CreateParams->Style = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
			d = GraphicsPanel->Width/_DataManager->ColumnCount;
			m_hDC = GetDC((HWND)this->Handle.ToPointer());
			if(m_hDC)
				MySetPixelFormat(m_hDC);
			Axes = gcnew List<Axis^>();
			//Draw the axes for each variable..
			for(int i = 0; i< _DataManager->ColumnCount; i++) {
				Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y),
									 gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y+GraphicsPanel->Height),
									 d,
									 GraphicsPanel->Location.X));
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DrawingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = L"DrawingForm";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
