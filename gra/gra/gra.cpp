#include "pch.h"
#include <SFML\Graphics.hpp>
#include <cmath>

int frame = 0;
int opacity = 255;
bool game = false;
bool isFirst = true;
sf::Sprite user;
sf::Sprite randomPoint;
sf::Text counter;
bool isLastPointChecked = true;
int lastFramePoint = 0;
int userPoints = 0;
const int SPEED = 7;
const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 480;
const int SIZE_OF_USER = 20;
const int SIZE_OF_POINT = 10;

void refreshPoints() {
	sf::Font font;
	font.loadFromFile("arial.ttf");
	counter.setString("LOL");
	counter.setPosition(1/2 * WINDOW_WIDTH - 10, 1 / 2 * WINDOW_HEIGHT - 10);
	counter.setCharacterSize(32);
	counter.setFillColor(sf::Color::White);
	counter.setStyle(sf::Text::Bold);
}

void generateRandomPoint() {
	if (!isLastPointChecked && frame - lastFramePoint <= 120) {
		return;
	}
	sf::Texture texture;
	texture.loadFromFile("point.png");
	randomPoint.setTexture(texture);
	randomPoint.setColor(sf::Color::Red);
	int x = rand() % WINDOW_WIDTH - 10;
	int y = rand() % WINDOW_HEIGHT - 10;
	randomPoint.setPosition(x, y);
	lastFramePoint = frame;
	isLastPointChecked = false;
}

void randomMove() {
	int x, y;
	if (rand()%2 == 1)
		x = rand() % 5;
	else 
		x = -(rand() % 5);
	if (rand() % 2 == 1)
		y = rand() % 5;
	else
		y = -(rand() % 5);
	randomPoint.move(x, y);
}

bool isUserTakedPoint() {
	if ((abs(user.getPosition().x - randomPoint.getPosition().x) <= SIZE_OF_POINT) && abs(user.getPosition().y - randomPoint.getPosition().y) <= SIZE_OF_POINT) {
		isLastPointChecked = true;
		userPoints++;
		return true;
	}
	return false;
}

void declareUser() {
	if (isFirst) {
		isFirst = false;
		sf::Texture texture;
		texture.loadFromFile("user.png");
		user.setTexture(texture);
	}
	return;
}

void mainGame(sf::RenderWindow &window, sf::Event &event) {
	generateRandomPoint();
	randomMove();
	declareUser();
	refreshPoints();
	window.clear();
	window.draw(randomPoint);
	window.draw(user);
	window.draw(counter);
	window.display();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (user.getPosition().y - SPEED >= 0)
			user.move(0, -SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (user.getPosition().y + SIZE_OF_USER + SPEED <= WINDOW_HEIGHT)
			user.move(0, SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (user.getPosition().x + SIZE_OF_USER + SPEED <= WINDOW_WIDTH)
			user.move(SPEED, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (user.getPosition().x - SPEED >= 0)
		user.move(-SPEED, 0);
	}

	if (isUserTakedPoint()) {

	}
};

void startGame(sf::RenderWindow &window) {
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("logo_1.png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, opacity -= 3));

	window.clear();
	window.draw(sprite);
	window.display();
}

void mainMenu(sf::RenderWindow &window) {
	if (game) {
		return;
	}
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("mainMenu.png");
	sprite.setTexture(texture);
	if (opacity < 255) {
		sprite.setColor(sf::Color(255, 255, 255, opacity += 3));
	}

	window.clear();
	window.draw(sprite);
	window.display();
}

int main() {
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gierka :)");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
				game = true;
				mainGame(window, event);
			}
		}

		if (frame >= 0 && frame < 85) {
			startGame(window);
		}
		else if (!game){
			mainMenu(window);
		}
		else {
			mainGame(window, event);
		}

		frame++;
	}

	return 0;
}