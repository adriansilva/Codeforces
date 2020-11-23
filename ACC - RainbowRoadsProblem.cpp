#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define endl '\n'

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

#define MOD 1000000007
#define maxN 50005

vector<vector<ii> > graph(maxN);
bool goodNodes[maxN];
bool visited[maxN];
bool allNoGood = false;//If we fall into case 4, we do not need to look any further. There are no good nodes left.

void dfs(int start, int parent)
{
    if(allNoGood) return;
    goodNodes[start] = 0;
    visited[start] = 1; //The actual node has already been visited

    unordered_map<int,int> observedColors;

    for(int i = 0; i<graph[start].size(); i++)
    {
        if(observedColors[graph[start][i].first])//If start node has already the actual color matched before.
        {
            if(observedColors[graph[start][i].first]-1==parent || graph[start][i].second-1 == parent)//If the edge with repeated color connects me with my parent, then there are two edges with the same color connected and in different levels.
            {
                allNoGood = true;
                return;
            }
        }
        else observedColors[graph[start][i].first] = graph[start][i].second;//X color has been matched with Y node.

        if(graph[start][i].second-1 == parent) continue; //Avoid infinite cycle, do not visit again parent
        dfs(graph[start][i].second-1,start);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, node1, node2, color;

    cin >> n;

    // We read the input and create our graph using vector of vectors of pairs
    for(int i = 0; i<n-1; i++)
    {
        cin >> node1 >> node2 >> color;
        graph[node1-1].pb(mp(color,node2));
        graph[node2-1].pb(mp(color,node1));
    }

    memset(goodNodes,1,sizeof(goodNodes));
    for(int i = 0; i<n && !allNoGood; i++)
    {
        if(graph[i].size()<2 || visited[i]) continue; // We ignore leaf nodes and visited nodes

        unordered_map<int,int> observedColors;

        for(int j = 0; j<graph[i].size() && !allNoGood; j++)
        {
            if(observedColors[graph[i][j].first])//If color has already been registered
            {
                dfs(observedColors[graph[i][j].first]-1,i);//Go to saved child node with repeated edge color
                dfs(graph[i][j].second-1,i);//Go to new child node with repeated edge color
            }
            else observedColors[graph[i][j].first] = graph[i][j].second;
        }

    }

    if(allNoGood) cout << 0 << endl;
    else
    {
        vi output;
        int cont = 0;

        for(int i = 0; i<n; i++)
        {
            if(goodNodes[i])
            {
                output.pb(i+1);
                cont++;
            }
        }

        cout << cont << endl;

        for(int i = 0; i<output.size(); i++)
            cout << output[i] << endl;
    }

    return 0;
}
