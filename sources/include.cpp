#include "../headers/include.h"

extern int Key[256] = {0}; // �L�[��������Ă���t���[�������i�[����
//extern int Key[28] = { 0 }; // �L�[��������Ă���t���[�������i�[����

int gpUpdateKey() {
    //int Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
    //for (int i = 0; i < 28; i++) {      //�{�^��28�����[�v
    //    if (Pad & (1<<i)) {             //�{�^��i�̓��̓t���O�������Ă�����
    //        Key[i]++;
    //    }
    //    else {                  // ������Ă��Ȃ����
    //        Key[i] = 0;         // 0�ɂ���
    //    }
    //}
    char tmpKey[256];           // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) {   // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            Key[i]++;           // ���Z
        }
        else {                  // ������Ă��Ȃ����
            Key[i] = 0;         // 0�ɂ���
        }
    }
    return 0;
}