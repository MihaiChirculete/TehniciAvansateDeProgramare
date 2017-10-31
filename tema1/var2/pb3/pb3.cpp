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

// A Simple Disjoint Set Data Structure
struct DisjointSet
{
    int *parent;
 
    // Constructor
    DisjointSet(int n)
    {
        parent = new int[n+1];
 
        // Every node is a parent of itself
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
 
    // Path Compression
    int find(int s)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (s == parent[s])
            return s;
        return parent[s] = find(parent[s]);
    }
 
    // Makes u as parent of v.
    void merge(int u, int v)
    {
        //update the greatest available
        //free slot to u
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

	//vector<int> result;	// vector de id-uri al taskurilor ce vor constituii secventa optima

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

	// Traverse through all the jobs
    for (int i = 0; i < n; i++)
    {
        // Find the maximum available free slot for
        // this job (corresponding to its deadline)
        int availableSlot = ds.find(tasks[i]->getDeadline());
 
        // If maximum available free slot is greater
        // than 0, then free slot available
        if (availableSlot > 0)
        {
            // This slot is taken by this job 'i'
            // so we need to update the greatest 
            // free slot. Note that, in merge, we 
            // make first parameter as parent of 
            // second parameter. So future queries
            // for availableSlot will return maximum
            // available slot in set of 
            // "availableSlot - 1"
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