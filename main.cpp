#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <ctime>
#include <string>

constexpr double PI_ = 3.14159265358979323846;

unsigned WIN_WIDTH;
unsigned WIN_HEIGHT;

constexpr unsigned C = 10.0;
constexpr float RADIUS = 4.0f; //radius of drawn circles

const double ANGLE = PI_ * (3.0 - std::sqrt(5.0)); //The Golden angle (in radians)


struct Point {
	int x, y;
};

std::vector<Point> points; //the points to be drawn on screen

unsigned n = 1;

int main()
{
	auto full_mode = sf::VideoMode::getDesktopMode();
	WIN_HEIGHT = full_mode.height;
	WIN_WIDTH = full_mode.width;
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		sf::Event event_q;

		while (window.pollEvent(event_q)) {
			if (event_q.type == sf::Event::Closed) {
				window.close();
			}
			else if (event_q.type == sf::Event::KeyPressed) {
				sf::Texture texture;
				switch (event_q.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;

				case sf::Keyboard::C:
					texture.create(WIN_WIDTH, WIN_HEIGHT);
					texture.update(window);
					texture.copyToImage().saveToFile("s.bmp");

					break;

				default:
					break;
				}
			}
		}


		//calculate polar cordinates
		double r = C * std::sqrt(n);
		double phi = n * ANGLE;

		//convert to cartesian co-ords
		double x = r * std::cos(phi);
		double y = r * std::sin(phi);

		//from cartesian to screen_pixel co_ords
		double screen_x = (WIN_WIDTH / 2.0 - x);
		double screen_y = (WIN_HEIGHT / 2.0 - y);

		if (r < (WIN_HEIGHT / 2.0)) {
			points.push_back({ (int)screen_x, (int)screen_y });
		}

		++n;


		window.clear();

		sf::CircleShape circle(RADIUS);
		for (Point p : points) {
			circle.setOrigin(RADIUS / 2.0f, RADIUS / 2.0f);
			circle.setFillColor({ 255, 231, 0, 255 }); //gold color
			circle.setPosition(p.x, p.y);
			window.draw(circle);
		}


		window.display();
	}
}