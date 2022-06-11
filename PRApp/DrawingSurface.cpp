#include "stdafx.h"
#include "DrawingSurface.h"

CDrawingSurface::CDrawingSurface()
{

	m_iWidth = 0;
	m_iHeight = 0;
	m_DrawingBuffer = NULL;
	m_DrawingDataSet = NULL;
	m_nMinX = 0.0f;
	m_nMaxX = 0.0f;
	m_nMinY = 0.0f;
	m_nMaxY = 0.0f;
	m_iXFeatureIndex = 0;
	m_iYFeatureIndex = 1;

}

CDrawingSurface::CDrawingSurface(int iDimension)
{

	m_DrawingDataSet = NULL;
	m_nMinX = 0.0f;
	m_nMaxX = 0.0f;
	m_nMinY = 0.0f;
	m_nMaxY = 0.0f;
	m_iXFeatureIndex = 0;
	m_iYFeatureIndex = 1;
	CreateDrawingSurface(iDimension);

}

CDrawingSurface::~CDrawingSurface()
{

	DeleteDrawingSurface();

}

void CDrawingSurface::CreateDrawingSurface (int iDimension){

	m_iWidth = iDimension;
	m_iHeight = iDimension;

	m_DrawingBuffer = new CDataMatrix2D(m_iHeight, m_iWidth);
	m_DrawingDataSet = new CDataSet();

	ClearDrawingSurface();

}

void CDrawingSurface::ClearDrawingSurface (void){

	FillDrawingSurface(0xFF);

	if (m_DrawingDataSet){
		m_DrawingDataSet->RemoveAllClasses();
	}

	DrawFrame(0xFF);

}

void CDrawingSurface::DeleteDrawingSurface (void){

	if (m_DrawingBuffer){
		delete m_DrawingBuffer;
		m_DrawingBuffer = NULL;
	}

	if (m_DrawingDataSet){
		delete m_DrawingDataSet;
		m_DrawingDataSet = NULL;
	}

}

void CDrawingSurface::SaveDrawingSurfaceToBmpFile8 (char *szFileName){

	if (m_DrawingBuffer){
		m_DrawingBuffer->WriteMatrixDataToBMPFile8(szFileName);
	}

}

void CDrawingSurface::SetPixel (int x, int y, unsigned char ucTone){

	if (m_DrawingBuffer){
		m_DrawingBuffer->SetMatrixValue(y, x, (double)(ucTone));
	}

}

unsigned char CDrawingSurface::GetPixel (int x, int y){

	if (m_DrawingBuffer){
		return (unsigned char)(m_DrawingBuffer->GetMatrixValue(y, x));
	}

	return 0;

}

void CDrawingSurface::FillDrawingSurface (unsigned char ucTone){

	if (m_DrawingBuffer){
		for (int i=0;i<m_DrawingBuffer->GetNumberOfRows();i++){
			for (int j=0;j<m_DrawingBuffer->GetNumberOfColumns();j++){
				m_DrawingBuffer->SetMatrixValue(i, j, (double)(ucTone));
			}
		}
	}

}

void CDrawingSurface::DrawFrame (unsigned char ucTone){

	DrawLine(0, 0, (GetDrawingSurfaceWidth() - 1), 0, ucTone);
	DrawLine((GetDrawingSurfaceWidth() - 1), 0, (GetDrawingSurfaceWidth() - 1), (GetDrawingSurfaceHeight() - 1), ucTone);
	DrawLine(0, (GetDrawingSurfaceHeight() - 1), (GetDrawingSurfaceWidth() - 1), (GetDrawingSurfaceHeight() - 1), ucTone);
	DrawLine(0, (GetDrawingSurfaceHeight() - 1), 0, 0, ucTone);

}

void CDrawingSurface::DrawLine (int X0, int Y0, int X1, int Y1, unsigned char ucTone){

	DrawAntiAliasedLine(X0, Y0, X1, Y1, ucTone);

}

