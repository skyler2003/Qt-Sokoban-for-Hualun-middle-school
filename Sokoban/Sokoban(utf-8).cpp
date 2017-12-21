#ifndef SOKOBAN_H_  //防止文件重复包含
#define SOKOBAN_H_
#include <bits/stdc++.h>
#include <conio.h>

using namespace std; 
//每一步的数据类型

int tot=0;

struct node {
 int bx, by; //箱子的坐标
 int px, py; //人的坐标
};
//推箱子类
class Sokoban {
	private:
 		enum {L = 15, H = 7};
 		char GameMap[H][L]; //地图
 		int Pex, Pey;  //人的位置
 		int Boxx, Boxy;  //箱子的位置
    	int Succeed, Prove; //是否成功到目的地, 是否可玩性
    	int dx[4], dy[4]; //方向数组
	protected:
 		char Empty;
 		char People;
 		char Box;
 		char Block;
 		char Target;
 		int dir;  //记录按键方向
 		node s, e;
	public:
 		Sokoban();  //构建函数
 		~Sokoban() {} //析构函数,即为inline
 	//地图初始化函数
 	void Initial();
 	//箱子路径验证函数,参数为箱子坐标(bx,by),人坐标(px,py)
 	void Box_Bfs(int bx, int by, int px, int py);
 	//人路径验证函数,人所到的目的地(ex,ey)
 	bool People_Bfs(int ex, int ey);
 	//地图刷新函数
 	void Show();
 	//按键判断函数
 	void Button();
 	//箱子人移动函数
 	void Move();
 	//验证越界函数
 	bool Check(int x, int y); 
};
#endif

