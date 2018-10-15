#pragma once

#include <vector>

struct ModelType;
using namespace std;


namespace ObjExporter
{
	void Create(vector<ModelType> data, vector<long> indices);
}