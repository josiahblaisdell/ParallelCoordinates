#pragma once
#include "DataManager.h"
#include "VisualizationWindow.h"
#include <vector>
namespace ParallelCoordinates {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form {
		public:
		MainWindow(void) {
			InitializeComponent();
			_Data.DataChanged += gcnew System::EventHandler(this, &ParallelCoordinates::MainWindow::OnDataChanged);
			_Data.DataChanged += gcnew System::EventHandler(this, &ParallelCoordinates::MainWindow::OnDataChanged_Click);
		}
		private: DataManager _Data;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
		private: System::Windows::Forms::ToolStripMenuItem^  createCoordVisualizationToolStripMenuItem;
		private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnX;
		private: System::Windows::Forms::DataGridViewTextBoxColumn^  ColumnY;
		private: System::Windows::Forms::ToolStripMenuItem^  createXyToolStripMenuItem;
				 array<System::String^> ^ColumnHeaders;
		protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow() {
			if(components) {
				delete components;
			}
		}

		private: System::Windows::Forms::MenuStrip^  menuStrip1;
		private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  dataToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  importToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  chartToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  createPToolStripMenuItem;
		private: System::Windows::Forms::MenuStrip^  menuStrip2;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  importDataToolStripMenuItem;
		private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
		private: System::Windows::Forms::DataGridView^  dataGridView1;
		private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		private: System::Void InitializeComponent() {
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->importDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createCoordVisualizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ColumnY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->createXyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem2,
					this->toolStripMenuItem1, this->toolStripMenuItem3
			});
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(1031, 24);
			this->menuStrip2->TabIndex = 0;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuItem4 });
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(37, 20);
			this->toolStripMenuItem2->Text = L"File";
			// 
			// toolStripMenuItem4
			// 
			this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
			this->toolStripMenuItem4->Size = System::Drawing::Size(92, 22);
			this->toolStripMenuItem4->Text = L"Exit";
			this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &MainWindow::exitAppToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->importDataToolStripMenuItem });
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(43, 20);
			this->toolStripMenuItem1->Text = L"Data";
			// 
			// importDataToolStripMenuItem
			// 
			this->importDataToolStripMenuItem->Name = L"importDataToolStripMenuItem";
			this->importDataToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control|System::Windows::Forms::Keys::I));
			this->importDataToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->importDataToolStripMenuItem->Text = L"Import Data";
			this->importDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::importDataToolStripMenuItem_Click);
			// 
			// toolStripMenuItem3
			// 
			this->toolStripMenuItem3->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->createCoordVisualizationToolStripMenuItem,
					this->createXyToolStripMenuItem
			});
			this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
			this->toolStripMenuItem3->Size = System::Drawing::Size(85, 20);
			this->toolStripMenuItem3->Text = L"Visualization";
			// 
			// createCoordVisualizationToolStripMenuItem
			// 
			this->createCoordVisualizationToolStripMenuItem->Name = L"createCoordVisualizationToolStripMenuItem";
			this->createCoordVisualizationToolStripMenuItem->Size = System::Drawing::Size(224, 22);
			this->createCoordVisualizationToolStripMenuItem->Text = L"Create ||-Coord Visualization";
			this->createCoordVisualizationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::createVisualizationWindow_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToOrderColumns = true;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ColumnX,
					this->ColumnY
			});
			this->dataGridView1->Location = System::Drawing::Point(26, 27);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(766, 537);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainWindow::dataGridView1_CellValueChanged);
			// 
			// ColumnX
			// 
			this->ColumnX->HeaderText = L"X";
			this->ColumnX->Name = L"ColumnX";
			// 
			// ColumnY
			// 
			this->ColumnY->HeaderText = L"Y";
			this->ColumnY->Name = L"ColumnY";
			// 
			// createXyToolStripMenuItem
			// 
			this->createXyToolStripMenuItem->Name = L"createXyToolStripMenuItem";
			this->createXyToolStripMenuItem->Size = System::Drawing::Size(224, 22);
			this->createXyToolStripMenuItem->Text = L"Create x-y Plot";
			this->createXyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::createXyToolStripMenuItem_Click);
			// 
			// MainWindow
			// 
			this->ClientSize = System::Drawing::Size(1031, 576);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->menuStrip2);
			this->MainMenuStrip = this->menuStrip2;
			this->Name = L"MainWindow";
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		private:
		System::Void importDataToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void exitAppToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void visualizationWindow_Closed(System::Object^  sender, System::EventArgs^  e);
		System::Void visualizationWindow_DataChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void createVisualizationWindow_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void OnDataChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void OnDataChanged_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void dataGridView1_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
		System::Void createXyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		List<VisualizationWindow^> ^_VisualizationWindows = gcnew List<VisualizationWindow^>();
		Void importFile(System::String ^file);
		
	};
}