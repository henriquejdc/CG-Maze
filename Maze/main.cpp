/* 
	Gabriel Fernando Casagrande
  Henrique José Dalla Corte
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define BLOCKSIZE 250
#define STEP 32
#define MAXTEXTURES 1
#define HEIGHT 800
#define WIDTH 640
void drawTable();
void drawWindow();
void drawBacia();
void desenhaBaseB();
void desenhaCorpoB();

void drawTrophy();
void drawBaseTrophy();
void drawBodyTrophy();

GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_specular1[] = {0.5, 0.5, 0.5, 0.5};
GLfloat mat_shininess[] = {50.0};
GLfloat mat_shininess1[] = {10.0};
GLfloat YELLOW[] = {0.8, 0.8, 0.1, 1.0};
GLfloat YELLOWP[] = {0.8, 0.8, 0.1, 0.9};
GLfloat GREEN[] = {0.1, 0.6, 0.1, 1.0};
GLfloat RED[] = {0.7, 0.1, 0.1, 1.0};
GLfloat LILAC[] = {0.8, 0.0, 1.0, 1.0};
GLfloat BLUE[] = {0.1, 0.0, 1.0, 0.8};
GLfloat BLUEP[] = {0.1, 0.0, 1.0, 0.9};
GLfloat BLUEGLASS[] = {0.1, 0.0, 1.0, 0.2};
GLfloat TEAL[] = {0.0, 0.5, 0.5, 0.9};
GLfloat BLACK[] = {0.0, 0.0, 0.0, 0.1};
GLfloat NAVY[] = {0.0, 0.0, 0.5, 0.9};
GLfloat MAROON[] = {0.5, 0.0, 0.0, 1.0};
GLfloat light_position[] = {0.0, 500.0, 0.0, 1.0};
GLfloat WHITE_LIGHT[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lmodel_ambient[] = {0.6, 0.6, 0.6, 1.0};

GLfloat rob_x = BLOCKSIZE, rob_z = BLOCKSIZE;
GLfloat mov_x = STEP, mov_z = 0, mov_y = 0;
GLdouble angle = 0;
///textura
GLuint texnum[MAXTEXTURES];

// char *infile = "img.bmp";
double zoomy;
int alpha = 0, del, Cam = 1, Cam_janela = 0, Cam_android = 0, Cam_tea = 0, Cam_circ = 0, Cam_cima = 0, Cam_baude = 0,Cam_trofeu =0;
double head = 16;
int mult = 1, multDel = 1, onMove = 0;
void drawCubo(GLdouble size);
void drawcubinho(GLfloat size, GLenum type);
void drawAndroid();

GLint map[20][20] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{5, 0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 2, 1, 0, 1},
		{1, 0, 1, 2, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
		{1, 4, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 2, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 2, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}};


void swapRB(unsigned char &b, unsigned char &r)
{
	unsigned char x;
	x = r;
	r = b;
	b = x;
}
unsigned char *loadBMP_custom(const char *filename, unsigned int &width, unsigned int &height)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;			// Position in the file where the actual data begins
	//unsigned int width, height;
	unsigned int imageSize; // = width*height*3
	// Actual RGB data
	unsigned char *data;
	// Open the file
	FILE *file;
	file = fopen(filename, "rb");
	if (!file)
	{
		printf("Image could not be opened %s \n", filename);
		return 0;
	}
	if (fread(header, 1, 54, file) != 54)
	{ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Read ints from the byte array
	dataPos = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);
	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way
	// Create a buffer
	data = new unsigned char[imageSize];
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
	for (unsigned int i = 0; i < imageSize; i += 3)
		swapRB(data[i], data[i + 2]);
	//Everything is in memory now, the file can be closed
	fclose(file);
	return data;
}

// Collision just works for camera point, need to be fixed
int can_move(float pos_x, float pos_z, float vet_x, float vet_z)
{
	float world_x = pos_x + vet_x;
	float world_z = pos_z + vet_z;

	int ind_x = (int)((world_x + BLOCKSIZE / 2) / BLOCKSIZE);
	int ind_z = (int)((world_z + BLOCKSIZE / 2) / BLOCKSIZE);

	if (map[ind_x][ind_z])
		return 0;
	else
		return 1;
}

void drawRobot()
{
	GLUquadric *quad = gluNewQuadric();

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	int aux_movi = 5;
	//LADO ESQUERDA
	// Wheel's sphere
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, -aux_movi);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.5, 100, 100);

	glPopMatrix();

	// Wheel axle 1
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 - aux_movi);

	glColor3f(1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 2
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 - aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(180, 1, 0, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 3
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 - aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 4
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 - aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(270, 0, 1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 - aux_movi);

	glColor3f(1, 0, 0);
	glRotatef(alpha, 0, 0, -1);
	glColor3f(0, 1.0, 0);
	glutWireTorus(1, 4, 20, 20);

	glPopMatrix();

	// Lateral axle
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, TEAL);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(15, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -1.7 - aux_movi, -5);
	glColor3f(1, 1, 1);
	glScalef(0.05, 0.05, 1);
	glutSolidCube(10);

	glTranslatef(0, 67, 0);
	glutSolidCube(10);
	glPopMatrix();

	//LADO DIREITO
	// Wheel's sphere
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, +aux_movi);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.5, 100, 100);

	glPopMatrix();

	// Wheel axle 1
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 + aux_movi);

	glColor3f(1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 2
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 + aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(180, 1, 0, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 3
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 + aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel axle 4
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 + aux_movi);

	glRotatef(90, 1, 0, 0);
	glRotatef(alpha, 0, -1, 0);
	glRotatef(270, 0, 1, 0);
	gluCylinder(quad, 0.2, 0.2, 4, 100, 100);

	glPopMatrix();

	// Wheel
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0 + aux_movi);

	glColor3f(1, 0, 0);
	glRotatef(alpha, 0, 0, -1);
	glColor3f(0, 1.0, 0);
	glutWireTorus(1, 4, 20, 20);

	glPopMatrix();

	// Lateral axle
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, TEAL);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(15, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -1.7 + aux_movi, -5);
	glColor3f(1, 1, 1);
	glScalef(0.05, 0.05, 1);
	glutSolidCube(10);

	glTranslatef(0, 67, 0);
	glutSolidCube(10);
	glPopMatrix();

	// QUADRIL
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -11);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	// Head
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, NAVY);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glRotatef(90, 1, 0, 0);
	if (head > 17)
		mult = -1;
	if (head < 16)
		mult = 1;
	head += 0.01 * mult;
	glTranslatef(0, 0, -head - 10);

	glColor3f(1, 1, 1);
	glutSolidSphere(3, 100, 100);
	glPopMatrix();

	//COXAS
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LILAC);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glTranslatef(0, 10, -7);
	glColor3f(1, 1, 1);
	gluCylinder(quad, 0.4, 0.4, 6, 100, 100);
	glTranslatef(0, 0, 8);
	gluCylinder(quad, 0.4, 0.4, 6, 100, 100);

	glPopMatrix();

	//Corpo
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -20);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -14);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -17);
	glColor3f(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	// Arms
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LILAC);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 0.51 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glTranslatef(0, 20, -7);
	glColor3f(1, 1, 1);
	gluCylinder(quad, 0.4, 0.4, 6, 100, 100);
	glTranslatef(0, 0, 8);
	gluCylinder(quad, 0.4, 0.4, 6, 100, 100);

	glPopMatrix();

	//MAOS
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 7, -20);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	//esquerda
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -7, -20);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();

	//Dedos ESQ
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -8.8, -20);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -8.0, -21.5);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -8.0, -18.5);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	//Dedos DIREITO
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 8.8, -20);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 8.0, -21.5);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(rob_x, 0, rob_z);
	glRotatef(mov_y, 0, 1, 0);
	glTranslatef(5 + 10, 0, 0);

	if (del > 11)
		multDel = -1;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	if (del < -11)
		multDel = 1;
	del += 1 * multDel;
	if (onMove)
		glRotatef(del, 0, -1, 0);

	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 8.0, -18.5);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.7, 100, 100);
	glPopMatrix();

	gluDeleteQuadric(quad);
}

void display(void)
{
	int x, z;
	int x_worl, z_worl;

	// Clear all the pixels
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	if (Cam)
	{ // Choose between cameras
		gluLookAt(rob_x-10, 24, rob_z, rob_x + mov_x, 20, rob_z + mov_z, 0, 1, 0);
	}
	else if (Cam_cima)
	{
		gluLookAt(0, 100, 1, 0, 0, 0, 1, 0, 0);
		printf("%f %f %f \n", rob_x, zoomy, rob_z);
		glTranslatef(-rob_x, -zoomy, -rob_z);
	}
	else if (Cam_android)
	{
		gluLookAt(000, 100, 1, 0, 0, 0, 1, 0, 0);
		// gluLookAt(rob_x, 23, rob_z, rob_x + mov_x, 20, rob_z + mov_z, 0, 1, 0);
		glTranslatef(-1850.f, -100.f - zoomy, -250.f);
	}
	else if (Cam_tea)
	{
		gluLookAt(000, 100, 1, 0, 0, 0, 1, 0, 0);
		glTranslatef(-650.f, -150.f - zoomy, -750.f);
	}
	else if (Cam_circ)
	{
		gluLookAt(000, 100, 1, 0, 0, 0, 1, 0, 0);
		glTranslatef(-250.f, -150.f - zoomy, -350.f);
	}
	else if (Cam_janela)
	{
		gluLookAt(000, 100, 1, 0, 0, 0, 1, 0, 0);
		glTranslatef(-250.f, -100.f - zoomy, -50.f);
	}
	else if (Cam_baude)
	{
		gluLookAt(-20, 10, 1, 0, 0, 0, 1, 0, 0);
		glTranslatef(-1300.f, -50.f , -750.f);
	}
	else if (Cam_trofeu)
	{
		gluLookAt(-400, 150, 1, 0, 0, 0, 1, 0, 0);
		glTranslatef(-3800.f, -70.f , -3750.f);
	}

	// Ground
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GREEN);
	glBindTexture(GL_TEXTURE_2D, texnum[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-10000, -BLOCKSIZE / 2, -10000);
	glTexCoord2f(0, 500);
	glVertex3f(-10000, -BLOCKSIZE / 2, 10000);
	glTexCoord2f(500, 0);
	glVertex3f(10000, -BLOCKSIZE / 2, 10000);
	glTexCoord2f(500, 500);
	glVertex3f(10000, -BLOCKSIZE / 2, -10000);

	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Shows the robot
	drawRobot();
	drawAndroid();
	drawWindow();

	// Desenha o trofeu
	glPushMatrix();
	glTranslatef(3710, 0, 3740);
	glRotatef(-90, 1, 0, 0);
	glScalef(25, 25, 25);
	drawTrophy();
	glPopMatrix();

	//Desenha a bacia
	glPushMatrix();
	glTranslatef(1500, -100, 740);
	glRotatef(-90, 1, 0, 0);
	glScalef(10, 10, 10);
	drawBacia();
	glPopMatrix();
	drawTable();
	glEnable(GL_TEXTURE_2D);

	// Draw the maze
	for (x = 0; x < 20; x++)
	{
		for (z = 0; z < 20; z++)
		{
			if (map[x][z] == 1) // Block of wall
			{
				x_worl = x * BLOCKSIZE;
				z_worl = z * BLOCKSIZE;

				//Wall
				glPushMatrix();
				glColor3f(1, 0, 1);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

				glTranslatef(x_worl, 0, z_worl);

				glBindTexture(GL_TEXTURE_2D, texnum[1]);
				drawCubo(BLOCKSIZE);
				glPopMatrix();
			}
			else if (map[x][z] > 1) // Object
			{
				x_worl = x * BLOCKSIZE;
				z_worl = z * BLOCKSIZE;
				if (map[x][z] == 2)
				{
					glDisable(GL_TEXTURE_2D);
					glPushMatrix();
					glColor3f(1, 0, 1);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

					glTranslatef(x_worl, -50, z_worl);

					glutSolidTeapot(BLOCKSIZE / 3);

					glPopMatrix();
					glEnable(GL_TEXTURE_2D);
				}
				if (map[x][z] == 6)
				{
					glDisable(GL_TEXTURE_2D);
					drawTable();
					glEnable(GL_TEXTURE_2D);
				}
				if (map[x][z] == 3)
				{

					glDisable(GL_TEXTURE_2D);
					glPushMatrix();
					glColor3f(1, 0, 1);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, LILAC);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

					glTranslatef(x_worl, -20, z_worl);
					glutSolidTorus(50, 100, 100, 100);

					glPopMatrix();
					glEnable(GL_TEXTURE_2D);
				}
				if (map[x][z] == 5)
				{
					x_worl = x * BLOCKSIZE;
					z_worl = z * BLOCKSIZE;

					glDisable(GL_TEXTURE_2D);
					glPushMatrix();

					glTranslatef(x_worl, 0, z_worl);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BLUEGLASS);
					glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
					glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

					glTranslatef(0, 0, 125);
					glScalef(1, 1, 0);
					glutSolidCube(BLOCKSIZE);

					glEnable(GL_TEXTURE_2D);
					glPopMatrix();
				}
			}
		}
	}

	glutSwapBuffers();
}

// Here begin the input control functions
void Keyboard_Function(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break; // ESC
	case 'W':
	case 'w':
		if (can_move(rob_x, rob_z, mov_x, mov_z))
		{
			rob_x += mov_x;
			rob_z += mov_z;
			alpha += 5;
			onMove = 1;
		}
		break;
	case 'S':
	case 's':
		if (can_move(rob_x, rob_z, -mov_x, -mov_z))
		{
			rob_x -= mov_x;
			rob_z -= mov_z;
			alpha -= 5;
			onMove = 1;
		}
		break;
	case 'z':
	case 'Z':
		Cam_cima = !Cam_cima;
		if (Cam_cima)
		{
			Cam = Cam_janela =  Cam_android = Cam_tea = Cam_circ = Cam_baude = Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '1':
		Cam_janela = !Cam_janela;
		if (Cam_janela)
		{
			Cam = Cam_android = Cam_tea = Cam_circ = Cam_cima = Cam_baude = Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '2':
		Cam_android = !Cam_android;
		if (Cam_android)
		{
			Cam =  Cam_janela = Cam_tea = Cam_circ = Cam_cima = Cam_baude = Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '3':
		Cam_tea = !Cam_tea;
		if (Cam_tea)
		{
			Cam = Cam_janela =  Cam_android =  Cam_circ = Cam_cima =Cam_baude = Cam_trofeu =0;;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '4':
		Cam_circ = !Cam_circ;
		if (Cam_circ)
		{
			Cam = Cam_janela =  Cam_android =  Cam_tea = Cam_cima = Cam_baude = Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '5':
		Cam = !Cam;
		if (Cam)
		{
			Cam_janela =Cam_android =  Cam_tea =  Cam_circ = Cam_cima =  Cam_baude =Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	case '6':
		Cam_baude = !Cam_baude;
		if (Cam_baude)
		{
			Cam =Cam_janela =  Cam_android =  Cam_tea =  Cam_circ =  Cam_cima =  Cam_trofeu =0;
		}
		else
		{
			Cam = 1;
		}
		break;
    case '7':
		Cam_trofeu = !Cam_trofeu;
		if (Cam_trofeu)
		{
			Cam = Cam_janela = Cam_android = Cam_tea = Cam_circ =  Cam_cima =Cam_baude =0;
		}
		else
		{
			Cam = 1;
		}
		break;
	}
}

void releaseKeyN(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
	case 'S':
	case 's':
		onMove = 0;
		break;
	}
}

void Special_Function(int key, int x, int y)
{
	float rad;

	switch (key)
	{
	case GLUT_KEY_DOWN:
		if (can_move(rob_x, rob_z, -mov_x, -mov_z))
		{
			rob_x -= mov_x;
			rob_z -= mov_z;
			alpha -= 5;
			onMove = 1;
		}
		break;
	case GLUT_KEY_UP:
		if (can_move(rob_x, rob_z, mov_x, mov_z))
		{
			rob_x += mov_x;
			rob_z += mov_z;
			alpha += 5;
			onMove = 1;
		}
		break;
	case GLUT_KEY_LEFT:
		angle -= 1;
		if (angle < 0)
			angle += 360;

		rad = (float)(M_PI * angle / 180.0f);
		mov_x = cos(rad) * STEP;
		mov_z = sin(rad) * STEP;
		break;

	case GLUT_KEY_RIGHT:
		angle += 1;
		if (angle >= 360)
			angle -= 360;
		rad = (float)(M_PI * angle / 180.0f);
		mov_x = cos(rad) * STEP;
		mov_z = sin(rad) * STEP;
		break;
	}
}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		onMove = 0;
		break;
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == 3)
		zoomy -= 20;
	if (zoomy < 0)
		zoomy = 0;
	if (button == 4)
		zoomy += 20;
	if (zoomy > 5400)
		zoomy = 5400;
	if (button == 2)
		zoomy = 0;
}

void mouseMove(int x, int y)
{
	double rad;
	// Pin the mouse in center and set moves
	if (x > (HEIGHT / 2) || x < (HEIGHT / 2))
	{
		if (x < (HEIGHT / 2))
		{
			angle -= 2.5;
			if (angle < 0)
				angle += 360;
			rad = (float)(3.14159 * angle / 180.0f);
			mov_x = cos(rad) * STEP;
			mov_z = sin(rad) * STEP;
			mov_y = -angle;
		}
		if (x > (HEIGHT / 2))
		{
			angle += 2.5;
			if (angle >= 360)
				angle -= 360;
			rad = (float)(3.14159 * angle / 180.0f);
			mov_x = cos(rad) * STEP;
			mov_z = sin(rad) * STEP;
			mov_y = -angle;
		}
		glutWarpPointer(HEIGHT >> 1, WIDTH >> 1);
	}
}

void Initialize(void)
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.3, 0.6, 0.8, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE_LIGHT);
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE_LIGHT);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Projection coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, 1, 0.1, 5500);

	unsigned int ih = 0, iw = 0;
	unsigned char *texture = NULL;
	unsigned char *texture1 = NULL;
	texture = loadBMP_custom("imagem.bmp", iw, ih);

	texture1 = loadBMP_custom("img.bmp", iw, ih);
	glShadeModel(GL_SMOOTH);

	// Define a textura corrente
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, texnum);

	glBindTexture(GL_TEXTURE_2D, texnum[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iw, ih, 0,
							 GL_RGB, GL_UNSIGNED_BYTE, texture);
	gluBuild2DMipmaps(texnum[0], GL_RGB, iw, ih, GL_RGB, GL_UNSIGNED_BYTE, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, texnum[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iw, ih, 0,
							 GL_RGB, GL_UNSIGNED_BYTE, texture1);
	gluBuild2DMipmaps(texnum[1], GL_RGB, iw, ih, GL_RGB, GL_UNSIGNED_BYTE, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	delete texture;
	delete texture1;
	glEnable(GL_TEXTURE_2D);

	// Model coordinate system
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	// glDisablel(GL_TEXTURE_2D);
}

void Redisplay(int)
{
	glutPostRedisplay();
	display();
	glutTimerFunc(10000, Redisplay, 1);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(HEIGHT, WIDTH);
	glutCreateWindow("mazE");

	glutTimerFunc(20, Redisplay, 1);
	Initialize();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutKeyboardFunc(Keyboard_Function);
	glutKeyboardUpFunc(releaseKeyN);
	glutSpecialFunc(Special_Function);
	glutSpecialUpFunc(releaseKeySpecial);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(HEIGHT >> 1, WIDTH >> 1);

	glutMainLoop();

	return 0;
}
void drawWindow()
{
	// GLUquadric *quad = gluNewQuadric();
	int movy_x = 0;
	int movy_z = 100;
	//Cima
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, 120, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(93, 1, 5);
	glutSolidCube(2.7);
	glPopMatrix();
	//Baixo
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, -120, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(93, 1, 5);
	glutSolidCube(2.7);
	glPopMatrix();
	//MEIO
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(93, 1, 2);
	glutSolidCube(2.7);
	glPopMatrix();
	//LATERAIS MEIO
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(0, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(2, 1, 85);
	glutSolidCube(2.7);
	glPopMatrix();
	//LATERAIS ESQ
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-60, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(2, 1, 85);
	glutSolidCube(2.7);
	glPopMatrix();
	//LATERAIS DIR
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(60, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(2, 1, 85);
	glutSolidCube(2.7);
	glPopMatrix();

	//LATERAIS ESQ 2
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-123, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(2, 1, 90);
	glutSolidCube(2.7);
	glPopMatrix();
	//LATERAIS DIR 2
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(123, 0, -225);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(2, 1, 90);
	glutSolidCube(2.7);
	glPopMatrix();
}

void drawTable()
{
	// GLUquadric *quad = gluNewQuadric();
	int movy_x = -30;
	int movy_z = -200;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	glDisable(GL_TEXTURE_2D);
	//MESA
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GREEN);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -33, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(37, 17, 1);
	glutSolidCube(2.7);
	glPopMatrix();

	//CONTORNO MESA ESQUERDA
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -32, -24);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(102, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	//CONTORNO MESA DIREITA
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -32, 24);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(102, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	//CONTORNO MESA BAIXO
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-12.5, -32, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 49, 1);
	glutSolidCube(1);
	glPopMatrix();

	//CONTORNO MESA ALTA
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(89, -32, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 49, 1);
	glutSolidCube(1);
	glPopMatrix();

	//Bola
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-7.5, -30, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();
	//AMARELAS
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(12.5, -30, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(50, -30, 15);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, YELLOW);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(50, -30, -15);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	//Ca�apas

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(86, -31.2, -21.7);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 0);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(86, -31.2, 21.7);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 0);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-10.2, -31.2, -21.7);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 0);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MAROON);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(-10.2, -31.2, 21.7);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 0);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	//PERNAS

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(68, -70, -20);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 30);
	glutSolidCube(2.5);
	glPopMatrix();

	//
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(68, -70, 20);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 30);
	glutSolidCube(2.5);
	glPopMatrix();

	//
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(8, -70, -20);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 30);
	glutSolidCube(2.5);
	glPopMatrix();

	//
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(8, -70, 20);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 30);
	glutSolidCube(2.5);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void drawCubo(GLdouble size)
{
	drawcubinho(size, GL_QUADS);
}

void drawcubinho(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
			{
					{-1.0, 0.0, 0.0},
					{0.0, 1.0, 0.0},
					{1.0, 0.0, 0.0},
					{0.0, -1.0, 0.0},
					{0.0, 0.0, 1.0},
					{0.0, 0.0, -1.0}};
	static GLint faces[6][4] =
			{
					{0, 1, 2, 3},
					{3, 2, 6, 7},
					{7, 6, 5, 4},
					{4, 5, 1, 0},
					{5, 6, 2, 1},
					{7, 4, 0, 3}};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--)
	{
		glBegin(type);
		glTexCoord2f(0, 0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(1, 1);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(0, 1);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1, 0);
		glVertex3fv(&v[faces[i][3]][0]);
		glNormal3fv(&n[i][0]);
		glEnd();
	}
}

void drawBacia()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glPushMatrix();
	glPushMatrix();
	desenhaCorpoB();
	desenhaBaseB();
	glPopMatrix();

	glPopMatrix();

	glDisable(GL_BLEND);
}

void desenhaBaseB()
{

	GLfloat cp[2][9][3] = {
			{{-4.5, 0.0, -1.5}, {-4.5, 2.7, -1.5}, {0.0, 2.7, -1.5}, {4.5, 2.7, -1.5}, {4.5, 0.0, -1.5}, {4.5, -2.7, -1.5}, {0.0, -2.7, -1.5}, {-4.5, -2.7, -1.5}, {-4.5, 0.0, -1.5}},
			{{-0.0, 0.0, -1.5}, {-0.0, 0.0, -1.5}, {0.0, 0.0, -1.5}, {0.0, 0.0, -1.5}, {0.0, 0.0, -1.5}, {0.0, -0.0, -1.5}, {0.0, -0.0, -1.5}, {-0.0, -0.0, -1.5}, {-0.0, 0.0, -1.5}}};

	int u, v;
	GLint un = 30;
	GLint vn = 30;
	glDisable(GL_BLEND);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 27, 2, 0, 1, 3, 9, &cp[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_QUADS);
	for (u = 0; u < un; u++)
	{
		for (v = 0; v < vn; v++)
		{
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)u / un);
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
		}
	}
	glEnd();
	glEnable(GL_BLEND);
}

void desenhaCorpoB()
{

	GLfloat cp[4][9][3] = {
			{{-4.5, 0.0, -1.5}, {-4.5, 2.7, -1.5}, {0.0, 2.7, -1.5}, {4.5, 2.7, -1.5}, {4.5, 0.0, -1.5}, {4.5, -2.7, -1.5}, {0.0, -2.7, -1.5}, {-4.5, -2.7, -1.5}, {-4.5, 0.0, -1.5}},
			{{-5.0, 0.0, -0.5}, {-5.0, 3.0, -0.5}, {0.0, 3.0, -0.5}, {5.0, 3.0, -0.5}, {5.0, 0.0, -0.5}, {5.0, -3.0, -0.5}, {0.0, -3.0, -0.5}, {-5.0, -3.0, -0.5}, {-5.0, 0.0, -0.5}},
			{{-5.0, 0.0, 0.5}, {-5.0, 3.0, 0.5}, {0.0, 3.0, 0.5}, {5.0, 3.0, 0.5}, {5.0, 0.0, 0.5}, {5.0, -3.0, 0.5}, {0.0, -3.0, 0.5}, {-5.0, -3.0, 0.5}, {-5.0, 0.0, 0.5}},
			{{-5.0, 0.0, 1.5}, {-5.0, 3.0, 1.5}, {0.0, 3.0, 1.5}, {5.0, 3.0, 1.5}, {5.0, 0.0, 1.5}, {5.0, -3.0, 1.5}, {0.0, -3.0, 1.5}, {-5.0, -3.0, 1.5}, {-5.0, 0.0, 1.5}}};

	int u, v;
	GLint un = 30;
	GLint vn = 30;

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 27, 4, 0, 1, 3, 9, &cp[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_QUADS);
	for (u = 0; u < un; u++)
	{
		for (v = 0; v < vn; v++)
		{
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)u / un);
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
		}
	}
	glEnd();
}

void drawAndroid()
{
	// GLUquadric *quad = gluNewQuadric();
	int movy_x = 1700;
	int movy_z = 0;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);

	//Corpo
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -33, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 17, 27);
	glutSolidCube(2.7);
	glPopMatrix();

	//Braços
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -33, 27);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 27);
	glutSolidCube(2.7);
	glPopMatrix();

	//Braço
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -33, -27);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 27);
	glutSolidCube(2.7);
	glPopMatrix();

	//Pernas
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -83, -15);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 17);
	glutSolidCube(2.7);
	glPopMatrix();

	//Pernas
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, -83, 15);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 17);
	glutSolidCube(2.7);
	glPopMatrix();

	//CABEÇA
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, 5, 0);

	glRotatef(90, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(1, 11.5, 11.5);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	//ANTENAS
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, 25, -15);

	glRotatef(45, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(0.5, 1, 3);
	glutSolidCube(2.7);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RED);
	glTranslatef(250 + movy_x, 0, 250 + movy_z);
	glRotatef(0, 0, 1, 0);
	glTranslatef(38, 25, 15);

	glRotatef(135, 1, 0, 0);
	glColor3f(1, 1, 1);
	glScalef(0.5, 1, 3);
	glutSolidCube(2.7);
	glPopMatrix();
}


GLfloat COR_Cuia[4] = {.90, .700, .50};

void drawTrophy()
{
	glDisable(GL_TEXTURE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BLUEP);
	glPushMatrix();

	drawBodyTrophy();
	drawBaseTrophy();
	glPopMatrix();
	glEnable(GL_TEXTURE);
}

void drawBaseTrophy()
{

	GLfloat cp[2][9][3] = {
			{{-3.0, 0.0, 5.5}, {-3.0, 3.0, 5.5}, {0.0, 3.0, 5.5}, {3.0, 3.0, 5.5}, {3.0, 0.0, 5.5}, {3.0, -3.0, 5.5}, {0.0, -3.0, 5.5}, {-3.0, -3.0, 5.5}, {-3.0, 0.0, 5.5}},
			{{-0.0, 0.0, 5.5}, {-0.0, 0.0, 5.5}, {0.0, 0.0, 5.5}, {0.0, 0.0, 5.5}, {0.0, 0.0, 5.5}, {0.0, -0.0, 5.5}, {0.0, -0.0, 5.5}, {-0.0, -0.0, 5.5}, {-0.0, 0.0, 5.5}}};

	int u, v;
	GLint un = 30;
	GLint vn = 30;

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 27, 2, 0, 1, 3, 9, &cp[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_QUADS);
	for (u = 0; u < un; u++)
	{
		for (v = 0; v < vn; v++)
		{
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)u / un);
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
		}
	}
	glEnd();
}

void drawBodyTrophy()
{

	GLfloat cp[8][9][3] = {
			{{-5.0, 0.0, -1.5}, {-5.0, 5.0, -1.5}, {0.0, 5.0, -1.5}, {5.0, 5.0, -1.5}, {5.0, 0.0, -1.5}, {5.0, -5.0, -1.5}, {0.0, -5.0, -1.5}, {-5.0, -5.0, -1.5}, {-5.0, 0.0, -1.5}},
			{{-1.0, 0.0, -0.5}, {-1.0, 1.0, -0.5}, {0.0, 1.0, -0.5}, {1.0, 1.0, -0.5}, {1.0, 0.0, -0.5}, {1.0, -1.0, -0.5}, {0.0, -1.0, -0.5}, {-1.0, -1.0, -0.5}, {-1.0, 0.0, -0.5}},
			{{-1.0, 0.0, 0.5}, {-1.0, 1.0, 0.5}, {0.0, 1.0, 0.5}, {1.0, 1.0, 0.5}, {1.0, 0.0, 0.5}, {1.0, -1.0, 0.5}, {0.0, -1.0, 0.5}, {-1.0, -1.0, 0.5}, {-1.0, 0.0, 0.5}},
			{{-6.0, 0.0, 1.5}, {-6.0, 6.0, 1.5}, {0.0, 6.0, 1.5}, {6.0, 6.0, 1.5}, {6.0, 0.0, 1.5}, {6.0, -6.0, 1.5}, {0.0, -6.0, 1.5}, {-6.0, -6.0, 1.5}, {-6.0, 0.0, 1.5}},
			{{-6.0, 0.0, 2.5}, {-6.0, 6.0, 2.5}, {0.0, 6.0, 2.5}, {6.0, 6.0, 2.5}, {6.0, 0.0, 2.5}, {6.0, -6.0, 2.5}, {0.0, -6.0, 2.5}, {-6.0, -6.0, 2.5}, {-6.0, 0.0, 2.5}},
			{{-1.0, 0.0, 3.5}, {-1.0, 1.0, 3.5}, {0.0, 1.0, 3.5}, {1.0, 1.0, 3.5}, {1.0, 0.0, 3.5}, {1.0, -1.0, 3.5}, {0.0, -1.0, 3.5}, {-1.0, -1.0, 3.5}, {-1.0, 0.0, 3.5}},
			{{-1.0, 0.0, 4.5}, {-1.0, 1.0, 4.5}, {0.0, 1.0, 4.5}, {1.0, 1.0, 4.5}, {1.0, 0.0, 4.5}, {1.0, -1.0, 4.5}, {0.0, -1.0, 4.5}, {-1.0, -1.0, 4.5}, {-1.0, 0.0, 4.5}},
			{{-3.0, 0.0, 5.5}, {-3.0, 3.0, 5.5}, {0.0, 3.0, 5.5}, {3.0, 3.0, 5.5}, {3.0, 0.0, 5.5}, {3.0, -3.0, 5.5}, {0.0, -3.0, 5.5}, {-3.0, -3.0, 5.5}, {-3.0, 0.0, 5.5}},
	};

	int u, v;
	GLint un = 30;
	GLint vn = 30;

	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 27, 8, 0, 1, 3, 9, &cp[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glBegin(GL_QUADS);
	for (u = 0; u < un; u++)
	{
		for (v = 0; v < vn; v++)
		{
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)(u + 1) / un);
			glEvalCoord2f((GLfloat)(v + 1) / vn, (GLfloat)u / un);
			glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
		}
	}
	glEnd();
}
