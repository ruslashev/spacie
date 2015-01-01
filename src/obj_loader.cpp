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
		if (ifs.eof())
			break;
		ifs >> temp;
		GLfloat x, y, z;
		if (temp == "v") {
			ifs >> x >> y >> z;
			cout << "v " << x << " " << y << " " << z << endl;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		} else if (temp == "vn") {
			ifs >> x >> y >> z;
			cout << "vn " << x << " " << y << " " << z << endl;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		} else if (temp == "f") {
			GLushort a, b, c;
			ifs >> a >> b >> c;
			cout << "f " << a << " " << b << " " << c << endl;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		} else {}
	}

	if (out_verts != NULL)
		*out_verts = vertices;
	if (out_normals != NULL)
		*out_normals = normals;
	if (out_elements != NULL)
		*out_elements = elements;
}

