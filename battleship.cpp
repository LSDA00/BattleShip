/*
Name: Lucas Allen, 5004607031, CS135 1002, Assignment #11.
Description: This program plays allows the user to play a game of battleship with the computer. 
Input: The user inputs numbers which are translated into x and y intercepts 
Output: This program outputs a grid on which battleship will be played. If the coordinates input by the user are a "hit", then 
	the coordinate location will change from the heiphen to an X. If the player misses then the - changes to an M.
	When no more ship locations are remaining the player is told they have won. 
Algorithm:
1. Initialize all grid locations to empty using a nested for loop. 
2. Print grids based on mode type. If silent, show only input prompt and whether hit or missed, 
	if normal show prompt, entire grid with all empty spaces and no ship locations shown, if demo show grid
	with ship locations. 
3.Demo and silent should have screen cleared after every x,y inpuy via code provided.
4.Use for loops and the double array to place battleship based on original random x coordinate and it's proximity to walls. 
5.Check play. 
6.End the game if the function GameOver which is set to true becomes false since there are no more ship locations left on the grid
7.Play game: take in user input coordinates and use prior functions to take action on the grid. If in silent mode cout proper responses (Missed or hit.)
	End game once no more ship locations are on the grid. 
*/
#include <iostream> 
#include <ctime> 
#include <cstdio>
using namespace std; 

enum cellType{EMPTY,SHIP,MISSED, HIT};
enum modeType{DEMO, SILENT, NORMAL};

const int GRID_SIZE=10; 
const int SHIP_SIZE=5; 

void initializeGrid(cellType[][GRID_SIZE]);				//
void printGrid(cellType[][GRID_SIZE], modeType);        // Function prototypes.
bool gameOver(cellType[][GRID_SIZE]);					//
void checkPlay(cellType[][GRID_SIZE], int x, int y);	//
void placeBattleShip(cellType[][GRID_SIZE] );			//
void playGame(cellType[][GRID_SIZE] , modeType mode);	//

int main(int argc, char *argv[])
{
	
	modeType type = DEMO;
	string input = argv[1];

	if(input == "DEMO") {
		type = DEMO;
	}
	if(input == "NORMAL"){
		type=NORMAL;
	}
	if(input =="SILENT"){
		type=SILENT;
	}


	cellType lGrid[GRID_SIZE][GRID_SIZE]; 
	

	initializeGrid(lGrid);
	placeBattleShip(lGrid);
	printGrid(lGrid, type);
	playGame(lGrid, type);


	

return 0; 

}
void initializeGrid(cellType lGrid[][GRID_SIZE])
{

	for(int i=0; i<GRID_SIZE; i++)
	{	
		for(int s=0; s<GRID_SIZE; s++)
		{

			lGrid[i][s]=EMPTY; 
		}
	}
	
}

void printGrid(cellType lGrid[][GRID_SIZE],modeType mode)
{
	if(mode==NORMAL){
	cout<<"\033[2J\033[1;1H"; //Code that moves the cursor to the top left-hand corner of the screen. Clearing the terminal so the last grid isn't seen. 
	cout<<" ";

	for(int i=0; i<GRID_SIZE; i++)//
	{							//	Formatting for the numbers on the top of the grid which must grow with GRID_SIZE.
		if(i>9){				//
			cout<<" "<<i;		//
		}else{					//
			cout<<"  "<<i;		//
		}
	}

	cout<<endl;
	for(int i=0; i<GRID_SIZE; i++)//
	{							//  Formatting for the numbers on the side of the grid which must grow with GRID_SIZE.
		if(i>9){				//	
			cout<<i<<" ";		//
		}else{					//
			cout<<" "<<i<<" ";	//
		}

		for(int s=0; s<GRID_SIZE; s++)
		{
			
			if(lGrid[i][s]==EMPTY)
			{
				cout<<'-'<<" "<<" "; //Puts the heiphens into the grid.
			} 
			if(lGrid[i][s]==HIT) 	//Hits are shown as 'X'.
			{
				cout<<"X  ";
			}
			if(lGrid[i][s]==MISSED)	//Misses are shown as an 'M'.
			{
				cout<<"M  ";
			}
			if(lGrid[i][s]==SHIP)//In normal mode SHIP is shown as '-'.
			{
				cout<<"-  ";
			}
		}
		cout<<endl;
	}
	cout<<endl;


}
if(mode==DEMO){
	cout<<"\033[2J\033[1;1H";
	cout<<" ";

	for(int i=0; i<GRID_SIZE; i++)
	{
		if(i>9){
			cout<<" "<<i;
		}else{
			cout<<"  "<<i;
		}


	}
	cout<<endl;
	for(int i=0; i<GRID_SIZE; i++)
	{
		if(i>9){
			cout<<i<<" ";
		}else{
			cout<<" "<<i<<" ";
		}

		for(int s=0; s<GRID_SIZE; s++)
		{
			
			if(lGrid[i][s]==EMPTY)
			{
				cout<<'-'<<" "<<" ";
			} 
			if(lGrid[i][s]==HIT)
			{
				cout<<"X  ";
			}
			if(lGrid[i][s]==MISSED)
			{
				cout<<"M  ";
			}
			if(lGrid[i][s]==SHIP)
			{
				cout<<"s  ";		// In demo mode SHIP is shown as an 's'.
			}
		}
		cout<<endl;
	}
	
}

	if(mode==SILENT)//Silent mode does not output a grid.
	{				//
		return;		//
	}				//

}

