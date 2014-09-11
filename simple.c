
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
#include <string.h>
#include <stdio.h>
#include <math.h>

#define CH1 0
#define CH2 0
#define CH3 0
#define CH4 0
#define CH5 0
#define CH6 0
#define CH7 0
#define CH8 1
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
#define CH2_VAO 0

#define CH3_CLIP 0
#define CH3_PLANET 0

#define CH5_LIGHT_SPINOBJ 0
#define CH5_MOVELIGHT 0

#define CH6_BLEND_TRIANGLE 0
#define CH6_LINE_ANTI 1

#define CH7_LIST 0
#define CH7_FONT_LIST 0

#define CH8_BITMAP 0
#define CH8_ANSCII 0
#define CH8_CHECK 1

#define PI 3.1415926535898
#define GL_TRUE 1
#define GL_FALSE 0

/*****************************************************************************
 * Calculate the angle to be passed to gluPerspective() so that a scene
 * is visible.  This function originates from the OpenGL Red Book.
 *
 * Parms   : size
 *           The size of the segment when the angle is intersected at "dist"
 *           (ie at the outermost edge of the angle of vision).
 *
 *           dist
 *           Distance from viewpoint to scene.
 *****************************************************************************/
GLfloat PerspectiveAngle( GLfloat size,
                          GLfloat dist )
{
   GLfloat radTheta, degTheta;

   radTheta = 2.f * (GLfloat) atan2( size / 2.f, dist );
   degTheta = (180.f * radTheta) / (GLfloat) M_PI;
   return degTheta;
}



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

#if CH3
#define BUFFER_OFFSET(of) ((GLvoid *)NULL + of)
#define NumberOf(array) (sizeof(array) / sizeof (array[0]))
#if CH3_CLIP
enum {Cube, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
enum {Vertices, Colors, Elements, NumVBOs};
GLuint buffers[NumVAOs][NumVBOs];
#endif

#if CH3_PLANET
enum {Cube, Cube2, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
enum {Vertices, Colors, Elements, NumVBOs};
GLuint buffers[NumVAOs][NumVBOs];
#endif

#endif


#if CH6
#if CH6_BLEND_TRIANGLE
static void drawLeftTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 0, 0.75);
	glVertex3f(0.1, 0.9, 0.0);
	glVertex3f(0.1, 0.1, 0.0);
	glVertex3f(0.7, 0.5, 0.0);
	glEnd();
}

static void drawRightTriangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor4f(0, 1, 1, 0.75);
	glVertex3f(0.9, 0.9, 0.0);
	glVertex3f(0.3, 0.5, 0.0);
	glVertex3f(0.9, 0.1, 0.0);
	glEnd();
}
#endif
#endif

#if CH7
#if CH7_LIST
static GLint tri_list;

static void drawLine()
{
	glBegin(GL_LINES);
	glVertex2f(0, 0.5);
	glVertex2f(15, 0.5);
	glEnd();
}
#endif

#if CH7_FONT_LIST
#define PT 1
#define STROKE 2
#define END 3

typedef struct charpoint {
	GLfloat x, y;
	int type;
} CP;

CP Adata[] = {
	{0, 0, PT}, {0, 9, PT}, {1, 10, PT}, {4, 10, PT},
	{5, 9, PT}, {5, 0, STROKE}, {0, 5, PT}, {5, 5, END}
};

CP Edata[] = {
	{5, 0, PT}, {0, 0, PT}, {0, 10, PT}, {5, 10, STROKE},
	{0, 5, PT}, {4, 5, END},
};

static void drawLetter(CP* l)
{
	glBegin(GL_LINE_STRIP);
	while(l) {
		switch (l->type) {
			case PT:
				glVertex2fv(&l->x);
				break;
			case STROKE:
				glVertex2fv(&l->x);
				glEnd();
				glBegin(GL_LINE_STRIP);
				break;
			case END:
				glVertex2fv(&l->x);
				glEnd();
				glTranslatef(8, 0, 0);
				return;
		}
		l++;
	}
}

char* test1 = "A E AA EE AAA EEE";
char* test2 = "E A EE AA EEE AAA";

