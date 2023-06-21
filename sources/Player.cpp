#include "../headers/Player.h"

Player::Player()
{
    // �摜�E�t�H���g�n���h��
    background_handle = LoadGraph("images/Back_Cyber_1920.jpg");
    index_font = CreateFontToHandle("�j�R�p", 25, 1, DX_FONTTYPE_ANTIALIASING);
    figure_font = CreateFontToHandle("�j�R�p", 40, 1, DX_FONTTYPE_ANTIALIASING);

    // �e��T�E���h
    sound.add("move",    "sounds/�J�[�\���ړ�2.mp3");
    sound.add("rotate",  "sounds/����A�{�^������35.mp3");
    sound.add("hold",    "sounds/����A�{�^������40.mp3");
    sound.add("drop",    "sounds/�J�[�\���ړ�7.mp3");
    sound.add("levelup", "sounds/������ ���ʉ� �����|�C���g11.mp3");

    sound.changeAllSoundVolume(70);
    sound.changeVolume("rotate", 60);

    // ���W
    x = 380, y = 50;
    gnrt_mx = FIELD_SIDE_X / 2, gnrt_my = 4;
    pre_mino_coordx = gnrt_mx;
    pre_mino_coordy = gnrt_my;

    // �X�R�A�E��Փx
    level = 1;
    score = 0;
    ren_num = 0;
    drop_speed = 60;

    // �I�[�g���s�[�g
    t = -1;
    lockdown_count = 0;
    autorepeat_count = 0;
    isautorepeat = false;

    // mino����
    new_gnrt_mino = 0;
    isbottom = false;
    can_generate = false;
    can_transcribe = false;
    can_incrrow = false;

    // ���C���폜
    erase_linenum = 0;
    sum_linenum = 0;
    levelup_count = 0;

    // �z�[���h
    hold_mino_num = -1;
    hold_enable = true;

    field = new Field(x, y - BLOCK_SIZE * 5);
    mino = new Mino(field);
    ghost_mino = new Mino(field);
    hold_mino = new StaticMino(x - STATIC_BLOCK_SIZE * 4, y + STATIC_BLOCK_SIZE * 1.5 + 10);

    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        next_mino[i] = new StaticMino(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + i * STATIC_BLOCK_SIZE * 2.8 + 35);
    }
}

Player::Player(int x, int y)
{

    // �摜�E�t�H���g�n���h��
    background_handle = LoadGraph("images/Back_Cyber_1920.jpg");
    index_font = CreateFontToHandle("�j�R�p", 25, 1, DX_FONTTYPE_ANTIALIASING);
    figure_font = CreateFontToHandle("�j�R�p", 40, 1, DX_FONTTYPE_ANTIALIASING);

    // �e��T�E���h
    sound.add("move", "sounds/�J�[�\���ړ�2.mp3");
    sound.add("rotate", "sounds/����A�{�^������35.mp3");
    sound.add("hold", "sounds/����A�{�^������40.mp3");
    sound.add("drop", "sounds/�J�[�\���ړ�7.mp3");
    sound.add("levelup", "sounds/������ ���ʉ� �����|�C���g11.mp3");

    sound.changeAllSoundVolume(70);
    sound.changeVolume("rotate", 60);

    // ���W
    this->x = x, this->y = y;
    gnrt_mx = FIELD_SIDE_X / 2, gnrt_my = 4;
    pre_mino_coordx = gnrt_mx;
    pre_mino_coordy = gnrt_my;

    // �X�R�A�E��Փx
    level = 1;
    score = 0;
    ren_num = 0;
    drop_speed = 60;

    // �I�[�g���s�[�g
    t = -1;
    lockdown_count = 0;
    autorepeat_count = 0;
    isautorepeat = false;

    // mino����
    new_gnrt_mino = 0;
    isbottom = false;
    can_generate = false;
    can_transcribe = false;
    can_incrrow = false;

    // ���C���폜
    erase_linenum = 0;
    sum_linenum = 0;
    levelup_count = 0;

    // �z�[���h
    hold_mino_num = -1;
    hold_enable = true;

    field = new Field(x, y - BLOCK_SIZE * 5);
    mino = new Mino(field);
    ghost_mino = new Mino(field);
    hold_mino = new StaticMino(x - STATIC_BLOCK_SIZE * 4, y + STATIC_BLOCK_SIZE * 1.5 + 10);

    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        next_mino[i] = new StaticMino(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + i * STATIC_BLOCK_SIZE * 2.8 + 35);
    }
}

void Player::initialize()
{
    // ��v�N���X
    mino->initialize();
    field->InitField();
    row.initialize();
    ghost_mino->initialize();
    hold_mino->initialize();

    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        next_mino[i]->initialize();
    }

    // ��Փx
    level = 1;
    score = 0;
    ren_num = 0;
    drop_speed = 60;

    // �I�[�g���s�[�g
    t = -1;
    lockdown_count = 0;
    autorepeat_count = 0;
    isautorepeat = false;

    // mino����
    new_gnrt_mino = 0;
    isbottom = false;
    can_generate = false;
    can_transcribe = false;
    can_incrrow = false;

    // ���C������
    erase_linenum = 0;
    sum_linenum = 0;
    levelup_count = 0;

    // �z�[���h
    hold_mino_num = -1;
    hold_enable = true;
}