void placeBattleShip(cellType lGrid[][GRID_SIZE])
{
	srand(time(NULL)); 
	int randomNumberX=rand()%GRID_SIZE-1; //The x and y coordinate of the location on the grid where the ship will be placed: (randomNumberX)(randomNumberX).
	int randomNumberCenter=rand()%3; 	  //The y coordinate between 0 and three which is given if the first random number places the ship in the center.
	
	
	
	if(randomNumberX<SHIP_SIZE)
	{
		for(int i=0; i<SHIP_SIZE; i++){
			lGrid[randomNumberX+i][randomNumberX]=SHIP; //Places rest ship downwards from starting point.
		}
	}
	else if(randomNumberX>SHIP_SIZE)
	{
		for (int i=0; i<SHIP_SIZE; i++){
			lGrid[randomNumberX-i][randomNumberX]=SHIP;//Places rest of ship upwards from starting point. 
		}
	}
	
	else if(randomNumberX>=(GRID_SIZE-SHIP_SIZE))//Places rest of ship left of starting point.
	{
		for(int i=0; i<SHIP_SIZE; i++){
			lGrid[randomNumberX][randomNumberX+i]=SHIP;
		}
	}
	
	 if(randomNumberX>=SHIP_SIZE-1 && randomNumberX<=(GRID_SIZE-SHIP_SIZE-1))// ship can go any direction.
	{
		if(randomNumberCenter==0){
		for(int i=0; i<SHIP_SIZE; i++){
			lGrid[randomNumberX-i][randomNumberX]=SHIP;//Y coordinate is 0. Place rest of ship up from starting point.

		}
		if(randomNumberCenter==1){
			for(int i=0; i<SHIP_SIZE; i++){
				lGrid[randomNumberX+i][randomNumberX]=SHIP;//Y coordinate is 1. Places rest of ship down from starting point. 
			}
		}
		if(randomNumberCenter==2){
			for(int i=0; i<SHIP_SIZE; i++){
				lGrid[randomNumberX][randomNumberX-i]=SHIP;//Y coordinate is 2. Places rest of ship left from starting point. 
			}
		}
		if(randomNumberCenter==3){
			for(int i=0; i<SHIP_SIZE; i++){
				for(int i=0; i<SHIP_SIZE;i++){
					lGrid[randomNumberX][randomNumberX+i]=SHIP;//Y coordinate is 3. Places rest of ship right from starting point. 
				}
			}
		}

		}
	}

}


void checkPlay(cellType lGrid[][GRID_SIZE],int x, int y)
{
	if(lGrid[x][y]==EMPTY)
	{
		lGrid[x][y]=MISSED;
	}
	if(lGrid[x][y]==SHIP)
	{
		lGrid[x][y]=HIT;
	}
	if(lGrid[x][y]==HIT)
	{
		lGrid[x][y]=HIT;
	}
	if(lGrid[x][y]==MISSED)
	{
		lGrid[x][y]=MISSED;
	}

}
bool gameOver(cellType lGrid[][GRID_SIZE])
{
	bool keepGoing=true;							//Set keepGoing to true.
		for(int i=0; i<GRID_SIZE; i++)
		{
			for(int s=0; s<GRID_SIZE; s++)
			{
				if(lGrid[i][s]==SHIP)			//set to false once no more ships are on the board. 
				{
					keepGoing=false;			// only end the game when keepGoing is false
				}
			}
		}
	return keepGoing;
}

void playGame(cellType lGrid[][GRID_SIZE], modeType mode)
{


	int x1;
	int y1;
	
	while(!gameOver(lGrid)){				//loop until the game is over. 
	cout<<endl;
	cout<<"Enter two grid points seperated by a space: ";
	cin>>x1>>y1;
	while((x1<0 || y1<0) || (x1>GRID_SIZE-1 || y1>GRID_SIZE-1))
	{
		cout<<"Error. Please enter a numbers between one and "<<GRID_SIZE<<"."<<endl; //Error when numbers input by user are too large or too small. 
		cin>>x1>>y1;
	}
	checkPlay(lGrid,x1,y1);
	printGrid(lGrid, mode);
	if(mode==SILENT && lGrid[x1][y1]==HIT){  	//
		cout<<"HIT!"<<endl;						 //
	}										 	//
	if(mode==SILENT && lGrid[x1][y1]==MISSED){  // In silent mode Hit and missed are output to help the player. 
		cout<<"You missed..."<<endl;			//
	}											//
	gameOver(lGrid);
	if(gameOver(lGrid)){
	cout<<"You sank my battleship!"<<endl; //Tell the player they won and the game is over. 
	cout<<"Game over."<<endl;
	exit(0);
	
	}
	}
}



