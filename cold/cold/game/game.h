#ifndef _COLD_GAME_GAME_H
#define _COLD_GAME_GAME_H

namespace cold {
class Application;
namespace game {

class Game {
public:
	Game(Application& app) : application(app) { }

	// Start and continue running the game
	// Blocks the current thread while the game is playing
	void run();

protected:
	Application& application;
	float time;

private:
	virtual void initialize() { };
	virtual void update(float elapsed) { };
	virtual void draw() { };
	virtual void uninitialize() { };
};

} }

#endif