void CDrawingSurface::DrawSquare (int x, int y, unsigned char ucTone){

	DrawLine(x - SHAPE_SPAWN, y - SHAPE_SPAWN, x + SHAPE_SPAWN, y - SHAPE_SPAWN, ucTone);
	DrawLine(x + SHAPE_SPAWN, y - SHAPE_SPAWN, x + SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	DrawLine(x + SHAPE_SPAWN, y + SHAPE_SPAWN, x - SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	DrawLine(x - SHAPE_SPAWN, y + SHAPE_SPAWN, x - SHAPE_SPAWN, y - SHAPE_SPAWN, ucTone);

}
	
void CDrawingSurface::DrawTriangle (int x, int y, unsigned char ucTone){

	DrawLine(x, y - SHAPE_SPAWN, x - SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	DrawLine(x - SHAPE_SPAWN, y + SHAPE_SPAWN, x + SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	DrawLine(x + SHAPE_SPAWN, y + SHAPE_SPAWN, x, y - SHAPE_SPAWN, ucTone);

}

void CDrawingSurface::DrawAsterisk (int x, int y, unsigned char ucTone){
	
	DrawLine(x - SHAPE_SPAWN, y, x + SHAPE_SPAWN, y, ucTone);
	DrawLine(x, y - SHAPE_SPAWN, x, y + SHAPE_SPAWN, ucTone);
	DrawLine(x - SHAPE_SPAWN, y - SHAPE_SPAWN, x + SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	DrawLine(x + SHAPE_SPAWN, y - SHAPE_SPAWN, x - SHAPE_SPAWN, y + SHAPE_SPAWN, ucTone);
	
}

void CDrawingSurface::DrawCross (int x, int y, unsigned char ucTone){

	DrawLine(x - SHAPE_SPAWN, y, x + SHAPE_SPAWN, y, ucTone);
	DrawLine(x, y - SHAPE_SPAWN, x, y + SHAPE_SPAWN, ucTone);

}

void CDrawingSurface::DrawCircle (int x, int y, int r, unsigned char ucTone){

	short x1, y1, x2, y2;
	float dt = 5;

	for (float theta=0;theta<360;theta+=dt){
		x1 = (short)( r * cos(theta * 3.141593 / 180.0) + x);
		y1 = (short)(-r * sin(theta * 3.141593 / 180.0) + y);

		x2 = (short)( r * cos((theta + dt) * 3.141593 / 180.0) + x);
		y2 = (short)(-r * sin((theta + dt) * 3.141593 / 180.0) + y);
		
		DrawLine (x1, y1, x2, y2, ucTone);
	}
}

void CDrawingSurface::DrawAntiAliasedLine (int X0, int Y0, int X1, int Y1, unsigned char ucTone){

	unsigned short ErrorAdj;
    unsigned short ErrorAccTemp, Weighting;
    unsigned short ErrorAcc = 0; 
    unsigned char tb = 0, tb2 = 0;
	double grayb = 0.0f;
	unsigned char rr = 0;

	if (Y0 > Y1){
        int Temp = Y0; Y0 = Y1; Y1 = Temp;
        Temp = X0; X0 = X1; X1 = Temp;
    }
    
    SetPixel(X0, Y0, ucTone);
    
    int XDir, DeltaX = X1 - X0;
    if (DeltaX >= 0){
        XDir = 1;
    }
    else{
        XDir = -1;
        DeltaX = 0 - DeltaX;
    }
    
    int DeltaY = Y1 - Y0;
    if (DeltaY == 0){
        while (DeltaX-- != 0){
            X0 += XDir;
            SetPixel(X0, Y0, ucTone);
        }
        return;
    }
    if (DeltaX == 0){
        do{
            Y0++;
            SetPixel(X0, Y0, ucTone);
        } 
		while (--DeltaY != 0);
        return;
    }
    
    if (DeltaX == DeltaY){
        do{
            X0 += XDir;
            Y0++;
            SetPixel(X0, Y0, ucTone);
        } 
		while (--DeltaY != 0);
        return;
    }
    
    double grayl = ucTone * 0.299 + ucTone * 0.587 + ucTone * 0.114;
    
    if (DeltaY > DeltaX){
		ErrorAdj = (unsigned short)(((unsigned long) DeltaX << 16) / (unsigned long) DeltaY);
        while (--DeltaY) {
            ErrorAccTemp = ErrorAcc;   
            ErrorAcc += ErrorAdj;      
            if (ErrorAcc <= ErrorAccTemp){
                X0 += XDir;
            }
            Y0++; 
            Weighting = ErrorAcc >> 8;
            
            tb = GetPixel(X0, Y0);
            grayb = tb * 0.299 + tb * 0.587 + tb * 0.114;
            
            rr = (tb > ucTone ? ((unsigned char)(((double)(grayl<grayb?Weighting:(Weighting ^ 255))) / 255.0 * (tb - ucTone) + ucTone)) : ((unsigned char)(((double)(grayl<grayb?Weighting:(Weighting ^ 255))) / 255.0 * (ucTone - tb) + tb)));
            SetPixel(X0, Y0, rr);
            
            tb2 = GetPixel(X0 + XDir, Y0);
            grayb = tb2 * 0.299 + tb2 * 0.587 + tb2 * 0.114;
            
            rr = (tb2 > ucTone ? ((unsigned char)(((double)(grayl<grayb?(Weighting ^ 255):Weighting)) / 255.0 * (tb2 - ucTone) + ucTone)) : ((unsigned char)(((double)(grayl<grayb?(Weighting ^ 255):Weighting)) / 255.0 * (ucTone - tb2) + tb2)));
            SetPixel(X0 + XDir, Y0, rr);
        }
        SetPixel(X1, Y1, ucTone );
        return;
    }
    
	ErrorAdj = (unsigned short)(((unsigned long) DeltaY << 16) / (unsigned long) DeltaX);
    
	while (--DeltaX){
        ErrorAccTemp = ErrorAcc;   
        ErrorAcc += ErrorAdj;      
        if (ErrorAcc <= ErrorAccTemp){
            Y0++;
        }
        X0 += XDir; 
        Weighting = ErrorAcc >> 8;
        
        tb = GetPixel(X0, Y0 );
        grayb = tb * 0.299 + tb * 0.587 + tb * 0.114;
        
        rr = (tb > ucTone ? ((unsigned char)(((double)(grayl<grayb?Weighting:(Weighting ^ 255))) / 255.0 * (tb - ucTone) + ucTone)) : ((unsigned char)(((double)(grayl<grayb?Weighting:(Weighting ^ 255))) / 255.0 * (ucTone - tb) + tb)));
        
        SetPixel(X0, Y0, rr);
        
        tb = GetPixel(X0, Y0 + 1);
        grayb = tb * 0.299 + tb * 0.587 + tb * 0.114;
        
        rr = (tb > ucTone ? ((unsigned char)(((double)(grayl<grayb?(Weighting ^ 255):Weighting)) / 255.0 * (tb - ucTone) + ucTone)) : ((unsigned char)(((double)(grayl<grayb?(Weighting ^ 255):Weighting)) / 255.0 * (ucTone - tb) + tb)));

        SetPixel(X0, Y0 + 1, rr);
    }
    
	SetPixel(X1, Y1, ucTone);

}

void CDrawingSurface::AddClass (CClass *pClass){

	if (m_DrawingDataSet){
		CClass *Class = pClass->CopyClass();
		m_DrawingDataSet->AddClass(Class);
	}

}

void CDrawingSurface::SetXYFeatureIndex (int iXFeatureIndex, int iYFeatureIndex){

	m_iXFeatureIndex = iXFeatureIndex;
	m_iYFeatureIndex = iYFeatureIndex;

}

void CDrawingSurface::Render (void){

	int i, j;

	if (m_DrawingBuffer == NULL){
		return;
	}
	if (m_DrawingDataSet == NULL){
		return;
	}

	GetMinMaxX(EXTENSION_RATE);
	GetMinMaxY(EXTENSION_RATE);

	for (i=0;i<m_DrawingDataSet->GetNumberOfClasses();i++){
		for (j=0;j<m_DrawingDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			DrawPattern(m_DrawingDataSet->GetClass(i)->GetPattern(j), m_DrawingDataSet->GetClass(i)->GetClassShape());
		}
	}

}

CDataSet *CDrawingSurface::NormalizeDataSetToDrawingSurface (void){

	int i, j;
	int x, y;

	if (m_DrawingDataSet == NULL){
		return NULL;
	}

	GetMinMaxX(EXTENSION_RATE);
	GetMinMaxY(EXTENSION_RATE);

	CDataSet *NormalizedDataSet = new CDataSet();
	NormalizedDataSet = m_DrawingDataSet->CopyDataSet();

	for (i=0;i<NormalizedDataSet->GetNumberOfClasses();i++){
		for (j=0;j<NormalizedDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			x = XNormalizeToDrawingSurface(NormalizedDataSet->GetClass(i)->GetPattern(j)->GetFeature(m_iXFeatureIndex)->GetFeatureValue());
			y = GetDrawingSurfaceHeight() - YNormalizeToDrawingSurface(NormalizedDataSet->GetClass(i)->GetPattern(j)->GetFeature(m_iYFeatureIndex)->GetFeatureValue());

			NormalizedDataSet->GetClass(i)->GetPattern(j)->GetFeature(m_iXFeatureIndex)->SetFeatureValue(x);
			NormalizedDataSet->GetClass(i)->GetPattern(j)->GetFeature(m_iYFeatureIndex)->SetFeatureValue(y);
		}
	}

	return NormalizedDataSet;

}

void CDrawingSurface::DrawPattern (CPattern *pPattern, ClassShape cs){

	int x, y;

	x = XNormalizeToDrawingSurface(pPattern->GetFeature(m_iXFeatureIndex)->GetFeatureValue());
	y = GetDrawingSurfaceHeight() - YNormalizeToDrawingSurface(pPattern->GetFeature(m_iYFeatureIndex)->GetFeatureValue());
	
	switch (cs){
		case CLASSSHAPE_TRIANGLE:
			DrawTriangle(x, y, 0);
			break;
		case CLASSSHAPE_CIRCLE:
			DrawCircle(x, y, SHAPE_SPAWN, 0);
			break;
		case CLASSSHAPE_SQUARE:
			DrawSquare(x, y, 0);
			break;
		case CLASSSHAPE_ASTERISK:
			DrawAsterisk(x, y, 0);
			break;
		case CLASSSHAPE_CROSS:
			DrawCross(x, y, 0);
			break;
	}

}

void CDrawingSurface::GetMinMaxX (double dblExtensionRate){

	int j;
	double dbMinValue = 0.0;
	double dbMaxValue = 0.0;

	CClass *MergedClass = m_DrawingDataSet->MergeDataSet();

	dbMaxValue = MergedClass->GetPattern(0)->GetFeature(m_iXFeatureIndex)->GetFeatureValue();
	dbMinValue = MergedClass->GetPattern(0)->GetFeature(m_iXFeatureIndex)->GetFeatureValue();

	for (j=0;j<MergedClass->GetNumberOfPatterns();j++){
		if (MergedClass->GetPattern(j)->GetFeature(m_iXFeatureIndex)->GetFeatureValue() > dbMaxValue){
			dbMaxValue = MergedClass->GetPattern(j)->GetFeature(m_iXFeatureIndex)->GetFeatureValue();
		}
	}

	for (j=0;j<MergedClass->GetNumberOfPatterns();j++){
		if (MergedClass->GetPattern(j)->GetFeature(m_iXFeatureIndex)->GetFeatureValue() < dbMinValue){
			dbMinValue = MergedClass->GetPattern(j)->GetFeature(m_iXFeatureIndex)->GetFeatureValue();
		}
	}

	m_nMaxX = dbMaxValue + (dblExtensionRate * fabs(dbMaxValue - dbMinValue));
	m_nMinX = dbMinValue - (dblExtensionRate * fabs(dbMaxValue - dbMinValue));

	delete MergedClass;
	MergedClass = NULL;

}

void CDrawingSurface::GetMinMaxY (double dblExtensionRate){

	int j;
	double dbMinValue = 0.0;
	double dbMaxValue = 0.0;

	CClass *MergedClass = m_DrawingDataSet->MergeDataSet();

	dbMaxValue = MergedClass->GetPattern(0)->GetFeature(m_iYFeatureIndex)->GetFeatureValue();
	dbMinValue = MergedClass->GetPattern(0)->GetFeature(m_iYFeatureIndex)->GetFeatureValue();

	for (j=0;j<MergedClass->GetNumberOfPatterns();j++){
		if (MergedClass->GetPattern(j)->GetFeature(m_iYFeatureIndex)->GetFeatureValue() > dbMaxValue){
			dbMaxValue = MergedClass->GetPattern(j)->GetFeature(m_iYFeatureIndex)->GetFeatureValue();
		}
	}

	for (j=0;j<MergedClass->GetNumberOfPatterns();j++){
		if (MergedClass->GetPattern(j)->GetFeature(m_iYFeatureIndex)->GetFeatureValue() < dbMinValue){
			dbMinValue = MergedClass->GetPattern(j)->GetFeature(m_iYFeatureIndex)->GetFeatureValue();
		}
	}

	m_nMaxY = dbMaxValue + (dblExtensionRate * fabs(dbMaxValue - dbMinValue)); 
	m_nMinY = dbMinValue - (dblExtensionRate * fabs(dbMaxValue - dbMinValue));

	delete MergedClass;
	MergedClass = NULL;

}

int CDrawingSurface::XNormalizeToDrawingSurface(double x){

	return (int)((double)GetDrawingSurfaceWidth() * (x - m_nMinX) / (m_nMaxX - m_nMinX));

}

int CDrawingSurface::YNormalizeToDrawingSurface(double y){
	
	return (int)((double)GetDrawingSurfaceHeight() * (y - m_nMinY) / (m_nMaxY - m_nMinY));

}
