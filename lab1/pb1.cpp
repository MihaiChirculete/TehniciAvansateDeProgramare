/*
	a1, a2, ... an APARTINE Z
	n APARTINE N
	S APARTINE Z
	(i, j), i<j a.î ai + aj = S
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Number{
	private:
		int id, val;

	public:
		Number()
		{
			this->id = 0;
			this->val = 0;
		}

		Number(int id, int val)
		{
			this->id = id;
			this->val = val;
		}

		void setID(int id) { this->id = id; }
		int getID() { return this->id; }

		void setVal(int val) { this->val = val; }
		int getVal() { return this->val; }

		friend bool operator<(const Number& l, const Number& r)
    	{
    		return l.val < r.val;
    	}
};

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int main()
{
	int s, n;

	vector<Number> a;

	cout << "N: "; cin >> n; cout << endl;
	cout << "S: "; cin >> s; cout << endl;

	for(int i=0; i<n; i++)
	{	
		Number x;
		int val;

		cout << "a" << i << "= ";
		cin >> val;
		x.setID(i);
		x.setVal(val);
		a.push_back(x);
		cout << endl;
	}

	// sortam numerele
	sort(a.begin(), a.end());

	int i=0, j=n-1;

	while(i != j)
	{
		if(a[i].getVal() + a[j].getVal() > s)
			j--;
		else if(a[i].getVal() + a[j].getVal() < s)
			i++;
		else if(a[i].getVal() + a[j].getVal() == s)
			break;
	}

	if(a[i].getID() > a[j].getID())
	{
		int k = i;
		i = j;
		j = k;
	}

	if(a[i].getVal() + a[j].getVal() != s)
		cout << "Nu exista!\n";
	else
	{
		cout << "i= " << a[i].getID() << endl;
		cout << "j= " << a[j].getID() << endl;
	}

	return 0;
}