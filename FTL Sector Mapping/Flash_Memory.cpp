
#include "Flash_Memory.h"

#define ONE_BLOCK_SECTOR 32
#define SECTOR_SIZE 512

FlashMemory::~FlashMemory () {                                          // 메모리 해제
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < ONE_BLOCK_SECTOR; j++)
            delete[] sector[i][j];
        delete[] sector[i];
    }
    delete[] sector;
}

void FlashMemory::init (int megabytes) {
    sector = new char** [megabytes * 64];                            // block
    for (int i = 0; i < megabytes * 64; i++) {
        sector[i] = new char* [ONE_BLOCK_SECTOR];                                 // 1block = 32sector
        for (int j = 0; j < ONE_BLOCK_SECTOR; j++)
            sector[i][j] = new char[SECTOR_SIZE];                          // 가상 sector 공간 512B
    }

    cout << megabytes << " megabytes flash memory" << endl;
    Flash_init (megabytes * 64);                                   // 메모리 초기화
}

void FlashMemory::Flash_write (int PSN, char data) {
    blockNum = BS_number (PSN, 'b');                                           // 몇번째 블록인지 계산
    secterNum = BS_number (PSN, 's');                                          // 몇번째 섹터인지 계산

    if (sector[blockNum][secterNum][0] == 0) {                      // 현재 섹터가 비어있으면
        sector[blockNum][secterNum][0] = data;
        cout << "PSN : " << PSN << "\t Data : " << sector[blockNum][secterNum][0] << endl;
        wrtiteCount++;
    }
    else {
        cout << "is full" << endl;
    }
    physical++;
}

void FlashMemory::Flash_read (int PSN) {
    blockNum = BS_number (PSN, 'b');                                           // 몇번째 블록인지 계산
    secterNum = BS_number (PSN, 's');                                          // 몇번째 섹터인지 계산
    cout << "PSN : " << PSN << "  PSN data : " << sector[blockNum][secterNum][0] << endl;
}

void FlashMemory::Flash_init (int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < ONE_BLOCK_SECTOR; j++)
            sector[i][j][0] = 0;
    }
}

void FlashMemory::Flash_erase (int block) {
    for (int i = 0; i < ONE_BLOCK_SECTOR; i++) {
        sector[block][i][0] = 0;
    }
    eraseCount++;
}

int FlashMemory::BS_number (int PSN, char choice) {
    int bNum = PSN / ONE_BLOCK_SECTOR;
    int sNum = PSN % ONE_BLOCK_SECTOR;

    if (choice == 's')      return sNum;
    else if (choice == 'b') return bNum;
}

int FlashMemory::Max_LSN (int megabytes, char choice) {
    int sectorNum = megabytes * 2048;
    int blockNum = megabytes * 64;
    int MaxSector = sectorNum - (ONE_BLOCK_SECTOR * 2);
    int MaxBlock = blockNum - 2;

    if (choice == 's')      return MaxSector;
    else if (choice == 'b') return MaxBlock;
}