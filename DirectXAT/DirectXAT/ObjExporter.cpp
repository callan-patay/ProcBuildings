#include "ObjExporter.h"
#include "ModelClass.h"
#include <fstream>
#include <string>

using namespace std;


void ObjExporter::Create(vector<ModelType> data, vector<long> indices)
{
	ofstream file("House.obj");

	vector<string> positions, texCords, normals, faces;



	for (int i = 0; i < data.size(); i++)
	{
		positions.push_back("v " + to_string(data[i].x)
			+ " " + to_string(data[i].y) + " "
			+ to_string(data[i].z));


		texCords.push_back("vt " + to_string(data[i].tu)
			+ " " + to_string(data[i].tv));

		normals.push_back("vn " + to_string(data[i].nx)
			+ " " + to_string(data[i].ny)
			+ " " + to_string(data[i].nz));



	}

	for (int i = 0; i < indices.size(); i++)
	{
		faces.push_back(to_string(indices[i] + 1) + "/" + to_string(indices[i] + 1) + "/" + to_string(indices[i] + 1) + " ");

	}

	file << "mtllib House.mtl" << endl;

	file << endl;


	for (int i = 0; i < data.size(); i++)
	{
		file << positions[i] << endl;
	}
	file << endl;

	for (int i = 0; i < data.size(); i++)
	{
		file << texCords[i] << endl;
	}
	file << endl;

	for (int i = 0; i < data.size(); i++)
	{
		file << normals[i] << endl;
	}
	file << endl;

	//file << "g House" << endl;
	file << "usemtl House" << endl;

	for (int i = 0; i < indices.size(); i += 3)
	{
		file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
	}

	file.close();



	ofstream mtlfile("House.mtl");

	mtlfile << "newmtl House" << endl;
	mtlfile << "d 1" << endl;
	mtlfile << "illum 1" << endl;
	mtlfile << "Ka 1.000 1.000 1.000" << endl;
	mtlfile << "Kd 1.000 1.000 1.000" << endl;
	mtlfile << "map_Kd House.tga" << endl;
	mtlfile << "map_Ka House.tga" << endl;

	mtlfile.close();



}
