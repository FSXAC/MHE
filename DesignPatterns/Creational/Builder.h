#pragma once

class GameConfigurationBuilder
{

public:
	GameConfigurationBuilder(int playerId) { this->playerId = playerId; }

	void setFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }
	void setOnline(bool online) { this->online = online; }
	void setDebug(bool debug) { this->debug = debug; }

	GameConfiguration* build()
	{
		return new GameConfiguration(this);
	}

public:
	int playerId = 0;
	bool fullscreen = false;
	bool online = false;
	bool debug = false;
};

class GameConfiguration
{
public:

	/* We don't want the following anti pattern because the list of parameters are long */
	// GameConfiguration(
	// 	int playerId = 0,
	// 	bool fullscreen = false,
	// 	bool online = true,
	// 	bool debug = false,
	// 	// ...
	// );

	/* So a builder encapsulates that */
	GameConfiguration(GameConfigurationBuilder* config)
	{
		m_playerId = config->playerId;
		m_fullscreen = config->fullscreen;
		m_online = config->online;
		m_debug = config->debug;
	}

private:
	int m_playerId = 0;
	bool m_fullscreen = false;
	bool m_online = false;
	bool m_debug = false;
};

// how it can be used ???
namespace builder
{
	void example()
	{
		auto builder = new GameConfigurationBuilder(100);
		builder->setFullscreen(true);
		builder->setOnline(true);

		GameConfiguration* gameConfig = builder->build();
	}
}