#pragma once
namespace ParallelCoordinates {
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Linq;
	public ref class DataManager {
		public:
		event EventHandler^ DataChanged;
		void FireEvent(Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e) {
			DataChanged(sender, e);
		}
		void FireEvent(Object ^sender, System::Windows::Forms::MouseEventArgs ^e) {
			DataChanged(sender, e);
		}
		List<String^>^ operator[](int i) {
			if(i>=_Data->Count || i < 0) {
				return nullptr;
			}
			_max->Clear();
			_min->Clear();
			return _Data[i];
		}
		List<String^>^ Add() {
			List<String^>^ temp = gcnew List<String^>();
			_Data->Add(temp);
			_max->Clear();
			_min->Clear();
			return temp;
		}
		Void Clear() {
			_Data->Clear();
		}
		property int RowCount{ int get(){return _Data->Count; } }
		property int ColumnCount { int get() { return _Data->Count == 0 ? 2 : _Data[0]->Count; } }
		double Max(int ColNum) { 
			if(ColNum>=ColumnCount) {
				return System::Double::NaN;
			}
			if(_max->Count <= ColNum || System::Double::IsNaN(_max[ColNum])) {
				while(_max->Count<=ColNum) {
					_max->Add(Double::NaN);
				}
				double prevmax = -Double::MaxValue;
				for(int i = 0; i<RowCount; i++) {
					double d = 0;
					List<String^>^ l = _Data[i];
					String^ s = l[ColNum];
					if(Double::TryParse(s, d)) {
						if(d>prevmax) {
							prevmax = d;
						}
					}
				}
				_max[ColNum] = prevmax;
				return prevmax;
			} else { 
				return _max[ColNum]; 
			} 
		}
		double Min(int ColNum) {
			if(ColNum>=ColumnCount) {
				return System::Double::NaN;
			}
			if(_min->Count<=ColNum||System::Double::IsNaN(_min[ColNum])) {
				while(_min->Count<=ColNum) {
					_min->Add(Double::NaN);
				}
				double prevmin = Double::MaxValue;
				for(int i = 0; i<RowCount; i++) {
					double d = 0;
					List<String^>^ l = _Data[i];
					String^ s = l[ColNum];
					if(Double::TryParse(s, d)) {
						if(d<prevmin) {
							prevmin = d;
						}
					}
				}
				_min[ColNum] = prevmin;
				return prevmin;
			} else {
				return _min[ColNum];
			}
		}
		private: List<List<String^>^> ^_Data = gcnew List<List<String^>^>();
				 List<double> ^_max = gcnew List<double>();
				 List<double> ^_min = gcnew List<double>();
	};
}