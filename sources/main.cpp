/*
* TETLIS 2��
* �쐬 j1813 �؎��x
* ���� 2021/07/
* 
* �T�v�F
*   ��{�I�ɋ����͑S�ăK�C�h���C���ɏ���
*   �i��̓I�ɂ́C�e�g���~�m�̐F�CNEXT�E�S�[�X�g�̕\���C�u�o�b�O�V�X�e���v�uHOLD�v�uSRS�v�u���b�N�_�E���v���̃V�X�e���̎����j
*   ����ɉ����C
*/
#pragma once
#include "../headers/SceneMgr.h"
#include "../headers/include.h"
#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hinst , HINSTANCE hinst2, LPSTR lps, int nCmd) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
    AddFontResourceEx("fonts/nicokaku_v1.ttf", FR_PRIVATE, NULL);
    //ChangeFont("�j�R�p", DX_CHARSET_DEFAULT);
    //AddFontResourceEx("fonts/Ronde-B_square.otf", FR_PRIVATE, NULL);
    //ChangeFont("�����h B �X�N�G�A", DX_CHARSET_DEFAULT);
    SceneMgr sceneMgr;
    sceneMgr.Initialize();

    //���C������
    // while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̏�ԍX�V)
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {

        sceneMgr.Update();  //�X�V
        sceneMgr.Draw();    //�`��
    }

    DxLib_End(); // DX���C�u�����I������
    return 0;
}