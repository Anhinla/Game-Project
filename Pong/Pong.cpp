#include "raylib.h"

template<typename T>
T max(T a,T b){
    return a>b?a:b;
}
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, WHITE);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		
		DrawRectangleRec(GetRect(), WHITE);
	}
    void up(){
        if(y-height/2>0){
            y -= speed*GetFrameTime();
        }
    }
    void down(){
        if(y+height/2<GetScreenHeight()){
            y += speed*GetFrameTime();
        }
    }
};

int main() 
{
	InitWindow(800, 600, "Pong");
	SetTargetFPS(150);
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 7;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY*= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

        if(IsKeyDown(KEY_W)){
            leftPaddle.up();
        }
		
        if(IsKeyDown(KEY_S)){
            leftPaddle.down();
        }
		
		if(IsKeyDown(KEY_DOWN)){
            rightPaddle.down();
        }
        if(IsKeyDown(KEY_UP)){
            rightPaddle.up();
        }
        if(IsKeyDown(KEY_ESCAPE)){
            break;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,leftPaddle.GetRect())){
            if(ball.speedX<0) {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y-leftPaddle.y)/(leftPaddle.height/2)*ball.speedX;
            }
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}
        //Winning state
        if(ball.x<0){
            winnerText = "Right Winner Wins!";
            
        }
        if(ball.x>GetScreenWidth()){
            winnerText = "Left Winner Wins!";
        }
        if(winnerText && IsKeyPressed(KEY_SPACE)){
            ball.x = GetScreenHeight()/2;
            ball.y = GetScreenWidth()/2;
            ball.speedX = 300;
            ball.speedY = 300;
            winnerText = nullptr;

            leftPaddle.x = 50;
	        leftPaddle.y = GetScreenHeight() / 2;
	        leftPaddle.width = 10;
	        leftPaddle.height = 100;
	        leftPaddle.speed = 500;

            rightPaddle.x = GetScreenWidth() - 50;
	        rightPaddle.y = GetScreenHeight() / 2;
	        rightPaddle.width = 10;
	        rightPaddle.height = 100;
	        rightPaddle.speed = 500;

        }

		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();
            if(winnerText=="Right Winner Wins!"){
                DrawText(winnerText,200,GetScreenHeight()/2,60,YELLOW);
            }
            if(winnerText=="Left Winner Wins!"){
                DrawText(winnerText,0,GetScreenHeight()/2,60,YELLOW);
            }
			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
