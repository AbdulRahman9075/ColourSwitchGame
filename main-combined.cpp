
//To compile file Change Paths and run following command

//g++ -c main-combined.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ main-combined.o -o main-combined -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system

// To Run File run command: ./main-combined
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>


using namespace sf;
using namespace std;

class GameConst {
    public:
    static float winLength;
    static float winHeight;
    static float  centerx;
    static float centery;
    static float hidex;
    static float hidey;
    static float colorChangeTime;
    static float obstacleSpeed;

};
float GameConst::winLength = 392;
float GameConst::winHeight = 696;
float GameConst::hidex = -5000;
float GameConst::hidey = winHeight+5000;
float GameConst::centerx = winLength/2;
float GameConst::centery = winHeight/2;
float GameConst::colorChangeTime = 2.0f;
float GameConst::obstacleSpeed = 9;


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

template<typename T>
class Ball : public Drawable {
private:
    Vector2f initialPosition;
    Color ballColor;
    T shape;
    float upSpeed = -200;
    float downSpeed = 0.0;
    float gravity = 0.0;
    

public:
    bool isJumping = false;
    Ball(const T& initialShape, const Color& fillColor = Color::White, const Vector2f& initialPos = {0, 0}, const Vector2f& initialOrigin = {0, 0}) : shape(initialShape) {
        initialPosition = initialPos;
        ballColor = fillColor;
        
        shape.setFillColor(ballColor);
        shape.setPosition(initialPosition);
        shape.setOrigin(initialOrigin);
        
    }

    // -ve up +ve down

    void jumpBall(float dt,Clock clk){
        downSpeed=0;
        clk.restart();
        gravity = 9.81;
        upSpeed += gravity*dt;

        shape.move(0,upSpeed);
    }

    void moveBall(float dt,Clock clk){
        if(isJumping){
            jumpBall(dt,clk);
        }
        else{
            clk.restart();
            downSpeed += gravity*dt;
            shape.move(0,downSpeed);
        }
        
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(shape, states);
    }

    void changeInitialPosition(float posx,float posy){
        shape.setPosition(Vector2f(posx,posy));
    }
};

class ArrayofBlocks {
    
    const int N;
    float Length = GameConst::winLength/N;
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
            
            if (blocks[i].getPosition().x > GameConst::winLength){
                blocks[i].setPosition(0,InitialY);
            }
        }
        
    }
    void drawBasicBlocks(RenderWindow &win){
        srand(time(0));
        for(int i=0;i<5;i++){
            blocks[i].setFillColor(colors[rand()%5]);
            win.draw(blocks[i]);
        }
        movingBlocks(GameConst::obstacleSpeed,win);

    }
    
    void drawMonoBlocks(RenderWindow &win){
        srand(time(0));
        Color c = colors[rand()%5];
        for(int i=0;i<5;i++){
            blocks[i].setFillColor(c);
            win.draw(blocks[i]);
        }
        movingBlocks(GameConst::obstacleSpeed,win);


    }

    
};

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
        if (colorChangeClock.getElapsedTime().asSeconds() >= GameConst::colorChangeTime) {
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
        if (colorChangeClock.getElapsedTime().asSeconds() >= GameConst::colorChangeTime) {
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






int main()
{   

    // Initializing Objects
    Clock clk;
    clk.restart();
    
    RenderWindow window(VideoMode(GameConst::winLength,GameConst::winHeight),"Color Switch",Style::Close | Style::Titlebar);
    
    // Create an Ball with initial circle shape, red color, position (200, 300), origin at (50, 50), and radius 50
    CircleShape circle(15);
    Ball<CircleShape> circleBall(circle, Color::Red, {GameConst::hidex,GameConst::hidey}, {50, 50});
    
    HomePage home;
    

    ArrayofBlocks obs1(GameConst::hidex,GameConst::hidey,15,5,1.075);
    ArrayofBlocks obs2(GameConst::hidex,GameConst::hidey,15,5,1.075);
    //s
    Pentagon pentagon(100,GameConst::hidex,GameConst::hidey);
    Rectangle rectangle(50,70,GameConst::hidex,GameConst::hidey); 


    float dt = clk.getElapsedTime().asSeconds()/2500;

    // Main Loop
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed){
                window.close();}

            //Check if left mouse button is pressed
            if (evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left || evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Enter) {
                
                Vector2i currentMousePos = Mouse::getPosition(window);
                
                if (home.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.move(GameConst::hidex,0);
                    home.easybutton.move(GameConst::hidex,0);
                    home.editbutton.move(GameConst::hidex,0);
                    home.hardbutton.move(GameConst::hidex,0);

                    circleBall.changeInitialPosition(GameConst::centerx,GameConst::centery);
                    obs1.changeInitialPos(-15,GameConst::centery);
                    obs2.changeInitialPos(0,GameConst::winHeight/4);
                    pentagon.changePosition(GameConst::centerx,10);
                    rectangle.changePosition(GameConst::centerx,600);
                }
            }

            if (((evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) ||
                (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Space)) &&
                home.getPosition().x == GameConst::hidex){
                        circleBall.isJumping = true;
                        circleBall.moveBall(dt,clk);
                     }
            circleBall.isJumping = false;

        }
    //s
    pentagon.updateColor();
    rectangle.updateColor();
    
    circleBall.moveBall(dt,clk);

    window.clear(Color::Black);
    
    // Draw Functions

    
    home.drawHome(home,window);
    obs1.drawBasicBlocks(window);
    obs2.drawMonoBlocks(window);

    window.draw(circleBall);

    //s
    window.draw(pentagon);
    window.draw(rectangle);



    window.display();   

    }
    

    return 0;
}