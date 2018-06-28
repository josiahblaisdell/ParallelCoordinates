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
	using namespace System::Collections::Generic;

	public ref class VisualizationWindow : public System::Windows::Forms::Form {
		public: VisualizationWindow(DataManager ^datamanager, Form ^parentform, GLsizei iWidth, GLsizei iHeight, int type) {
			InitializeComponent();
			_DataManager = datamanager;
			_type = type;
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
			
			m_hDC = GetDC((HWND)this->Handle.ToPointer());
			Axes = gcnew List<Axis^>();
			//Draw the axes for each variable..
			//switch(type) {
			//	//Graphics panel is a parallel coordinates plot.
			//	case 0:
			//		for(int i = 0; i<_DataManager->ColumnCount; i++) {
			//			Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y),
			//								 gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y+GraphicsPanel->Height),
			//								 d,
			//								 GraphicsPanel->Location.X));
			//		}
			//		break;
			//		//Graphics panel is an x-y plot.
			//	case 1:
			//		Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X, GraphicsPanel->Location.Y+GraphicsPanel->Height/2),
			//							 gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width, GraphicsPanel->Location.Y+GraphicsPanel->Height/2),
			//							 -1,
			//							 GraphicsPanel->Location.X));
			//		Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width/2, GraphicsPanel->Location.Y+GraphicsPanel->Height),
			//							 gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width/2, GraphicsPanel->Location.Y),
			//							 -1,
			//							 GraphicsPanel->Location.X));
			//		break;

			//}
			VisualizationWindow_SizeChanged(nullptr, nullptr);
			prevw = GraphicsPanel->Width;
			prevh = GraphicsPanel->Height;

		}
				GLint MySetPixelFormat(HDC hdc);
				GLint iPixelFormat;
				void CreateBox();
				void DrawLine(array<Point>^ points);
				List<Axis^>^ Axes;
				//InterAxis Distance
				double d;
		private: DataManager^_DataManager;
				 int _type;
				 double prevw;
				 double prevh;
				 #pragma region Windows Form Designer generated code
				 /// <summary>
				 /// Required method for Designer support - do not modify
				 /// the contents of this method with the code editor.
				 /// </summary>
				 void InitializeComponent(void) {
					 this->GraphicsPanel = (gcnew System::Windows::Forms::Panel());
					 this->SuspendLayout();
					 // 
					 // GraphicsPanel
					 // 
					 this->GraphicsPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top|System::Windows::Forms::AnchorStyles::Bottom)
																									   |System::Windows::Forms::AnchorStyles::Left)
																									  |System::Windows::Forms::AnchorStyles::Right));
					 this->GraphicsPanel->BackColor = System::Drawing::Color::Transparent;
					 this->GraphicsPanel->Location = System::Drawing::Point(12, 12);
					 this->GraphicsPanel->Name = L"GraphicsPanel";
					 this->GraphicsPanel->Size = System::Drawing::Size(314, 264);
					 this->GraphicsPanel->TabIndex = 0;
					 this->GraphicsPanel->Visible = false;
					 this->GraphicsPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VisualizationWindow::GraphicsPanel_Paint);
					 this->GraphicsPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseDown);
					 this->GraphicsPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseMove);
					 this->GraphicsPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseUp);
					 // 
					 // VisualizationWindow
					 // 
					 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 this->ClientSize = System::Drawing::Size(338, 288);
					 this->Controls->Add(this->GraphicsPanel);
					 this->Name = L"VisualizationWindow";
					 this->Text = L"VisualizationWindow";
					 this->SizeChanged += gcnew System::EventHandler(this, &VisualizationWindow::VisualizationWindow_SizeChanged);
					 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VisualizationWindow::VisualizationWindow_Paint);
					 this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseDown);
					 this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseMove);
					 this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &VisualizationWindow::GraphicsPanel_MouseUp);
					 this->ResumeLayout(false);

				 }
				 #pragma endregion
		private: virtual System::Void Render(System::Void);
				 System::Void SwapOpenGLBuffers(System::Void);
				 HDC m_hDC;
				 System::Windows::Forms::Panel^  GraphicsPanel;
				 System::ComponentModel::IContainer^  components;
				 HGLRC m_hglrc;
		private: System::Void GraphicsPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
				 System::Void VisualizationWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
				 System::Void VisualizationWindow_SizeChanged(System::Object^  sender, System::EventArgs^  e);
				 System::Void OnDataChanged(System::Object^  sender, System::EventArgs^  e);
				 System::Void GraphicsPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
				 System::Void GraphicsPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
				 System::Void GraphicsPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		protected: ~VisualizationWindow(System::Void) {
			this->DestroyHandle();
		}
};
}
