#include "stdafx.h"
#include "Bisector.h"

CBisector::CBisector()
{

	x_bisect_start = 0;
	y_bisect_start = 0;
	x_bisect_end = 0;
	y_bisect_end = 0;

}

CBisector::~CBisector()
{

}

void CBisector::CalculateBisector (int x_line_start, int y_line_start, int x_line_end, int y_line_end, int iUpExtend, int iDownExtend){

	double cross_x = (x_line_end + x_line_start) / 2;
	double cross_y = (y_line_end + y_line_start) / 2;

	double y_change = y_line_end - y_line_start;
	double x_change = x_line_end - x_line_start;
	double slope = y_change / x_change;
	double bisect_slope = - (1 / slope);

	y_bisect_start = (int)(cross_y - iUpExtend);
	x_bisect_start = int(((y_bisect_start - cross_y) / (bisect_slope)) + cross_x);

	y_bisect_end = (int)(cross_y + iDownExtend);
	x_bisect_end = (int)(((y_bisect_end - cross_y) / (bisect_slope)) + cross_x);

}
