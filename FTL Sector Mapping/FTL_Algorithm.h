
#include "Flash_Memory.h"

class FTL_Algorithm {
public:
    void menu ();                                   // �޴�
    void FTL_read (int LSN);                        // ftl �б�
    void FTL_write (int LSN, char data);            // ftl ����
    void make_table (char choice);                  // ���̺� ����
    void full_memory ();                            // ���̺� ��� ä���
    void Print_table ();                            // ���̺� ���

    FlashMemory f;
    int megabytes, * table, EraseNum;
};