static void printStr(char *s)
{
	GLsizei len = strlen(s);
	glCallLists(len, GL_BYTE, (GLbyte *)s);
}
#endif
#endif

#if CH8
#if CH8_BITMAP
GLubyte rasters[24] = {
	0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
	0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
	0xff, 0xc0, 0xff, 0xc0,
};
#endif

#if CH8_ANSCII
GLubyte space[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

GLubyte letters[][13] = {
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
};

GLuint offset;
void makeRasterFont(void)
{
	GLuint i, j;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	offset = glGenLists(128);
	for (i = 0, j = 'A'; i < sizeof(letters) / sizeof(letters[1]); i++, j++) {
		glNewList(offset + j, GL_COMPILE);
		glBitmap(8, 13, 0, 2, 10, 0, letters[i]);
		glEndList();
	}

	glNewList(offset + ' ', GL_COMPILE);
	glBitmap(8, 13, 0, 2, 10, 0, space);
	glEndList();
}

void printString(char *s)
{
	glPushAttrib(GL_LIST_BIT);
	glListBase(offset);
	glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *)s);
	glPopAttrib();
}
#endif

#if CH8_CHECK
#define CHECK_W 64
#define CHECK_H 64
GLubyte checkImage[CHECK_W][CHECK_H][3];
void makeCheckImage(void)
{
	int i, j, c;
	for (i = 0; i < CHECK_H; i++) {
		for (j = 0; j < CHECK_W; j++) {
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte) c;
			checkImage[i][j][1] = (GLubyte) c;
			checkImage[i][j][1] = (GLubyte) c;
		}
	}
}
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

#if CH3
#if CH3_CLIP
glClearColor(0, 0, 0, 0);
glShadeModel(GL_FLAT);

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
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},
	{0.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{0.5, 0.5, 0.5},
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

#endif

#if CH3_PLANET
glClearColor(0, 0, 0, 0);
glShadeModel(GL_FLAT);

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

GLfloat cubeVerts2[][3] = {
	{-0.5, -0.5, -0.5},
	{-0.5, -0.5, 0.5},
	{-0.5, 0.5, -0.5},
	{-0.5, 0.5, 0.5},
	{0.5, -0.5, -0.5},
	{0.5, -0.5, 0.5},
	{0.5, 0.5, -0.5},
	{0.5, 0.5, 0.5},
};

GLfloat cubeColors2[][3] = {
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0},
};

GLubyte cubeIndices2[] = {
	0, 1, 3, 2,
	4, 6, 7, 5,
	2, 3, 7, 6,
	0, 4, 5, 1,
	0, 2, 6, 4,
	1, 3, 7, 5,
};

glBindVertexArray(VAO[Cube2]);
glGenBuffers(NumVBOs, buffers[Cube2]);
glBindBuffer(GL_ARRAY_BUFFER, buffers[Cube2][Vertices]);
glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts2), cubeVerts2, GL_STATIC_DRAW);
glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_VERTEX_ARRAY);

glBindBuffer(GL_ARRAY_BUFFER, buffers[Cube2][Colors]);
glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors2), cubeColors2, GL_STATIC_DRAW);
glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
glEnableClientState(GL_COLOR_ARRAY);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Cube2][Elements]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices2), cubeIndices2, GL_STATIC_DRAW);

PrimType[Cube2] = GL_QUADS;
NumElements[Cube2] = NumberOf(cubeIndices2);
#endif

#endif