void Player::startProcess()
{
    mino->generateMinoWithPos(row.getMinoNum(0), gnrt_mx, gnrt_my);
    row.increase();
}

void Player::update()
{
    installMino();
    controlMino();
    dropMino();
    holdMino();
    makeGhost();
    setNext();
    t++;
}

void Player::controlMino()
{
    //���E�ړ�����
    //PAD PAD_LEFT
    if (Key[KEY_INPUT_A] >= 1) {
        if (mino->getMinoCoordX() != pre_mino_coordx && mino->getMinoCoordY() != pre_mino_coordy)
            lockdown_count = 0;

        if (autorepeat_count == 0) {
            if (!mino->collisionField(-1, 0)) {
                mino->moveMino(-1, 0);
                sound.play("move", DX_PLAYTYPE_BACK);
            }
            autorepeat_count++;
        }
        else if (isautorepeat && t % 3 == 0) {
            if (!mino->collisionField(-1, 0)) {
                mino->moveMino(-1, 0);
                sound.play("move", DX_PLAYTYPE_BACK);
            }
        }
        else if (autorepeat_count == 9) {
            isautorepeat = true;
        }
        else {
            autorepeat_count++;
        }
    }
    //PAD PAD_RIGHT
    if (Key[KEY_INPUT_D] >= 1) {
        if(mino->getMinoCoordX() != pre_mino_coordx && mino->getMinoCoordY() != pre_mino_coordy)
            lockdown_count = 0;

        if (autorepeat_count == 0) {
            if (!mino->collisionField(1, 0)) {
                mino->moveMino(1, 0);
                sound.play("move", DX_PLAYTYPE_BACK);
            }
            autorepeat_count++;
        }
        else if (isautorepeat && t % 3 == 0) {
            if (!mino->collisionField(1, 0)) {
                mino->moveMino(1, 0);
                sound.play("move", DX_PLAYTYPE_BACK);
            }
        }
        else if (autorepeat_count == 9) {
            isautorepeat = true;
        }
        else {
            autorepeat_count++;
        }
    }

    //��]����iSRS�t���j
    //PAD PAD_4
    if (Key[KEY_INPUT_L] == 1)
    {
        mino->rotateMinoWithCollision(true);
        sound.play("rotate", DX_PLAYTYPE_BACK);
        lockdown_count = 0;
    }
    //PAD PAD_3
    if (Key[KEY_INPUT_K] == 1)
    {
        mino->rotateMinoWithCollision(false);
        sound.play("rotate", DX_PLAYTYPE_BACK);
        lockdown_count = 0;
    }

    if (!CheckHitKeyAll(DX_CHECKINPUT_KEY)) {
        autorepeat_count = 0;
        isautorepeat = false;
    }
}

void Player::dropMino()
{
    //PAD PAD_UP
    if (Key[KEY_INPUT_W] == 1) {    //�n�[�h�h���b�v

        mino->dropToMaxBottom();
        new_gnrt_mino = row.getMinoNum(0);
        can_generate = true;
        can_transcribe = true;
        can_incrrow = true;
        hold_enable = true;
    }//PAD PAD_DOWN
    else if (Key[KEY_INPUT_S] >= 1 && t % 3 == 0) {   //�\�t�g�h���b�v
        if (!mino->collisionField(0, 1)) {
            mino->moveMino(0, 1);
            sound.play("move", DX_PLAYTYPE_BACK);
        }
        else {
            isbottom = true;
        }
    }
    else if (t % drop_speed == 0) {      //�i�`�������h���b�v
        if (!mino->collisionField(0, 1)) {
            mino->moveMino(0, 1);
            isbottom = false;
        }
        else {
            isbottom = true;
            pre_mino_coordx = mino->getMinoCoordX();
            pre_mino_coordy = mino->getMinoCoordY();
        }
    }
    
    if (isbottom) {
        if (lockdown_count == 30) {
            new_gnrt_mino = row.getMinoNum(0);
            can_generate = true;
            can_transcribe = true;
            can_incrrow = true;
            hold_enable = true;

            lockdown_count = 0;

            isbottom = false;
        }
        else if (!mino->collisionField(0, 1)) {
            can_generate = false;
            can_transcribe = false;
            can_incrrow = false;

            lockdown_count = 0;

            isbottom = false;
        }
        else {
            lockdown_count++;
        }
    }
}

void Player::holdMino()
{
    //PAD Key[PAD_5] == 1 || Key[PAD_7] == 1
    if (Key[KEY_INPUT_SPACE] && hold_enable) {
        sound.play("hold", DX_PLAYTYPE_BACK);
        if (hold_mino_num == -1) {
            hold_mino_num = mino->getMinoNum();
            hold_mino->generateMino(hold_mino_num);

            new_gnrt_mino = row.getMinoNum(0);
            can_generate = true;
            can_transcribe = false;
            can_incrrow = true;
        }
        else {
            int tmp_mino_num = hold_mino_num;
            hold_mino_num = mino->getMinoNum();
            hold_mino->generateMino(hold_mino_num);

            new_gnrt_mino = tmp_mino_num;
            can_generate = true;
            can_transcribe = false;
            can_incrrow = false;
        }
        hold_enable = false;
    }
}

