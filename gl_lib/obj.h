#include <string>
#include <vector>

using namespace std;

class Obj
{
	private:
		vector<vector<vector<int>>> faces;
		vector<vector<float>> vertex;
		void read();
		vector<string> specialSplit(string&, char);
		vector<string> split(string&, char);
		vector<vector<int>> faceToInt(string);
		vector<float> vertexToFLoat(string);

	public:
		Obj(string);
		float*** getVertices();
		vector<vector<vector<int>>> getFaces();
		vector<vector<float>> getVertex();
};