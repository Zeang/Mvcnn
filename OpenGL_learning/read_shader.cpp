#include "header.h"


void read_shader()
{
	string filePath1 = "minimal.ver";
	string filePath2 = "minimal.frag";
	ifstream file;
	file.open(filePath1.c_str(), ios::in);
	if (!file.is_open())
	{
		cout << "Can't open " << filePath1 << endl;
		return;
	}
	string str;
	while (getline(file, str))
	{
		if (str.empty())
			continue;
		//cout << str << endl;
		str_vertex_shader += str + "\n";
	}
	str_vertex_shader += "\0";

	file.close();
	file.open(filePath2.c_str(), ios::in);
	if (!file.is_open())
	{
		cout << "Can't open " << filePath2 << endl;
		return;
	}
	while (getline(file, str))
	{
		if (str.empty())
			continue;
		str_fragment_shader += str + "\n";
	}
	str_fragment_shader += "\0";

	file.close();
	/*size_t size = strlen(str_vertex_shader.c_str());
	testStr = new GLchar[size];
	memcpy(testStr, str_vertex_shader.c_str(), size);*/

}