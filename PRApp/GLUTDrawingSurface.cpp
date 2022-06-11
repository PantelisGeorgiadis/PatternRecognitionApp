#include "stdafx.h"
#include "GLUTDrawingSurface.h"

#ifdef USE_GLUT

CGLUTDrawingSurface *GLUTDrawingSurface = NULL;

CGLUTDrawingSurface::CGLUTDrawingSurface()
{

}

CGLUTDrawingSurface::CGLUTDrawingSurface(int iDimension, char *szWindowTitle)
{

	GLUTCreateDrawingSurface(iDimension, szWindowTitle);

}

CGLUTDrawingSurface::~CGLUTDrawingSurface()
{

}

void CGLUTDrawingSurface::GLUTCreateDrawingSurface (int iDimension, char *szWindowTitle){

	int argc = 1;
	char **argv = NULL;

	argv = (char**)malloc(sizeof(char*));
	argv[0] = (char*)malloc(sizeof(char));
	strcpy(argv[0], "\0");

	CreateDrawingSurface(iDimension);
	m_iWidth = iDimension;
	m_iHeight = iDimension;

	GLUTDrawingSurface = this;
	
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    
	free(argv[0]);
	free(argv);
	argv = NULL;

}

void CGLUTDrawingSurface::GLUTReshape(int w, int h){
    
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLUTDrawingSurface->m_iWidth = w;
	GLUTDrawingSurface->m_iHeight = h;
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

}

void CGLUTDrawingSurface::GLUTDisplay (void){

	glClear(GL_COLOR_BUFFER_BIT); 
    GLUTDrawingSurface->GLUTDrawScene();
    glFlush(); 

}

void CGLUTDrawingSurface::GLUTRender (void){

	glutInitWindowSize(GLUTGetDrawingSurfaceWidth(), GLUTGetDrawingSurfaceHeight());
    glutCreateWindow("PR");
	glClearColor(0.0, 0.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
	glutDisplayFunc(CGLUTDrawingSurface::GLUTDisplay);
	glutReshapeFunc(CGLUTDrawingSurface::GLUTReshape);

	glutMainLoop();

}

void CGLUTDrawingSurface::GLUTDrawScene (void){

	int i, j;

	if (GetDrawingDataSet() == NULL){
		return;
	}

	GetMinMaxX(EXTENSION_RATE);
	GetMinMaxY(EXTENSION_RATE);

	for (i=0;i<m_DrawingDataSet->GetNumberOfClasses();i++){
		for (j=0;j<m_DrawingDataSet->GetClass(i)->GetNumberOfPatterns();j++){
			GLUTDrawPattern(m_DrawingDataSet->GetClass(i)->GetPattern(j), m_DrawingDataSet->GetClass(i)->GetClassShape());
		}
	}

}

void CGLUTDrawingSurface::GLUTDrawPattern (CPattern *pPattern, ClassShape cs){

	double x, y;

	x = GLUTXNormalizeToDrawingSurface(pPattern->GetFeature(GetXFeatureIndex())->GetFeatureValue());
	y = GLUTYNormalizeToDrawingSurface(pPattern->GetFeature(GetYFeatureIndex())->GetFeatureValue());
	
	switch (cs){
		case CLASSSHAPE_TRIANGLE:
			GLUTDrawTriangle(x, y);
			break;
 		case CLASSSHAPE_CIRCLE:
 			GLUTDrawCircle(x, y, SHAPE_SPAWN);
 			break;
		case CLASSSHAPE_SQUARE:
			GLUTDrawSquare(x, y);
			break;
// 		case CLASSSHAPE_ASTERISK:
// 			DrawAsterisk(x, y, 0);
// 			break;
// 		case CLASSSHAPE_CROSS:
// 			DrawCross(x, y, 0);
// 			break;
	}

}

void CGLUTDrawingSurface::GLUTDrawTriangle (double x, double y){

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x - GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x - GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
    glEnd();

}

void CGLUTDrawingSurface::GLUTDrawSquare (double x, double y){

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x - GLUT_SHAPE_SPAWN, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
	glVertex2f(x - GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - GLUT_SHAPE_SPAWN, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y + GLUT_SHAPE_SPAWN);
	glVertex2f(x + GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
	glVertex2f(x - GLUT_SHAPE_SPAWN, y - GLUT_SHAPE_SPAWN);
    glEnd();

}

void CGLUTDrawingSurface::GLUTDrawCircle (double x, double y, double r){

	double vectorY1=y;
	double vectorX1=x;
	
	glBegin(GL_TRIANGLES);	
	for(int i=0;i<=360;i++){
		double angle = (((double)i) / 57.29577957795135);	
		double vectorX=x+(r*(float)sin((double)angle));
		double vectorY=y+(r*(float)cos((double)angle));		
		glVertex2d(x,y);
		glVertex2d(vectorX1,vectorY1);
		glVertex2d(vectorX,vectorY);
		vectorY1=vectorY;
		vectorX1=vectorX;	
	}
	glEnd();
}

double CGLUTDrawingSurface::GLUTXNormalizeToDrawingSurface(double x){

	return (double)((double)1.0f * (x - GetXMin()) / (GetXMax() - GetXMin()));

}

double CGLUTDrawingSurface::GLUTYNormalizeToDrawingSurface(double y){
	
	return (double)((double)1.0f * (y - GetYMin()) / (GetYMax() - GetYMin()));

}

#endif