#if CH5
#if CH5_LIGHT_SPINOBJ
	GLfloat mat_specular[] = {0.7, 0.2, 0.5, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_pos[] = {0.0, 0.0, 3.0, 1.0};
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
#endif

#if CH5_MOVELIGHT
	GLfloat mat_specular[] = {0.7, 0.2, 0.5, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_pos[] = {0.0, 0.0, 3.0, 1.0};
	GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
#endif

#endif

#if CH6
#if CH6_BLEND_TRIANGLE
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0);
#endif

#if CH6_LINE_ANTI
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClearColor(0, 0, 0, 0);
#endif
#endif

#if CH7
#if CH7_LIST
	tri_list = glGenLists(1);
	glNewList(tri_list, GL_COMPILE);
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(0, 1);
	glEnd();
	glTranslatef(0.5, 0, 0);
	glEndList();
#endif
#if CH7_FONT_LIST
	GLuint base;
	base = glGenLists(128);
	glListBase(base);

	glNewList(base + 'A', GL_COMPILE);
	drawLetter(Adata);
	glEndList();

	glNewList(base + 'E', GL_COMPILE);
	drawLetter(Edata);
	glEndList();

	glNewList(base + ' ', GL_COMPILE);
	glTranslatef(8.0, 0.0, 0.0);
	glEndList();
#endif
#endif

#if CH8
#if CH8_BITMAP
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0, 0, 0, 0);
#endif
#if CH8_ANSCII
	glShadeModel(GL_FLAT);
	makeRasterFont();
#endif
#if CH8_CHECK
	glClearColor(0, 0, 0, 0);
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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

#if CH3
#if CH3_CLIP
		int i;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

		glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(60, ratio, 1, 20); doesn't work!!!!!!!!!
        glOrtho(-ratio * 4, ratio * 4 , -1.f * 4, 1.f * 4, 10000.f, -10000.f);
		//glFrustum(-2, 2, -2/ratio, 2/ratio, 1, 20);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glScalef(2, 1, 1);
		glTranslatef(0, 0, -10.0);
        glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 0.f);

#if 0
		GLdouble eqn[4] = {0, 1, 0, 0};
		GLdouble eqn2[4] = {1, 0, 0, 0};
		glClipPlane(GL_CLIP_PLANE0, eqn);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn2);
		glEnable(GL_CLIP_PLANE1);
#endif

		for (i = 0; i < NumVAOs; i++) {
			glBindVertexArray(VAO[i]);
			glBindBuffer(GL_ARRAY_BUFFER, buffers[i][Vertices]);
			glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
			glBindBuffer(GL_ARRAY_BUFFER, buffers[i][Colors]);
			glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[i][Elements]);
			glDrawElements(PrimType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		}
#endif

#if CH3_PLANET
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

		glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		glFrustum(-5, 5, -5/ratio, 5/ratio, 1, 20);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		//glTranslatef(0, 0, -3.0);
        //glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 0.f);

		glPushMatrix();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 1.f, 0.f);
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0][Vertices]);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0][Colors]);
		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0][Elements]);
		glDrawElements(PrimType[0], NumElements[0], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		glPopMatrix();
		
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 1.f, 0.f);
		glTranslatef(4, 0, 0);
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 1.f, 0.f);
		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1][Vertices]);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1][Colors]);
		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1][Elements]);
		glDrawElements(PrimType[1], NumElements[1], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	

		//glPopMatrix();
#endif

#endif

#if CH5
#if CH5_LIGHT_SPINOBJ
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 4, ratio * 4 , -1.f * 4, 1.f * 4, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 0.f);

		glBegin(GL_QUADS);
		glNormal3f(0,0,-1); 
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glVertex3f(1,1,0);
		glVertex3f(0,1,0);

		glNormal3f(-1,0,0);//右
		glColor3f(0,1,0);
		glVertex3f(1,0, 0);
		glVertex3f(1,0,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,1, 0);

		glNormal3f(0,-1,0);//上
		glColor3f(0,0,1);
		glVertex3f(0,1, 0);
		glVertex3f(1,1, 0);
		glVertex3f(1,1,-1);
		glVertex3f(0,1,-1);

		glNormal3f(0,0,1); //后
		glColor3f(1,1,0);
		glVertex3f(0,1,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,0,-1);
		glVertex3f(0,0,-1);

		glNormal3f(1,0,0);//左
		glColor3f(0,1,1);
		glVertex3f(0,1, 0);
		glVertex3f(0,1,-1);
		glVertex3f(0,0,-1);
		glVertex3f(0,0, 0);

		glNormal3f(0,1,0);//下
		glColor3f(1,0,1);
		glVertex3f(0,0,-1);
		glVertex3f(1,0,-1);
		glVertex3f(1,0, 0);
		glVertex3f(0,0, 0);
		glEnd();
