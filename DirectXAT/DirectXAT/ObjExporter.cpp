#include "ObjExporter.h"
#include "ModelClass.h"
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
using namespace DirectX;


void ObjExporter::Create(vector<ModelClass*> data)
{
	
	for (int i = 0; i < data.size(); i++)
	{

		ofstream file("House.obj");

		vector<string> positions, texCords, normals, faces;


		vector<XMVECTOR> pos;
		pos.reserve(data[i]->GetModel().size());
		for (int p = 0; p < pos.size(); i++)
		{
			pos[p] = XMVectorSet(data[i]->GetModel()[p].x, data[i]->GetModel()[p].y, data[i]->GetModel()[p].z, 1.0f);
			pos[p] = XMVector3Transform(pos[p], data[i]->getWorldMat());

			

			//pos[p] = XMFLOAT3(data[i]->GetModel()[p].x, data[i]->GetModel()[p].y, data[i]->GetModel()[p].z) * data[i]->getWorldMat();
		}

		XMFLOAT3 position;

		

		for (int p = 0; p < data[i]->GetModel().size(); p++)
		{
			positions.push_back("v " + to_string(data[i]->GetModel()[p].x)
				+ " " + to_string(data[i]->GetModel()[p].y) + " "
				+ to_string(data[i]->GetModel()[p].z));


			texCords.push_back("vt " + to_string(data[i]->GetModel()[p].tu)
				+ " " + to_string(data[i]->GetModel()[p].tv));

			normals.push_back("vn " + to_string(data[i]->GetModel()[p].nx)
				+ " " + to_string(data[i]->GetModel()[p].ny)
				+ " " + to_string(data[i]->GetModel()[p].nz));



		}

		for (int p = 0;  p < data[i]->GetIndices().size(); p++)
		{
			faces.push_back(to_string(data[i]->GetIndices()[p] + 1) + "/" + to_string(data[i]->GetIndices()[p] + 1) + "/" + to_string(data[i]->GetIndices()[p] + 1) + " ");

		}

		file << "mtllib House.mtl" << endl;

		file << endl;


		for (int p = 0; p < positions.size(); p++)
		{
			file << positions[p] << endl;
		}
		file << endl;

		for (int p = 0; p < texCords.size(); p++)
		{
			file << texCords[p] << endl;
		}
		file << endl;

		for (int p = 0; p < normals.size(); p++)
		{
			file << normals[p] << endl;
		}
		file << endl;

		file << "g House" << endl;
		file << "usemtl House" << endl;

		for (int p = 0; p < data[i]->GetIndices().size(); p += 3)
		{
			file << "f " + faces[p] + faces[p + 1] + faces[p + 2] << endl;
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

}
