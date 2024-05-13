
//To compile file Change Paths and run following command

//g++ -c main-combined.cpp -I"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\include";g++ main-combined.o -o main-combined -L"C:\Users\Abdul Rahman\Documents\GitHub\ColourSwitchGame\lib" -lsfml-graphics -lsfml-window -lsfml-system

// To Run File run command: ./main-combined
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <variant>


using namespace sf;
using namespace std;

class GameConst {
    public:
    static float winLength;
    static float winHeight;
    static float centerx;
    static float centery;
    static float hidex;
    static float hidey;
    static float colorChangeTime;
    static float obstacleSpeed;
    static float gravity;
    static float ballUpSpeed;

    virtual void gameConst() = 0;

};
float GameConst::winLength = 392;
float GameConst::winHeight = 696;
float GameConst::hidex = -5000;
float GameConst::hidey = winHeight+5000;
float GameConst::centerx = winLength/2 + 25;
float GameConst::centery = winHeight/2;
float GameConst::colorChangeTime = 2.0f;
float GameConst::obstacleSpeed = 9;
float GameConst::gravity = 20;
float GameConst::ballUpSpeed = -70;






class Button:public Sprite{
    protected:
    Texture buttontexture;
    public:

    
    Button(string texturefilepath,float offsetx,float offsety){

        buttontexture.loadFromFile(texturefilepath);
        setTexture(buttontexture);
        setPosition(Vector2f(196,348));
        setOrigin(29,29);
        move(offsetx,offsety);
        
    }

    void drawButton(Button &obj,RenderWindow &win){
        win.draw(obj);
    }
};



class HomePage:public Sprite{
    Texture hometexture;
    Texture gameovertexture;
    Texture notexture;
    
    public:
    Button easybutton = Button("Sprites\\easy.png",-65,-170);
    Button hardbutton = Button("Sprites\\hard.png",55,-169);
    Button circlebutton = Button("Sprites\\circle.png",-65,-30);
    Button squarebutton = Button("Sprites\\square.png",55,-29);
    Button homebutton = Button("Sprites\\homebutton.png",GameConst::hidex,GameConst::hidex);
    // TO DO:: Add ScoreBoard Object which shows highscore and/or top three scores
    

    
    public:
    HomePage(){
        
        hometexture.loadFromFile("Sprites\\home.png");
        gameovertexture.loadFromFile("Sprites\\GameOver.png");
        notexture.loadFromFile("Sprites\\none.png");
        setTexture(hometexture);
    }

    void drawHome(HomePage &home,RenderWindow &win){
        win.draw(home);
        easybutton.drawButton(easybutton,win);
        hardbutton.drawButton(hardbutton,win);
        circlebutton.drawButton(circlebutton,win);
        squarebutton.drawButton(squarebutton,win);
        homebutton.drawButton(homebutton,win);
    }

    void hideHome(HomePage &home){
        
        home.setPosition(Vector2f(GameConst::hidex,0));
        home.easybutton.move(GameConst::hidex,0);
        home.circlebutton.move(GameConst::hidex,0);
        home.squarebutton.move(GameConst::hidex,0);
        home.hardbutton.move(GameConst::hidex,0);
    }

    void showHome(HomePage &home){
        setTexture(hometexture);
        home.setPosition(Vector2f(0,0));
        homebutton.move(GameConst::hidex,0);
        //196,348
        home.easybutton.setPosition(Vector2f(131,179));
        home.circlebutton.setPosition(Vector2f(131,319));
        home.squarebutton.setPosition(Vector2f(251,319));
        home.hardbutton.setPosition(Vector2f(251,179));
    }
    
    void gameOver(HomePage &home){
        setTexture(gameovertexture);
        home.setPosition(Vector2f(0,0));
        homebutton.setPosition(Vector2f(165,160));
    }
};


class Object: virtual public Drawable {
    public:

    virtual void changeInitialPosition(float posx,float posy) =0;

    virtual void updateColor()  = 0;

};



template<typename T>
class Ball : public Drawable {
private:
    Vector2f initialPosition;
    Color ballColor;
    T shape;
    float upSpeed = GameConst::ballUpSpeed;
    float downSpeed = 0.0;
    float gravity = 0.0;
    bool isJumping = false;
    
public:

    bool getIsJumping(){return isJumping;}
    void setIsJumping(bool value){isJumping = value;}
    
    

    Ball(const T& initialShape, const Color& fillColor = Color::White, const Vector2f& initialPos = {0, 0}, const Vector2f& initialOrigin = {0, 0}) : shape(initialShape) {
        initialPosition = initialPos;
        ballColor = fillColor;
        
        shape.setFillColor(ballColor);
        shape.setPosition(initialPosition);
        shape.setOrigin(initialOrigin);
        
    }

    // -ve up +ve down

