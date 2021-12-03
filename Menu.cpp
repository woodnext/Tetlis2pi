#include "Menu.h"
#include "include.h"
#include "DxLib.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
    NowSelect = eMenu_1PGame;
}

//������
void Menu::Initialize() {
    NowSelect = eMenu_1PGame;
    menu_font = CreateFontToHandle("�j�R�p", 40, 1, DX_FONTTYPE_ANTIALIASING);

    mImageHandle = LoadGraph("Images/rogo.png");    //�摜�̃��[�h
    background_Handle = LoadGraph("Images/Menu_Back.jpg");
    selectSE = LoadSoundMem("SE/�J�[�\���ړ�2.mp3");
    decisionSE = LoadSoundMem("SE/����A�{�^������26.mp3");
    menuBGM = LoadSoundMem("Sound/������  �T�C�o�[13.mp3");
    ChangeVolumeSoundMem(255 * 80 / 100, menuBGM);
    PlaySoundMem(menuBGM, DX_PLAYTYPE_BACK);
}

//�X�V
void Menu::Update() {
    if (Key[KEY_INPUT_S] == 1) {//���L�[��������Ă�����
        PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (Key[KEY_INPUT_W] == 1) {//��L�[��������Ă�����
        PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }
    if (Key[KEY_INPUT_SPACE] == 1){//�G���^�[�L�[�������ꂽ��
        PlaySoundMem(decisionSE, DX_PLAYTYPE_BACK);
        StopSoundMem(menuBGM);
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_1PGame:    //�Q�[���I�𒆂Ȃ�
            mSceneChanger->ChangeScene(eScene_Normal);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Config:  //�ݒ�I�𒆂Ȃ�
            mSceneChanger->ChangeScene(eScene_Tetlis2pi);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Exit:    //�Q�[���I���I�𒆂Ȃ�
            DxLib_End();
            break;
        }
    }
}

//�`��
void Menu::Draw() {
    //BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawGraph(0, 0, background_Handle, TRUE);
    DrawRotaGraph(WINDOW_SIZE_X / 2, 200, 0.7, 0, mImageHandle, TRUE);
    //DrawString(200, 150, "MENU", GetColor(255, 255, 255));
    //DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, GAME_Y,   "NORMAL", GetColor(255, 255, 255), menu_font);
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, CONFIG_Y, "TETLIS 2��", GetColor(255, 255, 255), menu_font);
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 50, EXIT_Y,   "EXIT", GetColor(255, 255, 255), menu_font);
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_1PGame://�Q�[���I�𒆂Ȃ�
        y = GAME_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Config://�ݒ�I�𒆂Ȃ�
        y = CONFIG_Y;    //�ݒ�̍��W���i�[
        break;
    case eMenu_Exit://�Q�[���I�𒆂Ȃ�
        y = EXIT_Y;
        break;
    }
    DrawStringToHandle(WINDOW_SIZE_X / 2 - 100, y, "��", GetColor(255, 255, 255), menu_font);
}
