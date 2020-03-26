#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h> 
#include <cmath> 
using namespace std;

//a point on the map
struct node{
	int x, y;
};


//finds how many digits in an int
int intlength (int i) {
   int size=0;
   while (i !=0) 
   {   
      size++;  
      i/=10;
   } 
   return size;
}

//global variable
vector<char> actions;
bool found = false;
int counter = 0;

//Recursive path pathfinder
void pathfinder(vector<vector<int>> maze, node str, node end, vector<char> pilot){
	//keeps count of nodes checked
	counter++;	

	//if current point is the end point then save the movement in maze
	//and break recurtion 
	if (str.x==end.x && str.y==end.y){
		actions=pilot;
		found = true;
		return;
	}
	
	//turning current point into a wall so that robot doesnt visit same point twice
	int path [4] = {0,0,0,0};
	maze[str.y][str.x] = 1;
	vector<char> newcords;

	//check to see if L,R,P,D is a wall, and if not how far is that point from the end point
	if(maze[str.y+1][str.x]==1){
		path[0]=-1;
	}else{
		path[0]=abs(str.y+1-end.y)+abs(str.x-end.x);
	}
	if(maze[str.y-1][str.x]==1){
		path[1]=-1;
	}else{
		path[1]=abs(str.y-1-end.y)+abs(str.x-end.x);
	}
	if(maze[str.y][str.x+1]==1){
		path[2]=-1;
	}else{
		path[2]=abs(str.y-end.y)+abs(str.x+1-end.x);
	}
	if(maze[str.y][str.x-1]==1){
		path[3]=-1;
	}else{
		path[3]=abs(str.y-end.y)+abs(str.x-1-end.x);
	}

	//check all current path options
	node temp =str;
	int min;
	int pointsaved;
	for(int i=0; i<4; i++){
		temp = str;
		newcords = pilot;
		min = INT_MAX;
		pointsaved = i;
		//checks closest point to end first
		for(int k=0; k<4; k++){
			if (path[k]<min && path[k]!=-1){
				min=path[k];
				pointsaved=k;
			}
		}
		if(pointsaved!=i){
			i=pointsaved-1;
			continue;
		}
		
		if(path[i]==-1){
			continue;
		} else {
			switch(i){
				case 0:
				temp.y+=1;
				newcords.push_back('D');
				pathfinder(maze,temp,end,newcords);
				break;
				case 1:
				temp.y-=1;
				newcords.push_back('U');
				pathfinder(maze,temp,end,newcords);
				break;
				case 2:
				temp.x+=1;
				newcords.push_back('R');
				pathfinder(maze,temp,end,newcords);
				break;
				case 3:
				temp.x-=1;
				newcords.push_back('L');
				pathfinder(maze,temp,end,newcords);
				break;
			}
			if (found){
				return;
			}
		}
		path[pointsaved]=-1;
	}
	return ;
}


int main(int argc, char* argv[])
{

	//splitting input 
	if (argc < 6){
		exit(0);
	}
	string file = argv[1];
	node start = {atoi(argv[2]), atoi(argv[3])};
	node finish = {atoi(argv[4]), atoi(argv[5])};


	//reading file
	string line;
	ifstream myfile(file);
	vector<string> v;
	if(myfile.is_open())
	{
		while (getline(myfile,line)){
			v.push_back(line);
		}
	}
	myfile.close();

	//getting values
	int x = stoi(v[0]); // length
	v[0].erase(0,intlength(x));
	int y = stoi(v[0]); // width 



	//getting maze
	vector<vector<int>> map;
	vector<int> wall(x+2, 1);
	map.push_back(wall);
	for (int i=1; i<=y; i++){
		map.push_back(vector<int>());
		stringstream conv(v[i]);
	    int value;
	    map[i].push_back(1);
	    while (conv >> value)
	    {
	        map[i].push_back(value);
	        if (conv.peek() == '	' || conv.peek()==' ' || conv.peek()==',')
	        {
	            conv.ignore();
	        }
	    }
	    map[i].push_back(1);
	}
	map.push_back(wall);

	//runs pathfinding function
	start.x++;
	start.y++;
	finish.x++;
	finish.y++;
	vector<char> empty;
	pathfinder(map,start,finish,empty);


	//prints output
	cout << counter << " " << actions.size() << endl;
	if(actions.size()==0){
		cout << "X" << endl;
	}else {
		for (int i=0; i<actions.size(); i++){
			cout << actions[i] << " ";
		}
	}
	cout << endl;

	return 0;

}

