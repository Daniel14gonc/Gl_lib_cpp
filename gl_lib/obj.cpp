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
		//cout << text << endl;
		if (text.size() > 0 && text.at(0) != ' ' && text.at(0) != '#')
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
			if (line.at(0) == "vt")
			{
				vt.push_back(vertexToFLoat(line.at(1)));
			}
		}	
	}

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
		if (numbers.size() > 1)
		{
			// cout << numbers.size() << endl;
			for (string j : numbers)
			{
				//cout << j << '/';
				if (j != " " && j != "" && !j.empty())
				{
					face.push_back(stoi(j));
				}
			}
			//cout << endl;
		}
		if (face.size() != 0)
			res.push_back(face);
	}
	//cout << res.size() << endl;
	return res;
}

vector<float> Obj::vertexToFLoat(string vertex)
{
	vector<string> temp = split(vertex, ' ');
	vector<float> res;
	for (string i : temp)
	{
		if (i != " " && i != "")
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
			if (i + 1 == line.length())
			{
				if (isdigit(line[i]))
					temp += line[i];
			}
			else
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

vector<vector<float>> Obj::getVt()
{
	return vt;
}