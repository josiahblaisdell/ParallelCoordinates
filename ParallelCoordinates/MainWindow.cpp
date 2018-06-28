#pragma once
#include<Windows.h>
#include "MainWindow.h"
#include "VisualizationWindow.h"

namespace ParallelCoordinates {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	Void MainWindow::importDataToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if(openFileDialog1->ShowDialog()==System::Windows::Forms::DialogResult::OK) {
			importFile(openFileDialog1->FileName);
		}

	}
	Void MainWindow::exitAppToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	Void MainWindow::visualizationWindow_Closed(System::Object^  sender, System::EventArgs^  e) {
		_VisualizationWindows->Remove((VisualizationWindow^)sender);
	}
	Void MainWindow::visualizationWindow_DataChanged(System::Object^  sender, System::EventArgs^  e) {
		// The data was changed by the vis window, I will update myself here.
	}
	Void MainWindow::createVisualizationWindow_Click(System::Object^  sender, System::EventArgs^  e) {
		if(dataGridView1->ColumnCount==0) {
			MessageBox::Show("You must import some data.");
			return;
		}
		VisualizationWindow ^visualizationWindow = gcnew ParallelCoordinates::VisualizationWindow(%_Data, this, 100, 100,0);
		visualizationWindow->Closed += gcnew System::EventHandler(this, &MainWindow::visualizationWindow_Closed);
		visualizationWindow->Show();
		_VisualizationWindows->Add(visualizationWindow);
		/*if(!_VisualizationWindow) {
			_VisualizationWindow = gcnew ParallelCoordinates::VisualizationWindow(%_Data, this, 100, 100);
			_VisualizationWindow->Closed += gcnew System::EventHandler(this, &MainWindow::visualizationWindow_Closed);
			_VisualizationWindow->Show();
		} else if(!_VisualizationWindow->Visible) {
			_VisualizationWindow->Show();
		} else { _VisualizationWindow->Focus(); }*/

	}
	Void MainWindow::createXyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		VisualizationWindow ^visualizationWindow = gcnew ParallelCoordinates::VisualizationWindow(%_Data, this, 100, 100, 1);
		visualizationWindow->Closed += gcnew System::EventHandler(this, &MainWindow::visualizationWindow_Closed);
		visualizationWindow->Show();
		_VisualizationWindows->Add(visualizationWindow);
	}
	Void MainWindow::OnDataChanged(System::Object^  sender, System::EventArgs^  e) {
		//do something
	}
	System::Void MainWindow::OnDataChanged_Click(System::Object^  sender, System::EventArgs^  e) {
		if(sender==this) { return; }
		int rownum = dataGridView1->Rows->Add(1);
		dataGridView1->Rows[rownum]->Cells[0]->Value = ((System::Windows::Forms::MouseEventArgs^)e)->X.ToString();
		dataGridView1->Rows[rownum]->Cells[1]->Value = ((System::Windows::Forms::MouseEventArgs^)e)->Y.ToString();
		dataGridView1->ResetBindings();
		dataGridView1->Refresh();
	}
	Void MainWindow::dataGridView1_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		List<String^> ^row = _Data[e->RowIndex];
		//If rowindex < 0, then this is the header.
		if(e->RowIndex<0) {
			return;
		}
		int i = e->RowIndex;
		//if row is nullptr
		if(!row) {
			row = _Data.Add();
		}
		while(row->Count<dataGridView1->ColumnCount) {
			row->Add("0");
		}
		row[e->ColumnIndex] = dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
		_Data.FireEvent(this, e);
	}
	void MainWindow::importFile(System::String ^file) {
		array<System::String^> ^contents = System::IO::File::ReadAllLines(file);
		_Data.Clear();
		//for each (DataGridViewRow^ R in dataGridView1->Rows) {
		//	dataGridView1->Rows->Remove(R);
		//}
		//dataGridView1->ResetBindings();
		//dataGridView1->Refresh();
		while(dataGridView1->ColumnCount>0) {
			dataGridView1->Columns->Remove(dataGridView1->Columns[0]);
		}
		dataGridView1->ResetBindings();
		dataGridView1->Refresh();
		bool firstline = true;
		for each (String^ line in contents) {
			array<System::String^> ^values = line->Split(',', '\t');
			if(firstline) {
				ColumnHeaders = values;
				for each (String^ s in values) {
					dataGridView1->Columns->Add(s, s);
				}
				firstline = false;
				continue;
			}

			int rownum = dataGridView1->Rows->Add(1);
			List<String^>^ row = _Data.Add();
			for(int i = 0; i<values->Length; i++) {
				dataGridView1->Rows[rownum]->Cells[i]->Value = values[i];
				row->Add(values[i]);
			}
		}
	}

}