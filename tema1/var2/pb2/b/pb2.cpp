/*
**	Autor: Chirculete Vlad Mihai
**	Data: 29.10.2017
**
**	Var 2, Pb2 b)
**/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Text
{
	private:
		int id, length;

	public:
		Text(int id, int length)
		{
			this->id = id;
			this->length = length;
		}

		void setLength(int length) { this->length = length; }
		int getLength() { return this->length; }

		int getId() { return this->id; }
};

bool cmp_function (Text* i, Text* j)
{
	return (i->getLength() < j->getLength());
}

int main()
{
	ifstream f("date.in");
	ofstream o("date.out");

	int n, p;

	vector<Text*> texts, *tapes;

	f >> n >> p;	// citim n si p

	// alocam P benzi
	tapes = new vector<Text*>[p];

	// citim n texte
	for(int i=0; i<n; i++)
	{
		int length;

		f >> length;

		Text* txt = new Text(i, length);
		texts.push_back(txt);
	}

	// sortam textele crescator
	sort(texts.begin(), texts.end(), cmp_function);

	// adaugam pe fiecare banda cate un text pana terminam toate textele
	int currentTextIndex = 0, currentTape = 0;
	while(currentTextIndex < texts.size())
	{
		if(currentTape >= p)
			currentTape = 0;

		tapes[currentTape].push_back(texts[currentTextIndex]);

		currentTextIndex++;
		currentTape++;
	}

	// scrie in fisier benzile
	currentTape = 0; currentTextIndex = 0;
	while(currentTape < p)
	{
		if(currentTextIndex == 0)
			o << "\nBanda " << currentTape << ": ";

		o << tapes[currentTape][currentTextIndex]->getId() + 1 << " ";

		currentTextIndex++;

		if(currentTextIndex >= tapes[currentTape].size())
		{
			currentTextIndex = 0;
			currentTape++;
		}
	}

	f.close();
	o.close();

	return 0;
}