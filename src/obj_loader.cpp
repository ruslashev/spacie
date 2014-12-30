#include "obj_loader.hpp"
#include "utils.hpp"

using namespace std;

std::vector<float> LoadOBJ(std::string path)
{
	std::ifstream ifs(path.c_str(), std::ifstream::in);
	assertf(ifs, "Failed to open file \"%s\" for reading.", path.c_str());

	std::vector<float> out;

	std::string temp;
	while (1) {
		if (!ifs)
			break;
		ifs >> temp;
		if (temp == "v") {
			float x, y, z;
			ifs >> x >> y >> z;
			cout << x << " " << y << " " << z << endl;
			out.push_back(x);
			out.push_back(y);
			out.push_back(z);
		}
	}

	std::cout << out.size() << std::endl;
	std::cout << out.size() / 3 << std::endl;

	return out;
}