    float jumpBall(float dt,Clock clk){
        downSpeed=0;
        clk.restart();
        gravity = GameConst::gravity;
        upSpeed += gravity*dt;

        shape.move(0,upSpeed);
        return upSpeed;
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

    void changeInitialPosition(float posx,float posy) {
        shape.setPosition(Vector2f(posx,posy));
    }

    Vector2f GetPosition()const{
        return shape.getPosition();
    }

    void SetPosition(float posx ,float posy)const{shape.setPosition(posx,posy);}
};

class ArrayofBlocks{
    
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

    

    void changeInitialPosition(int posx,int posy){
        InitialX = posx;
        InitialY = posy;
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

    Vector2f GetPosition()const{return blocks[0].getPosition();}

    void SetPosition(float posx ,float posy){blocks[0].setPosition(posx,posy);}
    
};

class Pentagon : virtual public Drawable,public Object {
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
        Vector2f center(
            (pentagonShape.getPoint(0).x + pentagonShape.getPoint(2).x) / 2.0f,
            (pentagonShape.getPoint(1).y + pentagonShape.getPoint(3).y) / 2.0f
        );
        // Set the origin to the center
        pentagonShape.setOrigin(center);
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

    void changeInitialPosition(float posx,float posy){
        pentagonShape.setPosition(posx,posy);
    }

    Vector2f GetPosition()const{return pentagonShape.getPosition();}

    void SetPosition(float posx ,float posy){pentagonShape.setPosition(posx,posy);}
};

class Rectangle : virtual public Drawable,public Object{
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

    void changeInitialPosition(float posx,float posy){
        rectangleShape.setPosition(posx,posy);
    }

    Vector2f GetPosition()const{return rectangleShape.getPosition();}
    // void SetPosition(Vector2f &newpos)const{rectangleShape.setPosition(newpos);}
};


// void hideObjects(ArrayofBlocks randomline1,ArrayofBlocks randomline2,ArrayofBlocks singleline1,ArrayofBlocks singleline2,Pentagon pentagon,Rectangle rectangle){
//     using Variant = variant<Ball<CircleShape>,Ball<RectangleShape>,ArrayofBlocks,Pentagon,Rectangle>;
//     vector<Variant> objects;

//     objects.push_back(randomline1);
//     objects.push_back(randomline2);
//     objects.push_back(singleline1);
//     objects.push_back(singleline2);
//     objects.push_back(pentagon);
//     objects.push_back(rectangle);

//     for (const auto &obj : objects) {
//         // Use std::visit to handle different types
//         visit([](const auto& val) {

//             if(val.GetPosition() != Vector2f(GameConst::hidex,GameConst::hidey)){
//                 val.SetPosition(GameConst::hidex,GameConst::hidey);
//             }

//         }, obj);
//     }

// }






int main()
{   
    
   
    // Ball<void>* shape = nullptr;
    
    int pageCount =0;
    string Level = "";
    string ballShape = "";

    // Initializing Objects
    Clock clk;
    clk.restart();
    
    RenderWindow window(VideoMode(GameConst::winLength,GameConst::winHeight),"Color Switch",Style::Close | Style::Titlebar);
    
    // Create a Ball with initialshape, red color, position, origin at (50, 50)
    CircleShape circle(15);
    RectangleShape square(Vector2f(25,25));
    Ball<CircleShape> circleBall(circle, Color::Red, {GameConst::hidex,GameConst::hidey}, {50, 50});
    Ball<RectangleShape> squareBall(square, Color::Red, {GameConst::hidex,GameConst::hidey}, {50, 50});
    
    HomePage home;
    

    ArrayofBlocks randomline1(GameConst::hidex,GameConst::hidey,15,5,1.075);
    ArrayofBlocks singleline1(GameConst::hidex,GameConst::hidey,15,5,1.075);
    ArrayofBlocks randomline2(GameConst::hidex,GameConst::hidey,15,5,1.075);
    ArrayofBlocks singleline2(GameConst::hidex,GameConst::hidey,15,5,1.075);
    //s
    Pentagon pentagon(100,GameConst::hidex,GameConst::hidey);
    Rectangle rectangle(GameConst::winLength-100,100,GameConst::hidex,GameConst::hidey); 

    float dt = clk.getElapsedTime().asSeconds()/1800;

    



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
                
                if (home.circlebutton.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    ballShape = "circle";
                }
                else if(home.squarebutton.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    ballShape = "square";
                }
                
               if(home.homebutton.getGlobalBounds().contains(Vector2f(currentMousePos))){

                    home.showHome(home);
               }
                if (home.easybutton.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.hideHome(home);

                    if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    
    
                    

                    Level = "easy";
                    pentagon.changeInitialPosition(GameConst::centerx,GameConst::centery);
                    
                }

                if (home.hardbutton.getGlobalBounds().contains(Vector2f(currentMousePos))) {
                    
                    home.hideHome(home);
                    
                    if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    

                    Level = "hard";
                    pentagon.changeInitialPosition(GameConst::centerx,GameConst::winHeight/4);
                    rectangle.changeInitialPosition(GameConst::centerx-30,GameConst::winHeight*3/4-55);///
                }

            }

