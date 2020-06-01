//
//  main.cpp
//  bbm203-3ass
//
//  Created by AhmetBayrak on 29.11.2018.
//  Copyright © 2018 AhmetBayrak. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

struct goalNode
{
    string away_team_name;
    int minute_of_goal;
    int match_ID;
    goalNode *next;
    goalNode *prev;
};

goalNode *goal_head = NULL;
goalNode *goal_tail = NULL;

struct footballerNode
{
    string footballer_name;
    string team_name;
    int number_of_goal;
    footballerNode *next;
    goalNode *goal_next;
};

footballerNode *footballer_head = NULL;
footballerNode *footballer_tail = NULL;

// Displays the whole linked list
void display_linked_list()
{
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    
    cout << "---------------------------" << endl << endl;
    
    while(footballer_node!=NULL)
    {
        cout<<"Footballer name: "<<footballer_node->footballer_name << endl;
        cout<<"Footballer team name: "<<footballer_node->team_name << endl;
        cout << "Number of goal: " << footballer_node->number_of_goal << endl << endl;
        goal_node = footballer_node->goal_next;
        while(goal_node!=NULL)
        {
            cout << "Away team name: " << goal_node->away_team_name << endl;
            cout << "Minute of goal: " << goal_node->minute_of_goal << endl;
            cout << "Match Id: " <<goal_node->match_ID << endl << endl;
            goal_node = goal_node->next;
        }
        cout << "--------------------------" << endl << endl;
        footballer_node=footballer_node->next;
    }
}

// Creates linked list sequentially according to name of footballers
void create_footballer_node_sequential(string footballer_name, string footballer_team_name, string away_team_name, int minute_of_goal, int match_ID)
{
    
    footballerNode *temp=new footballerNode;
    temp->footballer_name = footballer_name;
    temp->team_name = footballer_team_name;
    temp->next=NULL;
    temp->number_of_goal = 1;
    
    goalNode *temp1=new goalNode;
    temp1->away_team_name = away_team_name;
    temp1->minute_of_goal = minute_of_goal;
    temp1->match_ID = match_ID;
    temp1->next = NULL;
    temp1->prev = NULL;
    temp->goal_next=temp1;
    
    // if the linked list is empty adds to head
    if(footballer_head==NULL)
    {
        footballer_head=temp;
        footballer_tail=temp;
        temp=NULL;
    }
    else
    {
        // if the linked list has only one element
        if(footballer_head->next == NULL)
        {
            //adds to head
            if(footballer_head->footballer_name > temp->footballer_name)
            {
                temp->next = footballer_head;
                footballer_head = temp;
            }
            //adds to tail
            else
            {
                footballer_head->next = temp;
            }
        }
        //if the linked list has two or more element
        else
        {
            footballerNode *pre=new footballerNode;
            footballerNode *cur=new footballerNode;
            cur=footballer_head;
            pre = footballer_head;
            
            while(cur->next!=NULL)
            {
                //adds to head
                if(cur->footballer_name > temp->footballer_name)
                {
                    temp->next = cur;
                    footballer_head = temp;
                    break;
                }
                // adds between them
                if(cur->footballer_name < temp->footballer_name && cur->next->footballer_name > temp->footballer_name)
                {
                    pre=cur;
                    cur=cur->next;
                    pre->next = temp;
                    temp->next = cur;
                    break;
                }
                cur = cur->next;
                pre = pre ->next;
            }
            //for last element
            if(cur->footballer_name > temp->footballer_name)
            {
                temp->next = cur;
            }
            // adds to tail
            else
            {
                cur->next = temp;
            }
        }
    }
}

//adds goal to footballer
void insert_goal_node(string footballer_name, string away_team_name, int minute_of_goal, int match_ID)
{
    footballerNode *temp=footballer_head;
    goalNode *temp_goal_node;
    while(temp!=NULL)
    {
        // finds the fooballler in the linked list
        if(temp->footballer_name == footballer_name)
        {
            temp_goal_node = temp->goal_next;
            while(temp_goal_node->next!=NULL)
            {
                temp_goal_node = temp_goal_node->next;
            }
            goalNode *new_goal_node = new goalNode;
            new_goal_node->away_team_name = away_team_name;
            new_goal_node->minute_of_goal = minute_of_goal;
            new_goal_node->match_ID = match_ID;
            new_goal_node->next = NULL;
            new_goal_node->prev = temp_goal_node;
            temp_goal_node->next = new_goal_node;
            temp->number_of_goal++;
            break;
        }
        temp=temp->next;
    }
}

