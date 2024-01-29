#include <iostream>
#include <stdlib.h>
#include <queue>
#include <set>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
// ----------------------------------------------------------------------------------------------------------------------------------------------
struct state   // state structure
{
    int puz[3][3];       //matrix that has numbers in the puzzle
    int zero_i;          //row index of zero
    int zero_j;          //column index of zero
    int state_num;
    int state_depth;
    string path;
    int hn_manhattan;
    float hn_euclidean;
    int gn;
    int fn;
    float fn_euclidean;
};
// ----------------------------------------------------------------------------------------------------------------------------------------------
// This is used to generate the INITIAL STATE puzzle from arr[9]
state generate_puzzle(int arr[9])
{
    //variable to access values in the array (arr)
    int z=0;
    state s;
    // setting the parent pointer to null since this function will be used to generate the initial state only and it has no parent
    s.state_num=0;
    s.state_depth=0;
    s.path="";
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            s.puz[i][j]=arr[z];
            z++;
            if(s.puz[i][j]==0)
            {
                s.zero_i=i;
                s.zero_j=j;
            }
        }
    }
    s.gn = 0;
    s.hn_manhattan = abs(s.zero_i) + abs(s.zero_j);
    s.hn_euclidean = sqrt(pow(s.zero_i,2) + pow(s.zero_j,2));
    return s;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
int getInvCount(state s)
{
    int inv_count = 0;
    int arr[9];
    int z=0;

    for (int i = 0 ; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arr[z]=s.puz[i][j];
            z++;
        }
    }
    for (int i = 0; i < 9 - 1; i++)
    {
        for (int j = i+1; j < 9; j++)
        {
            // Value 0 is used for empty space
            if (arr[j] && arr[i] &&  arr[i] > arr[j])
            {
                inv_count++;
            }
        }
    }

    return inv_count;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
