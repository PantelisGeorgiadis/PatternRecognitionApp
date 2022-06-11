#if !defined(AFX_BISECTOR_H__C591136A_F063_451F_BB50_2D194B8AF92B__INCLUDED_)
#define AFX_BISECTOR_H__C591136A_F063_451F_BB50_2D194B8AF92B__INCLUDED_

class CBisector  
{
public:
	CBisector();
	virtual ~CBisector();

	void CalculateBisector (int x_line_start, int y_line_start, int x_line_end, int y_line_end, int iUpExtend, int iDownExtend);
	int GetBisectorXStart (void) { return x_bisect_start; }
	int GetBisectorYStart (void) { return y_bisect_start; }
	int GetBisectorXEnd (void) { return x_bisect_end; }
	int GetBisectorYEnd (void) { return y_bisect_end; }

protected:

	int x_bisect_start;
	int y_bisect_start;
	int x_bisect_end;
	int y_bisect_end;

};

#endif 
