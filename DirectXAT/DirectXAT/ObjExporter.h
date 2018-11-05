#pragma once

#include <vector>

class ModelClass;
class House;
class Skyscraper;
struct ModelType;
using namespace std;


namespace ObjExporter
{
	void Create(vector<House*> houses, vector<Skyscraper*> skyscrapers );
}