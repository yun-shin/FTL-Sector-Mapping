
#include "Flash_Memory.h"

class FTL_Algorithm {
public:
    void menu ();                                   // 메뉴
    void FTL_read (int LSN);                        // ftl 읽기
    void FTL_write (int LSN, char data);            // ftl 쓰기
    void make_table (char choice);                  // 테이블 생성
    void full_memory ();                            // 테이블 모두 채우기
    void Print_table ();                            // 테이블 출력

    FlashMemory f;
    int megabytes, * table, EraseNum;
};