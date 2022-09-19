
#include <iostream>

using namespace std;

class FlashMemory {
public:
    ~FlashMemory ();                                            // 메모리 해제
    void init (int megabytes);                                  // x megabytes 플레시 메모리 생성
    void Flash_write (int PSN, char data);                      // 물리적 읽기 수행
    void Flash_read (int PSN);                                  // 물리적 쓰기 수행
    void Flash_init (int size);                                // 초기화
    void Flash_erase (int block);                                // 해당 블록 지우기

    int BS_number (int PSN, char choice);
    int Max_LSN (int megabytes, char choice);                                //  LSN의 최대값을 구한다.


    int blockNum, secterNum, wrtiteCount = 0, eraseCount = 0, physical = 0;
    char*** sector;
};
