
//To run file Change Paths and run following command

//g++ -c main-combined.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ main-combined.o -o main-combined -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system;./main-combined

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace sf;
using namespace std;
using namespace chrono;

class WindowConst {
    public:
    static float winLength;
    static float winHeight;
    static float  centerx;
    static float centery;
    static float hidex;
    static float hidey;
};
float WindowConst::winLength = 392;
float WindowConst::winHeight = 696;
float WindowConst::hidex = -5000;
float WindowConst::hidey = winHeight+5000;
float WindowConst::centerx = winLength/2;
float WindowConst::centery = winHeight/2;


class Pentagon : public Drawable {
private:
    ConvexShape pentagonShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Pentagon(float size,float initialX,float initialY) {
        pentagonShape.setPointCount(5);
        pentagonShape.setPoint(0, Vector2f(0, -size));
        pentagonShape.setPoint(1, Vector2f(size * 0.9511f, -size * 0.3090f));
        pentagonShape.setPoint(2, Vector2f(size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(3, Vector2f(-size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(4, Vector2f(-size * 0.9511f, -size * 0.3090f));
        pentagonShape.setFillColor(Color::Red); 
        pentagonShape.setOrigin(0, -size); 
        pentagonShape.setPosition(initialX, initialY); 
        currentColor = Color::Red;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            pentagonShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(pentagonShape, states);
    }

    void changePosition(float posx,float posy){
        pentagonShape.setPosition(posx,posy);
    }
};

class Rectangle : public Drawable {
private:
    RectangleShape rectangleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Rectangle(float width, float height,float initialX,float initialY) {
        rectangleShape.setSize(Vector2f(width, height));
        rectangleShape.setFillColor(Color::Blue); 
        rectangleShape.setOrigin(width / 2.0f, height / 2.0f); 
        rectangleShape.setPosition(initialX, initialY); 
        currentColor = Color::Blue;
    }

    void updateColor() {
        if (colorChangeClock.getElapsedTime().asSeconds() >= 2.0f) {
            currentColor = Color(rand() % 256, rand() % 256, rand() % 256);
            rectangleShape.setFillColor(currentColor);
            colorChangeClock.restart(); 
        }
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(rectangleShape, states);
    }

    void changePosition(float posx,float posy){
        rectangleShape.setPosition(posx,posy);
    }
};



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
            blocks[i].setOrigin(Length/2,w/2);
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

    //s
    Pentagon pentagon(100,WindowConst::hidex,WindowConst::hidey);
    Rectangle rectangle(50,70,WindowConst::hidex,WindowConst::hidey); 



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
                    pentagon.changePosition(WindowConst::centerx,10);
                    rectangle.changePosition(WindowConst::centerx,600);
                }




            }

            
        }
    //s
    pentagon.updateColor();
    rectangle.updateColor();
    

    window.clear(Color::Black);
    
    // Draw Functions

    
    home.drawHome(home,window);
    obs1.drawBasicBlocks(obstacleSpeed,window);
    obs2.drawMonoBlocks(obstacleSpeed,window);

    //s
    window.draw(pentagon);
    window.draw(rectangle);



    window.display();   

    }
    

    return 0;
}