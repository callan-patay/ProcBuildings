#include "ObjExporter.h"
#include "ModelClass.h"
#include <fstream>
#include <string>

using namespace std;

//void ObjExporter::Create(vector<ModelType> data, vector<long>  indices)
//{
//	ofstream file("../DirectXAT/OBJs/house.obj");
//
//	vector<string> positions, texCords, normals, faces;
//
//
//
//	for (int i = 0; i < data.size(); i++)
//	{
//		positions.push_back("v " + to_string(data[i].x) 
//			+ " " + to_string(data[i].y) + " " 
//			+ to_string(data[i].z));
//
//
//		texCords.push_back("vt " + to_string(data[i].tu)
//			+ " " + to_string(data[i].tu));
//
//		normals.push_back("vn " + to_string(data[i].nx)
//			+ " " + to_string(data[i].ny)
//			+ " " + to_string(data[i].nz));
//
//
//
//	}
//
//	for (int i = 0; i < indices.size(); i++)
//	{
//		faces.push_back(to_string(indices[i] + 1) + "/" + to_string(indices[i] + 1) + "/" + to_string(indices[i] + 1));
//
//	}
//
//
//	for (int i = 0; i < data.size(); i++)
//	{
//		file << positions[i] << endl;
//	}
//	file << endl;
//
//	for (int i = 0; i < data.size(); i++)
//	{
//		file << texCords[i] << endl;
//	}
//	file << endl;
//	
//	for (int i = 0; i < data.size(); i++)
//	{
//		file << normals[i] << endl;
//	}
//	file << endl;
//
//
//
//	for (int i = 0; i < indices.size(); i += 3)
//	{
//		file << "f " + faces[i] + faces[i + 1] + faces[i + 2] << endl;
//	}
//
//
//
//}
