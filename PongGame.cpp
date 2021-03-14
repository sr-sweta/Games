#include<bits/stdc++.h>
#include<time.h>
#include<conio.h>
using namespace std;

enum eDir{ STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall{
	private:
		int x,y;
		int originalx,originaly;
		eDir direction;
	public:
		cBall(int posx,int posy){
			originalx = posx;
			originaly = posy;
			x = posx;
			y = posy;
			direction = STOP;
		}
		void reset(){
			x = originalx;
			y = originaly;
			direction = STOP;
		}
		void changeDirection(eDir d){
			direction = d;
		}
		void randomDirection(){
			direction = (eDir)((rand() % 6) + 1);
		}
		inline int getx(){ return x; } 
		inline int gety(){ return y; } 
		inline int getDirection(){ return direction; } 
		void move(){
			switch(direction){
				case STOP:
					break;
				case LEFT:
					x--;
					break;
				case RIGHT:
					x++;
					break;
				case UPLEFT:
					x--;y--;
					break;
				case DOWNLEFT:
					x--;y++;
					break;
				case UPRIGHT:
					x++;y--;
					break;
				case DOWNRIGHT:
					x++;y++;
					break;
				default:
					break;
			}
		}
		friend ostream & operator<<(ostream & o, cBall c){
			o<<"BALL ["<<c.x<<","<<c.y<<"]["<<c.direction<<"]";
			return o;
		}
};
class cPaddle{
	private:
		int x, y;
		int originalx, originaly;
	public:
		cPaddle(){
			x = y = 0;
		}
		cPaddle(int posx, int posy) : cPaddle(){
			originalx = posx;
			originaly = posy;
			x = posx;
			y = posy;
		}
		inline void reset(){ x = originalx; y = originaly; }
		inline int getx(){ return x; }
		inline int gety(){ return y; }
		inline void moveup(){ y--; }
		inline void movedown(){ y++; }
		friend ostream & operator<<(ostream & o, cPaddle c){
			o<<"Paddle ["<<c.x<<","<<c.y<<"]";
			return o;
		}
};
class cGameManager{
	private:
		int width, height;
		int score1, score2;
		char up1, down1, up2, down2;
		bool quit;
		cBall * ball;
		cPaddle *player1;
		cPaddle *player2;
	public:
		cGameManager(int w,int h){
			srand(time(NULL));
			quit = false;
			up1 = 'w'; up2 = 'i';
			down1 = 's'; down2 = 'k';
			score1 = score2 = 0;
			width = w; height = h;
			ball = new cBall(w/2,h/2);
			player1 = new cPaddle(1,h/2-3);
			player2 = new cPaddle(w-2,h/2-3);
		}
		~cGameManager(){
			delete ball, player1, player2;
		}
		void scoreup(cPaddle * player){
			if(player == player1)
				score1++;
			if(player == player2)
				score2++;
			
			ball->reset();
			player1->reset();
			player2->reset();
		}
		void draw(){
			system("cls");
			for(int i=0;i<width+2;i++)
				cout<<"\xB2";
			cout<<endl;
			
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					
					int ballx = ball->getx();
					int bally = ball->gety();
					int player1x = player1->getx();
					int player2x = player2->getx();
					int player1y = player1->gety();
					int player2y = player2->gety();
					
					if(j == 0 )
						cout<<"\xB2";
						
					if(ballx == j && bally == i)
						cout<<"O";//ball
					else if(player1x == j && player1y == i)
						cout<<"\xDB";//player1
					else if(player2x == j && player2y == i)
						cout<<"\xDB";//player2
						
					else if(player1x == j && player1y + 1 == i)
						cout<<"\xDB";//player1
					else if(player1x == j && player1y + 2 == i)
						cout<<"\xDB";//player1
					else if(player1x == j && player1y + 3 == i)
						cout<<"\xDB";//player1
					
					else if(player2x == j && player2y + 1 == i)
						cout<<"\xDB";//player2
					else if(player2x == j && player2y + 2 == i)
						cout<<"\xDB";//player2
					else if(player2x == j && player2y + 3 == i)
						cout<<"\xDB";//player2	
						
					
					else
						cout<<" ";
						
					if(j == width-1)
						cout<<"\xB2";
				}
				cout<<endl;
			}
			for(int i=0;i<width+2;i++)
				cout<<"\xB2";
			cout<<endl;
			
			cout<<"Score Player1: "<<score1<<endl;
			cout<<"Score Player2: "<<score2<<endl;
		}
		void input(){
			ball->move();
			
			int ballx = ball->getx();
			int bally = ball->gety();
			int player1x = player1->getx();
			int player2x = player2->getx();
			int player1y = player1->gety();
			int player2y = player2->gety();
			
			if(_kbhit()){
				char current = _getch();
				if(current == up1)
					if(player1y > 0)
						player1->moveup();
				if(current == up2)
					if(player2y > 0)
						player2->moveup();
				if(current == down1)
					if(player1y + 4 < height)
						player1->movedown();
				if(current == down2)
					if(player2y + 4 < height)
						player2->movedown();
				
				if(ball->getDirection() == STOP)
					ball->randomDirection();
				
				if(current == 'q')
					quit = true;		
			}
		}
		void logic(){
			
			int ballx = ball->getx();
			int bally = ball->gety();
			int player1x = player1->getx();
			int player2x = player2->getx();
			int player1y = player1->gety();
			int player2y = player2->gety();
			
			//left paddle
			for(int i = 0;i < 4; i++)
				if(ballx == player1x + 1)
					if(bally == player1y + i)
						ball->changeDirection((eDir)((rand() % 3)+ 4));
			
			//right paddle
			for(int i = 0;i < 4; i++)
				if(ballx == player2x - 1)
					if(bally == player2y + i)
						ball->changeDirection((eDir)((rand() % 3)+ 1));
			
			//bottom wall
			if(bally == height - 1)
				ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
			//top wall
			if(bally == 0)
				ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
			//right wall
			if(ballx == width - 1)
				scoreup(player1);
			//left wall
			if(ballx == 0)
				scoreup(player2);
		}
		void run(){
			while(!quit){
				draw();
				input();
				logic();
			}
		}
};
int main(){
	
	cGameManager c(40,20);
	c.run();	
	return 0;
}
//s,w,i,k button works for direction
//win+r -> charmap  for character codes 
//gcc.exe -std=c++11 
//g++.exe -std=c++11
