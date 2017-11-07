/*
**	Autor: Chirculete Vlad Mihai
**	Data: 29.10.2017
**
**	Var 2, Pb3
**/


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Task 
{
	private:
		int id, profit, deadline;

	public:
		Task(int id, int profit, int deadline)
		{
			this->id = id;
			this->profit = profit;
			this->deadline = deadline;
		}

		void setProfit(int profit) { this->profit = profit; }
		int getProfit() { return this->profit; }

		void setDeadline(int deadline) { this->deadline = deadline; }
		int getDeadline() { return this->deadline; }

		int getId() { return this->id; }
};

struct DisjointSet
{
    int *parent;
 
    DisjointSet(int n)
    {
        parent = new int[n+1];
 
        // Fiecare nod este parinte al sau
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
 
    // comprima drumul
    int find(int s)
    {
        // Face ca parintele nodurilor din drumul 
        // de la u --> parent[u] sa pointeze catre parent[u]
        if (s == parent[s])
            return s;
        return parent[s] = find(parent[s]);
    }
 
    // Face ca u sa fie parintele lui v
    void merge(int u, int v)
    {
        // actualizeaza cel mai mare slot
        // disponibil astfel incat acesta sa fie u
        parent[v] = u;
    }
};

bool cmp_function(Task* i, Task* j)
{
	return (i->getProfit() > j->getProfit());
}

int main()
{
	ifstream f("date.in");
	ofstream o("date.out");

	vector<Task*> tasks, result;

	int n, maxDeadline=0;

	f >> n;	// citim n

	// citim activitatile
	for(int i=0; i<n; i++)
	{
		int profit, deadline;

		f >> profit >> deadline;

		Task* t = new Task(i, profit, deadline);
		tasks.push_back(t);
	}

	// gasim deadlineul maxim
	for(int i=0; i<n; i++)
		if(tasks[i]->getDeadline() > maxDeadline)
			maxDeadline = tasks[i]->getDeadline();

	// sortam activitatile descrescator in functie de profit
	sort(tasks.begin(), tasks.end(), cmp_function);

 	DisjointSet ds(maxDeadline);

	// Parcurgem toate activitatile
    for (int i = 0; i < n; i++)
    {
        // Gaseste slotul maxim disponibil pentru activitatea curenta
        int availableSlot = ds.find(tasks[i]->getDeadline());

        // Daca slotul maxim disponibil este mai mare ca 0
        // atunci slotul este liber
        if (availableSlot > 0)
        {
            // Acest slot este luat de jobul i
            // prin urmare trebuie sa actualizam
            // cel mai mare slot disponibil. 
            // OBS: In merge facem ca primul parametru
            // sa devina tatal parametrului doi. 
            // Astfel urmatoarele cautari pentru availableSlot
            // vor intoarce cel mai mare slot disponibil in multimea 
            // availableSlot - 1
            ds.merge(ds.find(availableSlot - 1), 
                             availableSlot);
 
            result.push_back(tasks[i]);
        }
    }


    for(int i=result.size() - 1; i>=0; i--)
    	cout << result[i]->getId()+1 << " ";


	f.close();
	o.close();

	return 0;
}