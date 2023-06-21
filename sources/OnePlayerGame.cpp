#include "..\headers\OnePlayerGame.h"

OnePlayerGame::OnePlayerGame(ISceneChanger* changer) : BaseScene(changer)
{
	player = new Player();
    sound.add("select", "sounds/�J�[�\���ړ�2.mp3");
    sound.add("dicision", "sounds/����A�{�^������26.mp3");
    sound.changeAllSoundVolume(70);
    sound.add("count", "sounds/Countdown06-1.mp3");
    sound.add("pause", "sounds/�x����1.mp3");
    sound.add("bgm", "sounds/tetlis2pi.mp3");

    // �J�E���g�_�E���֘A	
    is_count = true;
    is_gamestart = true;
    count = 3;
    count_font = CreateFontToHandle("�j�R�p", 75, 1, DX_FONTTYPE_ANTIALIASING);
    t = 0;

    // �|�[�Y�֘A
	is_pause = false;
	now_select = ePause_Continue;
	pause_y = 0;
    pause_font = CreateFontToHandle("�j�R�p", 40, 1, DX_FONTTYPE_ANTIALIASING);

    // �Q�[�����U���g�֘A
    is_gameover = false;
    is_gameclear = false;

    /*std::ifstream file("savedatas/one_player.txt");
    std::string data;
    std::getline(file, data);

    highscore = stoi(data);*/
}

void OnePlayerGame::Initialize()
{
	player->initialize();

    // �J�E���g�_�E���֘A
    is_count = true;
    is_gamestart = true;
    count = 3;
    t = 0;

    // �|�[�Y�֘A
    is_pause = false;
    now_select = ePause_Continue;
    pause_y = 0;

    // �Q�[�����U���g�֘A
    is_gameover = false;
    is_gameclear = false;
}

void OnePlayerGame::Update()
{
    if (Key[KEY_INPUT_ESCAPE] == 1 && !is_count) {
        sound.play("pause", DX_PLAYTYPE_BACK);
        is_count = false;
        is_pause = true;
    }

    int game_result = player->judgeGameResult();

    if (is_count) countDown();
    else if (is_pause) pause();
    else if (game_result != 0) gameResultScene();
	else player->update();
}

void OnePlayerGame::Draw()
{
    int game_result = player->judgeGameResult();

    player->draw();

    if (is_count) countDownDraw();
    else if (is_pause) pauseDraw();
    else if (game_result) gameResultDraw(game_result);
}

void OnePlayerGame::Finalize()
{
	player->finalize();
}

void OnePlayerGame::countDown()
{
    if (t % 45 == 0) {
        //sound.play("count", DX_PLAYTYPE_BACK);
        count--;
    }
    if (count < 0) {
        is_count = false;
        count = 3;
        t = 0;
        sound.play("bgm", DX_PLAYTYPE_LOOP);

        if (is_gamestart) {
            player->startProcess();
        }
        is_gamestart = false;
    }
    t++;
}

void OnePlayerGame::countDownDraw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, WINDOW_SIZE_X - 1, WINDOW_SIZE_Y - 1, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
    if (count > 0) {
        DrawFormatStringToHandle(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 - 50, GetColor(255, 255, 255), count_font, "%d", count);
    }
    else DrawStringToHandle(WINDOW_SIZE_X / 2 - 100, WINDOW_SIZE_Y / 2 - 50, "START", GetColor(255, 255, 255), count_font);
}

void OnePlayerGame::pause()
{
    if (Key[KEY_INPUT_S] == 1) {                 //���L�[��������Ă�����
        sound.play("select", DX_PLAYTYPE_BACK);
        now_select = (now_select + 1) % ePause_Num;   //�I����Ԃ��������
    }
    if (Key[KEY_INPUT_W] == 1) {//��L�[��������Ă�����
        sound.play("select", DX_PLAYTYPE_BACK);
        now_select = (now_select + (ePause_Num - 1)) % ePause_Num;    //�I����Ԃ���グ��
    }
    if (Key[KEY_INPUT_SPACE] == 1) {    //�G���^�[�L�[�������ꂽ��
        sound.play("dicision", DX_PLAYTYPE_BACK);
        switch (now_select) { //���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case ePause_Continue:
            is_count = true;
            is_pause = false;
            break;
        case ePause_Restart:
            Initialize();
            player->initialize();
            break;
        case ePause_End://�ݒ�I�𒆂Ȃ�
            mSceneChanger->ChangeScene(eScene_Menu);
            break;
        }
    }
}