void Player::makeGhost()
{
    *ghost_mino = *mino;
    ghost_mino->dropToMaxBottom();
}

void Player::setNext()
{
    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        next_mino[i]->generateMino(row.getMinoNum(i));
    }
}

int Player::calcScore(int _level, int _drop_speed)
{
    int _score = 0;

    int tmp_erase_linenum = erase_linenum;
    erase_linenum = field->LineEraseAndShift();

    if (tmp_erase_linenum != 0 && erase_linenum != 0)
        ren_num++;

    int drop_score = (20 * _drop_speed / 60 - t / 60);
    int line_score = _level * 100 * erase_linenum;

    _score = (drop_score + line_score) * (ren_num + 1);
    
    return _score;
}

void Player::levelControl()
{
    int tmp_level = level;
    sum_linenum += erase_linenum;
    level = sum_linenum / 10 + 1;
    if (level != tmp_level) {
        sound.play("levelup", DX_PLAYTYPE_BACK);
        if (drop_speed != 1) {
            drop_speed /= 1.5;
        }
    }
}

void Player::installMino()
{
    if (can_generate){
        if (can_transcribe) {
            sound.play("drop", DX_PLAYTYPE_BACK);
            mino->transcribeMinoToField();
        }

        mino->generateMinoWithPos(new_gnrt_mino, gnrt_mx, gnrt_my);

        if(can_incrrow)row.increase();

        score += calcScore(level, drop_speed);

        levelControl();
        erase_linenum = 0;

        can_generate = false;
        can_transcribe = false;
        can_incrrow = false;
        t = 0;
    }
}

int Player::judgeGameResult()
{
    if (field->containMino(gnrt_mx, gnrt_my) || field->containMino(gnrt_mx + 1, gnrt_my)) {
        return -1;
    }
    else if (sum_linenum >= max_linenum) {
        return 1;
    }

    return 0;
}

void Player::draw()
{
    DrawGraph(0, 0, background_handle, TRUE);
    int drx = x - STATIC_BLOCK_SIZE * 5, dry = y;
    DrawRoundRect(drx, dry, drx + STATIC_BLOCK_SIZE * 5 + 10, dry + STATIC_BLOCK_SIZE * 4 + 10, 10, 10, GetColor(0, 0, 0), TRUE);
    drx = x + FIELD_SIDE_X * BLOCK_SIZE + 50, dry = y;
    DrawRoundRect(drx, dry, drx + STATIC_BLOCK_SIZE * 5 + 10, dry + STATIC_BLOCK_SIZE * 6 * 3, 10, 10, GetColor(0, 0, 0), TRUE);

    field->drawField();
    ghost_mino->draw(false);
    mino->draw(true);
    if(hold_enable)
        hold_mino->draw(true);
    else 
        hold_mino->draw(true, 100);
    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        next_mino[i]->draw(true);
    }

    DrawStringToHandle(x - STATIC_BLOCK_SIZE * 5 + 5, y + 5, "HOLD", GetColor(255, 255, 255), index_font);
    DrawStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 50 + 5, y + 5, "NEXT", GetColor(255, 255, 255), index_font);
    DrawStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 50, y + STATIC_BLOCK_SIZE * 6 * 3, "SCORE", GetColor(255, 255, 255), index_font);
    DrawFormatStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + STATIC_BLOCK_SIZE * 6 * 3 + 20, GetColor(255, 255, 255), figure_font, "%d", score);
    DrawStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 50, y + STATIC_BLOCK_SIZE * 6 * 3 + 60, "HIGH SCORE", GetColor(255, 255, 255), index_font);
    //DrawFormatStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + STATIC_BLOCK_SIZE * 6 * 3 + 80, GetColor(255, 255, 255), figure_font, "%d", highscore);
    DrawStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 50, y + STATIC_BLOCK_SIZE * 6 * 3 + 120, "LEVEL", GetColor(255, 255, 255), index_font);
    DrawFormatStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + STATIC_BLOCK_SIZE * 6 * 3 + 140, GetColor(255, 255, 255), figure_font, "%d", level);
    DrawStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 50, y + STATIC_BLOCK_SIZE * 6 * 3 + 180, "LINES", GetColor(255, 255, 255), index_font);
    DrawFormatStringToHandle(x + FIELD_SIDE_X * BLOCK_SIZE + 70, y + STATIC_BLOCK_SIZE * 6 * 3 + 200, GetColor(255, 255, 255), figure_font, "%d", sum_linenum);
}

void Player::finalize()
{
    delete(mino);
    delete(field);
    delete(ghost_mino);
    delete(hold_mino);

    InitFontToHandle();
    sound.finalize();

    for (int i = 0; i < NEXT_REFER_SIZE; i++) {
        delete(next_mino[i]);
    }
}
