#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include <math.h>

#include "Matrix.h"
#include "Vertex.h"
#include "FrameBuffer.h"
#include "Texture.h"

/* implements the triangle class */
class Triangle {
	private:
		/* per-vertex values */
		float c[3][3];		/* color at each vertex */
		float coords[3][2];

		/* point to the texture that is bound, if any */
		Texture *tex;

	public:
		Vertex v[3];		/* the original vertices of the triangle */

		/* constructors */
		Triangle() {
			v[0].set(0, 0, 0);
			v[1].set(0, 0, 0);
			v[2].set(0, 0, 0);

			c[0][0] = 0.0;	c[0][1] = 0.0;	c[0][2] = 0.0;
			c[1][0] = 0.0;	c[1][1] = 0.0;	c[1][2] = 0.0;
			c[2][0] = 0.0;	c[2][1] = 0.0;	c[2][2] = 0.0;

			coords[0][0] = 0.0;		coords[0][1] = 0.0;	
			coords[1][0] = 0.0;		coords[1][1] = 0.0;	
			coords[2][0] = 0.0;		coords[2][1] = 0.0;

			tex = NULL;
		};

		Triangle(Vertex *v0, Vertex *v1, Vertex *v2) {
			v[0] = (*v0);
			v[1] = (*v1);
			v[2] = (*v2);

			c[0][0] = 0.0;	c[0][1] = 0.0;	c[0][2] = 0.0;
			c[1][0] = 0.0;	c[1][1] = 0.0;	c[1][2] = 0.0;
			c[2][0] = 0.0;	c[2][1] = 0.0;	c[2][2] = 0.0;
			
			coords[0][0] = 0.0;		coords[0][1] = 0.0;		coords[0][2] = 0.0;
			coords[1][0] = 0.0;		coords[1][1] = 0.0;		coords[1][2] = 0.0;
			coords[2][0] = 0.0;		coords[2][1] = 0.0;		coords[2][2] = 0.0;

			tex = NULL;
		};


		/* sets the color of vertex v of the triangle to (r,g,b) */
		void setColor(int v, int r, int g, int b) {
			if ((r < 0) || (r > 255) ||
				(g < 0) || (g > 255) ||
				(b < 0) || (b > 255)) {
				fprintf(stderr,"ERROR! Invalid color set in triangle\n");
				fflush(stderr);
				exit(-1);
			}

			c[v][0] = ((float)r/(float)255);
			c[v][1] = ((float)g/(float)255);	
			c[v][2] = ((float)b/(float)255);
	
			return;
		};

		void setCoords(int v, int s, int t) {
			coords[v][0] = s;
			coords[v][1] = t;

			return;
		};

		void setTexture(Texture *t) {
			tex = t;
			return;
		}

		void setVertex(int i, Vertex ver)
		{
			v[i] = ver;
		}

		int getCoords(int v, int c)
		{
			return coords[v][c];
		}

		Vertex getVertex(int i) {
			return v[i];
		}

		Texture *getTexture()
		{
			return tex;
		}

		/* openGL rendering of the triangle */
		void renderOpenGL(void);
		/* My implementation rendering of the tirangle*/
		void renderSoftware(void);

		/* helper functions for bounding box algorithm and inside test */
		bool insideTriangle(int x, int y) {
			Vertex f0, f1, f2;
			Vertex temp[3];

			temp[0] = v[0]; temp[0].z = 1;
			temp[1] = v[1]; temp[1].z = 1;
			temp[2] = v[2]; temp[2].z = 1;

			/* For debuging*/
			//printf("vertex temp[0]\n");
			//temp[0].print();
			//printf("vertex temp[1]\n");
			//temp[1].print();
			//printf("vertex temp[2]\n");
			//temp[2].print();

			lineEquation(&temp[1], &temp[0], &f0);
			lineEquation(&temp[2], &temp[1], &f1);
			lineEquation(&temp[0], &temp[2], &f2);

			Vertex p(x, y, 1);

			if ((dotProduct(&p, &f0) * dotProduct(&f0, &temp[2]) > 0) &&
				(dotProduct(&p, &f1) * dotProduct(&f1, &temp[0]) > 0) &&
				(dotProduct(&p, &f2) * dotProduct(&f2, &temp[1]) > 0))
			{
				return true;
			}
			return false;

		}

		void lineEquation(Vertex *v1, Vertex *v2, Vertex *f) {
			/* Compute cross product of v1, v2
				v1 = [x1, y1, z1], v2 = [x2, y2, z2]
				| i  j  k |
				| x1 y1 z1| = (y1*z2)i + (x1*y2)k + (x2*z1)j - (x2*y1)k - (x1*z2)j - (y2*z1)i
				| x2 y2 z2|

				= (y1*z2 - y2*z1)i + (z1*x2 - z2*x1)j + (x1*y2 - x2*y1)k
			*/
			f->x = (v1->y * v2->z) - (v2->y * v1->z);
			f->y = (v1->z * v2->x) - (v2->z * v1->x);
			f->z = (v1->x * v2->y) - (v2->x * v1->y);
		}

		float dotProduct(Vertex *v1, Vertex *v2) {
			return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
		}

		Matrix Barycentric(float x, float y)
		{

			return temp;
		}


		/* for debugging */
		void print(void) {
			fprintf(stderr,"Triangle:\n");
			v[0].print();
			v[1].print();
			v[2].print();
			return;
		};
};

#endif		/* TRIANGLE_H */