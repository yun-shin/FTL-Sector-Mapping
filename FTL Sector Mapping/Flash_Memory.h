
#include <iostream>

using namespace std;

class FlashMemory {
public:
    ~FlashMemory ();                                            // �޸� ����
    void init (int megabytes);                                  // x megabytes �÷��� �޸� ����
    void Flash_write (int PSN, char data);                      // ������ �б� ����
    void Flash_read (int PSN);                                  // ������ ���� ����
    void Flash_init (int size);                                // �ʱ�ȭ
    void Flash_erase (int block);                                // �ش� ��� �����

    int BS_number (int PSN, char choice);
    int Max_LSN (int megabytes, char choice);                                //  LSN�� �ִ밪�� ���Ѵ�.


    int blockNum, secterNum, wrtiteCount = 0, eraseCount = 0, physical = 0;
    char*** sector;
};
