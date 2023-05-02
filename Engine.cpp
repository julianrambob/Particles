#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Particles", Style::Fullscreen);

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

		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::update(float dtAsSeconds)
{
	for(vector<Particle>::iterator i = m_particles.begin(); i != m_particles.end();)
	{
		Particle p = *i;
		if (p.getTTL() > 0.0)
		{
			p.update(dtAsSeconds);
			i++;
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
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();

}