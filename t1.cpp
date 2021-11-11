#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

ifstream f("abc.in");
ofstream g("abc.out");

const int nmax = 99999;
class graf
{
private:
    int n, m;
    vector <vector <int> > muchii;
    void DFS(int s, vector<int>&vizitate);
    void st(int a, vector<int> vizitate, stack<int>& s);

public:
    graf(int n, int m);
    void citire_orientat(int m);
    void citire_neorientat(int m);
    void bfs(int s);
    int conexe(int s);
    bool Havel_Hakimi(vector<int>v, int n);
    void sortare_topologica(int n);
};
graf::graf(int n, int m)
{
    this->n=n;
    this->m=m;
}
void graf::citire_neorientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
        muchii[nod2].push_back(nod1);
    }
}
void graf::citire_orientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
    }
}

void graf::bfs(int s)
{

    queue<int> q;
    vector<bool> vizitat;
    vector<int> distanta;
    for (int i = 0; i < n; i++)
        vizitat[i] = false;
    for (int i = 0; i <= n; i++)
    {
        vizitat.push_back(0);
        distanta.push_back(-1);
    }          //populeza vectorii si ii initializeaza ca si nevizitati
    q.push(s); //adaugam in coada s-ul de start si il marcam ca vizitat si distanta 0
    vizitat[s] = true;
    distanta[s] = 0;
    while (!q.empty()) //daca avem elemente in coada, executam:
    {
        int curent = q.front(); //nodul curent devine cel mai vechi nod adaugat in coada
        q.pop();
        //parcurgem lista de adicaneta pt a gasi varfurile adiacente nevizitate ale noduliui curent
        for (auto i:muchii[curent])
        {
            if (!vizitat[i])
            {
                vizitat[i] = true;
                q.push(i);
                distanta[i] = distanta[curent] + 1;
            }
        }
    }

}

void graf::DFS(int s, vector<int> &vizitate)
{
    vizitate[s] = 1;
    for (int i : muchii[s])
    {
        if (vizitate[i] == 0)
        {
            DFS(i, vizitate);
        }
    }
}

int graf::conexe(int s)
{   vector<int>vizitate;
    int componente_conexe = 0;
    int i;
    do
    {
        vizitate.push_back(0);
        i++;

    } while (i <= n);

    for (i = 1; i < vizitate.size(); i++)
    {
        if (vizitate[i] == 0)
        {
            DFS(i, vizitate);
            componente_conexe++;
        }
    }
    return componente_conexe;
}

bool Havel_Hakimi(vector<int> &v, int n)
{
    bool stare=1;
    while (stare)
    {
        sort(v.begin(), v.end(), greater<int>());
        if (v[0] == 0)
            return true; //verificam daca primul element e 0 dupa sortare

        int a = v[0];           //salvam valoarea primului el inainte sa il stergem
        v.erase(v.begin() + 0); //stergem primul element
        if (a > v.size())
            return false; //atunci nu vom avea cum sa scadem 1 din primele a elemente ramase
        for (int i = 0; i < a; i++)
        {
            v[i]--;
            if (v[i] < 0)
                return false; //oprim executarea deoarece o valoare nu poate fi negativa in cazul in care putem avea graf
        }
    }
}
void graf::st(int a, vector<int> vizitate, stack<int>& s)
{
    vizitate[a]=1; //marcam ca vizitat primul nod
    for(int i=1;i< muchii.size()-1;i++)
        if(vizitate[a]==0)//daca gasim un nod nevizitat, aplicam sort top pe el recursiv
            st(i, vizitate, s);
    s.push(a);//punem nodul curent in stack
}
void graf::sortare_topologica(int n)
{
    stack<int> s;
    vector<int> vizitate;
    for(int i=0;i<n;i++)
        vizitate[i]=0; //marcam ca fiind nevizitate

    for(int i=0; i<n;i++)
        if(vizitate[i]==0)
            st(i,vizitate,s);
    while(s.empty()==false)
    {cout<<s.top()<<"";
    s.pop();}//afisam stiva cu rezultatul final

}
int main()
{

}