//#include "Sokoban.h"     
Sokoban::Sokoban() { //构建函数即对变量初始化  
	dir = -1;  
	Succeed = Prove = 0;  
	memset(GameMap, '.', sizeof(GameMap));  
    Empty = '.';  
    People = 'P';  
    Box = '#';  
    Block = '*';  
    Target = 'T';  
    //方向依次为上右下左  
    dx[0] = -1;  dx[1] = 0;  dx[2] = 1;  dx[3] = 0;    
    dy[0] = 0;   dy[1] = 1;  dy[2] = 0;  dy[3] = -1;  
    //随机种子,使程序每次运行时所产生的随机数不同  
    srand(time(0));  
}  
//地图初始化函数  
inline void Sokoban::Initial()  {  
    int cnt = 0, x, y;  
    //对地图中随机产生25个阻碍物  
 	while(cnt != 25)  {  
  		x = rand()%H;  
  		y = rand()%L;  
        if(GameMap[x][y] == Empty)  {  
   			GameMap[x][y] = Block;  
      		cnt++;  
  		}  
 	}  
 	while(true) {  
  		x = rand()%H;  
  		y = rand()%L;  
     	if(GameMap[x][y] == Empty)  {  
   			GameMap[x][y] = People;  
   			Pex = x;  
   			Pey = y;  
   			break;  
  		}  
 	}  
 	while(true){ //随机产生箱子开始的位置   
  		x = rand()%H;  
  		y = rand()%L;  
  		//不让箱子在地图的边界处  
     	if(GameMap[x][y] == Empty && x != 0 && y != 0  
  		&& x != H-1 && y != L-1)  {  
   			GameMap[x][y] = Box;  
   			Boxx = x;  
   			Boxy = y;  
   			break;  
  		}  
 	}  
 	while(true) {//随机产生目标的位置   
  		x = rand()%H;  
  		y = rand()%L;  
     	if(GameMap[x][y] == Empty) {  
   			GameMap[x][y] = Target;  
   			break;  
  		}  
	}  
 	//对游戏地图检查是否可将箱子推到目的地,即判断游戏可玩性  
 	Sokoban::Box_Bfs(Boxx, Boxy, Pex, Pey);   
 	//如游戏不可玩,即再随机产生地图  
 	if(!Prove)  {  
        memset(GameMap, '.', sizeof(GameMap));  
  		Sokoban::Initial();  
 	}  
 	else  
  		Sokoban::Show();  
}  
//箱子路径验证函数  
//用BFS算法对箱子验证是否可到目的地  
void Sokoban::Box_Bfs(int bx, int by, int px, int py)  {  
 	queue<node>_Box; //创建箱子队列  
 	//vis对上一步走到下一步的记录,防止箱子走重复路劲  
 	//vis[i][j][z][k]表示箱子从点(i,j)到点(z,k)  
 	//vis[][][][]为0时表示为走过,1时表示已走过  
 	int vis[H][L][H][L];  
 	memset(vis, 0, sizeof(vis)); //vis数组初始化   
 	s.bx = bx;  s.by = by;  //将起始的箱子、人位置放入队列  
 	s.px = px;  s.py = py;  
 	_Box.push(s);  
 	int pe_x, pe_y;  
 	while(!_Box.empty()){ //队列为空时跳出  
        s = _Box.front();  
        _Box.pop();  
        if(GameMap[s.bx][s.by] == Target){  //到达目的地  
            Prove = 1;  
            break;  
        }  
        for(int i = 0; i < 4; i++)  {  
            e.bx = s.bx + dx[i];  e.by = s.by + dy[i];  
            switch(i){ //人推箱子的位置  
            	case 0:  pe_x = s.bx + dx[2]; pe_y = s.by + dy[2]; break;  
            	case 1:  pe_x = s.bx + dx[3]; pe_y = s.by + dy[3]; break;  
            	case 2:  pe_x = s.bx + dx[0]; pe_y = s.by + dy[0]; break;  
            	case 3:  pe_x = s.bx + dx[1]; pe_y = s.by + dy[1]; break;  
            }  
   			//验证箱子和人的位置的合法性  
            if(!Check(e.bx, e.by) || !Check(pe_x, pe_y)  
            || GameMap[e.bx][e.by] == Block || GameMap[pe_x][pe_y] == Block  
            || vis[s.bx][s.by][e.bx][e.by] )  
                continue;  
   			//如人可推箱子即进入队列  
            if(Sokoban::People_Bfs(pe_x, pe_y)){  
    			//保存人推箱子后的位置  
                e.px = pe_x;  e.py = pe_y;  
                _Box.push(e);  
                vis[s.bx][s.by][e.bx][e.by] = 1; //箱子路劲的标记  
            }  
        }  
 	}  
}  
//人路径验证函数  
//用BFS算法对人验证是否可推箱子  
inline bool Sokoban::People_Bfs(int ex, int ey)  {  
    queue<node>_People;  
    node t, end;  
 	//vis数组对人的路劲进行标记,0为未走过,1为走过  
    int vis[H][L];   
 	//vis数组初始化为0  
	memset(vis, 0, sizeof(vis));  
    t.px = s.px;  t.py = s.py;  //人初始位置进入队列  
    _People.push(t);  
    vis[t.px][t.py] = 1;   
    while(!_People.empty()){ //对立为空时跳出  
        t = _People.front();  
        _People.pop();  
        if(t.px == ex && t.py == ey)  //人可到达(ex,ey)该点  
   			return 1;  
        for(int i = 0; i < 4; i++)  {  
            end.px = t.px + dx[i];  end.py = t.py + dy[i];  
   			//检查人的位置合法性  
            if(!Check(end.px, end.py) || GameMap[end.px][end.py] == Block  
   			|| GameMap[end.px][end.py] == Box || vis[end.px][end.py])  
                 continue;  
   			//进入队列  
            _People.push(end);  
            vis[end.px][end.py] = 1; //记录  
        }  
    }  
    return 0;  
}  
//地图刷新函数  
inline void Sokoban::Show()  {  
 	int i, j;  
 	while(true)  {    
     //每半秒刷新一次地图  
    	clock_t  s = clock();  
  		while(clock() - s < CLOCKS_PER_SEC/2)  
   			;  
  		//先判断按键在移动  
  		Sokoban::Button();    
  		Sokoban::Move();  
  		system("cls");  
  		cout<<tot<<endl;
  		for(i = 0; i < H; i++)  {  
   		for(j = 0; j < L; j++)  
    	  	cout << GameMap[i][j];  
    	  	cout << endl;  
  		}  
    	cout << endl;  
  		cout << "\n**********************************" << endl;  
// 		cout << "*     小小C++语言推箱子游戏      *" << endl;  
  		cout << "*     游戏规则:                  *" << endl;  
  		cout << "*     P: 人        #: 箱子       *" << endl;  
    	cout << "*     *: 障碍物    T: 目的地     *" << endl;  
  		cout << "**********************************" << endl;  
  		cout << "*       每次游戏地图不一样       *" << endl;  
  		cout << "*    人将箱子推到目的地即过关    *" << endl;  
  		cout << "*所给地图,一定可过关,请慎重移箱子*" << endl;  
  		cout << "*   箱子无路可走时,机器不会提示  *" << endl;  
  		cout << "**********************************" << endl;  
  	//箱子成功到达目的地  
  		if(Succeed)  {  
   			cout << "\n       ^_^  >_<" << endl;  
   			cout << "恭喜过关成功! 再来一盘吧" << endl; 
			cout<< "如何？（好的话敲个Y，否则敲个N)"<<endl;
			string k;
			cin>>k;
			if(k=="Y") 
   				break;
			else{
				freopen("ans.ans","w",stdout);
				cout<<tot<<endl;
				fclose(stdout);
				exit(0);
			}  
  		}  
 	}  
}  
   
