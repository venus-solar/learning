
// Simple GLFW example
// Copyright (c) Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//! [code]

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CH1 0
#define CH2 1
#define CH3 0
#define CH4 0
#define CH5 0
#define CH6 0
#define CH7 0
#define CH8 0
#define CH9 0
#define CH10 0
#define CH11 0
#define CH12 0
#define CH13 0
#define CH14 0
#define CH15 0

#define CH2_POINTS 0
#define CH2_LINES 0
#define CH2_LINE_STRIP 0
#define CH2_TRIANGLE 0
#define CH2_QUADS 0
#define CH2_CIRCLE 0
#define CH2_QUERY 0
#define CH2_POLY 0
#define CH2_BATCH 0
#define CH2_PRIMRESTART 0
#define CH2_BUFFER 0
#define CH2_VAO 1

#define PI 3.1415926535898
#define GL_TRUE 1
#define GL_FALSE 0



#if CH2
#if CH2_VAO
#define BUFFER_OFFSET(of) ((GLvoid *)NULL + of)
#define NumberOf(array) (sizeof(array) / sizeof (array[0]))
struct vec3 {
	GLfloat x, y, z;
};

struct XForm {
	struct vec3 xlate;
	GLfloat angle;
	struct vec3 axis;	
};

enum {Cube, Cone, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
struct XForm xform[NumVAOs] = {
	{{-4.0, 0.0, 0.0}, 0.0, {0.0, 1.0, 0.0}},
	{{0.0, 0.0, 0.0}, 0.0, {1.0, 0.0, 0.0}},
};

GLfloat Angle = 0.0;

enum {Vertices, Colors, Elements, NumVBOs};
GLuint buffers[NumVAOs][NumVBOs];

#endif
#endif


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void init()
{
#if CH2
#if CH2_PRIMRESTART
#define XStart -0.8
#define XEnd 0.8
#define YStart -0.8
#define YEnd 0.8
#define NumXPoints 11
#define NumYPoints 11
#define NumPoints (NumXPoints * NumYPoints)
#define NumPointsPerStrip (2 * NumXPoints)
#define NumStrips (NumYPoints - 1)
#define RestartIndex 0xffff
#define BUFFER_OFFSET(offset) ((GLubyte*) NULL + offset)

	GLuint vbo, ebo;
	GLfloat *vertices;
	GLushort *indices;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * NumPoints * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (vertices == NULL) {
		fprintf(stderr, "Unable to map vertex buffer\n");
		exit(EXIT_FAILURE);
	} else {
		int i, j;
		GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
		GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);
		GLfloat *tmp = vertices;

		for (j = 0; j < NumYPoints; j++) {
			GLfloat y = YStart + j * dy;
			for (i = 0; i < NumXPoints; i++) {
				GLfloat x = XStart + i * dx;
				*tmp++ = x;
				*tmp++ = y;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_VERTEX_ARRAY);
	}

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort), NULL, GL_STATIC_DRAW);
	indices = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	if (indices == NULL) {
		fprintf(stderr, "Unable to map index buffer\n");
	} else {
		int i, j;
		GLushort *index = indices;
		for (j = 0; j < NumStrips; j++) {
			GLushort bottomRow = j * NumYPoints;
			GLushort topRow = bottomRow + NumYPoints;
			for (i = 0; i < NumXPoints; i++) {
				*index++ = topRow + i;
				*index++ = bottomRow + i;
			}
			*index++ = RestartIndex;
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glPrimitiveRestartIndex(RestartIndex);
		glEnable(GL_PRIMITIVE_RESTART);
	}
#endif

#if CH2_QUERY
		GLboolean ret;
		ret = glIsEnabled(GL_LINE_STIPPLE);
		printf("line stipple mode is %s\n", (ret == GL_TRUE) ? "true" : "false");

		GLfloat params[2];
		glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, params);
		printf("aliased point range is %f:%f\n", params[0], params[1]);
		glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, params);
		printf("smooth point range is %f:%f\n", params[0], params[1]);
		glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, params);
		printf("aliased line range is %f:%f\n", params[0], params[1]);
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, params);
		printf("smooth line range is %f:%f\n", params[0], params[1]);
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY, params);
		printf("smooth line granularity %f\n", params[0]);

		printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
		printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
		printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
		printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
