#include "Graph.h"  // Заголовок


//----------------------------------------------------------------------------------------//
//------------------------------РЕАЛИЗАЦИЯ МЕТОДОВ----------------------------------------//
//----------------------------------------------------------------------------------------//


// Конструктор
Graph::Graph(const string& file_path, const string& file_type)
{

    if (file_type == "-e") {            // Список рёбер
        read_edge_list(file_path);
    }
    else if (file_type == "-l") {       // Список смежности
        read_adjacency_list(file_path);
    }
    else if (file_type == "-m") {       // Матрица смежности
        read_adjacency_matrix(file_path);
    }
    else {
        cout << "Ошибка" << endl;
    }
    isDirected = is_directed();         // Проверяем ориентирован ли граф
}

//----------------------------------------------------------------------------------------//

// Конструктор по матрице смежности
Graph::Graph(const vector<vector<int>>& adjMatr)
{
    adjacencyMatrix.resize(adjMatr.size(), vector<int>(adjMatr.size(), 0)); // Выделяем память под матрицу смежности
    for (int i = 0; i < adjMatr.size(); ++i)                                // В цикле заполняем матрицу
    {
        for (int j = 0; j < adjMatr.size(); ++j)
        {
            adjacencyMatrix[i][j] = adjMatr[i][j];
        }
    }
    countVertex = adjacencyMatrix.size();   // Фиксируем количество вершин
    isDirected = is_directed();             // Фиксируем ориентированность графа                                
}

//----------------------------------------------------------------------------------------//