void OnePlayerGame::pauseDraw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, WINDOW_SIZE_X - 1, WINDOW_SIZE_Y - 1, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t

    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, 300, "�Â���", GetColor(255, 255, 255), pause_font);
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, 300+70, "���Ȃ���", GetColor(255, 255, 255), pause_font);
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, 300+70*2, "��߂�", GetColor(255, 255, 255), pause_font);

    switch (now_select) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case ePause_Continue://�R���e�B�j���[�I��
        sound.stop("bgm");
        pause_y = 300;   
        break;
    case ePause_Restart://���X�^�[�g�I��
        pause_y = 300 + 70; 
        break;
    case ePause_End://�G���h�I�𒆂Ȃ�
        pause_y = 300 + 70*2;
        break;
    }
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 100, pause_y, "��", GetColor(255, 255, 255), pause_font);
}

void OnePlayerGame::gameResultScene()
{
    sound.stop("bgm");
    sound.play("menuBGM", DX_PLAYTYPE_BACK);
    if (Key[KEY_INPUT_S] == 1) {                 //���L�[��������Ă�����
        sound.play("select", DX_PLAYTYPE_BACK);
        now_select = (now_select + 1) % eResult_Num;   //�I����Ԃ��������
    }
    if (Key[KEY_INPUT_W] == 1) {//��L�[��������Ă�����
        sound.play("select", DX_PLAYTYPE_BACK);
        now_select = (now_select + (eResult_Num - 1)) % eResult_Num;    //�I����Ԃ���グ��
    }
    if (Key[KEY_INPUT_SPACE] == 1) {    //�G���^�[�L�[�������ꂽ��
        sound.play("dicision", DX_PLAYTYPE_BACK);
        switch (now_select) {
        case eResult_Restart:
            Initialize();
            player->initialize();
            break;
        case eResult_End:
            mSceneChanger->ChangeScene(eScene_Menu);
            break;
        }
    }
}

void OnePlayerGame::gameResultDraw(int game_result)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(0, 0, WINDOW_SIZE_X - 1, WINDOW_SIZE_Y - 1, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t

    if (game_result == 1) {
        

        //if (score > highscore) {

        //    if (fopen_s(&fp, "savedates/highscore_normal.txt", "w") != NULL) {
        //        //�t�@�C���I�[�v�����s
        //    }
        //    else {
        //        fprintf(fp, "%d", score);
        //        fclose(fp);
        //    }
        //    DrawStringToHandle(WINDOW_SIZE_X / 2 - 100, 180, "HIGH SCORE", GetColor(255, 255, 255), pause_font);
        //}
        DrawStringToHandle(WINDOW_SIZE_X / 2 - 200, 100, "GAME CLEAR", GetColor(255, 255, 255), count_font);
    }
    else if(game_result == -1) {
        DrawStringToHandle(WINDOW_SIZE_X / 2 - 200, 100, "GAME OVER", GetColor(255, 255, 255), count_font);
    }

    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, 300, "���������ǗV��", GetColor(255, 255, 255), pause_font);
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, 300 + 70, "���j���[�ɖ߂�", GetColor(255, 255, 255), pause_font);

    switch (now_select) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eResult_Restart://�Q�[���I�𒆂Ȃ�
        pause_y = 300;    //�Q�[���̍��W���i�[
        break;
    case eResult_End://�ݒ�I�𒆂Ȃ�
        pause_y = 300 + 70;    //�ݒ�̍��W���i�[
        break;
    }
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 100, pause_y, "��", GetColor(255, 255, 255), pause_font);
}
