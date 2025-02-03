//========================
//
//�����L���O����;ranking.h
//Authar:KuramaeSatoshi
// 
//========================

#include "main.h"
#define JOIN_VERIFY 4    // �l���w��
#define MAX_RANK (5) //�����N�̐�
#define MAX_RANKTEX (3)
#define MAX_DIGIT    (8)    //����
#define MAX_RANKWIDTH    (60.0f)    //�����L���O�̕�
#define MAX_RANKHEIGHT    (65.0f)    //�����L���O�̍���
#define NUM_RANK_UITEX    (2)

//�����L���O�\����
typedef struct
{
    D3DXVECTOR3 pos;
    int nScore;
    int nScorePos;
    bool bRight;        //�V���������N�C�������ꍇ�_��������
}RankScore;

//�v���g�^�C�v�錾
void InitRanking(void);
void InitRanking_BG(void);
void UninitRanking(void);
void UninitRanking_BG(void);
void UpdateRanking(void);
void UpdateRanking_BG(void);
void DrawRanking_BG(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);