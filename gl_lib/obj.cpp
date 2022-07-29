#include "obj.h"
#include <iostream>
#include <fstream>
#include <cstring>  

Obj::Obj(string filename)
{
	string text;

	// Read from the text file
	ifstream file("../objects/" + filename);
	if (!file.is_open())
		cout << "Could not find file" << endl;

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (file, text)) 
	{
		vector<string> line = specialSplit(text, ' ');
		if (line.at(0) == "v")
		{
			vertex.push_back(vertexToFLoat(line.at(1)));
		}
		if (line.at(0) == "f")
		{
			faces.push_back(faceToInt(line.at(1)));
		}
	}

	// Close the file
	file.close();
}

vector<vector<int>> Obj::faceToInt(string faces)
{
	vector<vector<int>> res;
	vector<string> temp = split(faces, ' ');
	for(string i : temp)
	{
		vector<int> face;
		vector<string> numbers = split(i, '/');
		for (string j : numbers)
		{
			face.push_back(stoi(j));
		}
		res.push_back(face);
	}
	return res;
}

vector<float> Obj::vertexToFLoat(string vertex)
{
	vector<string> temp = split(vertex, ' ');
	vector<float> res;
	for (string i : temp)
	{
		res.push_back(stof(i));
	}
	return res;
} 

vector<string> Obj::split(string& line, char delimeter)
{
	vector<string> v;
	string temp = "";
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == delimeter)
		{
			v.push_back(temp);
			temp = "";
		}
		else 
		{
			temp += line[i];
		}
	}
	v.push_back(temp);
	return v;
}



vector<string> Obj::specialSplit(string& line, char delimeter)
{
	vector<string> v;
	string temp = "";
	int count = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == delimeter && count == 0)
		{
			v.push_back(temp);
			temp = "";
			count += 1;
		}
		else 
		{
			temp += line[i];
		}
	}
	v.push_back(temp);
	return v;
}

vector<vector<vector<int>>> Obj::getFaces()
{
	return faces;
}

vector<vector<float>> Obj::getVertex()
{
	return vertex;
}