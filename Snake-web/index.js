const canvas = document.getElementById("game");
const cxt = canvas.getContext('2d');
class SnakePart{
    constructor(x,y){
        this.x = x;
        this.y = y;
    }
}
let speed = 6;
let tileCount = 20;
let tileSize = canvas.clientWidth/tileCount - 2;

let headX = 10;
let headY = 10;

let appleX = 5;
let appleY = 5;
let xVelocity = 0;
let yVelocity = 0;
let tailLength = 0;
let snakeParts = [];

let score = 0;

const sound = new Audio('gulp.mp3');


function drawGame(){
    moveSnake();
    let result = isOver();
    if(result){
        return;
    }
    clearScreen();
    checkAppleCollision();
    drawSnake();
    drawApple();
    drawScore();
    if(score>5){
        speed = 8;
    }
    if(score>10){
        speed = 10;
    }
    setTimeout(drawGame,1000/speed);
}
function isOver(){
    let gameOver = false;
    // Check the game hasn't started
    if(xVelocity ===0 && yVelocity===0){
        return false;
    }
    if(headX<0 || headX ==tileCount || headY<0 || headY==tileCount){
        gameOver = true;
    }
    for(let i=0;i<snakeParts.length;i++){
        let part = snakeParts[i];
        if(part.x == headX && part.y == headY){
            gameOver = true;
            break;
        }
    }
    if(gameOver){
        cxt.fillStyle = 'white';
        cxt.font = "50px Verdana";
        cxt.fillText("Game Over!!!",canvas.clientWidth/9.5,canvas.clientHeight/2);
    }
    
    return gameOver;
}
function drawScore(){
    cxt.fillStyle = 'yellow';
    cxt.font = "20px Verdana";
    cxt.fillText("Score: "+score,canvas.clientWidth-120,20);
}
function clearScreen(){
    cxt.fillStyle = 'black';
    cxt.fillRect(0,0,canvas.clientWidth,canvas.clientHeight)
}

function moveSnake(){
    headX += xVelocity;
    headY += yVelocity;
}
function drawSnake(){
    cxt.fillStyle = 'green';
    for(let i=0;i<snakeParts.length;i++){
        part = snakeParts[i];
        cxt.fillRect(part.x*tileCount,part.y*tileCount,tileSize,tileSize);
    }
    snakeParts.push(new SnakePart(headX,headY));
    if(snakeParts.length>tailLength){
        snakeParts.shift();
    }
    cxt.fillStyle = 'orange';
    cxt.fillRect(headX*tileCount,headY*tileCount,tileSize,tileSize);
}
function drawApple(){
    cxt.fillStyle = 'red';
    cxt.fillRect(appleX*tileCount,appleY*tileCount,tileSize,tileSize);
}
document.body.addEventListener('keydown',keyDown);

function keyDown(event){
    if(event.keyCode == 37 ){
        if(xVelocity==1) return;
        xVelocity = -1;
        yVelocity = 0;
    }else if(event.keyCode ==39){
        if(xVelocity==-1) return;
        xVelocity = 1;
        yVelocity = 0;
    // up
    }else if(event.keyCode ==38){
        if(yVelocity==1) return;
        yVelocity = -1;
        xVelocity = 0;
    }else if(event.keyCode ==40){
        if(yVelocity==-1) return;
        yVelocity = 1;
        xVelocity = 0;
    }
}
function checkAppleCollision(){
    if(appleX === headX && appleY === headY){
        sound.play();
        appleX = Math.round(Math.random()*tileCount-1);
        appleY = Math.round(Math.random()*tileCount-1);
        tailLength++;
        score++;
    }
}
drawGame();