// Существует ли такое ребро в графе
bool Graph::is_edge(const Vertex& vi, const Vertex& vj) const
{
    vector<Edge> edges = list_of_edges();       // Получаем список рёбер
    // Обрабатываем вектор ребер
    for (const Edge& edge : edges) {           // Перебираем список рёбер
        // Если нашли ребро в списке - возвращаем true
        if (edge.start.index == vi.index && edge.end.index == vj.index) {
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------//

// Вес ребра
int Graph::weight(const Vertex& vi, const Vertex& vj) const
{
    vector<Edge> edges = list_of_edges();

    // Если нет ребра
    if (!is_edge(vi, vj)) return 0;

    // Обрабатываем вектор ребёр
    for (const Edge& edge : edges) {
        // Нашли подходящее ребро - возвращаем вес
        if (edge.start.index == vi.index && edge.end.index == vj.index) {
            return edge.weight;
        }
    }
}

//----------------------------------------------------------------------------------------//

// Матрица смежности графа
vector<vector<int>> Graph::adjacency_matrix() const
{
    // Возвращаем матрицу
    return adjacencyMatrix;
}


//----------------------------------------------------------------------------------------//

// Список вершин, смежных вершине v
vector<Vertex> Graph::adjacency_list(const Vertex& v) const
{
    // Вектор вершин
    vector<Vertex> adjList;

    // Получаем список рёбер
    vector<Edge> edges = list_of_edges();

    // Обрабатываем список ребёр
    for (const Edge& edge : edges) {
        // Если начало текущего ребра совпадает с вершиной
        if (edge.start.index == v.index)
            adjList.push_back(edge.end);       // Записываем вершину
    }

    // Возвращаем список смежности
    return adjList;
}

//----------------------------------------------------------------------------------------//

// Список смежности графа
vector<vector<Vertex>> Graph::adjacency_list() const
{
    // Список смежности
    vector<vector<Vertex>> adjacencyList;
    // По индексу вершины запихиваем список вершин, смежных текущей вершине
    for (int i = 0; i < countVertex; ++i)
    {
        adjacencyList.push_back(adjacency_list({ i }));
    }
    return adjacencyList;
}

//----------------------------------------------------------------------------------------//

// Список всех ребер/дуг графа
vector<Edge> Graph::list_of_edges() const
{
    vector<Edge> edges;     // Список рёбер
    // Заполняем список рёбер
    for (int i = 0; i < countVertex; ++i)
    {
        for (int j = 0; j < countVertex; ++j)
        {
            if (adjacencyMatrix[i][j])
            {
                edges.push_back({ {i}, {j}, adjacencyMatrix[i][j] });
            }
        }
    }
    return edges;   // Возвращаем поле, в котором список ребёр
}

//----------------------------------------------------------------------------------------//

// Список всех рёбер графа, инцидентных вершине v / исходящих из вершины v
vector<Edge> Graph::list_of_edges(const Vertex& v) const
{
    // Список рёбер
    vector<Edge> edges = list_of_edges();

    // Вспомогательный вектор для записи ребёр
    vector<Edge> incidentEdges;

    //  Обрабатываем список ребёр
    for (const Edge& edge : edges) {
        // Если начало или конец текущего ребра совпали с вершиной
        if (edge.start.index == v.index || edge.end.index == v.index)
            incidentEdges.push_back(edge);  // Записываем ребро в вектор
    }

    // Вовзращаем список инцидентных ребёр
    return incidentEdges;
}

//----------------------------------------------------------------------------------------//

// Граф/орграф
bool Graph::is_directed()
{
    // Список рёбер
    vector<Edge> edges = list_of_edges();

    // Векторы с исходниками и финишами
    vector<int> startVertices;
    vector<int> targetVertices;

    // Обрабатываем список ребер
    for (const auto& edge : edges)
    {
        startVertices.push_back(edge.start.index);
        targetVertices.push_back(edge.end.index);
    }
    // Обрабатываем список полученных вершин
    for (const auto& start : startVertices) {
        if (count(startVertices.begin(), startVertices.end(), start) != count(targetVertices.begin(), targetVertices.end(), start)) {
            return true;    // Если indeg != outdeg => орграф
        }
    }
    return false;
}


//----------------------------------------------------------------------------------------//

// Чтение из списка ребер
void Graph::read_edge_list(const string& filePath)
{
    vector<Edge> edges; // Список рёбер
    // Открываем файл для чтения
    ifstream file(filePath);
    string line;        // Текущая линия
    int start, end;     // Начало конец ребра
    int maxVertexIndex = -1;    // Через вспомогательную стековую переменную считаем количество вершин в графе
    int weight;         // Вес ребра
    while (getline(file, line)) {           // Пока файл не пуст
        stringstream ss(line);              // Текущая линия
        ss >> start >> end;                 // Разбиваем строку на начало и конец
        if (ss.eof()) weight = 1;           // Если список без весов
        else ss >> weight;                  // Иначе - вводим вес
        maxVertexIndex = max(maxVertexIndex, max(start, end));  // Вычисляем максимальную вершину в списке
        edges.push_back(Edge({ start }, { end }, weight));      // Добавляем ребро в список
    }
    file.close();                                               // Закрываем файл
    // Количество вершин
    countVertex = maxVertexIndex;
    // Выделяем необходимую память под матрицу смежности
    adjacencyMatrix.resize(countVertex, vector<int>(countVertex, 0));
    // Заполняем матрицу
    for (const Edge& edge : edges)
    {
        adjacencyMatrix[edge.start.index - 1][edge.end.index - 1] = edge.weight;
    }
}

//----------------------------------------------------------------------------------------//

// Чтение из списков смежности
void Graph::read_adjacency_list(const string& filePath)
{
    // Открываем файл для чтения
    ifstream file(filePath);
    string line;        // Текущая линия
    int counter = 0;    // Счётчик
    int N = 0;          // Индекс максимальной вершины
    vector<set<Vertex>> vertex_to_adjacent_vertices;  // Список списков смежных вершин
    while (getline(file, line)) {       // Пока файл не пуст
        if (!line.empty()) {
            stringstream ss(line);              // Текущая линия
            int vertexIndex;                    // Текущая смежная вершина
            set<Vertex> adjacent_vertices;   // Список смежности
            while (ss >> vertexIndex) {         // Пока в строке есть вершины
                N = max(N, vertexIndex);
                adjacent_vertices.insert({ vertexIndex - 1 });           // Записываем в список смежные вершины
            }

            vertex_to_adjacent_vertices.push_back(adjacent_vertices); // В словарь добавляем список смежности
        }
        else
        {
            vertex_to_adjacent_vertices.push_back({});
        }
        ++counter;
    }
    file.close();                                               // Закрываем файл
    // Количество вершин
    countVertex = max(counter, N);
    // Выделяем необходимую память под матрицу смежности
    adjacencyMatrix.resize(countVertex, vector<int>(countVertex, 0));
    // Заполняем матрицу
    for (int i = 0; i < counter; ++i)
    {
        for (const auto& current : vertex_to_adjacent_vertices[i])
        {
            adjacencyMatrix[i][current.index] = 1;
        }
    }
}

//----------------------------------------------------------------------------------------//

// Чтение из матрицы смежности
void Graph::read_adjacency_matrix(const string& filePath)
{
    ifstream file(filePath);            // Открываем файл для чтения
    string line;                        // Текущая линия
    while (getline(file, line)) {       // Пока не конец файла
        vector<int> row;                // Текущая строка в матрице
        istringstream iss(line);        // Текущая линия в файле
        int num;                        // Число
        while (iss >> num) {            // Пока не конец линии    
            row.push_back(num);         // Записываем в строку матрицы данные
        }
        adjacencyMatrix.push_back(row); // Добавляем в матрицу строку
    }
    file.close();                       // Закрываем файл
    // Количество вершин
    countVertex = adjacencyMatrix.size();
}

//----------------------------------------------------------------------------------------//

// Наличие отрицательных рёбер
bool hasNegativeEdges(const vector<Edge>& edges) {
    for (const auto& edge : edges)
    {
        if (edge.weight < 0) return true;
    }
    return false;                   // Отрицательных ребер не найдено
}

//----------------------------------------------------------------------------------------//