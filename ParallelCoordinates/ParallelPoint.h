#pragma once
#include "Axis.h"
namespace ParallelCoordinates {
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Drawing;


	public ref class ParallelPoint {
		public:
		ParallelPoint(DataManager^ data,int i, double dist, double offset, int height, int width);
		//A parallel point is a list of points indexed by dimension.
		List<PointF> _Points;
		double _d;
		double _offset;
		int _Height;
		int _Width;
		Void Draw();
		//double Scale(double x, double height, double width);
	};
}