// returns true if the name of footballer in the linked list otherwise returns false
bool search_footballer_name(string footballer_name_searched)
{
    footballerNode *disp=footballer_head;
    while(disp!=NULL)
    {
        if(disp->footballer_name == footballer_name_searched)
        {
            return true;
            break;
        }
        else if(disp->next==NULL)
        {
            return false;
            break;
        }
        disp=disp->next;
    }
    return false;
}

// prints most scored half if it is first half prints 0 if it is second half then prints 1
void most_scored_half(ofstream& outFile)
{
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    int first_half = 0;
    int second_half = 0;
    
    while(footballer_node!=NULL)
    {
        goal_node = footballer_node->goal_next;
        while(goal_node!=NULL)
        {
            if(goal_node->minute_of_goal > 45)
            {
                second_half++;
            }
            else
            {
                first_half++;
            }
            goal_node = goal_node->next;
        }
        footballer_node=footballer_node->next;
    }
    outFile << "1)THE MOST SCORED HALF" << endl;
    
    if(first_half > second_half)
    {
        outFile << "0" << endl;
    }
    else
    {
        outFile << "1" << endl;
    }
}

// prints the goal scorer
void goal_scorer(ofstream& outFile)
{
    outFile << "2)GOAL SCORER" << endl;
    
    footballerNode *footballer_node=footballer_head;
    int max_goal_number = 0;
    
    while(footballer_node!=NULL)
    {
        if(footballer_node->number_of_goal > max_goal_number)
        {
            max_goal_number = footballer_node->number_of_goal;
        }
        footballer_node=footballer_node->next;
    }
    
    // prints all of the goal scorers
    footballer_node=footballer_head;
    while(footballer_node!=NULL)
    {
        if(footballer_node->number_of_goal == max_goal_number)
        {
            outFile << footballer_node->footballer_name << endl;
        }
        footballer_node=footballer_node->next;
    }
}

// prints the footballers who had hattrick
void hattrick(ofstream& outFile)
{
    outFile << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK" << endl;
    
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    int k = 0;
    int j = 0;
    int count = 0;
    while(footballer_node!=NULL)
    {
        count = 0;
        vector<int> match_ids;
        goal_node = footballer_node->goal_next;
        while(goal_node!=NULL)
        {
            match_ids.push_back(goal_node->match_ID);
            goal_node = goal_node->next;
        }
        for(k = 0 ; k < match_ids.size(); k++)
        {
            count = 0;
            for( j = 0 ; j < match_ids.size(); j++)
            {
                if(match_ids[k] == match_ids[j])
                {
                    count++;
                }
            }
            // if there are more than two goal with the same match ID then it means hattrick
            if(count > 2)
            {
                outFile << footballer_node->footballer_name << endl;
                break;
            }
        }
        footballer_node=footballer_node->next;
    }
}

// prints the name of teams without duplicates
void list_of_teams(ofstream& outFile)
{
    outFile << "4)LIST OF TEAMS" << endl;
    
    int j = 0;
    int k = 0;
    int count = 0 ;
    
    vector<string> arr;
    
    footballerNode *footballer_node=footballer_head;
    
    arr.push_back(footballer_node->team_name);
    
    while(footballer_node!=NULL)
    {
        count = 0;
        for(j = 0 ; j < arr.size() ; j++)
        {
            if(footballer_node->team_name == arr[j])
            {
                count++;
            }
        }
        // if the name of team is not already in the list then add otherwise skip
        if(count == 0)
        {
            arr.push_back(footballer_node->team_name);
        }
        footballer_node=footballer_node->next;
    }
    
    for (k = 0 ; k < arr.size(); k++)
    {
        outFile << arr[k] << endl;
    }
}

// prints the names of footballers
void list_of_footballers(ofstream& outFile)
{
    outFile << "5)LIST OF FOOTBALLERS" << endl;
    
    footballerNode *footballer_node=footballer_head;
    
    while(footballer_node!=NULL)
    {
        outFile << footballer_node->footballer_name << endl;
        footballer_node=footballer_node->next;
    }
}

