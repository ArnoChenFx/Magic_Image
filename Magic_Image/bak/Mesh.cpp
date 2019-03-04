#include "Mesh.h"
//#include <glad/glad.h> 
#include <string>
#include <qopengltexture.h>
#include <iostream>
#include <qopenglfunctions.h>
#include "OpenGLWindow.h"
using namespace std;

//Mesh::Mesh(float verts[])
//{
//	//直接对内存进行拷贝
//	//把float[]转化成vector<Vertex>
//	this->vertices.resize(36);
//	memcpy((&this->vertices[0]), verts,36*8*sizeof(float));
//
//	//this->indices = indices;
//	//this->textures = textures;
//
//	this->setupMesh();
//}

Mesh::Mesh(std::vector<Vertex> vs, std::vector<unsigned int> is, std::vector<Texture> ts, OpenGLWindow *w)

{
	window = w;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}


Mesh::~Mesh()
{
	//window->VAO.destroy();
	//window->VBO.destroy();
	//window->EBO.destroy();
}

void Mesh::Draw(Shader *shader)
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

	// Bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	int sz = this->textures.size();

	//QList<QOpenGLTexture *> tex;


	for (unsigned int i = 0; i < sz; i++)
	{
		//QOpenGLTexture * tx;
		f->glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
		// Retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = this->textures[i].type;

		if (name == "texture_diffuse")
		{
			number = to_string(diffuseNr++);
			//tx = new QOpenGLTexture(QImage(QString::fromStdString(to_string(diffuseNr++))).mirrored());
		}
			
		else if (name == "texture_specular")
		{
			number = to_string(specularNr++);
			//tx = new QOpenGLTexture(QImage(QString::fromStdString(to_string(specularNr++))).mirrored());
		}


		// Now set the sampler to the correct texture unit
		shader->setInt(name,i);
		//shader->shaderProgram->setUniformValue(name.c_str(), i);
		// And finally bind the texture
		f->glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
		
		//this->textures[i].tex->bind();

		//tx = this->textures[i].tex;
		//tex.append(tx);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	//shader->setFloat("material.shininess", 16.0F);

	// Draw mesh
	window->VAO.bind();
	//f->glBindVertexArray(this->VAO);
	f->glDrawArrays(GL_TRIANGLES, 0, 36);//deleted
	f->glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	//f->glBindVertexArray(0);
	window->VAO.release();

	//清空槽位
	for (unsigned int i = 0; i < sz; i++)
	{
		f->glActiveTexture(GL_TEXTURE0 + i);
		f->glBindTexture(GL_TEXTURE_2D, 0);
		//tex[i]->release();
	}
}

void Mesh::setupMesh()
{

	
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	//f->initializeOpenGLFunctions();
	//QOpenGLContext::currentContext()->makeCurrent();
	//VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	//EBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

	// Create buffers/arrays
	//window->VAO.create();
	window->VAO.bind();
	//window->VAO.bind();


	window->VBO.create();
	window->EBO.create();

	//if (window->VAO.isCreated() == false) {
	//	std::cout << "ERROR - Vertex Buffer Object Couldn't created!!!" << std::endl;
	//	exit(1);
	//}

	//glGenVertexArrays(1, &this->VAO);
	//f->glGenBuffers(1, &this->VBO);
	//f->glGenBuffers(1, &this->EBO);

	
	//glBindVertexArray(this->VAO);
	// 绑定VBO ,向VBO注入数据
	window->VBO.bind();
	//window->VBO.allocate(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
	//f->glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//f->glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	// 绑定VEO,向VEO注入数据
	window->EBO.bind();
	//window->EBO.allocate(&this->indices[0], this->indices.size() * sizeof(unsigned int));
	//f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	//window->VAO.bind();
	// Vertex Positions
	//VAO.enablever

	f->glEnableVertexAttribArray(0);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	// Vertex Normals
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	f->glEnableVertexAttribArray(2);
	f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

	//f->glBindVertexArray(0);
	window->VAO.release();
}