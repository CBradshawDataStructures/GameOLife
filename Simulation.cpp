//Chase Bradshaw
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include "Simulation.h"

using namespace std;

    //constructor
    Simulation::Simulation(){

    }
    //destructor
    Simulation::~Simulation(){

    }

    //implementation of classic mode
    void Simulation::classicMode(){
        int x;
        int y;
        int xIndex;
        int yIndex;
        int userRounds;
        int userChoice = 0;
        bool runSimulation=true;
        string fileName = "";
        string readString = "";
        string fileString = "";
        //user entered decimal number for amount of filled cells to being with
        double popDensity;
        //counter of remaining filled cells
        int populationCount;
        while(!userChoice ==1 || !userChoice == 2){
            cout<<"Enter 1 for custom map, Enter 2 for the program to create one based on your parameters."<<endl;
            cin>>userChoice;
        }
        if (userChoice==1){
            cout<<"Enter filename of map"<<endl;
            cin>>fileName;
            //make sure that the parameters of the file are read in correctly
            int lineCounter = 0;
            fstream stream;
            string line;
            stream.open(fileName);

            while(getline(stream,line)){
                //assigns x value
                if(lineCounter==0){
                    x = stoi(line);
                    cout<<"X"<<line<<endl;
                }
                //assign y value
                if(lineCounter==1){
                    y = stoi(line);
                    cout<<"Y"<<line<<endl;
                }
                ++lineCounter;
            }

            stream.close();
            xIndex = x-1;
            yIndex = y-1;
        }
        //this if else block will make sure the parameters of the array are not read but the cell information is
        if (userChoice==1){
            int lineCounter2 = 0;
            fstream stream2;
            string line2;
            stream2.open(fileName);
            while(getline(stream2,line2)){
                //cout<<"fileString: "<<line2<<endl;
                if(lineCounter2>1){
                    fileString.append(line2);
                }
                ++lineCounter2;
            }
        stream2.close();
        cout<<"fileString: "<<fileString<<endl;
        }

        if (userChoice==2){
            cout<<"Enter map dimensions: "<<endl;
            cin>>x;
            cin>>y;
            cout<<"Enter population density: ";
            cin>>popDensity;
        }
        char grid[x][y];
        int gridHelper[x][y];
        int iterator=0;

        //cout<<"WORDL: "<<endl;
        //cout<<x<<endl;
        //cout<<y<<endl;
        //cout<<xIndex<<endl;
        //cout<<yIndex<<endl;

        if (userChoice==1){
            for (int i=0; i<x; ++i){
                for (int j=0; j<y; ++j){
                    char cstr[fileString.size()+1];
                    strcpy(cstr, fileString.c_str());
                    grid[i][j] = cstr[iterator];
                    ++iterator;
                    cout<<iterator<<endl;
                    //cout<<"i"<<i<<endl;
                    //cout<<"j"<<j<<endl;
                    //cout<<"IMPORTANT TEST: "<<cstr<<endl;
                    //cout<<"OUT YA GO: "<<fileString.substr(fileString.length()-1,fileString.length())<<endl;
                    //grid[i][j]=fileString.substr(fileString.length()-1,fileString.length());
                    //fileString.pop_back();
                    //cout<<"VWOOP"<<fileString<<endl;
                }
            }
        }
        if (userChoice==2){
            //populates grid
            for(int i=0; i<x; ++i){
                for(int j=0; j<y; ++j){
                    //creates random number to determine if cell is filled or not
                    int randomNum = rand()%100;
                    if(randomNum<(popDensity*100)){
                        grid[i][j] = 'X';
                        //cout<<"Spot: "<<i<<","<<j<<" is X"<<endl;
                        ++populationCount;
                    }
                    else{
                        grid[i][j] = '-';
                        //out<<"Spot: "<<i<<","<<j<<" is -"<<endl;
                    }
                }
            }
            //map generationg and population complete
        }

        //this decides future generations

//this is the 'running' part of the program
        while(runSimulation==true){
            //userRounds=4;
            for(int i=0; i<x; ++i){
                for(int j=0; j<y; ++j){
                    cout<<grid[i][j];
                }
                cout<<endl;
            }
            cout<<"User enter number of generations you wish to simulate or enter '-1' to stop"<<endl;  //still need to implement -1 function
            cin>>userRounds;
            while(userRounds>0 && populationCount>0){
                cout<<"STARTING ROUND"<<endl;
                //this nested for loop should check every cell in a classic mode simulation
                //was never able to create a more elegant solution that checks for out of bounds limits
                for(int i=0; i<x; ++i){
                    for(int j=0; j<y; ++j){

                        int localCounter=0;

                        //top left corner check
                        if(i==0 && j==0){
                            if(grid[i+1][j] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i][j+1] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i+1][j+1] == 'X'){
                                ++localCounter;
                            }
                        }

                        //top right corner check
                        if(i==xIndex && j==0){
                            if(grid[i-1][j] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i][j+1] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i-1][j+1] == 'X'){
                                ++localCounter;
                            }
                        }

                        //bottom left corner check
                        if(i==0 && j==yIndex){
                            if(grid[i+1][j] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i][j-1] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i][j-1] == 'X'){
                                ++localCounter;
                            }
                        }

                        //bottom right corner check
                        if(i==xIndex && j==yIndex){
                            if(grid[i-1][j] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i][j-1] == 'X'){
                                ++localCounter;
                            }
                            if(grid[i-1][j-1] == 'X'){
                                ++localCounter;
                            }
                        }


                        //do full 8 sided check of all non-border cells
                        if(i>0 && j>0 && i<xIndex && j<yIndex){

                            if (grid[i+1][j] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i+1][j+1] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i][j+1] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i-1][j+1] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i-1][j] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i-1][j-1] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i][j-1] == 'X'){
                                ++localCounter;
                            }

                            if (grid[i+1][j-1] == 'X'){
                                ++localCounter;
                            }

                        }
                        gridHelper[i][j]=localCounter;
                    }
                }
                cout<<"NEWGEN TIME: "<<endl;
                //this code will populate the new generation between user turns
                for(int i=0; i<x; ++i){
                    for(int j=0; j<y; ++j){
                        if (gridHelper[i][j]==1){
                            //keeps population count correct to end simulation if it reaches zero
                            if(grid[i][j]=='Z'){
                                --populationCount;
                            }
                            grid[i][j]=='Z';
                        }
                        if (gridHelper[i][j]==2){
                            //do nothing
                        }
                        if (gridHelper[i][j]==3){
                            grid[i][j]=='Z';
                        }
                        if (gridHelper[i][j]>=4){
                            if(grid[i][j]=='X'){
                                --populationCount;
                            }
                            grid[i][j]=='-';
                        }
                    }
                }
                for(int i=0; i<x; ++i){
                    for(int j=0; j<y; ++j){
                        cout<<gridHelper[i][j];
                    }
                    cout<<endl;
                }
                --userRounds;
            }
            //end condition for all cells being empty
            if(populationCount==0){
                runSimulation=false;
                cout<<"All cells empty"<<endl;
            }
            //end condition for user ending the simulation
            if(userRounds<0){
                runSimulation=false;
                cout<<"user has ended simulation"<<endl;
            }
        }
    }
    int main(){
        Simulation testGame;
        testGame.classicMode();
        return 0;
    }
