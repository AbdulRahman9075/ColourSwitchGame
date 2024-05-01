

//To run file Change Paths and run following command

//g++ -c abdulrahman.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ abdulrahman.o -o abdulrahman -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system;./abdulrahman

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class WindowConst {
    public:
    static int winLength;
    static int winHeight;
    static int centerx;
    static int centery;
    static int hidex;
    static int hidey;
};
int WindowConst::winLength = 392;
int WindowConst::winHeight = 696;
int WindowConst::hidex = -5000;
int WindowConst::hidey = winHeight+5000;
int WindowConst::centerx = winLength/2;
int WindowConst::centery = winHeight/2;

class Button:public Sprite{
    protected:
    Texture buttontexture;
    public:

    
    Button(string texturefilepath,float offsetx,float offsety){

        buttontexture.loadFromFile(texturefilepath);
        setTexture(buttontexture);
        setPosition(196,348);
        setOrigin(29,29);
        move(offsetx,offsety);
        
    }

    void drawButton(Button &obj,RenderWindow &win){
        win.draw(obj);
    }
};



class HomePage:public Sprite{
    Texture hometexture;
    public:
    Button easybutton = Button("Sprites\\easy.png",-70,-120);
    Button hardbutton = Button("Sprites\\hard.png",50,-120);
    Button editbutton = Button("Sprites\\edit.png",-10,-60);
    // TO DO:: Add ScoreBoard Object which shows highscore and/or top three scores
    

    
    
    HomePage(){
        
        hometexture.loadFromFile("Sprites\\home.png");
        setTexture(hometexture);
    }

    void drawHome(HomePage &home,RenderWindow &win){
        win.draw(home);
        easybutton.drawButton(easybutton,win);
        hardbutton.drawButton(hardbutton,win);
        editbutton.drawButton(editbutton,win);
    }

    

};

class ArrayofBlocks {
    
    const int N;
    float Length = WindowConst::winLength/N;
    float Width;
    const float Spacing;
    float InitialX;
    float InitialY;
    RectangleShape blocks[5];
    Color colors[5] = {Color(255,0,0),Color(0,255,0),Color(0,0,255),Color(255,255,0),Color(255,0,255)};
    public:
    
    
    ArrayofBlocks(float initialposx,float initialposy,float w,int n,float spacing):InitialX(initialposx),InitialY(initialposy),Width(w),N(n),Spacing(spacing){
        for(int i=0;i<5;i++){
            blocks[i] = RectangleShape(Vector2f(Length,w));
            // blocks[i].setOrigin(Length/2,w/2);
        }
        
        blocks[0].setPosition(InitialX,InitialY);

        for(int i=0;i<4;i++){
            blocks[i+1].setPosition(blocks[i].getPosition().x+(Spacing*Length),blocks[i].getPosition().y);
        }
        
        
      
    }
    void changeInitialPos(int x,int y){
        InitialX = x;
        InitialY = y;
        blocks[0].setPosition(InitialX,InitialY);
        for(int i=0;i<4;i++){
            blocks[i+1].setPosition(blocks[i].getPosition().x+(Spacing*Length),blocks[i].getPosition().y);
        }
    }

    void movingBlocks(float speed,RenderWindow &win){

        for(int i=0;i<5;i++){

            blocks[i].move(speed/100,0);
            
            if (blocks[i].getPosition().x > WindowConst::winLength){
                blocks[i].setPosition(0,InitialY);
            }
        }
        
    }
    void drawBasicBlocks(float speed,RenderWindow &win){

        srand(time(0));
        for(int i=0;i<5;i++){
            blocks[i].setFillColor(colors[rand()%5]);
            win.draw(blocks[i]);
        }
        movingBlocks(speed,win);

    }
    void drawMonoBlocks(float speed,RenderWindow &win){

        Color c = colors[rand()%5];
        for(int i=0;i<5;i++){
            blocks[i].setFillColor(c);
            win.draw(blocks[i]);
        }
        movingBlocks(speed,win);


    }

    
};



int main()
{   

    // Initializing Objects

    float obstacleSpeed = 9;
    RenderWindow window(VideoMode(WindowConst::winLength,WindowConst::winHeight),"Color Switch",Style::Close | Style::Titlebar);
    HomePage home;
    ArrayofBlocks obs1(WindowConst::hidex,WindowConst::hidey,15,5,1.075);
    ArrayofBlocks obs2(WindowConst::hidex,WindowConst::hidey,15,5,1.075);


    // Main Loop
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed){
                window.close();}

            //Check if left mouse button is pressed
            if (evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) {
                Vector2i currentMousePos = Mouse::getPosition(window);
                
                
                if (home.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.move(WindowConst::hidex,0);
                    home.easybutton.move(WindowConst::hidex,0);
                    home.editbutton.move(WindowConst::hidex,0);
                    home.hardbutton.move(WindowConst::hidex,0);


                    obs1.changeInitialPos(-15,WindowConst::centery);
                    obs2.changeInitialPos(0,WindowConst::winHeight/4);
                    
                }




            }

            
        }
   
    
    window.clear(Color::Black);
    
    // Draw Functions

    
    home.drawHome(home,window);

    obs1.drawBasicBlocks(obstacleSpeed,window);
    obs2.drawMonoBlocks(obstacleSpeed,window);

    window.display();   

    }
    

    return 0;
}