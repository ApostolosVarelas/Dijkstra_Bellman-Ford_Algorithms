#include <stdio.h>
#include <conio.h>
#include <limits.h> //for INT_MAX

#define INFINITY 9999
#define MAX 10
#define INF INT_MAX

struct AjlistNode
{
  int vId;//Vertices id
  int weight;
  struct AjlistNode*next;
};

struct Graph
{
  int data; //node key value
  struct AjlistNode*next;
};

int get_values_bellman(int startode);
void add_edge(struct Graph*node, int V ,int E,int weight);
void bellman(struct Graph*root,int source);
void view_path(int path[], int location);

void dijkstra(int G[MAX][MAX],int n,int startnode);
int get_values_dijkstra();

int size;

int main(int argc, char arcg[])
{
    float node;
    int method, flag=1, i, j, startnode;
	int *values;

    do
    {
        printf("Please, choose which method you want: \n\n1)Link-state(Dijkstra)\n2)Distance vector(Bellman-Ford)\n3)Both\n");
        scanf("%d",&method);
        system("cls");
        if( method == 1 || method == 2 || method == 3)
        {
            flag = 0;
        }
        else
        {
            printf("Please insert a number between 1 and 3\n\n");
        }
    }while(flag == 1);



	system("cls");

    if(method == 1)
    {
		values = get_values_dijkstra();
		printf("\nEnter the starting node:");
		scanf("%d",&startnode);
		system("cls");
		printf("****\tDijkstra's Algorithm\t****\n\n\n");
		dijkstra(values,6,startnode);
    }
    else if(method == 2)
    {
		printf("\nEnter the starting node:");
		scanf("%d",&startnode);
		system("cls");
		printf("****\tBellman's Algorithm\t****\n\n\n");
		get_values_bellman(startnode);
    }
    else
    {
        values = get_values_dijkstra();
		printf("\nEnter the starting node:");
		scanf("%d",&startnode);
		system("cls");
		printf("****\tDijkstra's Algorithm\t****\n\n\n");
		dijkstra(values,6,startnode);

        printf("\n\n\n****\tBellman's Algorithm\t****\n\n\n");
		get_values_bellman(startnode);
    }
    return 0;
}

int get_values_dijkstra()
{
    int i,j;
    static int values[MAX][MAX];
    FILE *file = fopen("Costs.txt", "r");


    for(i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            fscanf(file, "%d" , &values[i][j]);
        }
        fscanf(file,"\n");
    }

    fclose(file);
    return values;
}

void dijkstra(int values[MAX][MAX],int n,int startnode)
{
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(values[i][j]==0)
            {
                cost[i][j]=INFINITY;
            }
            else
            {
                cost[i][j]=values[i][j];
            }
        }
    }
    for(i=0; i<n; i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    while(count<n-1)
    {
        mindistance=INFINITY;
        for(i=0;i<n;i++)
        {
            if(distance[i]<mindistance && !visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }

//check if a better path exists through nextnode
        visited[nextnode]=1;
        for(i=0;i<n;i++)
        {
            if(!visited[i])
            {
                if(mindistance+cost[nextnode][i]<distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            }
        }
        count++;
    }

//print the path and distance of each node
    for(i=0;i<n;i++)
    {
        if(i!=startnode)
        {
            printf("\nDistance of node%d=%d",i,distance[i]);
            printf("\n   Path=%d",i);
            j=i;
            do
            {
                j=pred[j];
                printf("<-%d",j);
            }while(j!=startnode);
        }
        else if (i==startnode){
            printf("Distance of node%d=%d",i,distance[i]);
            printf("\n   Path=%d",i);
            printf("<-%d",i);
        }
    }

    printf("\nDestination Node\tCost\n");
    for(i=0;i<6;i++)
    {
        printf("%d\t\t\t%d\n", i,distance[i]);
    }
}

int get_values_bellman(int startnode)
{
 int i,j,values[8][3];
    size=6;
    struct Graph*node=NULL;

    node=(struct Graph*)malloc(sizeof(struct Graph)*size);

    if(node==NULL)
    {
      printf("\n Memory overflow");
    }else
    {
        //First set node keys
		if(node!=NULL && size>0)
  		{
    		int index=0;
    		for(index;index<size;index++)
    		{
        		//set vertic node data
        		node[index].data=index;//set node key
        		//Initial no AjlistNode
        		//set NULL Value
        		node[index].next=NULL;
      		}
    	}else
    	{
      		printf("Vertic Node is Empty");
    	}
		FILE *file = fopen("BellCosts.txt", "r");

		for(i = 0;i<8;i++)
		{
			for(j = 0;j<3;j++)
			{
				fscanf(file, "%d", &values[i][j]);
			}
			fscanf(file,"\n");
		}

    	for(i=0;i<8;i++)
		{
			add_edge(node,values[i][0],values[i][1],values[i][2]);
		}

		bellman(node,startnode);
	}
}

void add_edge(struct Graph*node, int V ,int E,int weight)
{
	//add edge form V to E
    //V and E is Node location
    if(V<size && E <size)
    {
      // create Adjacency node
    struct AjlistNode *newEdge=(struct AjlistNode*)malloc(
      sizeof(struct AjlistNode)
      );
    if(newEdge!=NULL)
    {

      newEdge->next=NULL;
      newEdge->vId=E;
      newEdge->weight=weight;

      struct AjlistNode *temp=node[V].next;

      if(temp==NULL)
      {
        node[V].next=newEdge;
      }else
      {
        //Add node at last
        while(temp->next!=NULL)
        {
          temp=temp->next;
        }
        temp->next=newEdge;
      }
    }else
    {
      printf("\n Memory overflow");

    }
    }else
    {
      //not valid Vertices
      printf("Invalid Node Vertices %d  %d", V,E);
    }


}

void view_path(int path[], int location)
{
	if (path[location] == - 1)
    {

      return;
    }

    view_path(path, path[location]);

    printf("%d ", location);
}

void bellman(struct Graph*root,int source)
{
	if(root!=NULL)
    {

      int distance[size],path[size];

	int i,j;
      for (i = 0; i < size; ++i)
      {
        //Initial distance is infinity
        distance[i] = INF;

        path[i]=-1;

      }

      distance[source] = 0;

      struct AjlistNode *temp=NULL;

      for (i = 1; i < size; ++i)
      {

        for (j = 0; j < size; ++j)
        {
          temp=root[j].next;
          //compare node (J) outgoing edges
          while(temp!=NULL)
          {
            if(distance[j] != INF && distance[j] + temp->weight < distance[temp->vId]  )
            {
              distance[temp->vId] = distance[j] + temp->weight;
              path[temp->vId]=j;
            }
            temp=temp->next;
          }
        }
      }

      for (i = 1; i < size; ++i)
      {

        for (j = 0; j < size; ++j)
        {
          temp=root[j].next;

          //compare node (J) outgoing edges
          while(temp!=NULL)
          {
            if(distance[j] != INF && distance[j] + temp->weight < distance[temp->vId]  )
            {
              printf("\n Negative Cycle exist node (%d %d)\n",temp->vId,j);
              return;

            }
            temp=temp->next;
          }
        }
      }
      printf("Destination Node\tCost \tPath\n");

      for (i = 0; i < size; ++i)
      {
        if(distance[i]==INF)
        {
          printf(" %d \t  INF\n", i+1);
        }
        else
        {
          printf("\n %d\t\t\t %d\t %d ", i, distance[i],source);


        }

		view_path(path,i);
      }
    }
    else
    {
      printf("Empty Graph");
    }
}
