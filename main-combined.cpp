
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

class Pentagon : public Drawable {
private:
    ConvexShape pentagonShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Pentagon(float size) {
        pentagonShape.setPointCount(5);
        pentagonShape.setPoint(0, Vector2f(0, -size));
        pentagonShape.setPoint(1, Vector2f(size * 0.9511f, -size * 0.3090f));
        pentagonShape.setPoint(2, Vector2f(size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(3, Vector2f(-size * 0.5877f, size * 0.8090f));
        pentagonShape.setPoint(4, Vector2f(-size * 0.9511f, -size * 0.3090f));
        pentagonShape.setFillColor(Color::Red); 
        pentagonShape.setOrigin(0, -size); 
        pentagonShape.setPosition(200, 150); 
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
};

class Rectangle : public Drawable {
private:
    RectangleShape rectangleShape;
    Color currentColor;
    Clock colorChangeClock;

public:
    Rectangle(float width, float height) {
        rectangleShape.setSize(Vector2f(width, height));
        rectangleShape.setFillColor(Color::Blue); 
        rectangleShape.setOrigin(width / 2.0f, height / 2.0f); 
        rectangleShape.setPosition(600, 400); 
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
};

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

class ObstacleCircle {
private:
    int x;
    int y;
    int radius;
    Color colors[4];
    int position;

public:
    ObstacleCircle(int x, int y, int radius) : x(x), y(y), radius(radius), position(0) {
        colors[0] = sf::Color::Red;
        colors[1] = sf::Color::Green;
        colors[2] = sf::Color::Blue;
        colors[3] = sf::Color::Yellow;
    }

    void draw(sf::RenderWindow& window) {
        position = (position + 1) % 4;
        for (int i = 0; i < 4; ++i) {
            CircleShape shape(radius, 60);
            shape.setFillColor(colors[(i + position) % 4]);
            shape.setPosition(x - radius, y - radius);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Black);
            window.draw(shape);
        }
    }
};

class Ball {
private:
    int x;
    int y;
    int radius;
    sf::Color colors[4];
    int colorIndex;

public:
    Ball(int x, int y, int radius) : x(x), y(y), radius(radius), colorIndex(0) {
        colors[0] = sf::Color::Red;
        colors[1] = sf::Color::Green;
        colors[2] = sf::Color::Blue;
        colors[3] = sf::Color::Yellow;
    }

    void draw(sf::RenderWindow& window) {
        CircleShape shape(radius);
        shape.setFillColor(colors[colorIndex]);
        shape.setPosition(x - radius, y - radius);
        window.draw(shape);
    }

    void moveAbove(sf::RenderWindow& window) {
        int maxY = y - 305;
        while (y > maxY) {
            y -= 1;
            draw(window);
            window.display();
            sf::sleep(sf::milliseconds(10));
        }
    }

    inline int getColorIndex() {
        return colorIndex;
    }
};

int main()
{   
    srand(time(NULL)); //j
    // Initializing Objects

    float obstacleSpeed = 9;
    RenderWindow window(VideoMode(WindowConst::winLength,WindowConst::winHeight),"Color Switch",Style::Close | Style::Titlebar);
    HomePage home;
    ArrayofBlocks obs1(WindowConst::hidex,WindowConst::hidey,15,5,1.075);
    ArrayofBlocks obs2(WindowConst::hidex,WindowConst::hidey,15,5,1.075);

    //s
    Pentagon pentagon(50.0f);
    Rectangle rectangle(100.0f, 80.0f); 

    //j
    ObstacleCircle obstacle(500, 550, 80);
    Ball ball(500, 750, 30);

    bool ballMoved = false;

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
    //s
    pentagon.updateColor();
    rectangle.updateColor();
    
    //j
    if (!ballMoved) {
            ballMoved = true;
            ball.moveAbove(window);
        }

    window.clear(Color::Black);
    
    // Draw Functions

    
    home.drawHome(home,window);
    obs1.drawBasicBlocks(obstacleSpeed,window);
    obs2.drawMonoBlocks(obstacleSpeed,window);

    //s
    window.draw(pentagon);
    window.draw(rectangle);

    //j
    ball.draw(window);
    obstacle.draw(window);


    window.display();   

    }
    

    return 0;
}