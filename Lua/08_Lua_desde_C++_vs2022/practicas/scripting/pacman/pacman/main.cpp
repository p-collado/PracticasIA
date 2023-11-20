#include <pacman_include.hpp>

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

int num_coins = 0;
const int platas_para_oro = 5;
const int bronces_para_plata = 100;
unsigned int scorepercoin = 50;
const float max_vida = 1.5f;
float vida = max_vida;
lua_State* L = luaL_newstate();

bool pacmanEatenCallback(int& score, bool& muerto)
{ // Pacman ha sido comido por un fantasma
	vida -= 0.5f;
	muerto = vida < 0.0f;

	return true;
}

bool coinEatenCallback(int& score)
{ // Pacman se ha comido una moneda
	++num_coins;
	score = num_coins * scorepercoin;

	return true;
}

bool frameCallback(float time)
{ // Se llama periodicamente cada frame
	return false;
}

bool ghostEatenCallback(int& score)
{ // Pacman se ha comido un fantasma
	return false;
}

bool powerUpEatenCallback(int& score)
{ // Pacman se ha comido un powerUp
	setPacmanSpeedMultiplier(2.0f);
	setPacmanColor(0, 255, 0);
	setPowerUpTime(5);

	score += 5000;

	return true;
}

bool powerUpGone()
{ // El powerUp se ha acabado
	setPacmanColor(255, 0, 0);
	setPacmanSpeedMultiplier(1.0f);
	return true;
}

bool pacmanRestarted(int& score)
{
	score = 0;
	num_coins = 0;
	vida = max_vida;

	return true;
}

bool computeMedals(int& oro, int& plata, int& bronce, int score)
{
	plata = score / bronces_para_plata;
	bronce = score % bronces_para_plata;
	
	oro = plata / platas_para_oro;
	plata = plata % platas_para_oro;

	return true;
}

bool getLives(float& vidas)
{
	vidas = vida;
	return true;
}

bool setImmuneCallback()
{
    return true;
}

bool removeImmuneCallback()
{
    return true;
}

bool InitGame()
{

	luaL_openlibs(L);
	int error = luaL_loadfile(L, "pacman.lua");
	if (error)
	{

	}

	lua_pcall(L, 0, 0, 0);
    return true;
}

bool EndGame()
{
	lua_close(L);
    return true;
}