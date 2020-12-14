#include<stdlib.h>
#include<stdio.h>

#define FALSE 0;
#define TRUE 1
#define ERROR 0
#define OK 1
#define Overflow 2//上溢
#define Underflow 3//下溢
#define NotPressent 4//元素不存在
#define Duplicate 5//有重复元素

typedef int BOOL;
typedef int ElemType;
typedef struct mGraph
{
    ElemType** a;//邻接矩阵
    int n;//图的当前顶点数
    int e;//图的当前边数
    ElemType noEdge;//两顶点间无边时的值
}MGraph;



typedef int Status;
Status Init(MGraph* mg, int nSize, ElemType noEdgeValue)//初始化
{
    int i, j;
    mg->n = nSize;
    mg->e = 0;
    mg->noEdge = noEdgeValue;
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));
    if (!mg->a)
        return ERROR;
    for (i = 0; i < mg->n; i++)//动态生成二维数组
    {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));
        for (j = 0; j < mg->n; j++)mg->a[i][j] = mg->noEdge;
        mg->a[i][i] = 0;
    }
    return OK;
}

void Destroy(MGraph* mg)
{
    int i;
    for (i = 0; i < mg->n; i++)
        free(mg->a[i]);
    free(mg->a);
}

Status Insert(MGraph* mg, int u, int v, ElemType w)//边的插入
{
    if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v)
        return ERROR;
    if (mg->a[u][v] != mg->noEdge)
        return Duplicate;//若待插入边已存在，则返回Duplicate
    mg->a[u][v] = w;//插入新边
    mg->e++;
    return OK;
}

Status Remove(MGraph* mg, int u, int v)
{
    if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v)
        return ERROR;
    if (mg->a[u][v] == mg->noEdge)
        return NotPressent;
    mg->a[u][v] = mg->noEdge;//删除边
    mg->e--;
    return OK;
}




/*
typedef struct mGraph
{
    ElemType** a;//邻接矩阵
    int n;//图的当前顶点数
    int e;//图的当前边数
    ElemType noEdge;//两顶点间无边时的值
}MGraph;
*/


//只适用于权值全为1的情况
void Dijkstra(int* m, int* visited, MGraph g, int begin, int end)
{
    int b = begin;
    int i, j;
    int maxSize = 999;

    for (i = 0; i < g.n; i++)
        m[i] = maxSize;

    m[b] = 0;

    for (i = 0; i < g.n; i++) {
        int min = maxSize;
        int minIndex;

        for (j = 0; j < g.n; j++) {//寻找合适的“下一个结点”
            if (m[j] <= min && visited[j] != 1)
            {
                min = m[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1;
        for (j = 0; j < g.n; j++) {
            if (g.a[minIndex][j] == 1 && m[minIndex] + 1 < m[j])
                m[j] = m[minIndex] + 1;
        }
    }
}


int main() {
    MGraph g;
    int nSize, edge, u, v, i, j;
    int p1, p2;
    ElemType w;
    int* Dis;
    int* visited;

    printf("Please enter the size of the mgraph:");
    scanf_s("%d", &nSize);
    Init(&g, nSize, -1);
    Dis = (ElemType*)malloc(nSize * sizeof(ElemType));
    visited = (ElemType*)malloc(nSize * sizeof(ElemType));
    for (i = 0; i < nSize; i++)
    {
        Dis[i] = 0;
        visited[i] = 0;
    }
    printf("Please enter the number of the edges:");
    scanf_s("%d", &edge);
    printf("Now init the graph.\n");

    for (i = 0; i < edge; i++) {
        printf("Please enter the edge:");
        scanf_s("%d%d", &u, &v);
        Insert(&g, u, v, 1);
    }

    //获取想查询的最短路径
    printf("Please enter two points:");
    scanf_s("%d%d", &p1, &p2);

    Dijkstra(Dis, visited, g, p1, p2);

    printf("最短路径为：%d", *(Dis+p2));

    return 0;
}