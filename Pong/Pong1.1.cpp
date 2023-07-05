#include<raylib.h>
#include<cstdlib>
#include<stdio.h>
class Ball{
public:
    float x,y;
    int radius;
    float speedX, speedY;
    Ball(){}
    Ball(float x, float y, int r, float X, float Y){
        this->x = x;
        this->y = y;
        this->radius = r;
        this->speedX = X;
        this->speedY = Y;
    }
    void Draw(){
        DrawCircle(x,y,radius,WHITE);
    }
};

class Paddle{
public:
    float x,y;
    float speedX;
    int width;
    int height;
    int level;
    int point;
    Color color;
    Paddle(){}
    Paddle(float x,float y,int w,int h,Color color){
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
        this->color = color;
    }
    Rectangle getRect(){
        return Rectangle{x,y,(float)width,(float)height};
    }
    void Draw(){
        DrawRectangle(x,y,width,height,color);
    }
};
class Item{
public:
    float x,y;
    int id;
    float width, height;
    Color color;
    Item();
    Item(int x,int y,int width,int height,Color color){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->color = color;
        this->id = rand()%3;
    }
    Rectangle getRect(){
        return Rectangle{x,y,width,height};
    }
    void Draw(){
        DrawRectangle(x,y,width,height,color);
    }
};
void Point_compute(Paddle& paddle,Vector2 v){
    paddle.point += (paddle.x+paddle.width-v.x)*10;

}
Paddle ItemDecision(Item item){
    Paddle ans;
    switch(item.id){
        case 0:
            ans = Paddle(GetScreenWidth()/2,GetScreenHeight()-100,100,8,WHITE);
            break;
           
        case 1:
            ans = Paddle(0,GetScreenHeight()-20,GetScreenWidth(),10,WHITE);
            break;
      
    }
    return ans;
}
int main(){
    // Set up Window
    InitWindow(800,1000,"Pong 1.1");
    SetTargetFPS(150);

    //Create Object
    Ball ball(GetScreenWidth()/2,GetScreenHeight()/2,7,300,300);

    Item mid(GetScreenWidth()/2-25,0,50,20,YELLOW);

    Paddle paddle(GetScreenWidth()/2-50,GetScreenHeight()-100,100,8,WHITE);
    paddle.speedX = 350;
    const char* state = nullptr;
    int cnt = 0;
    char buffer1[4096];
    char buffer2[4096];
    paddle.level = 1;
    paddle.point = 0;
    while(!WindowShouldClose()){
        ball.x += ball.speedX*GetFrameTime();
        ball.y += ball.speedY*GetFrameTime();
        if(ball.y<0){
            ball.y = 0;
			ball.speedY*= -1;
        }
        if(IsKeyDown(KEY_LEFT)){
            paddle.x -= paddle.speedX*GetFrameTime();
        }
        if(paddle.x<0) paddle.x = 0;

        if(IsKeyDown(KEY_RIGHT)){
            paddle.x += paddle.speedX*GetFrameTime(); 
        }
        // Collision border
        if(paddle.x>GetScreenWidth()-paddle.width) paddle.x = GetScreenWidth()-paddle.width;
        if(ball.x>GetScreenWidth()) {
            ball.speedX *= -1;
        }
        if(ball.x<0){
            ball.speedX *= -1;
        }
        //Collision paddle 
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,paddle.getRect())){
                cnt++;
                Vector2 v;
                v.x = ball.x;
                v.y = ball.y;
                Point_compute(paddle,v);
                ball.speedX *= -1.0f;
                ball.speedY *= -1.0f;			
        }
        if(cnt==5) {
            paddle.level += 1;
            cnt =0;
        }
        //Collision mid 
        Paddle tmp;
        bool x2 = false;
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,mid.getRect())){
            if(mid.id==0){
                tmp = ItemDecision(mid);
            }else if(mid.id==1){
                tmp = ItemDecision(mid);
            }else x2 = true;
        }
        if(x2){
            
        }
        if(ball.y>GetScreenHeight()-90){
            state = "You Lose!";
        }
        if(state && IsKeyDown(KEY_SPACE)){
            ball.x = GetScreenHeight()/2;
            ball.y = GetScreenWidth()/2;
            ball.speedX = 300;
            ball.speedY = 300;
            state = nullptr;

            paddle.x = GetScreenWidth()/2;
            paddle.y = GetScreenHeight()-100;
            paddle.width = 100;
            paddle.height = 8;
        }
        if(IsKeyDown(KEY_ESCAPE)) break;
        BeginDrawing();
        mid.Draw();
        ball.Draw();
        paddle.Draw();
     
        if(state=="You Lose!"){
            DrawText(state,GetScreenWidth()/2-100,GetScreenHeight()/2,60,YELLOW);
        }
        snprintf(buffer1,sizeof(buffer1),"LEVEL:%d",paddle.level);
        DrawText(buffer1,5,GetScreenHeight()-50,25,YELLOW);
        snprintf(buffer2,sizeof(buffer2),"POINT:%d",paddle.point);
        DrawText(buffer2,200,GetScreenHeight()-50,25,YELLOW);
        DrawFPS(GetScreenWidth()-100,GetScreenHeight()-50);
        ClearBackground(BLACK);
        EndDrawing();
    }
}