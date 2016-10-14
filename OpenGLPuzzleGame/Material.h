#pragma once
#include <gl\glew\glew.h>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <memory>
#include <string>
#include<gl\glm\glm.hpp>
#include<gl\glm\gtc\type_ptr.hpp>
#include<gl\glm\gtx\transform.hpp>
class Material
{
private:
	std::shared_ptr<sf::Shader> shader;
	std::map<std::string, std::shared_ptr< sf::Texture>> textures;
	//bool active = false;
	static Material* active;
public:
	Material(std::shared_ptr<sf::Shader> shader);
	~Material();
	virtual void bind();
	GLuint get_uniform_loc(std::string uniform)
	{
		return glGetUniformLocation(shader->getNativeHandle(), uniform.c_str());
	}
	GLuint get_attr_loc(std::string Attrib)
	{
		return glGetAttribLocation(shader->getNativeHandle(), Attrib.c_str());
	}
	void add_texture(std::string tex_uniform_name, std::shared_ptr< sf::Texture> _texture)
	{
		//if the tex_uniform_name exists it will be overwrite otherwise it will be added
		textures[tex_uniform_name] = _texture;
	}
};