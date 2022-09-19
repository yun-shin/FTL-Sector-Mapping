
#include "FTL_Algorithm.h"

void FTL_Algorithm::menu () {
    string Operation;
    int number;
    char data;

    cout << "write or read after init" << endl;
    cin >> Operation >> megabytes;
    if (!Operation.compare ("init") && cin.fail () == false && megabytes >= 0) {                   // x megabytes 플레시 메모리 생성
        f.init (megabytes);
        make_table ('s');

        while (true) {
            cin >> Operation >> number;
            if (!Operation.compare ("read") && cin.fail () == false && number >= -1)                // 읽기 명령
                FTL_read (number);
            else if (!Operation.compare ("write") && cin.fail () == false && number >= -1) {        // 쓰기 명령
                cin >> data;
                FTL_write (number, data);
            }
            else if (!Operation.compare ("full") && cin.fail () == false) {
                full_memory ();
            }
            else if (!Operation.compare ("print") && cin.fail () == false) {
                Print_table ();
            }
            else {
                cout << "재입력" << endl;
                cin.clear ();                           // 에러비트 초기화
                cin.ignore (1000, '\n');
            }
        }
    }
    else {
        cout << "재입력" << endl;
        cin.clear ();                           // 에러비트 초기화
        cin.ignore (1000, '\n');
        return;
    }
}

void FTL_Algorithm::make_table (char choice) {
    if (choice == 's') {
        int end_LSN = f.Max_LSN (megabytes, 's');
        table = new int[end_LSN];
    }
    else if (choice == 'b') {
        int end_LSN = f.Max_LSN (megabytes, 'b');
        table = new int[end_LSN];
    }

    for (int i = 0; i < _msize (table) / sizeof (int); i++)
        table[i] = -1;
}

void FTL_Algorithm::FTL_write (int LSN, char data) {
    int tableMax = _msize (table) / sizeof (int), emptyNum = 0;

    if (f.physical >= tableMax) {
        EraseNum = table[LSN] / 32;                                             // 지우는 블록
        for (int i = 0; i < megabytes * 64; i++) {
            if (f.sector[i][0][0] == 0) {
                emptyNum = i;
                break;
            }
        }
        emptyNum = emptyNum * 32;

        for (int i = 0; i < _msize (table) / sizeof (int); i++) {
            if (table[LSN] == i) {
                f.Flash_write (emptyNum, data);
                table[i] = emptyNum;
                emptyNum++;
            }
            else if (f.BS_number (table[i], 'b') == EraseNum) {
                f.Flash_write (emptyNum, f.sector[EraseNum][f.BS_number (table[i], 's')][0]);
                table[i] = emptyNum;
                emptyNum++;
            }
        }

        f.Flash_erase (EraseNum);
    }
    else {
        table[LSN] = f.physical;
        f.Flash_write (f.physical, data);
    }
    cout << "쓰기완료. " << "쓰기 " << f.wrtiteCount << "회, " << "지우기 " << f.eraseCount << "회" << endl;
    f.wrtiteCount = 0;
    f.eraseCount = 0;
}

void FTL_Algorithm::full_memory () {
    int tableMax = _msize (table) / sizeof (int);

    for (int i = 0; i < tableMax; i++) {
        table[i] = i;
        f.Flash_write (i, 'a');
    }
    cout << "done." << endl;
    f.wrtiteCount = 0;
}

void FTL_Algorithm::Print_table () {
    int tableMax = _msize (table) / sizeof (int), c = 1;

    for (int i = 0; i < tableMax; i++) {
        cout.width (10);
        cout << i << " : " << table[i];
        if (c % 5 == 0)
            cout << endl;
        c++;
    }
    cout << endl;
}

void FTL_Algorithm::FTL_read (int LSN) {
    f.Flash_read (table[LSN]);
}