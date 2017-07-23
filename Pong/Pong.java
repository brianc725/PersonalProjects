package pong;

import java.util.Random;

import processing.core.PApplet;


public class Pong extends PApplet {
	
	public Paddle p1 = new Paddle(50, 250);
	public Paddle p2 = new Paddle((1300-50-30), 250);
	public Ball b1 = new Ball (625, 300);
	
	public int score1 = 0;
	public int score2 = 0;

	public void setup() {
		size(1300, 700);
		background(0, 0, 0);
		//middle rectangles here
	}

	public void draw() {
	p1.update();
	p2.update();
	b1.update();
	refresh();
	p1.drawPaddle();
	p2.drawPaddle();
	b1.drawBall();
	}
	
	public class Paddle {
		float xPos;
		float yPos;
		float speed = 10;

		public boolean moveUp;
		public boolean moveDown;

		public Paddle (float startX, float startY)
		{
			xPos = startX;
			yPos = startY;
		}

		public void drawPaddle() {
			fill(255);
			rect(xPos, yPos, 30, 150);
		}

		public void update() {
			if (moveUp)
			{
				yPos -= speed;
			}
			if (moveDown)
			{
				yPos += speed;
			}
			checkBounds();
		}

		public void checkBounds(){
			if (yPos < 0)
			{
				yPos = 0;
				moveUp = false;
			}
			if (yPos + 150 > height)
			{
				yPos = height-150;
				moveDown = false;
			}
		}
	}
	
	public class Ball {
		float xPos;
		float yPos;
		float xSpeed = 5;
		float ySpeed = 5;
		
		public Ball (float startX, float startY)
		{
			xPos = startX;
			yPos = startY;
		}
		
		public void update() {
			xPos += xSpeed;
			yPos += ySpeed;
			checkBounds();
			checkCollision();
		}
		
		public void drawBall() {
			fill(255, 255, 255);
			rect(xPos, yPos, 25, 25);
		}
		
		public void checkCollision() {
			if (xPos+25 > p2.xPos && xPos+25 < p2.xPos + 30 && yPos > p2.yPos && yPos < p2.yPos+150 )
			{
				Random generator = new Random();
				xSpeed = -xSpeed;
				ySpeed = -ySpeed;
				xSpeed += generator.nextFloat()*16 - 8;
				ySpeed += generator.nextFloat()*16 - 8;
			}
			if (xPos < p1.xPos+30 && xPos > p1.xPos && yPos > p1.yPos && yPos < p1.yPos + 150)
			{
				Random generator = new Random();
				xSpeed = -xSpeed;
				ySpeed = -ySpeed;
				xSpeed += generator.nextFloat()*16 - 8;
				ySpeed += generator.nextFloat()*16 - 8;
			}
		}
		
		public void checkBounds() {
			if (yPos + 25 > height)
			{
				ySpeed = -ySpeed;
			}
			if (yPos < 0)
			{
				ySpeed = -ySpeed;
			}
			if (xPos + 25 > width)
			{
				score1++;
				xPos = 625;
				yPos = 300;
				xSpeed = 5;
				ySpeed = 5;
			}
			if (xPos < 0)
			{
				score2++;
				xPos = 625;
				yPos = 300;
				xSpeed = -5;
				ySpeed = 5;
			}
		}
	}

	public void refresh() {
		size(1300, 700);
		background(0, 0, 0);
		//middle rectangles here
		textSize(32);
		text(score1, 200, 50); 
		text(score2, 1100, 50);
	}

	public void keyPressed()
	{
		if (key == 'w' || key == 'W')
		{
			p1.moveUp = true;
		}
		if (key == 's' || key == 'S')
		{
			p1.moveDown = true;
		}
		if (key == 'i' || key == 'I')
		{
			p2.moveUp = true;
		}
		if (key == 'k' || key == 'K')
		{
			p2.moveDown = true;
		}
		if (key == '1')
		{
			score1++;
		}
		if (key == '2')
		{
			score2++;
		}
		if (key == 'r' || key == 'R')
		{
			refresh();
			p2.moveUp = false;
			p2.moveDown = false;
			p1.moveUp = false;
			p1.moveDown = false;
			b1.xPos = 650;
			b1.yPos = 300;
			b1.xSpeed = 5;
			b1.ySpeed = 5;
			score1 = 0;
			score2 = 0;
		}
	}
	
	public void keyReleased()
	{
		if (key == 'w' || key == 'W')
		{
			p1.moveUp = false;
		}
		if (key == 's' || key == 'S')
		{
			p1.moveDown = false;
		}
		if (key == 'i' || key == 'I')
		{
			p2.moveUp = false;
		}
		if (key == 'k' || key == 'K')
		{
			p2.moveDown = false;
		}
	}
	
}
