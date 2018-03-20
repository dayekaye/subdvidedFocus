#include "blur.h"

Blur::Blur() {
	
}

int Blur::init(double amount) {
	/* create the shader */

	/* create the texture lookups */
	/*std::stringstream ss_y, ss_x;
	ss_y << "  fragcolor = texture(u_tex, 
	) * " << weights[0] << ";\n";
	ss_x << "  fragcolor = texture(u_tex, v_tex) * " << weights[0] << ";\n";

	for (int i = 1; i < 5; ++i) {
		ss_y << "  fragcolor += texture(u_tex, vec2(v_tex.s, v_tex.y + (" << offsets[i] << ".0 * sy))) * " << weights[i] << ";\n";
		ss_y << "  fragcolor += texture(u_tex, vec2(v_tex.s, v_tex.y - (" << offsets[i] << ".0 * sy))) * " << weights[i] << ";\n";
		ss_x << "  fragcolor += texture(u_tex, vec2(v_tex.s + (" << offsets[i] << ".0 * sx), v_tex.t)) * " << weights[i] << ";\n";
		ss_x << "  fragcolor += texture(u_tex, vec2(v_tex.s - (" << offsets[i] << ".0 * sx), v_tex.t)) * " << weights[i] << ";\n";
	}

	ss_y << "}\n";
	ss_x << "}\n";
	std::string yfrag = ss_open.str() + ss_y.str();
	std::string xfrag = ss_open.str() + ss_x.str();*/

	/* create the shaders */
	assert((program = InitShader("blurV.glsl", "blurF.glsl")) != -1);

	/* set the texture binding points */
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "u_tex"), 0);
	xtex_w = glGetUniformLocation(program, "u_tex_w");
	xtex_h = glGetUniformLocation(program, "u_tex_h");

	glUseProgram(prog_y);
	glUniform1i(glGetUniformLocation(program, "u_tex"), 0);
	ytex_w = glGetUniformLocation(program, "u_tex_w");
	ytex_h = glGetUniformLocation(program, "u_tex_h");

	/* create our vao. */
	glGenVertexArrays(1, &VAO);

	return 0;
}

void Blur::blurX(float w, float h) {
	/* make sure init has been called. */
	if (0 == prog_x || 0 == prog_y) {
		return;
	}

	glBindVertexArray(VAO);
	glUseProgram(prog_x);
	glUniform1f(xtex_w, w);
	glUniform1f(xtex_h, h);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Blur::blurY(float w, float h) {
	if (0 == prog_x || 0 == prog_y) {
		return;
	}

	glBindVertexArray(VAO);
	glUseProgram(prog_y);
	glUniform1f(ytex_w, w);
	glUniform1f(ytex_h, h);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
//create our FBOs
