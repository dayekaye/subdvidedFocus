#include "Cube.h"

Cube::Cube() {
	buildCube();

	//get buffers for attributes and indices
	glGenBuffers(1, &VBO);

	//put the data on the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);

	//set up stuff for the body of the cube
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	assert((program = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl")) != -1);
	glUseProgram(program);  //make it the active one

	GLuint vPosition, vNormal;
	assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
	glEnableVertexAttribArray(vPosition);  //enable it
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	assert((vNormal = glGetAttribLocation(program, "vNormal")) != -1);
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

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

Cube::~Cube(){

}

//set the materials
void Cube::setMaterial(vec4 d, vec4 a, vec4 s, float sh) {
	matDiffuse = d;
	matAmbient = a;
	matSpecular = s;
	shininess = sh;
}

//----------------------------------------------------------------------------
void Cube::makeQuad(int ind1, int ind2, int ind3, int ind4) {
	int zero, one, two, three, four, five;
	//triangle #1
	vertexLocations[index] = vertices[ind1];
	zero = index;
	index++;

	vertexLocations[index] = vertices[ind2];
	one = index;
	index++;

	vertexLocations[index] = vertices[ind3];
	two = index;
	index++;

	//Triangle #2
	vertexLocations[index] = vertices[ind3];
	three = index;
	index++;

	vertexLocations[index] = vertices[ind4];
	four = index;
	index++;

	vertexLocations[index] = vertices[ind1];
	five = index;
	index++;

	//compute two of the edges
	vec4 e1 = vertexLocations[one] - vertexLocations[zero];
	vec4 e2 = vertexLocations[two] - vertexLocations[zero];

	vec4 e3 = vertexLocations[four] - vertexLocations[three];
	vec4 e4 = vertexLocations[five] - vertexLocations[three];

	//use the cross product to get the direction of the triangle's normal
	vec3 n = cross(vec3(e1.x, e1.y, e1.z), vec3(e2.x, e2.y, e2.z));
	vec3 n1 = cross(vec3(e3.x, e3.y, e3.z), vec3(e4.x, e4.y, e4.z));
	n = normalize(n);
	n1 = normalize(n1);
	//use computed normal for each vertex of the triangle
	vertexNormals[zero] = n;
	vertexNormals[one] = n;
	vertexNormals[two] = n;
	vertexNormals[three] = n1;
	vertexNormals[four] = n1;
	vertexNormals[five] = n1;
}

void Cube::buildCube() {
	index = 0;

	makeQuad(1, 0, 3, 2);  //front
	makeQuad(2, 3, 7, 6);  //right
	makeQuad(3, 0, 4, 7);  //bottom
	makeQuad(6, 5, 1, 2);  //top
	makeQuad(4, 5, 6, 7);  //back
	makeQuad(5, 4, 0, 1);  //left
}

void Cube::draw(Camera cam, vector<Light> lights){

	//Draw the cube body
	glBindVertexArray(VAO);
	glUseProgram(program);  //also switch to using this shader program
							//set all the uniform variables
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE, modelmatrix);
	glUniformMatrix4fv(cmLoc, 1, GL_TRUE, cam.getCameraMatrix());
	glUniformMatrix4fv(pmLoc, 1, GL_TRUE, cam.getProjectionMatrix());
	//glUniformMatrix4fv(pmLoc, 1, GL_TRUE, cam.getProjectionMatrix());
	glUniform4fv(maLoc, 1, matAmbient);
	glUniform4fv(mdLoc, 1, matDiffuse);
	glUniform4fv(msLoc, 1, matSpecular);
	glUniform1f(mAlphaLoc, shininess);
	glUniform4fv(lpLoc, 1, lights[0].getPosition());
	glUniform4fv(laLoc, 1, lights[0].getAmbient());
	glUniform4fv(ldLoc, 1, lights[0].getDiffuse());
	glUniform4fv(lsLoc, 1, lights[0].getSpecular());

	glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

}
