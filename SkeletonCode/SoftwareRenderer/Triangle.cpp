#include "Triangle.h"
#include "FrameBuffer.h"
#include "Texture.h"


extern FrameBuffer fb;

/* for openGL rendering of the triangle */
void Triangle :: renderOpenGL(void) {
	/* first bind the texture */
	if (tex) {
		tex->bind();
	}

	/* now draw the triangle */
	glBegin(GL_TRIANGLES);
		glTexCoord2fv(coords[0]);
		glColor3fv(c[0]);
		glVertex3f(v[0].x, v[0].y, v[0].z);

		glTexCoord2fv(coords[1]);
		glColor3fv(c[1]);
		glVertex3f(v[1].x, v[1].y, v[1].z);

		glTexCoord2fv(coords[2]);
		glColor3fv(c[2]);
		glVertex3f(v[2].x, v[2].y, v[2].z);
	glEnd();

	/* release the texture */
	if (tex) {
		tex->release();
	}

	return;
}

void Triangle::renderSoftware(void) {
	// Set r, g, b color
	float r, g, b;

	// Implement bouding box algorithm
	float x_min, y_min, x_max, y_max;

	x_min = min(min(v[0].x, v[1].x), v[2].x);
	x_max = max(max(v[0].x, v[1].x), v[2].x);
	y_min = min(min(v[0].y, v[1].y), v[2].y);
	y_max = max(max(v[0].y, v[1].y), v[2].y);

	if (x_min < 0.0 || y_min < 0.0 || x_max > window_width || y_max > window_height) {
		return;
	}

	for (float y = y_min; y < y_max; y = y + 1.0) {
		for (float x = x_min; x < x_max; x = x + 1.0) {
			if (insideTriangle(x, y)) {
				//Perspective Correct Interpolation
				Matrix color = Barycentric(x, y);

			}

		}
	}
}