            if(ballShape=="circle"){
                if (((evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) ||
                    (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Space)) &&
                    home.getPosition().x == GameConst::hidex){
                            circleBall.setIsJumping(true); ///
                            circleBall.moveBall(dt,clk); ///
                    }
                circleBall.setIsJumping(false); ///
            }
            else if(ballShape=="square"){
                if (((evnt.type == Event::MouseButtonPressed && evnt.mouseButton.button == Mouse::Left) ||
                    (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Space)) &&
                    home.getPosition().x == GameConst::hidex){
                            squareBall.setIsJumping(true); ///
                            squareBall.moveBall(dt,clk); ///
                    }
                squareBall.setIsJumping(false); ///
            }

            if(circleBall.GetPosition().y <= 0 || squareBall.GetPosition().y <= 0){ ///

                if(Level == "easy"){
                    

                    if(pageCount ==0){
                    pentagon.changeInitialPosition(GameConst::hidex,GameConst::hidey);

                    if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                     ///
                    
                    rectangle.changeInitialPosition(GameConst::centerx-30,GameConst::centery);
                    pageCount++;
                        
                    }
                    else if(pageCount ==1){
                        rectangle.changeInitialPosition(GameConst::hidex,GameConst::hidey);

                        if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                        else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);} ///
                        randomline1.changeInitialPosition(0,GameConst::centery-100);
                        singleline1.changeInitialPosition(0,GameConst::centery+100);
                        pageCount++;
                        
                    }

                     // Complete Easy Level
                    else if(pageCount==2){
                        if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::hidex,GameConst::hidey);}
                        else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::hidex,GameConst::hidey);} ///
                        randomline1.changeInitialPosition(GameConst::hidex,GameConst::hidey);
                        singleline1.changeInitialPosition(GameConst::hidex,GameConst::hidey);
                        pageCount =0;
                        home.gameOver(home);
                        
                    }
                    
                }

                else if(Level == "hard"){


                    if(pageCount ==0){
                    pentagon.changeInitialPosition(GameConst::hidex,GameConst::hidey);

                    if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                    else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);} ///
                    
                    rectangle.changeInitialPosition(GameConst::centerx-30,GameConst::winHeight/2 - 50);
                    randomline1.changeInitialPosition(0,GameConst::winHeight*3/4 - 30);
                    singleline1.changeInitialPosition(0,GameConst::winHeight/4 - 80);
                    
                    pageCount++;
                    
                    }
                    else if(pageCount ==1){
                        rectangle.changeInitialPosition(GameConst::hidex,GameConst::hidey);

                        if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);}
                        else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::centerx,GameConst::winHeight-30);} ///
                        
                        randomline1.changeInitialPosition(0,GameConst::winHeight*3/4 - 30);
                        singleline1.changeInitialPosition(0,GameConst::winHeight/2 - 30);
                        randomline2.changeInitialPosition(0,GameConst::winHeight/4 - 30);
                        pageCount++;
                        
                    }

                    // Complete Hard Level
                    else if(pageCount==2){
                        if(ballShape == "circle"){circleBall.changeInitialPosition(GameConst::hidex,GameConst::hidey);}
                        else if(ballShape == "square"){squareBall.changeInitialPosition(GameConst::hidex,GameConst::hidey);} ///
                        
                        randomline1.changeInitialPosition(GameConst::hidex,GameConst::hidey);
                        singleline1.changeInitialPosition(GameConst::hidex,GameConst::hidey);
                        randomline2.changeInitialPosition(GameConst::hidex,GameConst::hidey);
                        pageCount =0;
                        home.gameOver(home);
                    }
                }
            }
            
            
        }

    //s
    pentagon.updateColor();
    rectangle.updateColor();
    
    if(ballShape == "circle"){circleBall.moveBall(dt,clk);}
    else if(ballShape == "square"){squareBall.moveBall(dt,clk);}
    

    window.clear(Color::Black);
    
    // Draw Functions

    
    home.drawHome(home,window);
    randomline1.drawBasicBlocks(window);
    singleline1.drawMonoBlocks(window);
    randomline2.drawBasicBlocks(window);
    singleline2.drawMonoBlocks(window);

    if(ballShape == "circle"){window.draw(circleBall);}
    else if(ballShape == "square"){window.draw(squareBall);} ///

    //s
    window.draw(pentagon);
    window.draw(rectangle);



    window.display();   

    }
    

    return 0;
}