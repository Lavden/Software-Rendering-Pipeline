#include "Scene.h"
#include "Matrix.h"

extern FrameBuffer fb;
Matrix modelview, perspective, MVP, frustum;

/* set the perspective projection matrix given the following values */
void setPerspectiveProjection(float eye_fov, float aspect_ratio, float z_near, float z_far) {
	perspective = Matrix::createIdentity(4);
	perspective = perspective * Matrix::my_perspective(eye_fov, (double)window_width / (double)window_height, z_near, z_far);

	MVP = perspective * modelview;
}


/* set the modelview matrix with the given parameters */
void setModelviewMatrix(float *eye_pos, float eye_theta, float eye_phi) {
	modelview = Matrix::createIdentity(4);
	modelview = modelview * Matrix::rotateX(-eye_phi);
	modelview =  modelview * Matrix::rotateZ(-eye_theta);
	modelview = modelview * Matrix::my_translate(-eye_pos[0], -eye_pos[1], -eye_pos[2]);
}

/* this implements the software rendering of the scene */ 
void Scene :: renderSceneSoftware(void) {
/* this is the function you will write.  you will need to take the linked list of triangles
   given by *original_head and draw them to the framebuffer fb */
	fb.clear();
	TriangleList *ptr;

	for (ptr = original_head; ptr; ptr = ptr->next) {
		Matrix vector4_0 = Matrix::setVector4(ptr->t->getVertex(0));
		Matrix vector4_1 = Matrix::setVector4(ptr->t->getVertex(1));
		Matrix vector4_2 = Matrix::setVector4(ptr->t->getVertex(2));

		vector4_0 = MVP * vector4_0;
		vector4_1 = MVP * vector4_1;
		vector4_2 = MVP * vector4_2;

		vector4_0.toHomogeneous();
		vector4_1.toHomogeneous();
		vector4_2.toHomogeneous();

		if (!vector4_0.inRange(-1, 1) || !vector4_1.inRange(-1, 1) || !vector4_2.inRange(-1, 1))
			continue;

		// viewport transformation
		// glViewport(x, y, width, height), x,y specify the lower left corner
		float f1 = (700.0 - 0.1) / 2.0;
		float f2 = (700.0 + 0.1) / 2.0;

		vector4_0(0, 0) = 0.5*window_width*(vector4_0.getValueAt(0, 0) + 1.0);
		vector4_0(1, 0) = 0.5*window_height*(vector4_0.getValueAt(1, 0) + 1.0);
		vector4_0(2, 0) = vector4_0(2, 0)*f1 + f2;

		vector4_1(0, 0) = 0.5*window_width*(vector4_1.getValueAt(0, 0) + 1.0);
		vector4_1(1, 0) = 0.5*window_height*(vector4_1.getValueAt(1, 0) + 1.0);
		vector4_1(2, 0) = vector4_1(2, 0)*f1 + f2;

		vector4_2(0, 0) = 0.5*window_width*(vector4_2.getValueAt(0, 0) + 1.0);
		vector4_2(1, 0) = 0.5*window_height*(vector4_2.getValueAt(1, 0) + 1.0);
		vector4_2(2, 0) = vector4_2(2, 0)*f1 + f2;

		Vertex tri_vertex_0(vector4_0.getValueAt(0, 0), vector4_0.getValueAt(1, 0), vector4_0.getValueAt(2, 0), vector4_0.getValueAt(3, 0));
		Vertex tri_vertex_1(vector4_1.getValueAt(0, 0), vector4_1.getValueAt(1, 0), vector4_1.getValueAt(2, 0), vector4_1.getValueAt(3, 0));
		Vertex tri_vertex_2(vector4_2.getValueAt(0, 0), vector4_2.getValueAt(1, 0), vector4_2.getValueAt(2, 0), vector4_2.getValueAt(3, 0));

		Triangle *curr;
		curr = new Triangle(&tri_vertex_0, &tri_vertex_1, &tri_vertex_2);
		curr->setTexture(ptr->t->getTexture());
		curr->setColor(0, 125, 0, 125);
		curr->setColor(1, 0, 125, 125);
		curr->setColor(2, 125, 125, 0);

		curr->setCoords(0, ptr->t->getCoords(0, 0), ptr->t->getCoords(0, 1));
		curr->setCoords(1, ptr->t->getCoords(1, 0), ptr->t->getCoords(1, 1));
		curr->setCoords(2, ptr->t->getCoords(2, 0), ptr->t->getCoords(2, 1));

		curr->renderSoftware();
	}

	//
	//Triangle *t;

	//Vertex v0(1.5, 0, 1);
	//Vertex v1(0, 0.5, 2);
	//Vertex v2(0.3, 0, 0);

	//t = new Triangle(&v0, &v1, &v2);
	//t->setColor(0, 0, 0, 255);
	//t->setColor(1, 0, 0, 255);
	//t->setColor(2, 0, 0, 255);

	/*Matrix vector4_0 = Matrix::setVector4(t->getVertex(0));
	Matrix vector4_1 = Matrix::setVector4(t->getVertex(1));
	Matrix vector4_2 = Matrix::setVector4(t->getVertex(2));

	vector4_0 = MVP * vector4_0;
	vector4_1 = MVP * vector4_1;
	vector4_2 = MVP * vector4_2;

	printf("vector 0, MVP:\n");
	vector4_0.print();
	printf("vector 1, MVP:\n");
	vector4_1.print();
	printf("vector 2, MVP:\n");
	vector4_2.print();

	vector4_0.toHomogeneous();
	vector4_1.toHomogeneous();
	vector4_2.toHomogeneous();

	printf("vector , homogeneous:\n");
	vector4_0.print();
	printf("vector 1, homogeneous:\n");
	vector4_1.print();
	printf("vector 2, homogeneous:\n");
	vector4_2.print();*/

	//viewport transformation
	// glViewport(x, y, width, height), x,y specify the lower left corner
	/*float f1 = (700.0 - 0.1) / 2.0;
	float f2 = (700.0 + 0.1) / 2.0;

	vector4_0(0, 0) = 0.5*window_width*(vector4_0.getValueAt(0, 0) + 1.0);
	vector4_0(1, 0) = 0.5*window_height*(vector4_0.getValueAt(1, 0) + 1.0);
	vector4_0(2, 0) = vector4_0(2, 0)*f1 + f2;

	vector4_1(0, 0) = 0.5*window_width*(vector4_1.getValueAt(0, 0) + 1.0);
	vector4_1(1, 0) = 0.5*window_height*(vector4_1.getValueAt(1, 0) + 1.0);
	vector4_1(2, 0) = vector4_1(2, 0)*f1 + f2;

	vector4_2(0, 0) = 0.5*window_width*(vector4_2.getValueAt(0, 0) + 1.0);
	vector4_2(1, 0) = 0.5*window_height*(vector4_2.getValueAt(1, 0) + 1.0);
	vector4_2(2, 0) = vector4_2(2, 0)*f1 + f2;

	Vertex tri_vertex_0(vector4_0.getValueAt(0, 0), vector4_0.getValueAt(1, 0), vector4_0.getValueAt(2, 0), vector4_0.getValueAt(3, 0));
	Vertex tri_vertex_1(vector4_1.getValueAt(0, 0), vector4_1.getValueAt(1, 0), vector4_1.getValueAt(2, 0), vector4_1.getValueAt(3, 0));
	Vertex tri_vertex_2(vector4_2.getValueAt(0, 0), vector4_2.getValueAt(1, 0), vector4_2.getValueAt(2, 0), vector4_2.getValueAt(3, 0));
	
*/
	// Screen coordinate -> NDC -> raster space:
	//vector4_0.normalized();
	//vector4_1.normalized();
	//vector4_2.normalized();

	//Vertex tri_vertex_0((int)vector4_0.getValueAt(0, 0), (int)vector4_0.getValueAt(1, 0), 0);
	//Vertex tri_vertex_1((int)vector4_1.getValueAt(0, 0), (int)vector4_1.getValueAt(1, 0), 0);
	//Vertex tri_vertex_2((int)vector4_2.getValueAt(0, 0), (int)vector4_2.getValueAt(1, 0), 0);

	/*Triangle *curr;
	curr = new Triangle(&tri_vertex_0, &tri_vertex_1, &tri_vertex_2);

	curr->setCoords(0, t->getCoords(0, 0), t->getCoords(0, 1));
	curr->setCoords(1, t->getCoords(1, 0), t->getCoords(1, 1));
	curr->setCoords(2, t->getCoords(2, 0), t->getCoords(2, 1));

	curr->renderSoftware();*/
	
	return;
}