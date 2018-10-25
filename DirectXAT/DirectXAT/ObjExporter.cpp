#include "ObjExporter.h"
#include "ModelClass.h"
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
using namespace DirectX;


void ObjExporter::Create(vector<ModelClass*> data)
{
	
		ofstream file("House.obj");
		ofstream mtlfile("House.mtl");
		file << "mtllib House.mtl" << endl;
		long lastface = 0;
	for (int i = 0; i < data.size(); i++)
	{


		vector<string> positions, texCords, normals, faces;

		vector<XMFLOAT3> pos3;
		pos3.reserve(data[i]->GetModel().size());
		for (int p = 0; p < data[i]->GetModel().size(); p++)
		{
			XMVECTOR tempposVec;
			FXMVECTOR tempposVec2 = XMVectorSet(data[i]->GetModel()[p].x, data[i]->GetModel()[p].y, data[i]->GetModel()[p].z, 1.0f);
		
			tempposVec = XMVector3Transform(tempposVec2, data[i]->getWorldMat());



			XMFLOAT3 temppos;

			temppos.x = XMVectorGetByIndex(tempposVec,0);
			temppos.y = XMVectorGetByIndex(tempposVec, 1);
			temppos.z = XMVectorGetByIndex(tempposVec, 2);


			pos3.push_back(temppos);
			


		}



		

		for (int p = 0; p < data[i]->GetModel().size(); p++)
		{
			positions.push_back("v " + to_string(pos3[p].x)
				+ " " + to_string(pos3[p].y) + " "
				+ to_string(pos3[p].z));


			texCords.push_back("vt " + to_string(data[i]->GetModel()[p].tu)
				+ " " + to_string(data[i]->GetModel()[p].tv));

			normals.push_back("vn " + to_string(data[i]->GetModel()[p].nx)
				+ " " + to_string(data[i]->GetModel()[p].ny)
				+ " " + to_string(data[i]->GetModel()[p].nz));



		}

		for (int p = 0;  p < data[i]->GetIndices().size(); p++)
		{
			faces.push_back(to_string(data[i]->GetIndices()[p] + 1 + lastface) + "/" + to_string(data[i]->GetIndices()[p] + 1) + "/" + to_string(data[i]->GetIndices()[p] + 1) + " ");

		}

		file << "g default" << endl;

		for (int p = 0; p < positions.size(); p++)
		{
			
			file << positions[p] << endl;
		}
	

		for (int p = 0; p < texCords.size(); p++)
		{
			file << texCords[p] << endl;
		}
	

		for (int p = 0; p < normals.size(); p++)
		{
			file << normals[p] << endl;
		}

		file << "g House "<< i << endl;
		file << "usemtl House" << endl;

		for (int p = 0; p < data[i]->GetIndices().size(); p += 3)
		{
			file << "f " + faces[p] + faces[p + 1] + faces[p + 2] << endl;
			lastface = data[i]->GetIndices()[p];
		}




	}
		mtlfile << "newmtl House" << endl;
		mtlfile << "d 1" << endl;
		mtlfile << "illum 1" << endl;
		mtlfile << "Ka 1.000 1.000 1.000" << endl;
		mtlfile << "Kd 1.000 1.000 1.000" << endl;
		mtlfile << "map_Kd House.tga" << endl;
		mtlfile << "map_Ka House.tga" << endl;

		mtlfile.close();

		file.close();

}
