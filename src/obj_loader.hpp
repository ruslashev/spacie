#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void LoadOBJ(std::string path,
		std::vector<GLfloat> *out_verts,
		std::vector<GLfloat> *out_normals,
		std::vector<GLushort> *out_elements);

#endif

