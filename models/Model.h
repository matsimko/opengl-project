#pragma	once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::vec3
#include "Loadable.h"
#include "ShaderProgram.h"
#include "Material.h"

//Technically, this class could implement the whole loading for ModelWithXXX by parametrizing the load depending on number of floats per vertex,
//but it would seem like overengineering to do it now.
class Model : public Loadable {
private:
	GLuint VAO;
	Material* material;
protected:
	virtual void doLoad(GLuint VBO) = 0;
	virtual void doDraw(ShaderProgram* shaderProgram) = 0;
public:
	Model(Material* material = new Material());
	~Model();
	//(template method pattern) (I keep forgetting to call this method, but polymorphism doesn't work in the constructor so this is necessary)
	virtual void load() override;

	//(template method pattern)
	void draw(ShaderProgram* shaderProgram);
};

