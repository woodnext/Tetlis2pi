#pragma once

#include "BaseScene.h"

typedef enum {
    eMenu_1PGame,    //1P�Q�[��
    eMenu_Config,    //�ݒ�
    eMenu_Exit,
    eMenu_Num,        //�{���ڂ̐�
} eMenu;

//���j���[��ʃN���X
class Menu : public BaseScene {

public:
    Menu(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
    int background_Handle;
    const static int GAME_Y = 400;    //�u�Q�[���v������y�ʒu
    const static int CONFIG_Y = 470;    //�u�ݒ�v������y�ʒu
    const static int EXIT_Y = 540;    //�u�ݒ�v������y�ʒu
    int menu_font;
    int NowSelect;    //���݂̑I�����(�����̓Q�[���I��)
};