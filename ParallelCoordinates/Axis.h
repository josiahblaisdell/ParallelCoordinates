#pragma once
namespace ParallelCoordinates {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	public ref class Axis {
		public: Axis(Point^ p, Point^ q, double dist, double offset);
				Point _p1;
				Point _p2;
				Void Draw();
				Void Move(double dx, double dy);
				//interaxial distance.
				double _d;
				//the x coordinate of the left most point in the panel the ||-coord plot is drawn.
				double _offset;
				
	};
}