// prints the macthes of footballer
void matches_of_given_footballer(string line, ofstream& outFile)
{
    outFile << "6)MATCHES OF GIVEN FOOTBALLER\n";
    
    string first_footballer;
    string delimiter = ",";
    string second_footballer;
    
    // split the line according to comma and takes the name of two footballer names as a first and second footballer
    first_footballer = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + delimiter.length());
    second_footballer = line.substr(0, line.find("\n"));
    
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    
    while(footballer_node!=NULL)
    {
        if(first_footballer == footballer_node->footballer_name)
        {
            outFile << "Matches of " << footballer_node->footballer_name << endl;
            
            goal_node = footballer_node->goal_next;
            while(goal_node!=NULL)
            {
                outFile <<"Footballer Name: "<<footballer_node->footballer_name;
                outFile << ",Away Team: " << goal_node->away_team_name;
                outFile << ",Min of Goal: " << goal_node->minute_of_goal;
                outFile << ",Match ID: " <<goal_node->match_ID << endl;
                
                goal_node = goal_node->next;
            }
        }
        footballer_node=footballer_node->next;
    }
    
    footballerNode *footballer_node1=footballer_head;
    goalNode *goal_node1;
    
    while(footballer_node1!=NULL)
    {
        if(second_footballer == footballer_node1->footballer_name)
        {
            outFile << "Matches of " << footballer_node1->footballer_name << endl;
            goal_node1 = footballer_node1->goal_next;
            while(goal_node1!=NULL)
            {
                outFile<<"Footballer Name: "<<footballer_node1->footballer_name;
                outFile << ",Away Team: " << goal_node1->away_team_name;
                outFile << ",Min of Goal: " << goal_node1->minute_of_goal;
                outFile << ",Match ID: " <<goal_node1->match_ID << endl;
                
                goal_node1 = goal_node1->next;
            }
        }
        footballer_node1=footballer_node1->next;
    }
}

// prints the matches of given footballer according to match id ascending order
void ascending_order_match_id(string line, ofstream& outFile)
{
    outFile << "7)ASCENDING ORDER ACCORDING TO MATCH ID\n";
    
    string first_footballer;
    string delimiter = ",";
    string second_footballer;
    
    first_footballer = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + delimiter.length());
    second_footballer = line.substr(0, line.find("\n"));
    
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    vector<int> match_ids;
    
    while(footballer_node!=NULL)
    {
        if(first_footballer == footballer_node->footballer_name)
        {
            goal_node = footballer_node->goal_next;
            while(goal_node!=NULL)
            {
                match_ids.push_back(goal_node->match_ID);
                goal_node = goal_node->next;
            }
            sort(match_ids.begin(), match_ids.end());
            match_ids.erase( unique( match_ids.begin(), match_ids.end() ), match_ids.end() );
        }
        footballer_node=footballer_node->next;
    }
    int z = 0 ;
    for(z = 0 ; z < match_ids.size(); z++)
    {
        outFile << "footballer Name: " << first_footballer << ",Match ID: " << match_ids[z] << endl;
    }
    
    footballerNode *footballer_node1=footballer_head;
    goalNode *goal_node1;
    
    vector<int> match_ids1;
    
    while(footballer_node1!=NULL)
    {
        if(second_footballer == footballer_node1->footballer_name)
        {
            goal_node1 = footballer_node1->goal_next;
            while(goal_node1!=NULL)
            {
                match_ids1.push_back(goal_node1->match_ID);
                goal_node1 = goal_node1->next;
            }
            sort(match_ids1.begin(), match_ids1.end());
            match_ids1.erase( unique( match_ids1.begin(), match_ids1.end() ), match_ids1.end() );
        }
        footballer_node1=footballer_node1->next;
    }
    for(z = 0 ; z < match_ids1.size(); z++)
    {
        outFile << "footballer Name: " << second_footballer << ",Match ID: " << match_ids1[z] << endl;
    }
}

