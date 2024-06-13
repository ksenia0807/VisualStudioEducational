#include <iostream>
#include <fstream>

const char* xFNAME = "sorry.txt";

const int N = 10; //количество вершин
struct edge
{
	int beg;
	int end;
	int weight;
};

int ENTER(const char* xFNAME, edge arr[]);
void SELECTION_SORT(edge* xmass, int kol_reb); //сортировка выбором
int find_set(int k, int* parent);// возращает информацию о том, в каком множестве находится k
void union_sets(int a, int b, int* parent); //объединяет два множеств(первое содержит a, второе - b)
void KRUSKAL(edge* xarr, int kol_reb);
void Bellman_Ford(edge* xarr, int kol, int s);
using namespace std;


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	edge arr[N * (N - 1) / 2];
	int kol_reb = ENTER(xFNAME, arr);
	KRUSKAL(arr, kol_reb);
	int start;
	cout << "Введите стартовую вершину > "; cin >> start;
	cout << "Список кратчайших путей:" << endl;
	Bellman_Ford(arr, kol_reb, start);
	return 0;
}

int ENTER(const char* xFNAME, edge arr[]) //возвращает количество ребер
{
	ifstream fin(xFNAME);
	if (!fin)
	{
		cout << "Файл не найден\n";
		return 0;
	}
	char o;
	fin >> o;
	if (fin.eof())
	{
		cout << "Файл пустой\n";
		return 0;
	}
	fin.seekg(0);
	int i = 0;
	while (!fin.eof())
	{
		fin >> arr[i].beg;
		cout << arr[i].beg << "\t";
		fin >> arr[i].end;
		cout << arr[i].end << "\t";
		fin >> arr[i].weight;
		cout << arr[i].weight << "\t" << endl;
		i++;
	}
	fin.close();
	return i;
}

void SELECTION_SORT(edge* xmass, int kol_reb)
{
	for (int i = 0; i < kol_reb - 1; i++)
	{
		int smallest = i;
		for (int j = i + 1; j < kol_reb; j++)
		{
			if (xmass[j].weight < xmass[smallest].weight)
				smallest = j;
		}
		if (xmass[i].weight != xmass[smallest].weight)
		{
			edge perem;
			perem = xmass[i];
			xmass[i] = xmass[smallest];
			xmass[smallest] = perem;
		}
	}
}

int find_set(int k, int* parent)
{
	if (k == parent[k]) //элемент в корне дерева - нашли лидера
		return k;
	return find_set(parent[k], parent); //продолжаем путь до корня
}

void union_sets(int a, int b, int* parent)
{
	a = find_set(a, parent); //ищем лидера множества, содержащего a
	b = find_set(b, parent);//ищем лидера множества, содержащего b
	if (a != b)  //если a==b, то множества уже объедены, и нет смысла их снова объединять 
		parent[b] = a;
}
void KRUSKAL(edge* xarr, int kol_reb)
{
	SELECTION_SORT(xarr, kol_reb);
	int* parent = new int[N];
	//строим граф, в который изолированно включены все вершины (непересекающиеся множества вершин)
	for (int i = 0; i < N; i++)
	{
		parent[i] = i;
	}
	cout << "Ребра, входящие в остовное дерево\n";
	for (int k = 0; k < kol_reb; k++)
	{
		if (find_set(xarr[k].beg, parent) != find_set(xarr[k].end, parent))
		{
			union_sets(xarr[k].beg, xarr[k].end, parent);
			cout << xarr[k].beg << "\t" << xarr[k].end << "\n";
		}
	}
}

void Bellman_Ford(edge* xarr, int kol, int s)
{
	int d[N * (N - 1) / 2];  //В каждом i-ом элементе массива будет храниться значение кратчайшего пути 
				  //из вершины s до вершины i (если таковое имеется).
	int i, j;

	for (i = 0; i < N; i++) d[i] = 10000;
	d[s] = 0;

	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < kol; j++)
		{
			if (d[xarr[j].beg] + xarr[j].weight < d[xarr[j].end])
			{
				d[xarr[j].end] = d[xarr[j].beg] + xarr[j].weight;
			}
		}
	}
	    
	for (i = 0; i < N; i++) if (d[i] == 10000)
		cout << endl << s << "->" << i << "=" << "Нет пути";
	else cout << endl << s << "->" << i << "=" << d[i];

}