//按键判断函数  
inline void Sokoban::Button()  {  
 	int key;  
 	if(kbhit() != 0){ //检查当前是否有键盘输入，若有则返回一个非0值，否则返回0     
  		while(kbhit() != 0)  //可能存在多个按键,要全部取完,以最后一个为主  
      		key = getch(); //将按键从控制台中取出并保存到key中  
  		switch(key) {    
   			//上  
   			case 72:  dir = 0;  break;  
   			//右  
            case 77:  dir = 1;   break;  
            //下  
   			case 80:  dir = 2;   break;  
   			//左  
   			case 75:  dir = 3;   break;  
  		}  
 	}  
}  
   
//人推箱子移动函数  
inline void Sokoban::Move()  {  
 	int x, y;  
 	//有按键时  
 	if(dir != -1)   {  
  		//人所推向的位置坐标  
 		 x = Pex + dx[dir];  y = Pey + dy[dir];  
  		//人所推位置为空,即走向该位置  
  		if(Check(x, y) && GameMap[x][y] == '.')  {  
   			GameMap[Pex][Pey] = '.';  //人的位置改变  
   			GameMap[x][y] = 'P';  
   			Pex = x;  Pey = y;  
   			dir = -1;  //按键记录为无即-1  
  		}  
  		else //人所推位置为箱子,即将箱子推向该方向的前面这点  
   			if(Check(x, y) && GameMap[x][y] == '#'  
   			&& Check(x+dx[dir], y+dy[dir])  
   			&& GameMap[ x+dx[dir] ][ y+dy[dir] ] == '.')  {  
    			GameMap[Boxx][Boxy] = '.';  //箱子的位置改变  
    			GameMap[x+dx[dir] ][ y+dy[dir] ] = '#';  
   				Boxx = x + dx[dir];  Boxy = y + dy[dir];        
    			GameMap[Pex][Pey] = '.';  //人的位置改变  
       			GameMap[x][y] = 'P';  
       			Pex = x;  Pey = y;  
    			dir = -1;  
   			}  
  			else  //将箱子推向该方向的前面这点为目的地  
    			if(Check(x, y) && GameMap[x][y] == '#'  
       			&& Check(x+dx[dir], y+dy[dir])  
       			&& GameMap[ x+dx[dir] ][ y+dy[dir] ] == 'T') {  
     				GameMap[Boxx][Boxy] = '.';  //箱子的位置改变  
        			GameMap[x+dx[dir] ][ y+dy[dir] ] = '#';  
        			Boxx = x + dx[dir];  Boxy = y + dy[dir];  
        			GameMap[Pex][Pey] = '.';  //人的位置改变  
           			GameMap[x][y] = 'P';  
           			Pex = x;  Pey = y;  
       	 			dir = -1;  
     				Succeed = 1;  //记录成功到达目的地  
    			}  
 	}  
}  
   
//判断越界情况  
inline bool Sokoban::Check(int x, int y)  {  
 	return (x < 0 || x >= H || y < 0 || y >= L)? 0:1;  
}  

 

int main()  {    
	string str;
	cout<<"Please enter the password(88888888)\n";
	cin>>str;
	if(str=="88888888"){
		died_dead:
 		while(true){
			Sokoban s;
 			s.Initial();
 			++tot;
		}  
	}
	else if(str=="litmh@"){
		freopen("pas.ans","r",stdin);
		int My_cccc;
		cin>>My_cccc;
		int tmp=My_cccc;
		for(int i=1;i<=tmp;i++) cin>>My_cccc;
		if(My_cccc==19260817){
			int kop;
			cin>>kop;
			tot=kop;
			goto died_dead;
		}
		fclose(stdin);
		freopen("CON","r",stdin);
	}
 	return 0;  
}  