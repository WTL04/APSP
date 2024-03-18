#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

//{1, 13, 408} : first int = begin, second int = end, third int = weight

const int INF = INT_MAX; // infinity

// print matrix
void printMatrix(const vector<vector<int>> &matrix) {
  cout << "Matrix: " << endl;
  for (const auto &row : matrix) {
    for (int element : row) {
      cout << element << " ";
    }
    cout << endl;
  }
}

vector<vector<int>> parseFile(const string & filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Failed to open file: " << filename << endl;
    exit(1);
  }

  vector<vector<int>> matrix;
  string line;

  while (getline(file, line)) {

    stringstream ss(line);
    char ch;
    int num;
    vector<int> row;

    while (ss >> ch) {
      if (isdigit(ch) || ch == '-') {

        ss.putback(ch);
        ss >> num;
        row.push_back(num);

      } else if (ch == ',' || ch == '{') {

        continue; // skip commas and {

      } else if (ch == '}') {

        matrix.push_back(row);
        row.clear();

        // if consecutive closing brackets --> break
        char next_char;
        if (ss >> next_char && next_char == '}') {
          break;
        }
      }
    }
  }
  file.close();
  return matrix;
}

void apsp(vector<vector<int>> & matrix, int start, int end, int & shortest_dist)
{
  int n = 1000; // num of vertices in graph
  vector<vector<int>> m(n + 1, vector<int>(n + 1, INF)); //empty 2d vector
  

  for (int v = 0; v < n; v++)
    {
      m[v][v] = 0;
    }

  for (vector<int> & edge : matrix)
    {
      int u = edge[0];
      int v = edge[1];
      int weight = edge[2];
      m[u][v] = weight;
      m[v][u] = weight;  // Edge from v to u (for undirected graphs)
    }
  

  for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (m[i][k] != INF && m[k][j] != INF) {
                    m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
                }
            }
        }
    }
    shortest_dist = m[start][end];
}


int main() {
  vector<vector<int>> matrix = parseFile("graph.txt"); ;

  int start;
  int end;
  int shortest_dist;
  vector<int> shortest_path;
  
  cout << "Enter starting vertex: ";
  cin >> start;
  cout << endl;

  cout << "Enter ending vertex: ";
  cin >> end;
  cout << endl;

   // Find shortest path from vertex 1 to vertex 8
    apsp(matrix, start, end, shortest_dist);

    cout << "Shortest path from vertex " << start << " to vertex " << end << ": " << shortest_dist << endl;
    cout << endl;

  return 0;
}