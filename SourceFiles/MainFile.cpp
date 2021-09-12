#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>


const int NUMBEROFSAMPLES = 10000;
const int NOS = 10000;
const int RATE = 24100 / 26;
std::unique_ptr<std::vector<sf::Int16>> pointertovector{ std::make_unique <std::vector<sf::Int16>>() };
std::unique_ptr<std::vector<double>> pointertodouble{ std::make_unique <std::vector<double>>() };
std::vector<sf::Int16>* values{};
sf::Int16* valuevector{ new sf::Int16[100000]{} };
sf::SoundBuffer* Buffer{ new sf::SoundBuffer };
sf::Sound* SOUND{ new sf::Sound };
sf::Sound* SOUND2{ new sf::Sound };
double* increment{ new double{static_cast<double>(NOS / 5000)} };

void buildwindow() {
	for (size_t* i{ new size_t{1} }; *i < NOS; *i = *i + 1) {
		// DrawLine(*increment, valuevector[static_cast<sf::Int16>(*i - 1)] / 100 + 250, *increment + static_cast<double>(NOS / 5000), valuevector[static_cast<sf::Int16>(*i)] / 100 + 250, BLACK);
		*increment += static_cast<double>(NOS / 5000);
	}
}

void pushbackvalues(std::vector<sf::Int16>* vals) {
	for (size_t* i{ new size_t{0} }; *i < NUMBEROFSAMPLES; *i = *i + 1) {
		sf::Int16* val{ new sf::Int16{static_cast<sf::Int16>(sin(*i))} };
		vals->push_back(*val);
		//call();
	}
	return;
}
void printvalues(std::vector<sf::Int16>* vals) {
	std::cout << vals->size() << std::endl;
	for (size_t* i{ new size_t{0} }; *i < vals->size(); *i = *i + 1) {
		std::cout << (*vals).at(*i) << " ";
	}
}
void showresults() {
	std::cout << "______MATTHEW'S SYNTH VERSION 1.0 -> SINUSOIDAL APPROACH______\n" << std::endl;
	std::cout << "THIS IS A SINUSOIDAL SYNTH SIMULATOR BUILT BY MATT. USE IT WITH CAUTION. THE SAMPLE RATE VARIES BETWEEN"
		<< " 44100 AND 20000 SAMPES / SECOND DEPENDING ON THE ALPHABET LETTER YOU'RE PRESSING." <<
		"\n\nHAVE FUN!\n\n";
}
void buildvec() {
	double* valueforsin{ new double{0} };
	for (size_t* i{ new size_t{0} }; *i < NOS; *i = *i + 1) {
		valuevector[static_cast<sf::Int16>(*i)] = static_cast<sf::Int16>(sin(*valueforsin) * 10000);
		if (valuevector[static_cast<sf::Int16>(*i)] > 0) {
			valuevector[static_cast<sf::Int16>(*i)] = 10000;
		}
		else {
			valuevector[static_cast<sf::Int16>(*i)] = -10000;
		}
		*valueforsin += 0.075;
	}
}
void keypressedL() {
	for (;;) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			Buffer->loadFromSamples(valuevector, NOS / 5, 1, 44100);
			SOUND->setBuffer(*Buffer);
			SOUND->play();
		}
	}
}
void keypressedA() {
	for (;;) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			Buffer->loadFromSamples(valuevector, NOS / 5, 1, 20000 + sf::Keyboard::L);
			SOUND2->setBuffer(*Buffer);
			SOUND2->play();
		}
	}
}
void DrawFunction(sf::RenderWindow* wind) {
	*increment = 0;
	for (size_t* i{ new size_t{1} }; *i < NOS; *i = *i + 1) {
		sf::VertexArray line(sf::LinesStrip, 2);
		if (*increment < 500 && *increment + static_cast<double>(NOS / 5000) < 500) {
			line[0].position = sf::Vector2f(*increment, valuevector[static_cast<sf::Int16>(*i - 1)] / 100 + 250);
			line[1].position = sf::Vector2f(*increment + static_cast<double>(NOS / 5000), valuevector[static_cast<sf::Int16>(*i)] / 100 + 250);
		}

		*increment += static_cast<double>(NOS / 5000);
		wind->draw(line);
	}
}


void InitSFMLWindow() {
	sf::RenderWindow Wind{ sf::VideoMode(500, 500),"SineWaveRepresentation" };

	while (Wind.isOpen()) {
		sf::Event Event;
		while (Wind.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed) {
				Wind.close();
			}
		}
		Wind.clear(sf::Color::Blue);
		DrawFunction(&Wind);
		Wind.display();
	}
}

int main(void)
{
	showresults();
	buildvec();

	sf::Thread* MyThreadWindow = new sf::Thread(InitSFMLWindow);
	MyThreadWindow->launch();

	if (!Buffer->loadFromSamples(valuevector, NOS, 1, 44100)) {
		std::cout << "ERROR!";
	}
	else {
		for (;;) {
			for (size_t* i{ new size_t{0} }; *i < 26; *i = *i + 1) {
				if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(*i))) {
					Buffer->loadFromSamples(valuevector, NOS, 1, 20000 + *i * RATE);
					SOUND->setBuffer(*Buffer);
					SOUND->play();
				}
			}

		}
	}
	std::cin.get();
	// return 0;
}