#endif

#if CH2_BUFFER
#define BUFFER_OFFSET(offset) ((GLubyte*) NULL + offset)
#define NUM_BUFFERS 2
	enum {VERTICES, INDICES};
	GLuint buffers[NUM_BUFFERS];
	GLfloat vertices[][3] = {
			{-1.0, -1.0, -1.0},
			{1.0, -1.0, -1.0},

			{1.0, 1.0, -1.0},
			{-1.0, 1.0, -1.0},

			{-1.0, -1.0, 1.0},
			{1.0, -1.0, 1.0},

			{1.0, 1.0, 1.0},
			{-1.0, 1.0, 1.0},
	};

	GLubyte indices[][4]  = {
			{0, 1, 2, 3},
			{4, 7, 6, 5},
			{0, 4, 5, 1},
			{3, 2, 6, 7},
			{0, 3, 7, 4},
			{1, 5, 6, 2},
	};

	glGenBuffers(NUM_BUFFERS, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
#endif

#if CH2_VAO

glGenVertexArrays(NumVAOs, VAO);

GLfloat cubeVerts[][3] = {
	{-1.0, -1.0, -1.0},
	{-1.0, -1.0, 1.0},
	{-1.0, 1.0, -1.0},
	{-1.0, 1.0, 1.0},
	{1.0, -1.0, -1.0},
	{1.0, -1.0, 1.0},
	{1.0, 1.0, -1.0},
	{1.0, 1.0, 1.0},
};

GLfloat cubeColors[][3] = {
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
};

GLubyte cubeIndices[] = {
	0, 1, 3, 2,
	4, 6, 7, 5,
	2, 3, 7, 6,
	0, 4, 5, 1,
	0, 2, 6, 4,
	1, 3, 7, 5,
};

glBindVertexArray(VAO[Cube]);
glGenBuffers(NumVBOs, buffers[Cube]);
glBindBuffer(GL_ARRAY_BUFFER, buffers[Cube][Vertices]);
glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_VERTEX_ARRAY);

glBindBuffer(GL_ARRAY_BUFFER, buffers[Cube][Colors]);
glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_COLOR_ARRAY);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Cube][Elements]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

PrimType[Cube] = GL_QUADS;
NumElements[Cube] = NumberOf(cubeIndices);

int i, idx;
float dTheta;
#define NumConePoints 100
GLfloat coneVerts[NumConePoints + 1][3] = {
	{0.0, 0.0, -1.0},
};

GLfloat coneColors[NumConePoints + 1][3] = {
	{1.0, 1.0, 1.0},
};

GLubyte coneIndices[NumConePoints + 1] = {
	0,
};

dTheta = 2 * PI / (NumConePoints);
idx = 1;
for (i = 0; i < NumConePoints; i++, idx++) {
	float theta = i * dTheta;
	coneVerts[idx][0] = cos(theta);
	coneVerts[idx][1] = sin(theta);
	coneVerts[idx][2] = 0.0;
	coneColors[idx][0] = cos(theta);
	coneColors[idx][1] = sin(theta);
	coneColors[idx][2] = 0.0;
	coneIndices[idx] = idx;
}

coneVerts[NumConePoints][0] = coneVerts[1][0];
coneVerts[NumConePoints][1] = coneVerts[1][1];
coneVerts[NumConePoints][2] = 0;
coneColors[NumConePoints][0] = coneColors[1][0];
coneColors[NumConePoints][1] = coneColors[1][1];
coneColors[NumConePoints][2] = coneColors[1][2];
//coneIndices[NumConePoints] = NumConePoints;

