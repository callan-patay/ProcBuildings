#include "ObjExporter.h"
#include "ModelClass.h"
#include "House.h"
#include "Skyscraper.h"
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
using namespace DirectX;


void ObjExporter::Create(vector<House*> houses, vector<Skyscraper*> skyscrapers)
{
	
		
		ofstream mtlfile("Exports/House.mtl");
		
		

		for (int c = 0; c < houses.size(); c++)
		{
			long lastface = 0;
			ofstream file("Exports/" + houses[c]->getBuildingName() +".obj");
			file << "mtllib House.mtl" << endl;
			for (int i = 0; i < houses[c]->getHouseParts().size(); i++)
			{


				vector<string> positions, texCords, normals, faces;

				vector<XMFLOAT3> pos3;
				pos3.reserve(houses[c]->getHouseParts()[i]->GetModel().size());
				for (int p = 0; p <  houses[c]->getHouseParts()[i]->GetModel().size(); p++)
				{
					XMVECTOR tempposVec;
					FXMVECTOR tempposVec2 = XMVectorSet(houses[c]->getHouseParts()[i]->GetModel()[p].x, houses[c]->getHouseParts()[i]->GetModel()[p].y, houses[c]->getHouseParts()[i]->GetModel()[p].z, 1.0f);

					tempposVec = XMVector3Transform(tempposVec2, houses[c]->getHouseParts()[i]->getWorldMat());
					XMFLOAT3 temppos;

					temppos.x = XMVectorGetByIndex(tempposVec, 0);
					temppos.y = XMVectorGetByIndex(tempposVec, 1);
					temppos.z = XMVectorGetByIndex(tempposVec, 2);
					pos3.push_back(temppos);

				}

				for (int p = 0; p <  houses[c]->getHouseParts()[i]->GetModel().size(); p++)
				{
					positions.push_back("v " + to_string(pos3[p].x)
						+ " " + to_string(pos3[p].y) + " "
						+ to_string(pos3[p].z));


					texCords.push_back("vt " + to_string(houses[c]->getHouseParts()[i]->GetModel()[p].tu)
						+ " " + to_string(houses[c]->getHouseParts()[i]->GetModel()[p].tv));

					normals.push_back("vn " + to_string(houses[c]->getHouseParts()[i]->GetModel()[p].nx)
						+ " " + to_string(houses[c]->getHouseParts()[i]->GetModel()[p].ny)
						+ " " + to_string(houses[c]->getHouseParts()[i]->GetModel()[p].nz));

				}

				for (int p = 0; p < houses[c]->getHouseParts()[i]->GetIndices().size(); p++)
				{
					faces.push_back(to_string(houses[c]->getHouseParts()[i]->GetIndices()[p] + 1 + lastface) + "/" + to_string(houses[c]->getHouseParts()[i]->GetIndices()[p] + 1 + lastface) + "/" + to_string(houses[c]->getHouseParts()[i]->GetIndices()[p] + 1 + lastface) + " ");

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

				file << "g House " << i << endl;
				switch (houses[c]->getHouseParts()[i]->getTextureType())
				{
				case Texture::BRICK:
				{

					file << "usemtl Brick" << endl;
					break;
				}

				case Texture::HOUSE:
				{
					file << "usemtl House" << endl;
					break;
				}
				case Texture::WOOD:
				{
					file << "usemtl Wood" << endl;
					break;
				}
				case Texture::SKYSCRAPER:
				{
					file << "usemtl Skyscraper" << endl;
					break;
				}

				}

				for (int p = 0; p < houses[c]->getHouseParts()[i]->GetIndices().size(); p += 3)
				{
					file << "f " + faces[p] + faces[p + 1] + faces[p + 2] << endl;
				}


				lastface += houses[c]->getHouseParts()[i]->GetIndices()[houses[c]->getHouseParts()[i]->GetIndices().size() - 1] + 1;


			}
			file.close();
		}


		for (int c = 0; c < skyscrapers.size(); c++)
		{
			long lastface = 0;
			ofstream file("Exports/" + skyscrapers[c]->getBuildingName() + ".obj");
			file << "mtllib House.mtl" << endl;
			for (int i = 0; i < skyscrapers[c]->getSkyscraperParts().size(); i++)
			{


				vector<string> positions, texCords, normals, faces;

				vector<XMFLOAT3> pos3;
				pos3.reserve(skyscrapers[c]->getSkyscraperParts()[i]->GetModel().size());
				for (int p = 0; p < skyscrapers[c]->getSkyscraperParts()[i]->GetModel().size(); p++)
				{
					XMVECTOR tempposVec;
					FXMVECTOR tempposVec2 = XMVectorSet(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].x, skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].y, skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].z, 1.0f);

					tempposVec = XMVector3Transform(tempposVec2, skyscrapers[c]->getSkyscraperParts()[i]->getWorldMat());
					XMFLOAT3 temppos;

					temppos.x = XMVectorGetByIndex(tempposVec, 0);
					temppos.y = XMVectorGetByIndex(tempposVec, 1);
					temppos.z = XMVectorGetByIndex(tempposVec, 2);
					pos3.push_back(temppos);

				}

				for (int p = 0; p < skyscrapers[c]->getSkyscraperParts()[i]->GetModel().size(); p++)
				{
					positions.push_back("v " + to_string(pos3[p].x)
						+ " " + to_string(pos3[p].y) + " "
						+ to_string(pos3[p].z));


					texCords.push_back("vt " + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].tu)
						+ " " + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].tv));

					normals.push_back("vn " + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].nx)
						+ " " + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].ny)
						+ " " + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetModel()[p].nz));

				}

				for (int p = 0; p < skyscrapers[c]->getSkyscraperParts()[i]->GetIndices().size(); p++)
				{
					faces.push_back(to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetIndices()[p] + 1 + lastface) + "/" + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetIndices()[p] + 1 + lastface) + "/" + to_string(skyscrapers[c]->getSkyscraperParts()[i]->GetIndices()[p] + 1 + lastface) + " ");

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

				file << "g House " << i << endl;
				switch (skyscrapers[c]->getSkyscraperParts()[i]->getTextureType())
				{
				case Texture::BRICK:
				{

					file << "usemtl Brick" << endl;
					break;
				}

				case Texture::HOUSE:
				{
					file << "usemtl House" << endl;
					break;
				}
				case Texture::WOOD:
				{
					file << "usemtl Wood" << endl;
					break;
				}
				case Texture::SKYSCRAPER:
				{
					file << "usemtl Skyscraper" << endl;
					break;
				}

				}

				for (int p = 0; p < skyscrapers[c]->getSkyscraperParts()[i]->GetIndices().size(); p += 3)
				{
					file << "f " + faces[p] + faces[p + 1] + faces[p + 2] << endl;
				}


				lastface += skyscrapers[c]->getSkyscraperParts()[i]->GetIndices()[skyscrapers[c]->getSkyscraperParts()[i]->GetIndices().size() - 1] + 1;


			}
			file.close();
		}
		mtlfile << "newmtl House" << endl;
		mtlfile << "d 1" << endl;
		mtlfile << "illum 1" << endl;
		mtlfile << "Ka 1.000 1.000 1.000" << endl;
		mtlfile << "Kd 1.000 1.000 1.000" << endl;
		mtlfile << "map_Kd House.tga" << endl;
		mtlfile << "map_Ka House.tga" << endl;

		mtlfile << "newmtl Brick" << endl;
		mtlfile << "d 1" << endl;
		mtlfile << "illum 1" << endl;
		mtlfile << "Ka 1.000 1.000 1.000" << endl;
		mtlfile << "Kd 1.000 1.000 1.000" << endl;
		mtlfile << "map_Kd brick.tga" << endl;
		mtlfile << "map_Ka brick.tga" << endl;

		mtlfile << "newmtl Wood" << endl;
		mtlfile << "d 1" << endl;
		mtlfile << "illum 1" << endl;
		mtlfile << "Ka 1.000 1.000 1.000" << endl;
		mtlfile << "Kd 1.000 1.000 1.000" << endl;
		mtlfile << "map_Kd Wood.tga" << endl;
		mtlfile << "map_Ka Wood.tga" << endl;

		mtlfile << "newmtl Skyscraper" << endl;
		mtlfile << "d 1" << endl;
		mtlfile << "illum 1" << endl;
		mtlfile << "Ka 1.000 1.000 1.000" << endl;
		mtlfile << "Kd 1.000 1.000 1.000" << endl;
		mtlfile << "map_Kd Skyscraper.tga" << endl;
		mtlfile << "map_Ka Skyscraper.tga" << endl;

		mtlfile.close();

	

}
