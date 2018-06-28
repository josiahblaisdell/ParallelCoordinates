#include "VisualizationWindow.h"
#include "ParallelPoint.h"
namespace ParallelCoordinates {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	Void VisualizationWindow::Render(System::Void) {
		// Clear the color and depth buffers.
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	Void VisualizationWindow::SwapOpenGLBuffers(System::Void) {
		SwapBuffers(m_hDC);
	}

	GLint VisualizationWindow::MySetPixelFormat(HDC hdc) {
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
			1,                                // version number 
			PFD_DRAW_TO_WINDOW|              // support window 
			PFD_SUPPORT_OPENGL|              // support OpenGL 
			PFD_DOUBLEBUFFER,                 // double buffered 
			PFD_TYPE_RGBA,                    // RGBA type 
			24,                               // 24-bit color depth 
			0, 0, 0, 0, 0, 0,                 // color bits ignored 
			0,                                // no alpha buffer 
			0,                                // shift bit ignored 
			0,                                // no accumulation buffer 
			0, 0, 0, 0,                       // accum bits ignored 
			32,                               // 32-bit z-buffer     
			0,                                // no stencil buffer 
			0,                                // no auxiliary buffer 
			PFD_MAIN_PLANE,                   // main layer 
			0,                                // reserved 
			0, 0, 0                           // layer masks ignored 
		};

		GLint  iPixelFormat;

		// get the device context's best, available pixel format match 
		if((iPixelFormat = ChoosePixelFormat(hdc, &pfd))==0) {
			MessageBox::Show("ChoosePixelFormat Failed");
			return 0;
		}

		// make that match the device context's current pixel format 
		if(SetPixelFormat(hdc, iPixelFormat, &pfd)==FALSE) {
			MessageBox::Show("SetPixelFormat Failed");
			return 0;
		}

		if((m_hglrc = wglCreateContext(m_hDC))==NULL) {
			MessageBox::Show("wglCreateContext Failed");
			return 0;
		}

		if((wglMakeCurrent(m_hDC, m_hglrc))==NULL) {
			MessageBox::Show("wglMakeCurrent Failed");
			return 0;
		}


		return 1;
	}
	Void VisualizationWindow::GraphicsPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {}
	Void VisualizationWindow::VisualizationWindow_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		MySetPixelFormat(m_hDC);
		int w = GraphicsPanel->Width;
		int h = GraphicsPanel->Height;
		glClearColor(1, 1, 1, 1);
		glShadeModel(GL_FLAT);
		//specify the coordinate system, defines how image gets mapped to screen
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);

		switch(_type) {
			case 0:
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.5, 20);
				gluOrtho2D(0, w, 0, h);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0, 0, 0);
				glLineWidth(1);
				for each (Axis^ Ax in Axes) {
					Ax->Draw();
				}
				for(int i = 0; i<_DataManager->RowCount; i++) {
					ParallelPoint ^p = gcnew ParallelPoint(_DataManager, i, d, GraphicsPanel->Location.X, GraphicsPanel->Height, GraphicsPanel->Width);
					p->Draw();
				}
				break;
			case 1:
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.5, 20);
				gluOrtho2D(0, w, h,0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(0, 0, 0);
				glLineWidth(1);
				for each (Axis^ Ax in Axes) {
					Ax->Draw();
				}
				glPointSize(10);
				glBegin(GL_POINTS);
					for(int i = 0; i<_DataManager->RowCount; i++) {
						
						ParallelPoint ^p = gcnew ParallelPoint(_DataManager, i, d, GraphicsPanel->Location.Y, GraphicsPanel->Height, GraphicsPanel->Width);
						glVertex3f(	System::Convert::ToDouble(_DataManager[i][0])*(w/prevw), System::Convert::ToDouble(_DataManager[i][1])*(h/prevh)-2*GraphicsPanel->Location.Y, 0);
					}
				glEnd();
				break;
		}
		
		SwapOpenGLBuffers();
	}
	void VisualizationWindow::CreateBox() {
		//color to use for drawing objects (white).
		glColor3f(0, 0, 0);
		//draw white polygon at (.25,.25,0) (.75,.75,0)
		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
			glVertex3f(12, 12, 0.0);
			glVertex3f(24, 12, 0.0);
			glVertex3f(24, 24, 0.0);
			glVertex3f(12, 24, 0.0);
			glVertex3f(12, 12, 0.0);
		glEnd();
	}
	void VisualizationWindow::DrawLine(array<Point>^ points) {
		glBegin(GL_LINE_STRIP);
			for(int i = 0; i<points->Length; i++) {
				glVertex2f(points[i].X,points[i].Y);
			}
		glEnd();
	}
	Void VisualizationWindow::VisualizationWindow_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		if(_DataManager->ColumnCount==2) {
			d = GraphicsPanel->Width - GraphicsPanel->Location.X;
		} else { d = GraphicsPanel->Width/_DataManager->ColumnCount-GraphicsPanel->Location.X; }
		
		Axes->Clear();
		//Draw the axes for each variable..
		switch(_type) {
			case 0:
				for(int i = 0; i< _DataManager->ColumnCount; i++) {
					Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y),
										 gcnew Point(GraphicsPanel->Location.X+i*d, GraphicsPanel->Location.Y+GraphicsPanel->Height),
										 d,
										 GraphicsPanel->Location.X));
				}
				break;
			case 1:
				Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X, -GraphicsPanel->Location.Y+GraphicsPanel->Height/2),
									 gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width, -GraphicsPanel->Location.Y+GraphicsPanel->Height/2),
									 -1,
									 GraphicsPanel->Location.X));
				Axes->Add(gcnew Axis(gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width/2, -2*GraphicsPanel->Location.Y+GraphicsPanel->Height),
									 gcnew Point(GraphicsPanel->Location.X+GraphicsPanel->Width/2, GraphicsPanel->Location.Y),
									 -1,
									 GraphicsPanel->Location.X));

				break;
		}
		
		Invalidate();
	}
	Void VisualizationWindow::OnDataChanged(System::Object^  sender, System::EventArgs^  e) {
		if(sender==this) { return; }
		Invalidate();
	}
	System::Void VisualizationWindow::GraphicsPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		List<String^>^ ps = _DataManager->Add();
		ps->Add(((e->X - GraphicsPanel->Location.X)*(Width/prevw)).ToString());
		ps->Add(((e->Y - GraphicsPanel->Location.Y)*(Height/prevh)).ToString());
		_DataManager->FireEvent(sender, e);
	}
	System::Void VisualizationWindow::GraphicsPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		List<String^>^ ps = _DataManager->Add();
		ps->Add(((e->X-GraphicsPanel->Location.X)*(Width/prevw)).ToString());
		ps->Add(((e->Y-GraphicsPanel->Location.Y)*(Height/prevh)).ToString());
		_DataManager->FireEvent(sender, e);
	}
	System::Void VisualizationWindow::GraphicsPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if(e->Button!=System::Windows::Forms::MouseButtons::None) {
			List<String^>^ ps = _DataManager->Add();
			ps->Add(((e->X-GraphicsPanel->Location.X)*(Width/prevw)).ToString());
			ps->Add(((e->Y-GraphicsPanel->Location.Y)*(Height/prevh)).ToString());
			_DataManager->FireEvent(sender, e);
		} else { return; }
		_DataManager[_DataManager->RowCount-1][0]->Remove(0);
	}
}