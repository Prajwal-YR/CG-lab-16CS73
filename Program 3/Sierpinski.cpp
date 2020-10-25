#include <GL\glew.h>
#include <GL\freeglut.h>
#include<iostream>
//#define M 5
typedef float point[3];
point tetra[4] = {
	{0,10,-10},
	{0,0,10},
	{10,-10,-10},
	{-10,-10,-10}
};
int M;
void draw_triangle(point a, point b, point c) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void draw_tetra(point a, point b, point c, point d) {
	glColor3f(0.0, 0.0, 0.0);
	draw_triangle(a, b, c);
	glColor3f(1.0, 0.0, 0.0);
	draw_triangle(a, c, d);
	glColor3f(0.0, 1.0, 0.0);
	draw_triangle(a, b, d);
	glColor3f(0.0, 0.0, 1.0);
	draw_triangle(b, c, d);
}
void divide_tetra(point a, point b, point c, point d, int i) {
	point v1, v2, v3, v4, v5, v6;
	if (i > 0) {
		for (int j = 0; j < 3; j++) {
			v1[j] = (a[j] + b[j]) / 2;
			v2[j] = (a[j] + c[j]) / 2;
			v3[j] = (a[j] + d[j]) / 2;
			v4[j] = (b[j] + c[j]) / 2;
			v5[j] = (b[j] + d[j]) / 2;
			v6[j] = (c[j] + d[j]) / 2;

		}
		divide_tetra(a, v1, v2, v3, i - 1);
		divide_tetra(v1, b, v4, v5, i - 1);
		divide_tetra(v2, v4, c, v6, i - 1);
		divide_tetra(v3, v5, v6, d, i - 1);

	}
	else
		draw_tetra(a, b, c, d);
}

void tetrahedron() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBegin(GL_TRIANGLES);
	divide_tetra(tetra[0], tetra[1], tetra[2], tetra[3], M);
	//glEnd();

	glFlush();
}

void myinit() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0, 0, 0, 1);
	glClearColor(1, 1, 1, 1);

	//glFlush();
	glOrtho(-12.0, 12.0, -12.0, 12.0, -12.0, 12.0);
}
int main(int argv, char** argc)
{
	std::cout << "Enter the number of iterations: ";
	//scanf_s("%d", &m);
	std::cin >> M;
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowPosition(100, 200);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Seirpinski Gasket");
	glutDisplayFunc(tetrahedron);
	glEnable(GL_DEPTH_TEST);
	myinit();
	glutMainLoop();
}