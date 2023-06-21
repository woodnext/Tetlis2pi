#pragma once
#include "include.h"
#include "Mino.h"
#include "StaticMino.h"
#include "MinoRow.h"
#include "Field.h"
#include "Sound.h"

typedef enum {
	ePause_Continue,	//������
	ePause_Restart,		//���Ȃ���
	ePause_End,			//�X�^�[�g�ɖ߂�
	ePause_Num,			//�{���ڂ̐�
} ePause;

typedef enum {
	eResult_Restart,	//���Ȃ���
	eResult_End,		//�X�^�[�g�ɖ߂�
	eResult_Num,			//�{���ڂ̐�
} eResult;

class Player
{
private:
	Field* field;
	Mino* mino;
	Mino* ghost_mino;
	StaticMino* hold_mino;
	StaticMino* next_mino[NEXT_REFER_SIZE];

	MinoRow row;

	// �摜�E�t�H���g�n���h��
	int background_handle;
	int index_font;
	int figure_font;

	// �����Ǘ�
	Sound sound;

	// ���W
	int x, y;
	int gnrt_mx, gnrt_my;
	int pre_mino_coordx;
	int pre_mino_coordy;

	// �X�R�A
	int level;
	int score;
	int ren_num;
	int drop_speed;
	const int max_linenum = 100;

	// �I�[�g���s�[�g
	int t;
	int lockdown_count;
	int autorepeat_count;
	bool isautorepeat;

	// mino�����t���O
	int new_gnrt_mino;
	bool isbottom;
	bool can_generate;
	bool can_transcribe;
	bool can_incrrow;

	// ���C���폜
	int erase_linenum;
	int levelup_count;
	int sum_linenum;

	// �z�[���h
	int hold_mino_num;
	bool hold_enable;

	// private�֐�
	void controlMino();
	void dropMino();
	void holdMino();
	void makeGhost();
	void setNext();
	void levelControl();
	void installMino();
public:
	Player();
	Player(int x, int y);

	void initialize();
	void update();
	void draw();
	void finalize();

	void startProcess();
	int judgeGameResult();
	int calcScore(int _level, int _drop_speed);

};