// This function returns true if given 8 puzzle is solvable.
bool isSolvable(state s)
{
    // Count inversions in given 8 puzzle
    int invCount = getInvCount(s);

    // return true if inversion count is even.
    if(invCount%2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
void print_state(state s) //function prints matrix
{
//    cout << endl << " h = " << s.hn_manhattan << endl;
    cout << " _____________" << endl;

    for(int i=0; i<3; i++)
    {
        cout << " |" ;
        for(int j=0; j<3; j++)
        {
            cout << " " <<s.puz[i][j] <<" |" ;
        }
        if(i<2)
        {
            cout << endl <<" -------------" << endl;
        }
    }
    cout << endl <<" _____________" << endl;

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_left(state* parent)//function moves the zero to the left
{
    if(parent->zero_j==0)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = *parent;
        child->state_depth=parent->state_depth+1;
        child->path=child->path+"l";

        // zero is swapped with element to its left in the same row
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i][child->zero_j-1]);

        // updating the zero index (moved to left)
        child->zero_j=child->zero_j-1;

        //print_state(parent);
        //cout << "------ LEFT ------" << endl;
        //print_state(*child);
        return child;
    }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_right(state* parent)//function moves the zero to the right
{
    if(parent->zero_j==2)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = *parent;
        child->state_depth=parent->state_depth+1;
        child->path=child->path+"r";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i][child->zero_j+1]);//zero is swapped with element to its right in the same row
        child->zero_j=child->zero_j+1;
        //print_state(parent);
        //cout << "------ RIGHT ------" << endl;
        //print_state(*child);
        return child;
    }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_up(state* parent)//function moves the zero upward
{
    if(parent->zero_i==0)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = *parent;
        child->state_depth=parent->state_depth+1;
        child->path=child->path+"u";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i-1][child->zero_j]);//zero is swapped with element above it in the same column
        child->zero_i=child->zero_i-1;
        //print_state(parent);
        //cout << "------ UP ------" << endl;
        //print_state(*child);
        return child;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_down(state* parent)//function moves the zero downward
{
    if(parent->zero_i==2)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = *parent;
        child->state_depth=parent->state_depth+1;
        child->path=child->path+"d";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i+1][child->zero_j]);;//zero is swapped with element below it in the same column
        child->zero_i=child->zero_i+1;
        //print_state(parent);
        //cout << "------ DOWN ------" << endl;
        //print_state(*child);
        return child;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool check_goal(state s)
{
    int mat[3][3]= {0,1,2,3,4,5,6,7,8};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(s.puz[i][j]!= mat[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool compare_equal(int a[3][3], int b[3][3])
{
    for (int i = 0 ; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(a[i][j]!=b[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool contains(queue<state> q, state* n)
{
    queue<state> duplicate=q;
    bool exist = false;
    if(n!=NULL)
    {
        while (!duplicate.empty())
        {
            if (compare_equal(duplicate.front().puz,n->puz))
            {
                exist = true;
            }
            duplicate.pop();
        }
    }
    return exist;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
void path(state intial, string path)
{
    state* x=&intial;
    //cout << endl << "Initial State:" << endl;
    //print_state(intial);
    cout << endl ;

    for (int i=0; i< path.length(); i++)
    {
        switch(path[i])
        {
        case 'l':
            //cout<<"LEFT"<<endl;
            cout<<"LEFT -> ";
            x=move_left(x);
            // print_state(*x);

            break;
        case 'r':
            //cout<<"RIGHT"<<endl;
            cout<<"RIGHT -> ";
            x=move_right(x);
            //print_state(*x);
            break;
        case 'u':
            //cout<<"UP"<<endl;
            cout<<"UP -> ";
            x=move_up(x);
            //print_state(*x);
            break;
        case 'd':
            //cout<<"DOWN"<<endl;
            cout<<"DOWN -> ";
            x=move_down(x);
            //print_state(*x);
            break;
        }
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
int Depth(queue<state> q)
{
    queue<state> duplicate=q;

    int depth=0;
    while (!duplicate.empty())
    {
        if (duplicate.front().state_depth>depth)
        {
            depth = duplicate.front().state_depth;
        }
        duplicate.pop();
    }
    return depth;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* BFS(state initial)
{
    // First: check if the puzzle is solvable
    if (!isSolvable(initial))
    {
        cout << "No Solution" << endl;
        return NULL;
    }
    else cout << endl << "-->> SOLVABLE! wait for the solution.. BFS in progress..";

    // Second: creating a queue for explores states and frontiers (to be explored)
    queue<state> frontier;
    queue<state> explored;

    // Third: some initializations
    frontier.push(initial); // Insert the initial state into the queue
    int c = 1;
    int count_exp = 0;
    clock_t time_req = clock();

    //state x; // Temporary state variable used for printing explored nodes

    // Fourth: main While loop
    while (!frontier.empty())
    {
        //cout << "HEYY " << c << endl;

        state current = frontier.front();
        frontier.pop();

        // Explore the current node (push into explored queue)
        explored.push(current);
        count_exp++;

        if (check_goal(current))
        {
            // Calculate the time taken by BFS and print the result
            time_req = clock() - time_req;

            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Time taken to find the goal by BFS = " << (float)time_req / CLOCKS_PER_SEC << endl;
            cout << "The number of explored nodes = " << count_exp << endl;
            cout << "The number of expanded nodes = " << c << endl;
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Path is: " << current.path;
            path(initial, current.path);
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            return &current;
        }

        // Generate neighboring states by moving tiles
        state* neighbours[4];
        neighbours[0] = move_left(&current);
        neighbours[1] = move_right(&current);
        neighbours[2] = move_up(&current);
        neighbours[3] = move_down(&current);

        // Check if neighbors are not in the frontier or explored, and add them to the frontier
        for (int i = 0; i < 4; i++)
        {
            if (neighbours[i] != NULL && !contains(frontier, neighbours[i]) && !contains(explored, neighbours[i]))
            {
                neighbours[i]->state_num = c;
                c++;
                frontier.push(*neighbours[i]);
            }
        }
    }

    cout << "No Solution" << endl;
    return NULL;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool stackContains(stack<state> s, state* n)
{
    stack<state> ss = s;
    if(n != NULL)
    {
        while(!ss.empty())
        {
            if(compare_equal(ss.top().puz,n->puz))
                return true;
            ss.pop();
        }
    }
    return false;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_left2(state parent)//function moves the zero to the left
{
    if(parent.zero_j==0)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = parent;
        child->state_depth=parent.state_depth+1;
        child->path=child->path+"l";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i][child->zero_j-1]); //zero is swapped with element to its left in the same row
        child->zero_j=child->zero_j-1;
        return child;
    }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_right2(state parent)//function moves the zero to the right
{
    if(parent.zero_j==2)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = parent;
        child->state_depth=parent.state_depth+1;
        child->path=child->path+"r";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i][child->zero_j+1]);//zero is swapped with element to its right in the same row
        child->zero_j=child->zero_j+1;
        return child;
    }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_up2(state parent)//function moves the zero upward
{

    if(parent.zero_i==0)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = parent;
        child->state_depth=parent.state_depth+1;
        child->path=child->path+"u";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i-1][child->zero_j]);//zero is swapped with element above it in the same column
        child->zero_i=child->zero_i-1;
        return child;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* move_down2(state parent)//function moves the zero downward
{
    if(parent.zero_i==2)
    {
        return NULL;
    }
    else
    {
        state* child = new state;
        *child = parent;
        child->state_depth=parent.state_depth+1;
        child->path=child->path+"d";
        swap(child->puz[child->zero_i][child->zero_j],child->puz[child->zero_i+1][child->zero_j]);;//zero is swapped with element below it in the same column
        child->zero_i=child->zero_i+1;
        return child;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool stackContains2(stack<state*> s, state* n)
{
    stack<state*> ss = s;
    if(n != NULL)
    {
        while(!ss.empty())
        {
            if(compare_equal(ss.top()->puz,n->puz))
                return true;
            ss.pop();
        }
    }
    return false;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool contains2(queue<state*> q, state* n)
{
    queue<state*> duplicate=q;
    bool exist = false;
    if(n!=NULL)
    {
        while (!duplicate.empty())
        {
            if (compare_equal(duplicate.front()->puz,n->puz))
            {
                exist = true;
            }
            duplicate.pop();
        }
    }
    return exist;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
int Depth2(queue<state*> q)
{
    queue<state*> duplicate=q;

    int depth=0;
    while (!duplicate.empty())
    {
        if (duplicate.front()->state_depth>depth)
        {
            depth = duplicate.front()->state_depth;
        }
        duplicate.pop();
    }
    return depth;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* DFS(state initial)
{
    // First: check if the puzzle is solvable
    if(!isSolvable(initial))
    {
        cout <<"No Solution"<< endl;
        return NULL;
    }
    else cout<<endl<<"-->> SOLVABLE! wait for the solution.. DFS in progress..";

    // Second: creating a queue for explores states and stack for frontiers states(to be explored)
    queue<state*> explored; //explored queue
    stack<state*> frontier; //frontier stack

    // Third: some initializations
     frontier.push(&initial);//push the initial state into the frontier stack
    int c=1;
    int count_exp = 0;
    clock_t time_req = clock();//clock gets the time at the start of search

    state* neighbours[4]; //array of state pointers to store the current state neighbors

    // Fourth: main While loop
    while(!frontier.empty())
    {
        state* current=frontier.top();
        frontier.pop();

        // Explore the current node (push into explored queue)
        explored.push(current);
        count_exp++;

        if(check_goal(*current))
        {
            time_req = clock() - time_req;//clock gets the time at the end of search
            //print time taken by DFS and the goal
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Time taken to find the goal by DFS="<< double(time_req)/double(CLOCKS_PER_SEC) << endl;
            cout << "The number of explored nodes = " << count_exp << endl;
            cout << "The number of expanded nodes = " << c << endl;
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Path is: " << current->path;
            cout << "Cost = " << current->path.length() << endl;
            cout << "Search Depth = " << Depth2(explored) << endl;
            path(initial, current->path);
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;

            return current;
        }

        // Generate neighboring states by moving tiles
        neighbours[0]=move_left2(*current);
        neighbours[1]=move_right2(*current);
        neighbours[2]=move_up2(*current);
        neighbours[3]=move_down2(*current);

        // Check if neighbors are not in the frontier or explored, and add them to the frontier
        for(int i=0; i<4; i++)
        {
            if(neighbours[i]!=NULL && !stackContains2(frontier,neighbours[i]) && !contains2(explored,neighbours[i]))
            {
                c++;
                frontier.push(neighbours[i]);
            }
        }
    }
     cout <<"No Solution"<< endl;
    return NULL;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------
struct CompareStates
{
    // Compare states based on g(n) + h(n) -> h(n) is the Manhattan distance
    bool operator()(const state& a, const state& b)
    {
        return (a.gn + a.hn_manhattan) > (b.gn + b.hn_manhattan);
    }
};
// ----------------------------------------------------------------------------------------------------------------------------------------------
struct CompareStatesE
{
    // Compare states based on g(n) + h(n) -> h(n) is the Manhattan distance
    bool operator()(const state& a, const state& b)
    {
        return (a.gn + a.hn_euclidean) > (b.gn + b.hn_euclidean);
    }
};
// ----------------------------------------------------------------------------------------------------------------------------------------------
bool operator<(const state& a, const state& b)
{
    return a.fn > b.fn; // Use the same comparison you used in CompareStates
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
int manhattan(state s)
{
   int md=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            switch(s.puz[i][j])
        {
        case 1:
            md=md+abs(i) + abs(j-1);
            break;

        case 2:
            md=md+abs(i) + abs(j-2);
            break;

        case 3:
            md=md+abs(i-1) + abs(j);
            break;

        case 4:
            md=md+abs(i-1) + abs(j-1);
            break;

        case 5:
            md=md+abs(i-1) + abs(j-2);
            break;

        case 6:
            md=md+abs(i-2) + abs(j);
            break;

        case 7:
            md=md+abs(i-2) + abs(j-1);
            break;

        case 8:
             md=md+abs(i-2) + abs(j-2);
            break;
        }

        }
    }
    return md;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
float euclidean(state s)
{
    float ed=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            switch(s.puz[i][j])
        {
        case 1:
            ed = sqrt(pow(i,2) + pow(j-1,2));
            break;

        case 2:
            ed = sqrt(pow(i,2) + pow(j-2,2));
            break;

        case 3:
            ed = sqrt(pow(i-1,2) + pow(j,2));
            break;

        case 4:
            ed = sqrt(pow(i-1,2) + pow(j-1,2));
            break;

        case 5:
            ed = sqrt(pow(i-1,2) + pow(j-2,2));
            break;

        case 6:
            ed = sqrt(pow(i-2,2) + pow(j,2));
            break;

        case 7:
            ed = sqrt(pow(i-2,2) + pow(j-1,2));
            break;

        case 8:
            ed = sqrt(pow(i-2,2) + pow(j-2,2));
            break;
        }

        }
    }
    return ed;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* A_STAR_Manhattan(state initial)
{
    // First: check if the puzzle is solvable
    if (!isSolvable(initial))
    {
        cout << "No Solution" << endl;
        return NULL;
    }
    else cout << endl << "-->> SOLVABLE! wait for the solution.. A* Search in progress..";

    // Second: creating a priority queue for frontiers, and a set for explored states
    priority_queue<state, vector<state>, CompareStates> frontier;
    queue<state> explored;

    // Third: some intializations
    int c = 1;
    int count_exp = 0;
    clock_t time_req = clock();
    frontier.push(initial);

    // Fourth: the main While loop
    while (!frontier.empty())
    {
        //cout << "HEYY " << c << endl;

        state current = frontier.top();
        frontier.pop();

        // Explore the current node (insert to explored set)
        explored.push(current);
        count_exp++;

        if (check_goal(current))
        {
            // Calculate the time taken by BFS and print the result
            time_req = clock() - time_req;

            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Time taken to find the goal by A* Search (Manhattan) = " << (float)time_req / CLOCKS_PER_SEC << endl;
            cout << "The number of explored nodes = " << count_exp << endl;
            cout << "The number of expanded nodes = " << c << endl;
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Path is: " << current.path;
            path(initial, current.path);
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            return &current;
        }


        // Expand the neighboring states and calculate their f(n) = h(n) + g(n)
        state* neighbors[4] = {move_left(&current), move_right(&current), move_up(&current), move_down(&current)};

        for (int i = 0; i < 4; i++)
        {
            state* neighbor = neighbors[i];
            if (neighbor != NULL && !contains(explored,neighbor))
            {
                // Update the cost to reach this state
                neighbor->gn = current.gn + 1;
                // Update the Manhattan distance for this state
                neighbor->hn_manhattan = manhattan(*neighbor);
                // Calculate f(n) = h(n) + g(n)
                neighbor->fn = neighbor->gn + neighbor->hn_manhattan;
                // Add the neighbor to the priority queue
                neighbor->state_num = c;
                c++;
                frontier.push(*neighbor);
            }
        }
    }

    cout << "No Solution" << endl;
    return NULL;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
state* A_STAR_Euclidean(state initial)
{
    // First: check if the puzzle is solvable
    if (!isSolvable(initial))
    {
        cout << "No Solution" << endl;
        return NULL;
    }
    else cout << endl << "-->> SOLVABLE! wait for the solution.. A* Search in progress..";

    // Second: creating a priority queue for frontiers, and a queue for explored states
    priority_queue<state, vector<state>, CompareStatesE> frontier;
    queue<state> explored;

    // Third: some intializations
    int c = 1;
    int count_exp = 0;
    clock_t time_req = clock();
    frontier.push(initial);

    // Fourth: the main While loop
    while (!frontier.empty())
    {
        //cout << "HEYY " << c << endl;

        state current = frontier.top();
        frontier.pop();

        // Explore the current node (insert to explored set)
        explored.push(current);
        count_exp++;

        if (check_goal(current))
        {
            // Calculate the time taken by BFS and print the result
            time_req = clock() - time_req;

            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Time taken to find the goal by A* Search (Euclidean) = " << (float)time_req / CLOCKS_PER_SEC << endl;
            cout << "The number of explored nodes = " << count_exp << endl;
            cout << "The number of expanded nodes = " << c << endl;
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
            cout << "Path is: " << current.path;
            path(initial, current.path);
            cout << endl << "----------------------------------------------------------------------------------------------------------" << endl;
            return &current;
        }


        // Expand the neighboring states and calculate their f(n) = h(n) + g(n)
        state* neighbors[4] = {move_left(&current), move_right(&current), move_up(&current), move_down(&current)};

        for (int i = 0; i < 4; i++)
        {
            state* neighbor = neighbors[i];
            if (neighbor != NULL && !contains(explored,neighbor))
            {
                // Update the cost to reach this state
                neighbor->gn = current.gn + 1;
                // Update the Euclidean distance for this state
                neighbor->hn_euclidean = euclidean(*neighbor);
                // Calculate f(n) = h(n) + g(n)
                neighbor->fn_euclidean = neighbor->gn + neighbor->hn_euclidean;
                // Add the neighbor to the priority queue
                neighbor->state_num = c;
                c++;
                frontier.push(*neighbor);
            }
        }
    }

    cout << "No Solution" << endl;
    return NULL;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    int arr10[9] = {0,2,1,3,4,5,6,7,8}; // -> This is an example of a not solvable puzzle
    int arr11[9] = {1,5,8,6,0,2,4,3,7}; // Sample Run #1
    int arr12[9] = {4,2,5,6,3,8,7,1,0}; // Sample Run #2
    int arr13[9] = {1,2,0,3,4,5,6,7,8}; // Sample Run #3
    int arr14[9] = {6,4,5,7,2,8,0,3,1}; // Sample Run #4
    int arr15[9] = {1,2,5,3,4,0,6,7,8};
    int arr16[9] = {8,2,1,5,4,6,0,3,7};
    state s = generate_puzzle(arr11);
    cout << "Here's the initial state: " << endl;
    print_state(s);

    BFS(s);
    A_STAR_Manhattan(s);
    A_STAR_Euclidean(s);
    DFS(s);


    /*
    string key;
    do{
        cout <<"Enter key:"; cin >>key;
    } while(key!="exit");
    */
    string key;
    do{
        cout <<"Enter key:";
        cin >>key;

    }while(key!="exit");

    return 0;
}


// SOME ARRAYS TO TEST
/*
int arr1[9] = {8,1,2,0,4,3,7,6,5};
int arr2[9] = {1,8,2,0,4,3,7,6,5};
int arr3[9] = {1,2,0,3,4,5,6,7,8};
int arr4[9] = {1,2,3,5,6,4,7,8,0};
int arr5[9] = {3,1,2,6,4,5,0,7,8};
int arr6[9] = {4,1,6,2,3,5,7,8,0};
int arr7[9] = {3,7,4,2,8,6,5,1,0};
int arr8[9] = {1,0,2,3,4,5,6,7,8};
int arr9[9] = {1,4,2,3,5,0,6,7,8};
*/

