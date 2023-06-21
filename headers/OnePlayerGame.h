#pragma once
#include "include.h"
#include "Player.h"
#include "MinoRow.h"
#include "BaseScene.h"
#include <time.h> 
#include <iostream>
#include <fstream>
#include <string>

class OnePlayerGame : public BaseScene
{
private:
	Player* player;
	Sound sound;
	// �J�E���g�_�E���֘A	
	bool is_count;
	bool is_gamestart;
	int count;
	int count_font;
	int t;

	// �|�[�Y��ʊ֘A
	bool is_pause;
	int now_select;
	int pause_y;
	int pause_font;

	// ���U���g�֘A	
	bool is_gameover;
	bool is_gameclear;
	const int GAMECLEAR = 1;
	const int GAMEOVER = -1;

	// �X�R�A�֘A
	int highscore = 0;

public:
	OnePlayerGame(ISceneChanger* changer);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

	void countDown();
	void countDownDraw();
	void pause();
	void pauseDraw();
	void gameResultScene();
	void gameResultDraw(int);
};

