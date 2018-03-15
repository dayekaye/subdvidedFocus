#include "Sphere.h"
#define PI 3.1415926535897932384626433832795

Sphere::Sphere() {

	//get a vertex buffer and a vertex array object
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	build();

	//Now let's set up the shaders!!
	// Load shaders
	//assert((program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl")) != -1);
	assert((program = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl")) != -1);
	glUseProgram(program);  //make it the active one

							//get the location of the vPosition attribute
	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	assert((vNormal = glGetAttribLocation(program, "vNormal")) != -1);
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	//get the location of the model matrix
	assert((mmLoc = glGetUniformLocation(program, "model_matrix")) != -1);
	assert((cmLoc = glGetUniformLocation(program, "cam_matrix")) != -1);
	assert((pmLoc = glGetUniformLocation(program, "proj_matrix")) != -1);
	assert((maLoc = glGetUniformLocation(program, "matAmbient")) != -1);
	assert((mdLoc = glGetUniformLocation(program, "matDiffuse")) != -1);
	assert((msLoc = glGetUniformLocation(program, "matSpecular")) != -1);
	assert((mAlphaLoc = glGetUniformLocation(program, "matAlpha")) != -1);
	assert((lpLoc = glGetUniformLocation(program, "lightPos")) != -1);
	assert((laLoc = glGetUniformLocation(program, "lightAmbient")) != -1);
	assert((ldLoc = glGetUniformLocation(program, "lightDiffuse")) != -1);
	assert((lsLoc = glGetUniformLocation(program, "lightSpecular")) != -1);

}

Sphere::~Sphere() {

}

void Sphere::draw(Camera cam, vector<Light> lights) {
	//make this object's VAO active
	//this in turn makes it's associate VBO active
	//and the attributes links to the shader
	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program


	glUniformMatrix4fv(mmLoc, 1, GL_TRUE, modelmatrix);
	glUniformMatrix4fv(cmLoc, 1, GL_TRUE, cam.getCameraMatrix());
	glUniformMatrix4fv(pmLoc, 1, GL_TRUE, cam.getProjectionMatrix());
	glUniform4fv(maLoc, 1, matAmbient);
	glUniform4fv(mdLoc, 1, matDiffuse);
	glUniform4fv(msLoc, 1, matSpecular);
	glUniform1f(mAlphaLoc, shininess);
	glUniform4fv(lpLoc, 1, lights[0].getPosition());
	glUniform4fv(laLoc, 1, lights[0].getAmbient());
	glUniform4fv(ldLoc, 1, lights[0].getDiffuse());
	glUniform4fv(lsLoc, 1, lights[0].getSpecular());
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

}

void Sphere::build() {
	sqrt2 = (float)sqrt(2.0);
	sqrt6 = (float)sqrt(6.0);

	index = 0;

	tetrahedron(4);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
}

void Sphere::tetrahedron(int count) {
	vec4 v[4] = {
		vec4(0,0,1,1),
		vec4(0, 2*sqrt2/3, -1.0f/3.0f, 1),
		vec4(-sqrt6/3.0f, -sqrt2/3.0f, -1.0f/3.0f, 1.0f),
		vec4(sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f)
	};

	//subdivide each of the 4 faces of tetrahedron count timess
	divideTriangle(v[0], v[1], v[2], count);
	divideTriangle(v[3], v[2], v[1], count);
	divideTriangle(v[0], v[3], v[1], count);
	divideTriangle(v[0], v[2], v[3], count);
}

void Sphere::divideTriangle(const vec4& a, const vec4& b, const vec4& c, int count) {
	if (count > 0) {
		vec4 v1 = unit(a + b);
		v1.w = 1.0;
		vec4 v2 = unit(a + c);
		v2.w = 1.0;
		vec4 v3 = unit(b + c);
		v3.w = 1.0;

		divideTriangle(a, v1, v2, count - 1);
		divideTriangle(c, v2, v3, count - 1);
		divideTriangle(b, v3, v1, count - 1);
		divideTriangle(v1, v3, v2, count - 1);
	}
	else {
		buildTriangle(a,b,c);
	}
}

void Sphere::setMaterial(vec4 d, vec4 a, vec4 s, float sh) {
	matDiffuse = d;
	matAmbient = a;
	matSpecular = s;
	shininess = sh;
}

//void Sphere::triangle(const vec4& a, const vec4& b, const vec4& c) {
//	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0);
//	vertexLocations[index] = a;
//	vertexNormals[index] = color;
//	index++;
//
//	vertexLocations[index] = b;
//	vertexColors[index] = color;
//	index++;
//
//	vertexLocations[index] = c;
//	vertexColors[index] = color;
//	index++;
//}

void Sphere::buildTriangle(const vec4& a, const vec4& b, const vec4& c) {
	//set up the vertices
	int zero, one, two;

	zero = index;
	vertexLocations[index] = a;
	index++;

	one = index;
	vertexLocations[index] = b;
	index++;

	two = index;
	vertexLocations[index] = c;
	index++;

	//compute two of the edges
	vec4 e1 = vertexLocations[one] - vertexLocations[zero];
	vec4 e2 = vertexLocations[two] - vertexLocations[zero];

	//use the cross product to get the direction of the triangle's normal
	vec3 n = cross(vec3(e1.x, e1.y, e1.z), vec3(e2.x, e2.y, e2.z));
	n = normalize(n);
	//use computed normal for each vertex of the triangle
	vertexNormals[zero] = n;
	vertexNormals[one] = n;
	vertexNormals[two] = n;
}

vec4 Sphere::unit(const vec4& p) {
	float len = p.x*p.x + p.y*p.y + p.z*p.z;
	vec4 t;
	if (len > DivideByZeroTolerance) {
		t = p / sqrt(len);
		t.w = 1.0;
	}
	return t;
}