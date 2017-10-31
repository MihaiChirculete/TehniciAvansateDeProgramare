/*
**	Autor: Chirculete Vlad Mihai
**	Data: 29.10.2017
**  
**	Var 2, Pb1
**/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Cube
{
	private:
		int id, edge, col;

	public:
		Cube(int id, int edge, int color)
		{
			this->id = id;
			this->edge = edge;
			this->col = color;
		}

		void setEdge(int edge) { this->edge = edge; }
		int getEdge() { return this->edge; }

		void setColor(int color) { this->col = color; }
		int getColor() { return this->col; }

		int getId() { return this->id; }
};

// functia de sortare descrescatoare
bool cmp_function (Cube* i, Cube* j) { return (i->getEdge() > j->getEdge()); }

int main()
{
	ifstream f("date.in");
	ofstream o("date.out");

	vector<Cube*> cubes, tower;

	int n, p;

	// citim N si P
	f >> n >> p;

	// citim cuburile
	for(int i=0; i<n; i++)
	{
		int edge, color;
		f >> edge >> color;

		Cube *c = new Cube(i, edge, color);
		cubes.push_back(c);
	}

	// sortam descrescator cuburile (in functie de laturile lor)
	sort(cubes.begin(), cubes.end(), cmp_function);

	int lastInsertedLength, lastInsertedColor, currentCubeIndex, totalHeight=0;

	// adaugam primul cub la vectorul ce constituie turnul nostru
	tower.push_back(cubes[0]);

	// primul cub din vectorul de cuburi care nu a fost inca adaugat la turn
	currentCubeIndex = 1;

	// salvam latura si culoarea ultimului cub adaugat la turn
	lastInsertedLength = cubes[0]->getEdge();
	lastInsertedColor = cubes[0]->getColor();

	// modificam inaltimea turnului
	totalHeight += cubes[0]->getEdge();

	while(currentCubeIndex < n)
	{
		if(cubes[currentCubeIndex]->getEdge() <= lastInsertedLength && cubes[currentCubeIndex]->getColor() != lastInsertedColor)
		{
			// adaugam primul cub gasit cu proprietatea ca latura sa este mai mica sau egala decat a ultimului adaugat
			// iar culoarea este diferita
			tower.push_back(cubes[currentCubeIndex]);

			// salvam latura si culoarea ultimului cub adaugat la turn
			lastInsertedLength = cubes[currentCubeIndex]->getEdge();
			lastInsertedColor = cubes[currentCubeIndex]->getColor();

			// modificam inaltimea turnului
			totalHeight += lastInsertedLength;
		}

		// trecem la urmatorul cub din vector
		currentCubeIndex++;
	}

	
	// scrie in fisier inaltimea
	o << totalHeight << endl;

	// scrie si in fisier cuburile
	for(int i=0; i<tower.size(); i++)
		o << tower[i]->getId()+1 << " ";

	cout << endl;

	f.close();
	o.close();

	return 0;
}