#include "obj_loader.hpp"

using namespace std;

void LoadOBJ(std::string path,
		std::vector<GLfloat> *out_verts,
		std::vector<GLfloat> *out_normals,
		std::vector<GLushort> *out_elements)
{
	std::ifstream ifs(path.c_str(), std::ifstream::in);
	assertf(ifs, "Failed to open file \"%s\" for reading.", path.c_str());

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLushort> elements;

	std::string temp;
	while (1) {
		ifs >> temp;
		if (!ifs.good())
			break;
		GLfloat x, y, z;
		if (temp == "v") {
			ifs >> x >> y >> z;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		} else if (temp == "vn") {
			ifs >> x >> y >> z;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		} else if (temp == "f") {
			GLushort a, b, c;
			ifs >> a >> b >> c;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
	}

	printf("verts: %zu\n", vertices.size());
	printf("norms: %zu\n", normals.size());
	printf("elems: %zu\n", elements.size());

	if (out_verts)
		*out_verts = vertices;
	if (out_normals)
		*out_normals = normals;
	if (out_elements)
		*out_elements = elements;
}

