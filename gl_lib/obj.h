#include <string>
#include <vector>

using namespace std;

class Obj
{
	private:
		vector<vector<vector<int>>> faces;
		vector<vector<float>> vertex;
		vector<vector<float>> vt;
		vector<vector<float>> vn;
		void read();
		vector<string> specialSplit(string&, char);
		vector<string> split(string&, char);
		vector<vector<int>> faceToInt(string);
		vector<float> vertexToFLoat(string);
		vector<float> vnToFLoat(string);

	public:
		Obj(string);
		float*** getVertices();
		vector<vector<vector<int>>> getFaces();
		vector<vector<float>> getVertex();
		vector<vector<float>> getVt();
		vector<vector<float>> getVn();
};