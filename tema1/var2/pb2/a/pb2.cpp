/*
**	Autor: Chirculete Vlad Mihai
**	Data: 29.10.2017
**
**	Var 2, Pb2 a)
**/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Text
{
	private:
		int id, length, frequency;

	public:
		Text(int id, int length, int frequency)
		{
			this->id = id;
			this->length = length;
			this->frequency = frequency;
		}

		void setLength(int length) { this->length = length; }
		int getLength() { return this->length; }

		void setFrequency(int frequency) { this->frequency = frequency; }
		int getFrequency() { return this->frequency; }

		int getId() { return this->id; }
};

bool cmp_function (Text* i, Text* j)
{
	if(i->getLength() == j->getLength())
		return (i->getFrequency() > j->getFrequency());

	if(i->getFrequency() == j->getFrequency())
		return (i->getLength() < j->getLength());

	return (i->getLength() < j->getLength());
}

int main()
{
	ifstream f("date.in");
	ofstream o("date.out");

	int n;

	vector<Text*> texts;

	f >> n;	// citim n

	// citim n texte
	for(int i=0; i<n; i++)
	{
		int length, freq;

		f >> length >> freq;

		Text* txt = new Text(i, length, freq);
		texts.push_back(txt);
	}

	// sortam textele
	sort(texts.begin(), texts.end(), cmp_function);

	for(int i=0; i<texts.size(); i++)
		o << texts[i]->getId() + 1 << " ";

	f.close();
	o.close();

	return 0;
}