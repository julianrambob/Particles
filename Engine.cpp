#include "Engine.h"

Engine::Engine()
{
	//m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Particles", Style::Fullscreen);
	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Particles", Style::Default);


}

void Engine::run()
{
	// Timing 	
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;


	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		double dtAsSeconds = dt.asSeconds();
		//cout << dtAsSeconds << endl;

		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while(m_Window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			m_Window.close();
		if (event.mouseButton.button == Mouse::Left)
		{
			for (int i = 0; i < 5; i++)
			{
				Vector2i click = Mouse::getPosition(m_Window);
				int numPoints = rand() % 26 + 25;
				Particle p(m_Window, numPoints, click);
				m_particles.push_back(p);
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	int count = 1;
	for(vector<Particle>::iterator i = m_particles.begin(); i != m_particles.end();)
	{
		//Particle p = *i;
		if (i -> getTTL() > 0.0)
		{
			//cout << "Particle " << count << ":" << endl;
			count++;
			i -> update(dtAsSeconds);
			++i;
			//cout << endl;
		}
		else
		{
			i = m_particles.erase(i);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		//cout << "draw" << endl;
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();

}