glBindVertexArray(VAO[Cone]);
glGenBuffers(NumVBOs, buffers[Cone]);
glBindBuffer(GL_ARRAY_BUFFER, buffers[Cone][Vertices]);
glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts, GL_STATIC_DRAW);
glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_VERTEX_ARRAY);

glBindBuffer(GL_ARRAY_BUFFER, buffers[Cone][Colors]);
glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors, GL_STATIC_DRAW);
glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_COLOR_ARRAY);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Cone][Elements]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);

PrimType[Cone] = GL_TRIANGLE_FAN;
NumElements[Cone] = NumberOf(coneIndices);

glEnable(GL_DEPTH_TEST);

#endif

#endif
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

	init();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

#if CH2
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
		glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 4, ratio * 4 , -1.f * 4, 1.f * 4, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 0.f);

#if CH2_TRIANGLE // triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
#endif

#if CH2_QUADS
        glBegin(GL_QUADS);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-1.0f, -1.0f, 0.f);
        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(-1.0f, 1.0f, 0.f);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(1.f, 1.0f, 0.f);
        glVertex3f(1.f, -1.0f, 0.f);
        glEnd();
#endif
	
#if CH2_POINTS // points
		glPointSize(255);
		glBegin(GL_POINTS);
		glColor3f(1.f, 1.f, 1.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
#endif

#if CH2_LINES // lines
		glLineWidth(2);
		glLineStipple(1, 0x0f0f);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		glColor3f(1.f, 1.f, 1.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
#endif

#if CH2_LINE_STRIP // line_strip
		glBegin(GL_LINE_STRIP);
		glColor3f(1.f, 1.f, 1.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
#endif

#if CH2_CIRCLE
		GLint circle_points = 100;
		glBegin(GL_LINE_LOOP);
		glColor3f(1.f, 1.f, 1.f);
		for (int i = 0; i < circle_points; i++) {
			GLfloat angle = 2 * PI * i / circle_points;
			glVertex2f(cos(angle), sin(angle));
		}
		glEnd();
#endif

#if CH2_POLY
		glPolygonMode(GL_FRONT, GL_LINE);
        glBegin(GL_POLYGON);
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
		glVertex3f(-1.f, 1.f, 0.f);
        glEnd();
#endif

#if CH2_BATCH
		static GLint vertices[] = {
				25, 25,
				100, 325,
				175, 25,
				250, 25,
				325, 325,
		};

		static GLfloat colors[] = {
				1.0, 0.2, 0.2,
				0.2, 0.2, 1.0,
				0.8, 1.0, 0.2,
				0.75, 0.75, 0.75,
				0.35, 0.35, 0.35,
				0.5, 0.5, 0.5,
		};

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colors);
		glVertexPointer(2, GL_INT, 0, vertices);

		glBegin(GL_TRIANGLES);
		glArrayElement(2);
		glArrayElement(3);
		glArrayElement(5);
		glEnd();
#endif

#if CH2_PRIMRESTART
		glColor3f(1, 1, 1);
		glDrawElements(GL_TRIANGLES, NumStrips * (NumPointsPerStrip + 1), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
#endif

#if CH2_VAO
		int i;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glRotatef(Angle, 0.0, 1.0, 0.0);

		for (i = 0; i < NumVAOs; i++) {
			glPushMatrix();
			glTranslatef(xform[i].xlate.x, xform[i].xlate.y, xform[i].xlate.z);
			glRotatef(xform[i].angle, xform[i].axis.x, xform[i].axis.y, xform[i].axis.z);
			glBindVertexArray(VAO[i]);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[i][Vertices]);
			glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
			glBindBuffer(GL_ARRAY_BUFFER, buffers[i][Colors]);
			glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[i][Elements]);
			glDrawElements(PrimType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
			glPopMatrix();
		}
		glPopMatrix();
#endif

#endif


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

//! [code]
