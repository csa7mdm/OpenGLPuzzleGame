#include "MyWindow.h"


MyWindow::MyWindow() :GameWindow("OpenGL Puzzle Game", 800, 600)
{
}


MyWindow::~MyWindow()
{
}

void MyWindow::Update(sf::Time dt)
{
	static float t = 0;
	static int fps = 0;
	fps++;
	t += dt.asSeconds();
	if (t > 1)
	{
		t -= 1;
		std::cout << "FPS: " << fps << std::endl;
		fps = 0;
	}

	elapsedTime += dt.asSeconds();
	float x = 8 * sin(elapsedTime);
	float z = 8 * cos(elapsedTime);

	view_mat = glm::lookAt(glm::vec3(x, 8.0f, z), glm::vec3(), glm::vec3(0, 1, 0));
	proj_mat = glm::perspective(45.0f, width*1.0f / height, 0.1f, 100.0f);
}


void MyWindow::Render(sf::Time dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sf::Shader::bind(&normalColorShader);
	glm::mat4 model_mat = glm::translate(1.0f, 0.0f, 1.0f);
	GLuint mvp = glGetUniformLocation(normalColorShader.getNativeHandle(), "mvp_mat");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(proj_mat*view_mat*model_mat));
	GLuint model_mat_location =glGetUniformLocation(normalColorShader.getNativeHandle(), "model_mat");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, glm::value_ptr(model_mat));
	GLuint view_mat_location = glGetUniformLocation(normalColorShader.getNativeHandle(), "view_mat");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view_mat));
	GLuint proj_mat_location = glGetUniformLocation(normalColorShader.getNativeHandle(), "proj_mat");
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, glm::value_ptr(proj_mat));
	cubeGeometry->Bind();
	glDrawElements(GL_TRIANGLES, cubeGeometry->GetIndicesCount(), GL_UNSIGNED_INT, NULL);

	model_mat = glm::translate(-1.0f, 0.0f, 1.0f);
	mvp = glGetUniformLocation(normalColorShader.getNativeHandle(), "mvp_mat");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(proj_mat*view_mat*model_mat));
	model_mat_location = glGetUniformLocation(normalColorShader.getNativeHandle(), "model_mat");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, glm::value_ptr(model_mat));
	glDrawElements(GL_TRIANGLES, cubeGeometry->GetIndicesCount(), GL_UNSIGNED_INT, NULL);

	model_mat = glm::translate(-1.0f, 0.0f, -1.0f);
	mvp = glGetUniformLocation(normalColorShader.getNativeHandle(), "mvp_mat");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(proj_mat*view_mat*model_mat));
	model_mat_location = glGetUniformLocation(normalColorShader.getNativeHandle(), "model_mat");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, glm::value_ptr(model_mat));
	glDrawElements(GL_TRIANGLES, cubeGeometry->GetIndicesCount(), GL_UNSIGNED_INT, NULL);

	model_mat = glm::translate(1.0f, 0.0f, -1.0f);
	mvp = glGetUniformLocation(normalColorShader.getNativeHandle(), "mvp_mat");
	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(proj_mat*view_mat*model_mat));
	model_mat_location = glGetUniformLocation(normalColorShader.getNativeHandle(), "model_mat");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, glm::value_ptr(model_mat));
	glDrawElements(GL_TRIANGLES, cubeGeometry->GetIndicesCount(), GL_UNSIGNED_INT, NULL);
}

void MyWindow::Start()
{
	glClearColor(.192f, 0.302f, 0.475f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	normalColorShader.loadFromFile("NormalColorVS.glsl", "NormalColorFS.glsl");
	cubeGeometry = Geometry::Create_cube();
}