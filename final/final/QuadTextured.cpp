#include "QuadTextured.h"

QuadTextured::QuadTextured(bool chooseShade) {
	build();

	glGenBuffers(1, &VBO);
	
	//move the data onto the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations)+sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexTextureLocations), vertexTextureLocations);

	//set up stuff for the body of the cube
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //make this VAO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //associate the VBO with the active VAO

	
	if (chooseShade) {
		program1 = InitShader("vshaderTM_v150.glsl", "fshaderTM_v150.glsl");
		glUseProgram(program1);

		//link the vertex attributes with the buffer
		GLuint vPosition, vTexture;

		assert((vPosition = glGetAttribLocation(program1, "vPosition")) != -1);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		assert((vTexture = glGetAttribLocation(program1, "vTexture")) != -1);
		glEnableVertexAttribArray(vTexture);
		glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

		//get the texture data for the quad
		glGenTextures(1, &texture);
		int imgsize = 512;
		GLubyte *data = ppmRead("crate_texture.ppm", &imgsize, &imgsize);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgsize, imgsize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  //move the data onto the GPU
		delete[] data;  //dont' need this data now that its on the GPU

						//set the texturing parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//get the locations of the uniform shader variables
		assert((mmLoc = glGetUniformLocation(program1, "model_matrix")) != -1);
		assert((cmLoc = glGetUniformLocation(program1, "cam_matrix")) != -1);
		assert((pmLoc = glGetUniformLocation(program1, "proj_matrix")) != -1);
		assert((tex_loc = glGetUniformLocation(program1, "textureID")) != -1);
	}
	else {
		program = InitShader("blurV.glsl", "blurF.glsl");
		glUseProgram(program);

		//link the vertex attributes with the buffer
		GLuint vPosition, vTexture;

		assert((vPosition = glGetAttribLocation(program, "vPosition")) != -1);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		assert((vTexture = glGetAttribLocation(program, "vTexture")) != -1);
		glEnableVertexAttribArray(vTexture);
		glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

		//get the texture data for the quad
		glGenTextures(1, &texture);
		int imgsize = 512;
		GLubyte *data = ppmRead("crate_texture.ppm", &imgsize, &imgsize);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgsize, imgsize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  //move the data onto the GPU
		delete[] data;  //dont' need this data now that its on the GPU

						//set the texturing parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//get the locations of the uniform shader variables
		assert((mmLoc = glGetUniformLocation(program, "model_matrix")) != -1);
		assert((cmLoc = glGetUniformLocation(program, "cam_matrix")) != -1);
		assert((pmLoc = glGetUniformLocation(program, "proj_matrix")) != -1);
		assert((tex_loc = glGetUniformLocation(program, "textureID")) != -1);
	}
	


}

//on destroy, delete the buffer (cleanup)
QuadTextured::~QuadTextured() {
	glDeleteTextures(1, &texture);
}

void QuadTextured::build(){
	
		index = 0;
		makeQuad(vec4(0,0,0,1), vec4(1,0,0,1),vec4(1,0,-1,1), vec4(0,0,-1,1));
}


void QuadTextured::draw(Camera cam, vector<Light> lights){
	glBindVertexArray(VAO);
	glUseProgram(program);

	//set uniform variable values
	glUniformMatrix4fv(mmLoc, 1, GL_TRUE, modelmatrix);
	glUniformMatrix4fv(cmLoc, 1, GL_TRUE, cam.getCameraMatrix());
	glUniformMatrix4fv(pmLoc, 1, GL_TRUE, cam.getProjectionMatrix());
	glUniform1i(tex_loc, 0);

	//enable the necessary texturing
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	//draw
	glDrawArrays( GL_TRIANGLES, 0, 6);


}


void QuadTextured::makeQuad(vec4 a, vec4 b, vec4 c, vec4 d){
	//Triangle #1
	vertexLocations[index] = a;
	vertexTextureLocations[index] = vec2(0,0);
	index++;
	
	vertexLocations[index] = b;
	vertexTextureLocations[index] = vec2(1,0);
	index++;

	vertexLocations[index] = c;
	vertexTextureLocations[index] = vec2(1,1);
	index++;
	
	//Triangle #2
	vertexLocations[index] = c;
	vertexTextureLocations[index] = vec2(1,1);
	index++;
	
	vertexLocations[index] = d;
	vertexTextureLocations[index] = vec2(0,1);
	index++;

	vertexLocations[index] = a;
	vertexTextureLocations[index] = vec2(0,0);
	index++;
	
}



