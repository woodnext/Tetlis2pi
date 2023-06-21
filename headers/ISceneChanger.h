#pragma once

enum eScene {
    eScene_Menu,        //���j���[���
    eScene_Normal,      //�Q�[�����
    eScene_Tetlis2pi,   //�ݒ���
    eScene_Exit,        //�Q�[���I��
    eScene_None,        //����
};

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger 
{
public:
    virtual ~ISceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};