#endif

#if CH5_MOVELIGHT
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

		GLfloat light_pos[] = {0.0, 0.0, 3.0, 1.0};
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 4, ratio * 4 , -1.f * 4, 1.f * 4, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		glPushMatrix();
        glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 0.f);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glPopMatrix();

		glBegin(GL_QUADS);
		glNormal3f(0,0,-1); 
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glVertex3f(1,1,0);
		glVertex3f(0,1,0);

		glNormal3f(-1,0,0);//右
		glColor3f(0,1,0);
		glVertex3f(1,0, 0);
		glVertex3f(1,0,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,1, 0);

		glNormal3f(0,-1,0);//上
		glColor3f(0,0,1);
		glVertex3f(0,1, 0);
		glVertex3f(1,1, 0);
		glVertex3f(1,1,-1);
		glVertex3f(0,1,-1);

		glNormal3f(0,0,1); //后
		glColor3f(1,1,0);
		glVertex3f(0,1,-1);
		glVertex3f(1,1,-1);
		glVertex3f(1,0,-1);
		glVertex3f(0,0,-1);

		glNormal3f(1,0,0);//左
		glColor3f(0,1,1);
		glVertex3f(0,1, 0);
		glVertex3f(0,1,-1);
		glVertex3f(0,0,-1);
		glVertex3f(0,0, 0);

		glNormal3f(0,1,0);//下
		glColor3f(1,0,1);
		glVertex3f(0,0,-1);
		glVertex3f(1,0,-1);
		glVertex3f(1,0, 0);
		glVertex3f(0,0, 0);
		glEnd();
#endif

#endif

#if CH6
#if CH6_BLEND_TRIANGLE
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 4, ratio * 4 , -1.f * 4, 1.f * 4, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		if (0) {
			drawLeftTriangle();
			drawRightTriangle();
		} else {
			drawRightTriangle();
			drawLeftTriangle();
		}
#endif

#if CH6_LINE_ANTI
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 2, ratio * 2 , -1.f * 2, 1.f * 2, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		
		glLineWidth(8);
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glPopMatrix();
		glEnd();
		
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glPopMatrix();
		glEnd();

#endif
#endif
		
#if CH7
#if CH7_LIST
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 10, ratio * 10 , -1.f * 10, 1.f * 10, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		glColor3f(0, 1, 0);
		GLuint i;
		for (i = 0; i < 10; i++) {
			glCallList(tri_list);
		}

		drawLine();
#endif
#if CH7_FONT_LIST
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 100, ratio * 100 , -1.f * 100, 1.f * 100, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		glColor3f(1, 1, 1);

		glPushMatrix();
		glTranslatef(-20, 20, 0);
		printStr(test1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-20, 0, 0);
		printStr(test2);
		glPopMatrix();
#endif
#endif

#if CH8
#if CH8_BITMAP
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 100, ratio * 100, -1.f * 100, 1.f * 100, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glColor3f(1, 0, 0);
		glRasterPos2i(20, 20);
		glColor3f(1, 1, 0);
		glBitmap(10, 12, 0, 0, 11, 0, rasters);
		glBitmap(10, 12, 0, 0, 11, 0, rasters);
		glBitmap(10, 12, 0, 0, 11, 0, rasters);
		glFlush();
#endif
#if CH8_ANSCII
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 100, ratio * 100, -1.f * 100, 1.f * 100, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glColor3f(1, 0, 0);
		glRasterPos2i(20, 60);
		printString("A AA AAA A   A");
		glRasterPos2i(20, 40);
		printString("A AA AAA A A  A");
#endif

#if CH8_CHECK
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio * 100, ratio * 100, -1.f * 100, 1.f * 100, 10000.f, -10000.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glColor3f(1, 0, 0);
		glRasterPos2i(0, 0);
		glDrawPixels(CHECK_W, CHECK_H, GL_RGB, GL_UNSIGNED_BYTE, checkImage);

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