// prints the matches of given footballer according to match id descending order
void descending_order_match_id(string line, ofstream& outFile)
{
    outFile << "8)DESCENDING ORDER ACCORDING TO MATCH ID\n";
    
    string first_footballer;
    string delimiter = ",";
    string second_footballer;
    
    first_footballer = line.substr(0, line.find(delimiter));
    line.erase(0, line.find(delimiter) + delimiter.length());
    second_footballer = line.substr(0, line.find("\n"));
    
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node;
    
    vector<int> match_ids;
    
    while(footballer_node!=NULL)
    {
        if(first_footballer == footballer_node->footballer_name)
        {
            goal_node = footballer_node->goal_next;
            while(goal_node!=NULL)
            {
                match_ids.push_back(goal_node->match_ID);
                goal_node = goal_node->next;
            }
            match_ids.erase( unique( match_ids.begin(), match_ids.end() ), match_ids.end() );
            sort(match_ids.begin(), match_ids.end());
            reverse(match_ids.begin(), match_ids.end());
        }
        footballer_node=footballer_node->next;
    }
    int z = 0 ;
    for(z = 0 ; z < match_ids.size(); z++)
    {
        outFile << "footballer Name: " << first_footballer << ",Match ID: " << match_ids[z] << endl;
    }
    
    footballerNode *footballer_node1=footballer_head;
    goalNode *goal_node1;
    
    vector<int> match_ids1;
    
    while(footballer_node1!=NULL)
    {
        if(second_footballer == footballer_node1->footballer_name)
        {
            goal_node1 = footballer_node1->goal_next;
            while(goal_node1!=NULL)
            {
                match_ids1.push_back(goal_node1->match_ID);
                goal_node1 = goal_node1->next;
            }
            match_ids1.erase( unique( match_ids1.begin(), match_ids1.end() ), match_ids1.end() );
            sort(match_ids1.begin(), match_ids1.end());
            reverse(match_ids1.begin(), match_ids1.end());
        }
        footballer_node1=footballer_node1->next;
    }
    for(z = 0 ; z < match_ids1.size(); z++)
    {
        outFile << "footballer Name: " << second_footballer << ",Match ID: " << match_ids1[z] << endl;
    }
}

// traverses in the linked list and delete them
void clear_linked_lists()
{
    footballerNode *footballer_node=footballer_head;
    goalNode *goal_node = NULL;
    
    footballerNode *deleted_footballer_node;
    goalNode *deleted_goal_node;
    
    while(footballer_node!=NULL)
    {
        goal_node = footballer_node->goal_next;
        while(goal_node!=NULL)
        {
            deleted_goal_node = goal_node;
            delete deleted_goal_node;
            goal_node = goal_node->next;
        }
        deleted_footballer_node = footballer_node;
        delete deleted_footballer_node;
        footballer_node=footballer_node->next;
    }
    delete footballer_node;
    delete goal_node;
}

// reads the input txt and creates the linked list sequentially to name of footballers
void read_and_create_linked_list(ifstream& inFile, int lineSize)
{
    string tempStringArray[lineSize][5];
    string line;
    size_t pos = 0;
    string token;
    string delimiter = ",";
    
    int i = 0;
    int k = 0;
    while (getline(inFile, line))
    {
        i = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            tempStringArray[k][i++] = token;
            line.erase(0, pos + delimiter.length());
        }
        tempStringArray[k++][4] = line.substr(0, line.find("\n"));
    }
    
    int d = 0;
    int number_of_footballer = 0;
    
    for(d = 0; d < lineSize ; d++)
    {
        // if footballer is not already in the linked list then add the footballer to the linked list
        if(!search_footballer_name(tempStringArray[d][0]))
        {
            create_footballer_node_sequential(tempStringArray[d][0], tempStringArray[d][1], tempStringArray[d][2], stoi(tempStringArray[d][3]), stoi(tempStringArray[d][4]));
            number_of_footballer++;
        }
        // if footballer is already in the linked list then add only goal not footballer
        else
        {
            insert_goal_node(tempStringArray[d][0], tempStringArray[d][2], stoi(tempStringArray[d][3]), stoi(tempStringArray[d][4]));
        }
    }
}

// calculate number of line size
int determine_line_size(ifstream& inFileTemp)
{
    int lineSize = 0;
    string lineTemp;
    while(getline(inFileTemp, lineTemp))
    {
        lineSize++;
    }
    return lineSize;
}

int main(int argc, const char * argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);
    
    ifstream opFile;
    opFile.open(argv[2]);
    
    ofstream outFile;
    outFile.open(argv[3]);
    
    int lineSize = 0;
    ifstream inFileTemp;
    inFileTemp.open(argv[1]);
    lineSize = determine_line_size(inFileTemp);
    inFileTemp.close();
    
    read_and_create_linked_list(inFile, lineSize);
    inFile.close();
    
    string line;
    string operationsVector[3];
    int o = 0;
    while (getline(opFile, line))
    {
        operationsVector[o++] = line;
    }
    opFile.close();
    
    most_scored_half(outFile);
    goal_scorer(outFile);
    hattrick(outFile);
    list_of_teams(outFile);
    list_of_footballers(outFile);
    matches_of_given_footballer(operationsVector[0], outFile);
    ascending_order_match_id(operationsVector[1], outFile);
    descending_order_match_id(operationsVector[2], outFile);
    outFile.close();
    clear_linked_lists();
    
    return 0;
}
