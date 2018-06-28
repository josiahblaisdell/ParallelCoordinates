#include <Windows.h>
#include "VisualizationWindow.h"
#include "Axis.h"
#include <GL/GL.h>


namespace ParallelCoordinates {
	Axis::Axis(Point^ p, Point^ q, double dist, double offset) {
		_p1 = *p;
		_p2 = *q;
		_d = dist;
		//The x coordinate of the left most point in the panel the Parallel Coordinates Visualization is drawn.
		_offset = offset;
	}
	Void Axis::Draw() {
		glBegin(GL_LINE_STRIP);
			glVertex3f(_p1.X, _p1.Y, 0.0);
			glVertex3f(_p2.X, _p2.Y, 0.0);
		glEnd();

	}
	Void Axis::Move(double dx, double dy) {

	}
}
