#include <Windows.h>
#include "DataManager.h"
#include "ParallelPoint.h"
#include <GL/GL.h>

namespace ParallelCoordinates {
	using namespace System::Collections::Generic;
	using namespace System::Drawing;
	ParallelPoint::ParallelPoint(DataManager^ data, int i, double dist, double offset, int height, int width) {
			_d = dist;
			_offset = offset;
			_Height = height;
			_Width = width;
		//i is the row, j is the column
		for(int j = 0; j<data->ColumnCount; j++) {
			double val;
			try {
				val = System::Convert::ToDouble(data[i][j]);
			} catch (Exception ^ex){
				throw gcnew Exception("Problem because the column is not a number it is a string or something.");
			}
			//double a = (height-_offset)/(data->Max(j)-data->Min(j));
			//double b = (height-offset)-a*data->Max(j);
			double newval;
			if(data->Max(j)==data->Min(j) || offset < 0) {
				newval = val;
			} else {
				newval = _offset+((_Height-_offset)-_offset)/(data->Max(j)-data->Min(j))*(val-data->Min(j));
			}
			

			_Points.Add(PointF(_offset+j*_d,newval));
		}
	}
	
	Void ParallelPoint::Draw() {
		glBegin(GL_LINE_STRIP);
			for each (PointF p in _Points) {
				glVertex2f(p.X, p.Y);
			}
		glEnd();
	}
}