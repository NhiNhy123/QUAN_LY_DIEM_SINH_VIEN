#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define mx 40
#define mx_hp 20
#define so_lop 2 
#define soGV 3
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"
#define HIGHLIGHT_BLUE "\033[46;30m"
#define HIGHLIGHT_YELLOW "\033[43;30m"
#define BOLD_CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define BOLD "\x1b[1m"

typedef struct {
    char taiKhoan[30];
    char matKhau[30];
    char tenGV[50];
    char lopPhanCong[20]; 
} TaiKhoanGiangVien;

typedef struct {
    char tenLop[20];
    int n; 
    char maSV[mx][20];
    char tenSV[mx][30];
    float lab1[mx];
    float lab2[mx];
    float pt1[mx];
    float pt2[mx];
    float pre[mx];
    float final[mx];
    char dsHocPhan[mx_hp][100];
    int soHp;
} LopHoc;

TaiKhoanGiangVien danhSachGV[50];
int soLuongGV = 0;

char taiKhoanGV[soGV][20] = { "admin", "giangvien1", "giangvien2" };
char matKhauGV[soGV][20] = { "123", "gv001", "gv002"};

LopHoc danhSachLop[so_lop];
int lopHienTai = 0; // Chi so lop dang lam viec (0: 25T_DT1, 1: 25T_DT2)

// Su dung con tro hoac lien ket mang de hien thi chuc nang
int n = 40; 
char (*maSV)[20];
char (*tenSV)[30];
float *lab1, *lab2, *pt1, *pt2, *pre, *final;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Ham khoi tao tai khoan he thong mac dinh ban dau
void khoiTaoTaiKhoanHeThong() {
    strcpy(danhSachGV[0].taiKhoan, "giangvien1");
    strcpy(danhSachGV[0].matKhau, "gv001");
    strcpy(danhSachGV[0].tenGV, "Tran Thi Binh");
    strcpy(danhSachGV[0].lopPhanCong, "25T_DT1");

    strcpy(danhSachGV[1].taiKhoan, "giangvien2");
    strcpy(danhSachGV[1].matKhau, "gv002");
    strcpy(danhSachGV[1].tenGV, "Le Van Chau");
    strcpy(danhSachGV[1].lopPhanCong, "25T_DT2");

    soLuongGV = 2; 
}

void dongBoMangTheoLop(int indexLop) {
    if (indexLop < 0 || indexLop >= so_lop) return;
    
    lopHienTai = indexLop;
    // Ð?ng b? si s? n toàn c?c v?i si s? th?c t? c?a l?p trong struct
    n = danhSachLop[lopHienTai].n; 
    
    // Ép các con tr? toàn c?c tr? th?ng vào vùng nh? l?p tuong ?ng trong struct
    maSV  = danhSachLop[lopHienTai].maSV;
    tenSV = danhSachLop[lopHienTai].tenSV;
    lab1  = danhSachLop[lopHienTai].lab1;
    lab2  = danhSachLop[lopHienTai].lab2;
    pt1   = danhSachLop[lopHienTai].pt1;
    pt2   = danhSachLop[lopHienTai].pt2;
    pre   = danhSachLop[lopHienTai].pre;
    final = danhSachLop[lopHienTai].final;
}

void khoiTaoDuLieuGoc() {

    danhSachLop[0].soHp = 3; // L?p này ban d?u có 3 môn
    strcpy(danhSachLop[0].dsHocPhan[0], "Cau Truc Du Lieu");
    strcpy(danhSachLop[0].dsHocPhan[1], "Phuong Phap Tinh");
    strcpy(danhSachLop[0].dsHocPhan[2], "Toan Roi Rac");

    strcpy(danhSachLop[0].tenLop, "25T_DT1");
    danhSachLop[0].n = 40;
    char msv1[mx][20] = {
        "102250001","102250002","102250003","102250004","102250005","102250006","102250007","102250008","102250009","102250010",
        "102250011","102250012","102250013","102250014","102250015","102250016","102250017","102250018","102250019","102250020",
        "102250021","102250022","102250023","102250024","102250025","102250026","102250027","102250028","102250029","102250030",
        "102250031","102250032","102250033","102250034","102250035","102250036","102250037","102250038","102250039","102250040"
    };
    char tsv1[mx][30] = {
        "Nguyen Van An","Tran Thi Ngoc Anh","Mai Thi Ngoc Chau","Le Van Chanh","Pham Thuy Duong","Hoang Van Thai Duy",
        "Nguyen Thi Danh","Le Thi Mai Giang","Tran Van Hoang","Pham Van Huy","Hoang Thi Hong Hoa",
        "Nguyen Van Khanh","Tran Thi Khanh","Le Tuan Kiet","Le Van Luc","Pham Thi Linh","Hoang Van Lanh",
        "Nguyen Thi My","Le Thi Minh","Nguyen Thi Nhi","Le Thi Nhim","Tran Van Cong Nhat","Tran Van Nhan","Pham Van Nhat","Hoang Thai U Ninh",
        "Nguyen Van Oanh","Tran Thi Phai","Le Thien Phong","Pham Thi Quyen","Hoang Van Quy",
        "Nguyen Thi Sinh","Le Thi Thy","Tran Van Tien", "Le Thanh Thu", "Hoang Mai Truc","Pham Van Thai","Hoang Thi Hong Vy",
        "Nguyen Van Cong Vy","Tran Thi Thieu Vy","Le Van Vinh"
    };
    memcpy(danhSachLop[0].maSV, msv1, sizeof(msv1));
    memcpy(danhSachLop[0].tenSV, tsv1, sizeof(tsv1));
    
    danhSachLop[1].soHp = 3; 
    strcpy(danhSachLop[1].dsHocPhan[0], "Cau Truc Du Lieu");
    strcpy(danhSachLop[1].dsHocPhan[1], "Phuong Phap Tinh");
    strcpy(danhSachLop[1].dsHocPhan[2], "Toan Roi Rac");
    
    strcpy(danhSachLop[1].tenLop, "25T_DT2");
    danhSachLop[1].n = 30;
    char msv2[mx][20] = {
        "102250101","102250102","102250103","102250104","102250105","102250106","102250107","102250108","102250109","102250110",
        "102250111","102250112","102250113","102250114","102250115","102250116","102250117","102250118","102250119","102250120",
        "102250121","102250122","102250123","102250124","102250125","102250126","102250127","102250128","102250129","102250130"
    };
    char tsv2[mx][30] = {
        "Bui Minh Quan","Cao Ngoc Bao","Dang Hoang Long","Dinh Tien Dung","Do Tuan Kiet","Duong Hong Nhung",
        "Ha Minh Triet","Hoang Thanh Lam","Huynh Quoc Bao","Lai Tien Dat","Lam Gia Hao",
        "Luu Duc Manh","Ngo Chi Thanh","Ngo Gia Huy","Nguyen Bao Ngoc","Nguyen Dinh Nam","Nguyen Hoang Em",
        "Nguyen Minh Trieu","Nguyen Thanh Tung","Phan Cam Tu","Phung Hoang Anh","Tang Vinh Kiet","Thai Duy Chinh",
        "To Minh Tri","Ton That Bach","Trinh Xuan Son","Vu Duc Thang","Vu Hoang Giang","Vu Minh Hieu","Vuong Tu Nam"
    };
    memcpy(danhSachLop[1].maSV, msv2, sizeof(msv2));
    memcpy(danhSachLop[1].tenSV, tsv2, sizeof(tsv2));

    // Mac dinh ban dau tro he thong ve lop thu nhat
    dongBoMangTheoLop(0);
}

int vaiTro = 0; 
char svDangNhap[20];
char mkMacDinhSV[20] = "123456";
char dsHocPhan[mx_hp][100] = {"Cau Truc Du Lieu", "Phuong Phap Tinh", "Toan Roi Rac"};
int soHp = 3;
char tenHp[30];
char tenFile[50];

int binary_search(char *ma) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int m = (left + right) / 2;
        int k = strcmp(maSV[m], ma);
        if (k == 0) return m;
        else if (k < 0) left = m + 1;
        else right = m - 1;
    }
    return -1;
}

void taoTenFile() {
    sprintf(tenFile, "%s_%s.txt", danhSachLop[lopHienTai].tenLop, tenHp);
}

void luuFile() {
    FILE *f = fopen(tenFile, "w");
    if (!f) return;
    fprintf(f,"%d\n", n);
    int i;
    for (i=0;i<n;i++) {
        fprintf(f,"%s %s %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f\n",
            maSV[i], tenSV[i], lab1[i], lab2[i], pt1[i], pt2[i], pre[i], final[i]);
    }
    fclose(f);
    danhSachLop[lopHienTai].n = n; 
}

void docFile() {
    int i;
    for(i = 0; i < mx; i++) {
        lab1[i] = lab2[i] = pt1[i] = pt2[i] = pre[i] = final[i] = -1;
    }
    FILE *f = fopen(tenFile, "r");
    if (!f) return;

    int sl;
    fscanf(f, "%d\n", &sl); 
    n = sl;
    danhSachLop[lopHienTai].n = sl; 

    for (i = 0; i < sl; i++) {
        if (i >= mx) break;
        fscanf(f, "%s ", maSV[i]); 
        fscanf(f, "%[^0-9-]", tenSV[i]); 
        fscanf(f, "%f %f %f %f %f %f\n",
               &lab1[i], &lab2[i], &pt1[i], &pt2[i], &pre[i], &final[i]);
        int len = strlen(tenSV[i]);
        while(len > 0 && tenSV[i][len-1] == ' ') {
            tenSV[i][len-1] = '\0';
            len--;
        }
    }
    fclose(f);
}

void luuDanhSachMon() {
    FILE *f = fopen("DanhSachMon.txt", "w");
    if (!f) return;
    fprintf(f, "%d\n", soHp);
    int i;
    for (i = 0; i < soHp; i++) {
        fprintf(f, "%s\n", dsHocPhan[i]); 
    }
    fclose(f);
}

void docDanhSachMon() {
    FILE *f = fopen("DanhSachMon.txt", "r");
    if (!f) {
        soHp = 3;
        strcpy(dsHocPhan[0], "Cau Truc Du Lieu");
        strcpy(dsHocPhan[1], "Phuong Phap Tinh");
        strcpy(dsHocPhan[2], "Toan Roi Rac");
        return;
    }
    fscanf(f, "%d\n", &soHp); 
    int i;
    for (i = 0; i < soHp; i++) {
        fscanf(f, "%s\n", dsHocPhan[i]); 
    }
    fclose(f);
}

int realLen(char *text) {
    int len = 0;
    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == '\033') { 
            while (text[i] != 'm' && text[i] != '\0') i++;
        } else {
            len++;
        }
        if (text[i] != '\0') i++;
    }
    return len;
}

void printCenter(char *text) {
    int visibleLen = realLen(text);
    int pos = (120 - visibleLen) / 2; 
    if (pos < 0) pos = 0;
    
    int i;
    for (i = 0; i < pos; i++) printf(" ");
    printf("%s\n", text);
}

void xoaDongVuaNhap() {
    printf("\033[A\33[2K\r");
}

void chooseRoleBox() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();

    gotoxy(12, 3);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

    gotoxy(12, 4);  printf(CYAN "|" RESET);
    gotoxy(46, 4);  printf(RED "HE THONG QUAN LY DIEM SINH VIEN" RESET);
    gotoxy(106, 4); printf(CYAN "|" RESET);
    gotoxy(12, 5);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

    int y;
    for (y = 6; y <= 22; y++) {
        gotoxy(12, y);  printf(CYAN "|" RESET);
        gotoxy(106, y); printf(CYAN "|" RESET);
    }
    gotoxy(12, 23);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);
    gotoxy(35, 8);
    printf(YELLOW "+----------------------------------------------+" RESET);
    
    gotoxy(35, 9);
    printf(GREEN  "|                CHON DOI TUONG                |" RESET);
    
    gotoxy(35, 10);
    printf(YELLOW "+----------------------------------------------+" RESET); 

    gotoxy(35, 11);
    printf(YELLOW "|                                              |" RESET);
    
    gotoxy(35, 12);
    printf(YELLOW "|        1. DANG NHAP GIANG VIEN               |" RESET);
    
    gotoxy(35, 13);
    printf(YELLOW "|                                              |" RESET);
    
    gotoxy(35, 14);
    printf(YELLOW "|        2. DANG NHAP SINH VIEN                |" RESET);
    
    gotoxy(35, 15);
    printf(YELLOW "|                                              |" RESET);
    
    gotoxy(35, 16);
    printf(YELLOW "|        0. THOAT                              |" RESET);
    
    gotoxy(35, 17);
    printf(YELLOW "|                                              |" RESET);
    
    gotoxy(35, 18);
    printf(YELLOW "+----------------------------------------------+" RESET);

    gotoxy(35, 20);
    printf(GREEN "Nhap lua chon cua ban: " RESET);

    showCursor();
}

void lecturerLoginBox() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();

    gotoxy(12, 3);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);
    int y;
    for (y = 4; y <= 22; y++) {
        gotoxy(12, y);  printf(CYAN "|" RESET);
        gotoxy(106, y); printf(CYAN "|" RESET);
    }
    gotoxy(46, 4);
    printf(RED "HE THONG QUAN LY DIEM SINH VIEN" RESET);
    gotoxy(12, 5);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);
    gotoxy(12, 23);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

    gotoxy(30, 8);
    printf(MAGENTA "+------------------------------------------------------------+" RESET);
    gotoxy(30, 9);
    printf(MAGENTA "|                  DANG NHAP TAI KHOAN GIANG VIEN            |" RESET);
    gotoxy(30, 10);
    printf(MAGENTA "+------------------------------------------------------------+" RESET);

    for (y = 11; y <= 18; y++) {
        gotoxy(30, y);
        printf(MAGENTA "|                                                            |" RESET);
    }

    gotoxy(32, 12);
    printf(MAGENTA "TEN DANG NHAP" RESET);
    gotoxy(50, 11);
    printf(MAGENTA "     +---------------------------+" RESET);
    gotoxy(50, 12);
    printf(MAGENTA "     |                           |" RESET);
    gotoxy(50, 13);
    printf(MAGENTA "     +---------------------------+" RESET);

    gotoxy(32, 16);
    printf(MAGENTA "MAT KHAU" RESET);
    gotoxy(50, 15);
    printf(MAGENTA "     +---------------------------+" RESET);
    gotoxy(50, 16);
    printf(MAGENTA "     |                           |" RESET);
    gotoxy(50, 17);
    printf(MAGENTA "     +---------------------------+" RESET);

    gotoxy(30, 19);
    printf(MAGENTA "+------------------------------------------------------------+" RESET);
}



void studentLoginBox() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();

    gotoxy(12, 3);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);
    
    int y;
    for (y = 4; y <= 22; y++) {
        gotoxy(12, y);  printf(CYAN "|" RESET);
        gotoxy(106, y); printf(CYAN "|" RESET);
    }
    
    gotoxy(46, 4);
    printf(RED "HE THONG QUAN LY DIEM SINH VIEN" RESET);
    
    gotoxy(12, 5);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);
    
    gotoxy(12, 23);
    printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

    gotoxy(30, 8);
    printf(GREEN "+------------------------------------------------------------+" RESET);
    gotoxy(30, 9);
    printf(GREEN "|                    DANG NHAP TAI KHOAN SINH VIEN           |" RESET);
    gotoxy(30, 10);
    printf(GREEN "+------------------------------------------------------------+" RESET);

    for (y = 11; y <= 18; y++) {
        gotoxy(30, y);
        printf(GREEN "|                                                            |" RESET);
    }

    gotoxy(32, 12);
    printf(GREEN "MA SINH VIEN" RESET);
    gotoxy(50, 11); printf(GREEN "     +---------------------------+" RESET);
    gotoxy(50, 12); printf(GREEN "     |                           |" RESET);
    gotoxy(50, 13); printf(GREEN "     +---------------------------+" RESET);

    gotoxy(32, 16);
    printf(GREEN "MAT KHAU" RESET);
    gotoxy(50, 15); printf(GREEN "     +---------------------------+" RESET);
    gotoxy(50, 16); printf(GREEN "     |                           |" RESET);
    gotoxy(50, 17); printf(GREEN "     +---------------------------+" RESET);

    gotoxy(30, 19);
    printf(GREEN "+------------------------------------------------------------+" RESET);
}

void loadingEffect(int x, int y) {
    gotoxy(x, y);
    printf(CYAN "Dang xu ly" RESET);
    int i;
    for (i = 0; i < 4; i++) {
        printf(CYAN "." RESET);
        fflush(stdout);
        Sleep(250);
    }
}

int dangNhapHeThong() {
    char tk[30], mk[30];
    int i, j;

    while (1) {
        system("cls");
        lecturerLoginBox(); 

        gotoxy(57, 12); showCursor(); fflush(stdin); scanf("%s", tk);
        if (strcmp(tk, "0") == 0) return 0; 

        gotoxy(57, 16); showCursor(); fflush(stdin); scanf("%s", mk);
        
        hideCursor();
        loadingEffect(52, 21); 
        
        // 1. KI?M TRA TÀI KHO?N ADMIN TRU?C
        if (strcmp(tk, "admin") == 0 && strcmp(mk, "123") == 0) {
            vaiTro = 1;
            gotoxy(42, 21); printf("                                                 "); 
            gotoxy(48, 21); printf(GREEN "[ V ] DANG NHAP ADMIN THANH CONG!" RESET);
            fflush(stdout);
            Sleep(1200);
            return 1; 
        }

        // 2. DUY?T DANH SÁCH GI?NG VIÊN TRONG STRUCT
        for (i = 0; i < soLuongGV; i++) {
            if (strcmp(tk, danhSachGV[i].taiKhoan) == 0 && strcmp(mk, danhSachGV[i].matKhau) == 0) {
                
                int indexTimThay = -1;
                for (j = 0; j < so_lop; j++) {
                    if (strcmp(danhSachGV[i].lopPhanCong, danhSachLop[j].tenLop) == 0) {
                        indexTimThay = j;
                        break;
                    }
                }

                if (indexTimThay != -1) {
                    vaiTro = 2;
                    // S?A T?I ÐÂY: G?i dúng tên hàm dongBoMangTheoLop thay vì tên cu
                    dongBoMangTheoLop(indexTimThay); 
                    
                    gotoxy(42, 21); printf("                                                 "); 
                    gotoxy(48, 21); printf(GREEN "[ V ] DANG NHAP THANH CONG!" RESET);
                    fflush(stdout);
                    Sleep(1200);
                    return 2; 
                }
            }
        }

        gotoxy(42, 21); printf("                                                 "); 
        gotoxy(42, 21); printf(RED "[ X ] TAI KHOAN HOAC MAT KHAU KHONG CHINH XAC!" RESET);
        gotoxy(45, 22); printf(YELLOW "Nhan phim bat ky de thuc hien nhap lai..." RESET);
        getch(); 
    }
    return 0;
}

int dangNhapSinhVien() {
    char tk[30], mk[30];
    int i;

    while (1) {
        system("cls");
        studentLoginBox(); 
        gotoxy(57, 12);
        showCursor();
        fflush(stdin);
        scanf("%s", tk);

        if (strcmp(tk, "0") == 0) {
            return 0;
        }

        gotoxy(57, 16);
        showCursor();
        fflush(stdin);
        scanf("%s", mk);
        
        hideCursor();
        loadingEffect(52, 21); 
        
        int row;
        for (row = 21; row <= 22; row++) {
            gotoxy(35, row);
            printf("                                                             ");
        }

        gotoxy(12, 23);
        printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

        for (i = 0; i < n; i++) { 
            if (strcmp(tk, maSV[i]) == 0 && strcmp(mk, mkMacDinhSV) == 0) {
                vaiTro = 2; 
                strcpy(svDangNhap, maSV[i]); 

                gotoxy(48, 21); 
                printf(GREEN "[ V ] DANG NHAP THANH CONG!" RESET);
                fflush(stdout);
                Sleep(1200);
                return 1;
            }
        }
        gotoxy(12, 23);
        printf(CYAN "+---------------------------------------------------------------------------------------------+" RESET);

        gotoxy(42, 21);
        printf(RED "[ X ] MA SINH VIEN HOAC MAT KHAU KHONG CHINH XAC!" RESET);
        gotoxy(45, 22);
        printf(YELLOW "Nhan phim bat ky de thuc hien nhap lai..." RESET);
        getch();
    }
    return 0;
}

void menuAdmin() {
    system("cls");
    int d;
    for(d = 0; d < 10; d++) printf("\n"); // Ð?y menu xu?ng t?m gi?a màn hình gi?ng menu GV

    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    printCenter(CYAN "|          VAI TRO: ADMIN (QUAN LY HE THONG)               |" RESET);
    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    printCenter("|  1. Tao lop hoc moi                                      |");
    printCenter("|  2. Them giang vien moi                                  |");
    printCenter("|  3. Phan lop cho giang vien                              |");
    printCenter("|  4. Quan ly thong tin he thong                           |");
    printCenter("|  5. Dang xuat (Quay lai menu chinh)                      |");
    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    
    printf("\n");
    for(d = 0; d < 48; d++) printf(" ");
    printf("NHAP LUA CHON CUA BAN: ");
}

void menuGiangVien() {
    system("cls");
    int d;
    for(d = 0; d < 10; d++) printf("\n");

    char tieuDeMenu[100];
    // V?N D?NG STRUCT: L?y tên l?p tr?c ti?p t? danh sách l?p c? d?nh
    sprintf(tieuDeMenu, CYAN "|                QUAN LY DIEM - LOP: %-10s            |" RESET, danhSachLop[lopHienTai].tenLop);

    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    printCenter(tieuDeMenu);
    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    
    // V?N D?NG STRUCT: Ki?m tra si s? th?c t? c?a l?p (n) so v?i m?c t?i da mx (40)
    if (danhSachLop[lopHienTai].n < mx) {
        printCenter("|  1. Nhap diem & Them sinh vien moi                       |");
    } else {
        printCenter("|  1. Nhap & Sua diem 40 SV hien co (KHOA THEM MOI)        |");
    }
    
    printCenter("|  2. Xem diem chi tiet                                    |");
    printCenter("|  3. Sua diem da nhap                                     |");
    printCenter("|  4. Sap xep danh sach                                    |");
    printCenter("|  5. In bang thong ke                                     |");
    printCenter("|  6. Thoat chuong trinh                                   |");
    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    
    printf("\n");
    for(d = 0; d < 48; d++) printf(" ");
    printf("NHAP LUA CHON CUA BAN: ");
}

void layTenChinh(char hoTen[], char tenChinh[]) {
    int len = strlen(hoTen);
    int i = len - 1;
    while (i >= 0 && hoTen[i] == ' ') i--; 
    int ketThucTen = i; 
    while (i >= 0 && hoTen[i] != ' ') i--;
    int idx = 0;
    int j;
    for (j = i + 1; j <= ketThucTen; j++) {
        tenChinh[idx++] = hoTen[j];
    }
    tenChinh[idx] = '\0';
}

char xepLoai (float tb) {
    if (tb>=8.5) return 'A';
    if (tb>=7) return 'B';
    if (tb>=5) return 'C';
    if (tb>=4) return 'D';
    return 'F';
}

float tinhTB(int i) {
    if (lab1[i] == -1 || lab2[i] == -1 || pt1[i] == -1 || 
        pt2[i] == -1 || pre[i] == -1 || final[i] == -1) {
        return -1.0; 
    }
    return (lab1[i] + lab2[i] + pt1[i] + pt2[i] + pre[i] + final[i]) / 6.0;
}

void menuSinhVien(char maTruyenVao[], char monSua[], int cotSua) {
    int i, j, k;
    float l1, l2, p1, p2, pr, fi, tb;
    float tongDiem = 0;
    int soMonDaHoc = 0;
    int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;

    k = binary_search(maTruyenVao);
    if (k == -1) {
        printf(RED "Khong tim thay sinh vien!" RESET); getch(); return;
    }

    system("cls");
    printf("\n" GREEN "----- THONG TIN CA NHAN -----" RESET "\n");
    printf(YELLOW "   MSSV      : " RESET "%s\n", maSV[k]);
    printf(YELLOW "   HO VA TEN : " RESET "%s\n", tenSV[k]);
    printf("   LOP HOC   : %s\n", danhSachLop[lopHienTai].tenLop);
    printf("\n");

    printCenter("------------------------------ BANG DIEM CUA BAN -----------------------------");
    printf("\n");
    printCenter("+-------------------+------+------+------+------+------+-------+------+------+");
    printCenter("|     Hoc phan      | Lab1 | Lab2 | PT1  | PT2  | Pre  | Final |  TB  |  XL  |");
    printCenter("+-------------------+------+------+------+------+------+-------+------+------+");

    for (i = 0; i < soHp; i++) {
        char file[100], row[300];
        sprintf(file, "%s_%s.txt", danhSachLop[lopHienTai].tenLop, dsHocPhan[i]);
        FILE *f = fopen(file, "r");
        int found = 0;
        l1 = l2 = p1 = p2 = pr = fi = -1.0;

        if (f) {
            int sl;
            if (fscanf(f, "%d\n", &sl) == 1) {
                char maF[20], tenTam[100];
                for (j = 0; j < sl; j++) {
                    if (fscanf(f, "%s ", maF) != 1) break;
                    if (fscanf(f, "%[^0-9-]", tenTam) != 1) break;
                    if (fscanf(f, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                        if (strcmp(maF, maSV[k]) == 0) { found = 1; break; }
                    }
                }
            }
            fclose(f);
        }

        char sL1[30], sL2[30], sP1[30], sP2[30], sPr[30], sFi[30], sTb[30], sXl[10];
        int laMonSua = (strcmp(dsHocPhan[i], monSua) == 0);

        if (found) {
            if (l1 == -1.0) strcpy(sL1, "N/A "); else if (laMonSua && cotSua == 1) sprintf(sL1, GREEN "%-4.1f" RESET, l1); else sprintf(sL1, "%-4.1f", l1);
            if (l2 == -1.0) strcpy(sL2, "N/A "); else if (laMonSua && cotSua == 2) sprintf(sL2, GREEN "%-4.1f" RESET, l2); else sprintf(sL2, "%-4.1f", l2);
            if (p1 == -1.0) strcpy(sP1, "N/A "); else if (laMonSua && cotSua == 3) sprintf(sP1, GREEN "%-4.1f" RESET, p1); else sprintf(sP1, "%-4.1f", p1);
            if (p2 == -1.0) strcpy(sP2, "N/A "); else if (laMonSua && cotSua == 4) sprintf(sP2, GREEN "%-4.1f" RESET, p2); else sprintf(sP2, "%-4.1f", p2);
            if (pr == -1.0) strcpy(sPr, "N/A  "); else if (laMonSua && cotSua == 5) sprintf(sPr, GREEN "%-5.1f" RESET, pr); else sprintf(sPr, "%-5.1f", pr);
            if (fi == -1.0) strcpy(sFi, "N/A  "); else if (laMonSua && cotSua == 6) sprintf(sFi, GREEN "%-5.1f" RESET, fi); else sprintf(sFi, "%-5.1f", fi);
            
            if (l1 == -1.0 || l2 == -1.0 || p1 == -1.0 || p2 == -1.0 || pr == -1.0 || fi == -1.0) {
                strcpy(sTb, "N/A "); strcpy(sXl, "-");
            } else {
                tb = (l1 + l2 + p1 + p2 + pr + fi) / 6.0;
                tongDiem += tb; soMonDaHoc++;
                sprintf(sTb, "%-4.1f", tb);
                if (tb >= 8.5) { strcpy(sXl, "A"); countA++; }
                else if (tb >= 7.0) { strcpy(sXl, "B"); countB++; }
                else if (tb >= 5.5) { strcpy(sXl, "C"); countC++; }
                else if (tb >= 4.0) { strcpy(sXl, "D"); countD++; }
                else { strcpy(sXl, "F"); countF++; }
            }
            sprintf(row, "| %-17s | %-4s | %-4s | %-4s | %-4s | %-5s | %-5s | %-4s | %-4s |", dsHocPhan[i], sL1, sL2, sP1, sP2, sPr, sFi, sTb, sXl);
        } else {
            sprintf(row, "| %-17s | %-4s | %-4s | %-4s | %-4s | %-4s | %-5s | %-4s | %-4s |", dsHocPhan[i], "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "-");
        }
        printCenter(row);
    }
    printCenter("+-------------------+------+------+------+------+------+-------+------+------+");

    if (soMonDaHoc > 0) {
        float gpa = tongDiem / soMonDaHoc;
        printf("\n" CYAN "--- THONG KE KET QUA HOC TAP ---" RESET "\n");
        printf(">> Tong so mon: %d | GPA Trung binh: %.2f\n", soMonDaHoc, gpa);
        printf(">> Ty le xep loai: A(%.0f%%) - B(%.0f%%) - C(%.0f%%) - D(%.0f%%) - F(%.0f%%)\n", 
               (float)countA*100/soMonDaHoc, (float)countB*100/soMonDaHoc, 
               (float)countC*100/soMonDaHoc, (float)countD*100/soMonDaHoc, (float)countF*100/soMonDaHoc);
        printf("\n");
        if (gpa < 4.0) printCenter(RED "!!! CANH BAO: Hoc luc KEM (Nguy co duoi hoc) !!!" RESET);
        else if (gpa < 5.0) printCenter(YELLOW "!!! LUU Y: Hoc luc YEU (Can cai thien) !!!" RESET);
        else if (gpa >= 8.5) printCenter(GREEN "*** XUAT SAC: Chuc mung sinh vien gioi ***" RESET);
    }
    printf("\n"); printCenter(YELLOW "Nhan phim bat ky de tiep tuc..." RESET); getch();
}

void themHp() {
    char tenMoi[50];
    int i, exists;
    system("cls");
    printf("\n");
    printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
    printCenter(BOLD_CYAN "|              THEM HOC PHAN MOI           |" RESET);
    printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
    
    while (1) {
        if (danhSachLop[lopHienTai].soHp >= mx_hp) {
            printCenter("DANH SACH HOC PHAN C?A L?P ÐÃ Ð?Y!");
            getch();
            return;
        }
        
        printf("%75s", "Nhap ten hoc phan moi (0 de thoat): ");
        
        // ?? BU?C 1: Xóa b? d?m tru?c khi nh?p chu?i d? tránh b? trôi l?nh
        fflush(stdin); 
        
        // ?? BU?C 2: Thay %s b?ng %[^\n] d? cho phép d?c c? d?u cách cho d?n khi nh?n Enter
        scanf(" %[^\n]", tenMoi); 
        
        if (strcmp(tenMoi, "0") == 0) return;
        
        exists = 0;
        for (i = 0; i < danhSachLop[lopHienTai].soHp; i++) {
            if (strcmp(danhSachLop[lopHienTai].dsHocPhan[i], tenMoi) == 0) {
                exists = 1;
                break;
            }
        }
        
        if (exists) {
            xoaDongVuaNhap(); 
            // In thông báo n?u mu?n
        } else {
            xoaDongVuaNhap();
            strcpy(tenHp, tenMoi);
            
            int viTriMoi = danhSachLop[lopHienTai].soHp;
            strcpy(danhSachLop[lopHienTai].dsHocPhan[viTriMoi], tenHp);
            danhSachLop[lopHienTai].soHp++;
            
            luuDanhSachMon(); 
            taoTenFile();
            FILE *f = fopen(tenFile, "w");
            if (f) {
                fprintf(f, "%d\n", danhSachLop[lopHienTai].n);
                fclose(f);
            }
            
            printf(GREEN "%30s %s" RESET, "DA THEM THANH CONG CHO LOP:", tenHp);
            printf("\n\n%50s", "Nhan phim bat ky de quay lai...");
            getch();
            break; 
        }
    }
}

int menuHocPhan() {
    int chon;
    char line[100];
    while (1) {
        system("cls");
        int d;
        for(d = 0; d < 8; d++) printf("\n"); 

        printf(CYAN);
        printCenter("+-------------------------------------------+");
        // Hi?n th? rõ ràng dang ch?n môn cho l?p nào d? gi?ng viên không b? nh?m l?n
        sprintf(line, "|        CHON HOC PHAN LOP: %-15s |", danhSachLop[lopHienTai].tenLop);
        printCenter(line);
        printCenter("+-------------------------------------------+");
        printf(RESET);

        // Hi?n th? danh sách môn tuong ?ng c?a RIÊNG l?p hi?n t?i
        int i;
        for (i = 0; i < danhSachLop[lopHienTai].soHp; i++) {
            sprintf(line, "|    %d. %-33s   |", i + 1, danhSachLop[lopHienTai].dsHocPhan[i]);
            printCenter(line);
        }

        printCenter("|-------------------------------------------|");
        // L?a ch?n t?o môn m?i s? linh ho?t nh?y theo s? lu?ng môn hi?n t?i c?a l?p dó
        int nutThemMon = danhSachLop[lopHienTai].soHp + 1;
        sprintf(line, "|    %d. Tao hoc phan moi                    |", nutThemMon);
        printCenter(line);
        printCenter("|    0. Quay lai                            |");
        printCenter(CYAN"+-------------------------------------------+"RESET);
        
        printf("\n");
        for(d = 0; d < 45; d++) printf(" "); 
        printf("NHAP LUA CHON CUA BAN: ");

        if (scanf("%d", &chon) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        if (chon == 0) return 0;
        
        // X? lý khi ch?n m?t h?c ph?n có s?n c?a l?p
        if (chon >= 1 && chon <= danhSachLop[lopHienTai].soHp) {
            strcpy(tenHp, danhSachLop[lopHienTai].dsHocPhan[chon - 1]);
            taoTenFile();
            docFile();
            return 1;
        } 
        // X? lý khi ch?n t?o h?c ph?n m?i cho l?p
        else if (chon == nutThemMon) {
            themHp();
        } else {
            printf("\n");
            printCenter(RED"LUA CHON KHONG HOP LE! VUI LONG THU LAI" RESET);
            getch();
        }
    }
}

int HocPhan() {
    int chon;
    char line[100];
    while (1) {
        system("cls");
        int d,i;
        for(d = 0; d < 8; d++) printf("\n");
        
        printf(CYAN);
        printCenter("+-------------------------------------------+");
        printCenter("|           CHON HOC PHAN DAO TAO           |");
        printCenter("+-------------------------------------------+");
        printf(RESET);
        
        for (i = 0; i < soHp; i++) {
            sprintf(line, "|    %d. %-33s   |", i + 1, dsHocPhan[i]);
            printCenter(line);
        }
        printCenter("|-------------------------------------------|");
        printCenter("|    0. Quay lai                            |");
        printf(CYAN);
        printCenter("+-------------------------------------------+");
        printf(RESET);
        
        printf("\n");
        for(d = 0; d < 45; d++) printf(" "); 
        printf("NHAP LUA CHON CUA BAN: ");
        
        if (scanf("%d", &chon) != 1) {
            while (getchar() != '\n'); continue;
        }
        while (getchar() != '\n'); 
        if (chon == 0) return 0;
        if (chon >= 1 && chon <= soHp) {
            strcpy(tenHp, dsHocPhan[chon - 1]);
            taoTenFile();
            docFile(); 
            return 1;
        } else {
            printCenter(RED "Lua chon khong hop le!" RESET);
            getch();
        }
    }
}

void DanhSachSV() {
	printf("\n");
    printCenter(BOLD_CYAN" DANH SACH SINH VIEN LOP HOC PHAN " RESET);
    printf(CYAN"+-----+------------+---------------------+------+------+------+------+------+------+------+\n"RESET);
    printf("| STT |  Ma so SV  |      Ho va ten      | Lab1 | Lab2 | PT1  | PT2  | Pre  | Final|  TB  |\n");
    printf(CYAN"+-----+------------+---------------------+------+------+------+------+------+------+------+\n"RESET);
    int j;
    for (j = 0; j < n; j++) {
        printf("| %-3d | %-10s | %-19s | ", j + 1, maSV[j], tenSV[j]);
        if (lab1[j] == -1) printf("%-4s | ", "N/A"); else printf("%-4.1f | ", lab1[j]);
        if (lab2[j] == -1) printf("%-4s | ", "N/A"); else printf("%-4.1f | ", lab2[j]);
        if (pt1[j] == -1)  printf("%-4s | ", "N/A"); else printf("%-4.1f | ", pt1[j]);
        if (pt2[j] == -1)  printf("%-4s | ", "N/A"); else printf("%-4.1f | ", pt2[j]);
        if (pre[j] == -1)  printf("%-4s | ", "N/A"); else printf("%-4.1f | ", pre[j]);
        if (final[j] == -1)printf("%-4s | ", "N/A"); else printf("%-4.1f | ", final[j]);
        if (lab1[j] != -1 && final[j] != -1) printf("%-4.1f |\n", tinhTB(j));
        else printf("%-4s |\n", "N/A");
    }
    printf(CYAN"+-----+------------+---------------------+------+------+------+------+------+------+------+\n"RESET);
}

float NhapMotCotDiem(char tenCot[], float diemCu) {
    char s[50];
    float diem;
    while(1) {
        if (diemCu != -1) {
            printf("Nhap %s (Hien tai: %.1f, Nhan ENTER de giu nguyen, 'q' de dung): ", tenCot, diemCu);
        } else {
            printf("Nhap %s (Go 'q' de dung) : ", tenCot);
        }
		if (fgets(s, sizeof(s), stdin) == NULL) continue;
        s[strcspn(s, "\n")] = '\0'; 
        if (strlen(s) == 0 && diemCu != -1) {
            return diemCu; 
        }
        if (strcmp(s, "q") == 0 || strcmp(s, "Q") == 0) {
            return -2.0; 
        }
        if (strcmp(s, "0") == 0 || strcmp(s, "0.0") == 0) {
            return 0.0;
        }
        diem = atof(s);
        if (diem > 0.0 && diem <= 10.0) {
            return diem;
        }
		printf(RED " (!) Du lieu khong hop le. Vui long thu lai!\n" RESET);
        Sleep(800);
        xoaDongVuaNhap(); 
        xoaDongVuaNhap();
    }
}

int NhapDiemMotSV(int k) {
    float tam;
    fflush(stdin); 
    printf(HIGHLIGHT_YELLOW "\n>>> CAP NHAT DIEM CHO: %s\n" RESET, tenSV[k]);
    tam = NhapMotCotDiem("Lab1", lab1[k]);
    if (tam == -2.0) return 0;
    lab1[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + Lab1 : " GREEN "%.1f" RESET "\n", lab1[k]);
    tam = NhapMotCotDiem("Lab2", lab2[k]);
    if (tam == -2.0) return 0;
    lab2[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + Lab2 : " GREEN "%.1f" RESET "\n", lab2[k]);
	tam = NhapMotCotDiem("Pt1", pt1[k]);
    if (tam == -2.0) return 0;
    pt1[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + PT1  : " GREEN "%.1f" RESET "\n", pt1[k]);
    tam = NhapMotCotDiem("Pt2", pt2[k]);
    if (tam == -2.0) return 0;
    pt2[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + PT2  : " GREEN "%.1f" RESET "\n", pt2[k]);
    tam = NhapMotCotDiem("Pre", pre[k]);
    if (tam == -2.0) return 0;
    pre[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + Pre  : " GREEN "%.1f" RESET "\n", pre[k]);
    tam = NhapMotCotDiem("Final", final[k]);
    if (tam == -2.0) return 0;
    final[k] = tam;
    luuFile();
    xoaDongVuaNhap();
    printf("   + Final: " GREEN "%.1f" RESET "\n", final[k]);
    if (lab1[k] != -1 && lab2[k] != -1 && pt1[k] != -1 && pt2[k] != -1 && pre[k] != -1 && final[k] != -1) {
        printf("   ==> " BOLD_CYAN "DIEM TRUNG BINH : %.1f" RESET "\n", tinhTB(k));
        printf(YELLOW "\nDa hoan thanh cap nhat full diem cho sinh vien nay!" RESET);
    } else {
        printf(YELLOW "\nDa luu tam thoi cac cot diem cho sinh vien nay." RESET);
    }
    Sleep(1000);
    return 1; 
}

void Nhap() {
    int start, end;
    char line[100];

    while(1) {
        system("cls");
        if (menuHocPhan() == 0) return; 
        
        while(1) {
            system("cls");
            printf(BOLD_CYAN);
            sprintf(line, "--- DU LIEU DIEM: %s ---", tenHp);
            printCenter(line);
            printf(RESET);
            DanhSachSV(); 
            
            printf("\n" YELLOW "CHON KHOANG STT MUON NHAP (1-%d)" RESET " - Nhap 0 de DOI MON: ", n);
            if (scanf("%d", &start) != 1) {
                while(getchar() != '\n'); continue;
            }
            if (start == 0) break;
            
            if (scanf("%d", &end) != 1) {
                while(getchar() != '\n'); continue;
            }
            
            if (start > 0 && end <= n && start <= end) {
                int i;
                for (i = start - 1; i <= end - 1; i++) {
                    system("cls");
                    printf(CYAN "Dang nhap diem cho STT %d: %s\n" RESET, i + 1, tenSV[i]);
                    
                    if (lab1[i] != -1 && lab2[i] != -1 && pt1[i] != -1 && 
                        pt2[i] != -1 && pre[i] != -1 && final[i] != -1) {
                        printf(RED "\n [!] Sinh vien %s da co du diem! Dang chuyen..." RESET, tenSV[i]);
                        Sleep(400);
                        continue;
                    } else {
                        if (NhapDiemMotSV(i) == 0) {
                            printf(RED "\n[THONG BAO] Da bo qua va luu diem tam thoi cho sinh vien nay!" RESET);
                            Sleep(800);
                            
                            continue; 
						}
                    }
                }
                system("cls");
                DanhSachSV();
                printf(GREEN "\n[THANH CONG] Da duyet qua het cac sinh vien tu STT %d den %d!" RESET, start, end);
                printf("\nNhan phim bat ki de tiep tuc...");
                getch();
            } else {
                printf(RED "\nKhoang STT khong hop le! Thu lai." RESET);
                getch();
            }
        }
    }
}

void XemDiemMotSV(char maTruyenVao[], char monSua[], int cotSua) {
    char nhap[50], nhapUP[50];
    int i, j, k, d, cheDoXemDocLap = 0; 
    float l1, l2, p1, p2, pr, fi, tb;
    int indexGoc[40];
    int soLuongTimThay = 0;
    if (strcmp(maTruyenVao, "") == 0) {
        cheDoXemDocLap = 1; 
    } else {
        strcpy(nhap, maTruyenVao); 
    }
    while (1) {
        if (cheDoXemDocLap) {
            system("cls");
            printf("\n");
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
            printCenter(BOLD_CYAN "|         TRA CUU DIEM MOT SINH VIEN       |" RESET);
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);        
            while (1) {
				soLuongTimThay = 0; 
                printf("\n");
                for(d = 0; d < 40; d++) printf(" ");
                printf(YELLOW "Nhap MSSV hoac TEN SINH VIEN (0 de huy): " RESET);
                fflush(stdin);
                fgets(nhap, sizeof(nhap), stdin);
                nhap[strcspn(nhap, "\n")] = '\0';
                if (strcmp(nhap, "0") == 0) return;
                if (strlen(nhap) == 0) { xoaDongVuaNhap(); continue; }
                k = binary_search(nhap); 
                if (k != -1) {
                    break; 
                }
				strcpy(nhapUP, nhap);
                strupr(nhapUP);
                for (i = 0; i < n; i++) {
                    char tChinh[50];
                    layTenChinh(tenSV[i], tChinh); 
                    strupr(tChinh);
                    if (strstr(tChinh, nhapUP) != NULL) {
                        indexGoc[soLuongTimThay] = i;
                        soLuongTimThay++;
                    }
                }
                if (soLuongTimThay == 0) {
                    xoaDongVuaNhap();
                    continue; 
                }
                if (soLuongTimThay == 1) {
                    k = indexGoc[0];
                    break;
                }
                char tempRow[200]; 
                printf("\n");
                sprintf(tempRow, GREEN "Tim thay %d sinh vien phu hop:" RESET, soLuongTimThay);
                printCenter(tempRow);
                printCenter("+-----+---------------+--------------------------------+");
                printCenter("| STT |      MSSV     |           HO VA TEN            |");
                printCenter("+-----+---------------+--------------------------------+");
                for (i = 0; i < soLuongTimThay; i++) {
                    int idx = indexGoc[i];
                    sprintf(tempRow, "| %-3d | %-13s | %-30s |", i + 1, maSV[idx], tenSV[idx]);
                    printCenter(tempRow);
                }   
                printCenter("+-----+---------------+--------------------------------+");
				int chon;
				while (1) {
    				printf("\n");
					printf("                     " BOLD_CYAN "Nhap STT sinh vien muon xem (0 de nhap lai): " RESET);
    				if (scanf("%d", &chon) != 1) {
        				while (getchar() != '\n');
        				xoaDongVuaNhap(); 
        				continue;
    				}
					if (chon == 0) break;
    				if (chon >= 1 && chon <= soLuongTimThay) {
        				k = indexGoc[chon - 1];
        				break;
    				}
    				xoaDongVuaNhap();
				}   
                if (chon == 0) {
                    cheDoXemDocLap = 2; 
                    break;
                }
                break; 
            }
            if (cheDoXemDocLap == 2) { cheDoXemDocLap = 1; continue; }
        } else {
            k = binary_search(nhap);
            if (k == -1) return;
        }
        system("cls");
        printf("\n");
        if (!cheDoXemDocLap) {
            printf("\n" GREEN "--- KET QUA SAU KHI SUA (DIEM DOI MAU XANH) ---" RESET "\n");
        }
        printf("\n" GREEN "----- THONG TIN SINH VIEN -----" RESET "\n");
        printf(YELLOW "   MSSV      : " RESET "%s\n", maSV[k]);
        printf(YELLOW "   HO VA TEN : " RESET "%s\n", tenSV[k]);
        printf("\n");
        printCenter("------------------- BANG DIEM CUA SINH VIEN -------------------");
        printf("\n");
        printCenter("+-------------------+------+------+------+------+------+-------+------+");
        printCenter("|     Hoc phan      | Lab1 | Lab2 | PT1  | PT2  | Pre  | Final |  TB  |");
        printCenter("+-------------------+------+------+------+------+------+-------+------+");
        for (i = 0; i < soHp; i++) {
            char file[50];
            char row[250];
            sprintf(file, "%s.txt", dsHocPhan[i]);
            FILE *f = fopen(file, "r");
            int found = 0;
            if (f) {
                int sl;
                if (fscanf(f, "%d\n", &sl) == 1) {
                    char maF[20], tenTam[100];
                    for (j = 0; j < sl; j++) {
                        if (fscanf(f, "%s ", maF) != 1) break;
                        if (fscanf(f, "%[^0-9-]", tenTam) != 1) break; 
                        if (fscanf(f, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                            int len = strlen(tenTam);
                            while(len > 0 && tenTam[len-1] == ' ') {
                                tenTam[len-1] = '\0';
                                len--;
                            }
                            if (strcmp(maF, maSV[k]) == 0) { found = 1; break; }
                        }
                    }
                }
                fclose(f);
            }
            if (found) {
                char sL1[30], sL2[30], sP1[30], sP2[30], sPr[30], sFi[30], sTb[30];
                int laMonSua = (strcmp(dsHocPhan[i], monSua) == 0);
                if (l1 == -1.0) strcpy(sL1, "N/A "); 
                else if (laMonSua && cotSua == 1) sprintf(sL1, GREEN "%-4.1f" RESET, l1); else sprintf(sL1, "%-4.1f", l1);
                if (l2 == -1.0) strcpy(sL2, "N/A "); 
                else if (laMonSua && cotSua == 2) sprintf(sL2, GREEN "%-4.1f" RESET, l2); else sprintf(sL2, "%-4.1f", l2);
                if (p1 == -1.0) strcpy(sP1, "N/A "); 
                else if (laMonSua && cotSua == 3) sprintf(sP1, GREEN "%-4.1f" RESET, p1); else sprintf(sP1, "%-4.1f", p1);
                if (p2 == -1.0) strcpy(sP2, "N/A "); 
                else if (laMonSua && cotSua == 4) sprintf(sP2, GREEN "%-4.1f" RESET, p2); else sprintf(sP2, "%-4.1f", p2);
                if (pr == -1.0) strcpy(sPr, "N/A  "); 
                else if (laMonSua && cotSua == 5) sprintf(sPr, GREEN "%-5.1f" RESET, pr); else sprintf(sPr, "%-5.1f", pr);
                if (fi == -1.0) strcpy(sFi, "N/A  "); 
                else if (laMonSua && cotSua == 6) sprintf(sFi, GREEN "%-5.1f" RESET, fi); else sprintf(sFi, "%-5.1f", fi);
                if (l1 == -1.0 || l2 == -1.0 || p1 == -1.0 || p2 == -1.0 || pr == -1.0 || fi == -1.0) {
                    strcpy(sTb, "N/A ");
                } else {
                    tb = (l1 + l2 + p1 + p2 + pr + fi) / 6.0;
                    sprintf(sTb, "%-4.1f", tb);
                }
                sprintf(row, "| %-17s | %-4s | %-4s | %-4s | %-4s | %-5s | %-5s | %-4s |", 
                        dsHocPhan[i], sL1, sL2, sP1, sP2, sPr, sFi, sTb);
            } else {
                sprintf(row, "| %-17s | %-4s | %-4s | %-4s | %-4s | %-4s | %-5s | %-4s |", 
                        dsHocPhan[i], "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A");
            }
            printCenter(row);
        }
        printCenter("+-------------------+------+------+------+------+------+-------+------+");
        printf("\n");
        if (!cheDoXemDocLap) return; 
        printCenter(YELLOW "Nhan phim bat ky de tiep tuc tra cuu..." RESET);
        getch();
    }
}

void XemDiemMotLopHocPhan() {
    char line[100];
    while (1) {
        if (HocPhan() == 0) return; 
        system("cls");
        printf(GREEN);
        sprintf(line, "--- DU LIEU DIEM: %s ---", tenHp);
        printCenter(line);
        printf(RESET);
        DanhSachSV(); 
        printf(YELLOW "\nNhan phim bat ky de quay lai chon hoc phan..." RESET);
        getch(); 
    }
}

void Xem() {
    int ch;
    do {
        system("cls");
        int d;
        for(d = 0; d < 10; d++) printf("\n");
        printf(GREEN);
        printCenter("+-------------------------------------------+");
        printCenter("|               MUC XEM DIEM                |");
        printCenter("+-------------------------------------------+");
        printf(RESET);
        printCenter("|  1. Xem diem mot sinh vien                |");
        printCenter("|  2. Xem diem mot lop hoc phan             |");
        printCenter("|  0. Quay lai Menu chinh                   |");
        printf(GREEN);
        printCenter("+-------------------------------------------+");
        printf(RESET);
        printf("\n");
        for(d = 0; d < 48; d++) printf(" ");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n'); continue;
        }
        switch(ch) {
            case 1: 
                XemDiemMotSV("", "", 0); 
                break;
            case 2: 
                XemDiemMotLopHocPhan(); 
                break;
        }
    } while (ch != 0);
}

void inBangMotSV(int i, int cotSua) {
    char line[150]; 
    int j;
    float diem[6] = {lab1[i], lab2[i], pt1[i], pt2[i], pre[i], final[i]};
    printf(YELLOW "   MSSV      : " RESET "%s\n", maSV[i]);
    printf(YELLOW "   HO VA TEN : " RESET "%s\n", tenSV[i]);
    printf("\n"); 
    printCenter(CYAN "-------------------- BANG DIEM CUA SINH VIEN -------------------" RESET);
    printCenter("+------------+------+------+------+------+------+-------+-------+");
    printCenter("|  Hoc phan  | Lab1 | Lab2 | PT1  | PT2  | Pre  | Final |  TB   |");
    printCenter("+------------+------+------+------+------+------+-------+-------+");
    char dataRow[200];
    char temp[50];
    sprintf(dataRow, "| %-10s | ", tenHp);
    for (j = 0; j < 6; j++) {
        if (diem[j] == -1) {
            strcat(dataRow, "N/A  | ");
        } else {
            if (cotSua == j + 1) {
                sprintf(temp, GREEN "%-4.1f" RESET " | ", diem[j]);
            } else {
                sprintf(temp, "%-4.1f | ", diem[j]);
            }
            strcat(dataRow, temp);
        }
    }
    int daydu = 1;
    for (j = 0; j < 6; j++) {
        if (diem[j] == -1) daydu = 0;
    }
    if (daydu) {
        sprintf(temp, "%-5.1f |", tinhTB(i));
    } else {
        sprintf(temp, "%-5s |", "N/A");
    }
    strcat(dataRow, temp);
    printCenter(dataRow);
    printCenter("+------------+------+------+------+------+------+-------+-------+");
}

int ChuaNhapDiem(int i) {
	if (lab1[i] == -1 && lab2[i] == -1 && pt1[i] == -1 && pt2[i] == -1 && pre[i] == -1 && final[i] == -1 ) {
		return 1;
	}
	return 0;
}

void Sua() {
    char nhapTimKiem[100]; 
    char tuKhoaUp[100];
    char ma[20];
    char chonMon[50];
    int chonCot, tiep;
    int i, j, k, d;
    int indexGoc[100];     
    int soLuongTimThay;
    int chon; 

    while (1) {
        while (1) {
            system("cls");
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
            printCenter(BOLD_CYAN "|          CHINH SUA DIEM SINH VIEN        |" RESET);
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);      
            printf("\n");
            for(d = 0; d < 40; d++) printf(" ");
            printf(YELLOW "Nhap MSSV hoac TEN SINH VIEN (0 de huy): " RESET);
            fflush(stdin);
            fgets(nhapTimKiem, sizeof(nhapTimKiem), stdin);
            nhapTimKiem[strcspn(nhapTimKiem, "\n")] = '\0';

            if (strcmp(nhapTimKiem, "0") == 0) return;
            if (strlen(nhapTimKiem) == 0) continue;
            k = binary_search(nhapTimKiem); 
            if (k != -1) {
                strcpy(ma, maSV[k]); 
                break; 
            }
            strcpy(tuKhoaUp, nhapTimKiem);
            strupr(tuKhoaUp);

            soLuongTimThay = 0;
            for (i = 0; i < n; i++) { 
                char tChinh[50];
                layTenChinh(tenSV[i], tChinh); 
                strupr(tChinh);

                if (strstr(tChinh, tuKhoaUp) != NULL) {
                    indexGoc[soLuongTimThay] = i;
                    soLuongTimThay++;
                }
            }

            if (soLuongTimThay == 0) {
                printf("\n");
                printCenter(RED "(!) Khong tim thay sinh vien nao phu hop. Vui long nhap lai!\n" RESET);
                Sleep(1200);
                continue;
            }
            if (soLuongTimThay == 1) {
                k = indexGoc[0];
                strcpy(ma, maSV[k]);
                break;
            }
            printf("\n");
            char tieuDe[100];
            sprintf(tieuDe, GREEN "Tim thay %d sinh vien phu hop:" RESET, soLuongTimThay);
            printCenter(tieuDe);
            
            printCenter(BOLD_CYAN "+-----+---------------+-------------------------------------+" RESET);
            printCenter(BOLD_CYAN "| STT |      MSSV     |              HO VA TEN              |" RESET);
            printCenter(BOLD_CYAN "+-----+---------------+-------------------------------------+" RESET);
            for (i = 0; i < soLuongTimThay; i++) {
                char row[150];
                sprintf(row, "| %-3d | %-13s | %-35s |", i + 1, maSV[indexGoc[i]], tenSV[indexGoc[i]]);
                printCenter(row);
            }
            printCenter(BOLD_CYAN "+-----+---------------+-------------------------------------+" RESET);
            int hopLe = 0;
            while (1) {
                printf("\n");
                for(d = 0; d < 22; d++) printf(" ");
                printf(CYAN "Nhap STT sinh vien muon sua (0 de nhap lai): " RESET);
                if (scanf("%d", &chon) != 1) {
                    while (getchar() != '\n'); 
                    xoaDongVuaNhap();
                    continue;
                }
                
                if (chon == 0) break; 
                
                if (chon >= 1 && chon <= soLuongTimThay) {
                    k = indexGoc[chon - 1]; 
                    strcpy(ma, maSV[k]);   
                    hopLe = 1;
                    break;
                }
                xoaDongVuaNhap();
            }
            if (hopLe) break; 
        }
        
        int daCoItNhatMotDauDiem = 0;
        for (i = 0; i < soHp; i++) {
            char fileCheck[100];
            sprintf(fileCheck, "%s.txt", dsHocPhan[i]);
            FILE *fCheck = fopen(fileCheck, "r");
            if (fCheck) {
                int slCheck;
                if (fscanf(fCheck, "%d\n", &slCheck) == 1) {
                    char maF[20], tenT[100];
                    float l1, l2, p1, p2, pr, fi;
                    for (j = 0; j < slCheck; j++) {
                        if (fscanf(fCheck, "%s ", maF) != 1) break;
                        if (fscanf(fCheck, "%[^-0-9]", tenT) != 1) break;
                        if (fscanf(fCheck, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                            if (strcmp(maF, ma) == 0) {
                                if (l1 != -1.0 || l2 != -1.0 || p1 != -1.0 || p2 != -1.0 || pr != -1.0 || fi != -1.0) {
                                    daCoItNhatMotDauDiem = 1;
                                }
                                break;
                            }
                        }
                    }
                }
                fclose(fCheck);
            }
            if (daCoItNhatMotDauDiem) break; 
        }
        if (!daCoItNhatMotDauDiem) {
            system("cls");
            printf("\n\n\n");
            printCenter(RED "(!) Sinh vien nay chua duoc nhap bat ky diem nao. Khong the sua!" RESET);
            fflush(stdout); 
            Sleep(1500); 
            continue;
        }
        while (1) {
            system("cls");
            XemDiemMotSV(ma, "", 0);
            int indexMonCanSua = -1;
            while (1) {
                printf(YELLOW "Nhap TEN HOC PHAN muon sua: " RESET);
                fflush(stdin);
                fgets(chonMon, sizeof(chonMon), stdin);
                chonMon[strcspn(chonMon, "\n")] = '\0';
                strupr(chonMon);
                
                for (i = 0; i < soHp; i++) {
                    char tempHp[50];
                    strcpy(tempHp, dsHocPhan[i]);
                    strupr(tempHp);
                    if (strcmp(tempHp, chonMon) == 0) { 
                        indexMonCanSua = i; 
                        break; 
                    }
                }
                if (indexMonCanSua != -1) break;
                xoaDongVuaNhap();
            }
            
            char fileSua[100];
            sprintf(fileSua, "%s.txt", dsHocPhan[indexMonCanSua]);
            int slTam;
            char maTam[40][20], tenTam[40][100];
            float bL1[40], bL2[40], bP1[40], bP2[40], bPr[40], bFi[40];
            float diemHienTai = -1.0;
            int timThaySVTrongFile = 0;

            FILE *fIn = fopen(fileSua, "r");
            if (!fIn) {
                if (strcmp(dsHocPhan[indexMonCanSua], "CAU TRUC DU LIEU") == 0) {
                    fIn = fopen("CTDL.txt", "r");
                    if (fIn) strcpy(fileSua, "CTDL.txt");
                }
            }

            if (fIn) {
                if (fscanf(fIn, "%d\n", &slTam) == 1) {
                    for (i = 0; i < slTam; i++) {
                        if (fscanf(fIn, "%s ", maTam[i]) != 1) break;
                        if (fscanf(fIn, "%[^-0-9]", tenTam[i]) != 1) break;
                        if (fscanf(fIn, "%f %f %f %f %f %f\n", &bL1[i], &bL2[i], &bP1[i], &bP2[i], &bPr[i], &bFi[i]) == 6) {
                            if (strcmp(maTam[i], ma) == 0) {
                                timThaySVTrongFile = 1;
                                k = i; 
                            }
                        }
                    }
                }
                fclose(fIn);
            }

            if (!timThaySVTrongFile) {
                printf(RED "(!) Sinh vien khong co trong lop hoc phan %s.\n" RESET, dsHocPhan[indexMonCanSua]);
                getch();
                continue; 
            }

            printf(GREEN "CHON COT CAN SUA CUA MON %s:" RESET "\n", dsHocPhan[indexMonCanSua]);
            printf(MAGENTA "1.Lab1   2.Lab2   3.PT1   4.PT2   5.Pre   6.Final" RESET "\n");
            
            while (1) {
                printf(CYAN "Lua chon cot (1-6): " RESET);
                if (scanf("%d", &chonCot) != 1) { 
                    while(getchar() != '\n'); 
                    xoaDongVuaNhap(); 
                    continue; 
                }
                if (chonCot < 1 || chonCot > 6) {
                    xoaDongVuaNhap();
                    continue;
                }
                if (chonCot == 1) diemHienTai = bL1[k];
                else if (chonCot == 2) diemHienTai = bL2[k];
                else if (chonCot == 3) diemHienTai = bP1[k];
                else if (chonCot == 4) diemHienTai = bP2[k];
                else if (chonCot == 5) diemHienTai = bPr[k];
                else if (chonCot == 6) diemHienTai = bFi[k];
                
                if (diemHienTai == -1.0) {
                    xoaDongVuaNhap(); 
                    printf(RED "    (!) Cot nay chua co diem (N/A), khong the sua! Vui long chon cot khac.\n" RESET);
                    Sleep(1000);
                    xoaDongVuaNhap(); 
                    continue; 
                }
                break; 
            }

            printf("\n");
            fflush(stdin); 
            
            float diem = NhapMotCotDiem("diem moi", diemHienTai); 
            if (diem == -2.0) {
                printf(RED "\n[THONG BAO] Da huy thao tac sua!\n" RESET);
                Sleep(1200); break; 
            }

            switch(chonCot) {
                case 1: bL1[k] = diem; break;
                case 2: bL2[k] = diem; break;
                case 3: bP1[k] = diem; break;
                case 4: bP2[k] = diem; break;
                case 5: bPr[k] = diem; break;
                case 6: bFi[k] = diem; break;
            }
            int indexSVDongBo = binary_search(ma); 
            if (indexSVDongBo != -1) {
                strcpy(tenTam[k], tenSV[indexSVDongBo]); 
            }
            char fileXuatChuan[100];
            sprintf(fileXuatChuan, "%s.txt", dsHocPhan[indexMonCanSua]);
            FILE *fOut = fopen(fileXuatChuan, "w");
            if (fOut) {
                fprintf(fOut, "%d\n", slTam);
                for (i = 0; i < slTam; i++) {
                    fprintf(fOut, "%s %s%.1f %.1f %.1f %.1f %.1f %.1f\n", 
                            maTam[i], tenTam[i], bL1[i], bL2[i], bP1[i], bP2[i], bPr[i], bFi[i]);
                }
                fclose(fOut);
                if (strcmp(fileSua, "CTDL.txt") == 0) {
                    remove("CTDL.txt");
                }
            }

            if (indexSVDongBo != -1) {
                switch(chonCot) {
                    case 1: lab1[indexSVDongBo] = diem; break;
                    case 2: lab2[indexSVDongBo] = diem; break;
                    case 3: pt1[indexSVDongBo] = diem; break;
                    case 4: pt2[indexSVDongBo] = diem; break;
                    case 5: pre[indexSVDongBo] = diem; break;
                    case 6: final[indexSVDongBo] = diem; break;
                }
            }

            system("cls");
            XemDiemMotSV(ma, dsHocPhan[indexMonCanSua], chonCot); 
            printf(GREEN "[THANH CONG] Da cap nhat va dong bo vao file moi hoc phan!\n" RESET);
            break; 
        }
        printf("\n");
        char dongHuongDan[150];
        sprintf(dongHuongDan, "%sBam [1] de tiep tuc sua SV khac | Bam phim bat ky de ve Menu chinh%s", BOLD_CYAN, RESET);
        printCenter(dongHuongDan);
        
        printf("\n");
        for(d = 0; d < 48; d++) printf(" "); 
        printf(GREEN "LUA CHON: " RESET);
        
        if (scanf("%d", &tiep) != 1) {
            while (getchar() != '\n');
            tiep = 0; 
        }
        if (tiep != 1) break;
    }
}

float temp_dtb[mx];

void swap1 (float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void swap (int a, int b) {
    char tempMaSV[20];
    strcpy(tempMaSV, maSV[a]);
    strcpy(maSV[a],maSV[b]);
    strcpy(maSV[b], tempMaSV);

    char tempTenSV[30];
    strcpy(tempTenSV, tenSV[a]);
    strcpy(tenSV[a],tenSV[b]);
    strcpy(tenSV[b], tempTenSV);

    swap1(&lab1[a], &lab1[b]);
    swap1(&lab2[a], &lab2[b]);
    swap1(&pt1[a], &pt1[b]);
    swap1(&pt2[a], &pt2[b]);
    swap1(&pre[a], &pre[b]);
    swap1(&final[a], &final[b]);
}

void QuickSort (int left , int right, int chon) {
    int i = left, j = right;
    float pivot = temp_dtb[(left + right)/2];
    do {
        if (chon == 1) {
            while (temp_dtb[i] < pivot) 
                i++;
            while (temp_dtb[j] > pivot)
                j--;
        } else if (chon == 2) {
            while (temp_dtb[i] > pivot) 
                i++;
            while (temp_dtb[j] < pivot)
                j--;
        }
        if (i <= j) {
            swap(i,j);
            swap1(&temp_dtb[i], &temp_dtb[j]);
            i++; 
            j--;
        }
    } while (i<=j);
    if (left < j) QuickSort(left,j,chon);
    if (i < right) QuickSort(i,right,chon);
}

void SapXep() {
    char line[100];
    int chon, i, j, k;
    
    while(1) {
        if (HocPhan() == 0) return; 
        
        while(1) {
            system("cls");
            int d;
            for(d = 0; d < 5; d++) printf("\n");
            printf(BOLD_CYAN);
            sprintf(line, "--- SAP XEP (Hoc phan: %s) ---", tenHp);
            printCenter(line);
            printf(RESET);
            printCenter("+------------------------------------------+");
            printCenter("|  1. Diem trung binh Tang dan             |");
            printCenter("|  2. Diem trung binh Giam dan             |");
            printCenter("|  0. Quay lai Chon mon hoc                |");
            printCenter("+------------------------------------------+");
            printf("\n");
            for(d = 0; d < 48; d++) printf(" ");
            printf("Chon thao tac: ");
            
            if (scanf("%d", &chon) != 1) {
                while (getchar() != '\n'); 
                continue;
            }
            if (chon == 0) break; 
            
            if (chon == 1 || chon == 2) {
                int bieuDienThucTe = 0;
                for (i = 0; i < n; i++) {
                    float diem[6] = {lab1[i], lab2[i], pt1[i], pt2[i], pre[i], final[i]};
                    int daydu = 1;
                    for (j = 0; j < 6; j++) {
                        if (diem[j] == -1) { daydu = 0; break; }
                    }
                    if (daydu) {
                        temp_dtb[i] = tinhTB(i);
                        bieuDienThucTe++;
                    } else {
                        if (chon == 1) {
                            temp_dtb[i] = 99.0; 
						} else {
                            temp_dtb[i] = -99.0;
                        }
                    }
                }
                for (i = 0; i < n - 1; i++) {
                    for (j = i + 1; j < n; j++) {
                        int logic_day_xuong = 0;
                        if (chon == 1 && temp_dtb[i] == 99.0 && temp_dtb[j] != 99.0) logic_day_xuong = 1;
                        if (chon == 2 && temp_dtb[i] == -99.0 && temp_dtb[j] != -99.0) logic_day_xuong = 1;

                        if (logic_day_xuong) {
                            swap(i, j);
                            swap1(&temp_dtb[i], &temp_dtb[j]);
                        }
                    }
                }
                if (bieuDienThucTe > 1) {
                    QuickSort(0, bieuDienThucTe - 1, chon);
                }
                system("cls");
                printf("\n" BOLD_CYAN "-------------------------------------------- BANG DIEM MON %s -----------------------------------------" RESET "\n\n", tenHp);
                printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);
                printf("| STT |  Ma so SV  |       Ho va ten     | Lab1 | Lab2 | PT1  | PT2  |  Pre  | Final |  TB   | XEP LOAI |\n");
                printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);
                
                for (i = 0; i < n; i++) {
                    float diem[6] = {lab1[i], lab2[i], pt1[i], pt2[i], pre[i], final[i]};
                    int daydu = 1;
                    for (j = 0; j < 6; j++) {
                        if (diem[j] == -1) { daydu = 0; break; }
                    }
                    printf("| %-3d | %-10s | %-19.19s | ", i + 1, maSV[i], tenSV[i]);
                    for (j = 0; j < 6; j++) {
                        if (diem[j] == -1) {
                            if (j >= 4) printf("%-5s | ", "N/A"); 
                            else printf("%-4s | ", "N/A");      
                        } else {
                            if (j >= 4) printf("%-5.1f | ", diem[j]);
                            else printf("%-4.1f | ", diem[j]);
                        }
                    }
                    if (daydu) {
                        float tb = tinhTB(i);
                        char xl = xepLoai(tb);   
                        printf("%-5.1f |    %-5c |\n", tb, xl);           
                    } else {
                        printf("%-5s |    %-5s |\n", "N/A", "N/A");
                    }
                }
                printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);

                printf("\n");
                printCenter(GREEN "=> DA SAP XEP THANH CONG!" RESET);
                printCenter("Nhan phim bat ky de quay lai menu sap xep...");
                getch();
                docFile(); 
            }
        }
    }
}

void ThongKeHocVu() {
    int i, j;
    system("cls");
    printCenter(MAGENTA "=========================================================================" RESET);
    printCenter(MAGENTA "|                          BAO CAO THONG KE HOC VU                      |" RESET);
    printCenter(MAGENTA "=========================================================================" RESET);
    printf("\n");

    if (soHp == 0) {
        printCenter(RED "Chua co du lieu hoc phan nao de thong ke!" RESET);
        getch();
        return;
    }

   
    for (i = 0; i < soHp; i++) {
        char file[50];
        sprintf(file, "%s.txt", dsHocPhan[i]);
        FILE *f = fopen(file, "r");

        if (!f) {
            printf(YELLOW " [!] Mon %-10s: Chi tiet file du lieu chua duoc khoi tao.\n" RESET, dsHocPhan[i]);
            printf("-------------------------------------------------------------------------\n");
            continue;
        }

        int sl;
        if (fscanf(f, "%d\n", &sl) != 1 || sl == 0) {
            printf(YELLOW " [!] Mon %-10s: Mon hoc nay hien chua co sinh vien nao.\n" RESET, dsHocPhan[i]);
            printf("-------------------------------------------------------------------------\n");
            fclose(f);
            continue;
        }

        int demA = 0, demB = 0, demC = 0, demD = 0, demF = 0;
        int coDiem = 0; 
        float maxTB = -1.0;
        char sTTThuKhoa[20] = "", sTenThuKhoa[50] = "";
        char dsYeuMa[40][20], dsYeuTen[40][50];
        float dsYeuDiem[40];
        int demYeu = 0;

        char maF[20], tenTam[100];
        float l1, l2, p1, p2, pr, fi;

        for (j = 0; j < sl; j++) {
            if (fscanf(f, "%s ", maF) != 1) break;
            if (fscanf(f, "%[^0-9]", tenTam) != 1) break;
            if (fscanf(f, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                
                if (l1 != -1 && l2 != -1 && p1 != -1 && p2 != -1 && pr != -1 && fi != -1) {
                    float tb = (l1 + l2 + p1 + p2 + pr + fi) / 6.0;
                    coDiem++;
                    char xl = xepLoai(tb);
                    if (xl == 'A') demA++;
                    else if (xl == 'B') demB++;
                    else if (xl == 'C') demC++;
                    else if (xl == 'D') demD++;
                    else demF++;
                    if (tb > maxTB) {
                        maxTB = tb;
                        strcpy(sTTThuKhoa, maF);
                        strcpy(sTenThuKhoa, tenTam);
                    }
                    if (tb < 4.0 || fi < 4.0) {
                        strcpy(dsYeuMa[demYeu], maF);
                        strcpy(dsYeuTen[demYeu], tenTam);
                        dsYeuDiem[demYeu] = (tb < fi) ? tb : fi;
                        demYeu++;
                    }
                }
            }
        }
        fclose(f);
        printf(BOLD_CYAN " HOC PHAN: %s" RESET " (Tong so: %d SV | Da co diem: %d SV)\n", dsHocPhan[i], sl, coDiem);
        
        if (coDiem == 0) {
            printf(RED "   -> Mon nay chua co sinh vien nao duoc nhap day du diem.\n" RESET);
            printf("-------------------------------------------------------------------------\n");
            continue;
        }
        printf("   * Ty le hoc luc: " 
               GREEN "A: %.1f%%  " RESET 
               CYAN "B: %.1f%%  " RESET 
               BOLD_CYAN "C: %.1f%%  " RESET 
               YELLOW "D: %.1f%%  " RESET 
               RED "F: %.1f%%\n" RESET,
               (demA * 100.0) / coDiem, 
               (demB * 100.0) / coDiem, 
               (demC * 100.0) / coDiem, 
               (demD * 100.0) / coDiem, 
               (demF * 100.0) / coDiem);
        printf("   * Thu khoa mon: " YELLOW "%s" RESET " - MSSV: %s - Diem TB: " YELLOW "%.1f" RESET "\n", 
               sTenThuKhoa, sTTThuKhoa, maxTB);
        if (demYeu > 0) {
            printf("   * " RED "CANH BAO HOC LAI (%d SV):" RESET "\n", demYeu);
            for (j = 0; j < demYeu; j++) {
                printf("     + %s - %-18s (Diem thap: %.1f)\n", dsYeuMa[j], dsYeuTen[j], dsYeuDiem[j]);
            }
        } else {
            printf("   * Canh bao hoc lai: " GREEN "Khong co sinh vien nguy co rot mon." RESET "\n");
        }
        printf("-------------------------------------------------------------------------\n");
    }

    printf("\n");
    printCenter(YELLOW "Nhan phim ENTER de chon HOC PHAN..." RESET);
    getch();
}

void InBangDiemToanLop() {
    system("cls");
    printCenter("\n" GREEN "---------------------------- BANG DIEM TONG HOP CUA LOP --------------------------------" RESET "\n\n");
    
    char dsMaSV[100][20];
    char dsTenSV[100][50];
    float dsCPA[100];
    int soMonHocCuaSV[100];
    int tongSoSV = 0;
    
    int i,j,k,m;
    for (i = 0; i < n; i++) {
        strcpy(dsMaSV[tongSoSV], maSV[i]);
        strcpy(dsTenSV[tongSoSV], tenSV[i]);
        dsCPA[tongSoSV] = 0;
        soMonHocCuaSV[tongSoSV] = 0;
        tongSoSV++;
    }

    for (m = 0; m < soHp; m++) {
        char fileMon[50];
        sprintf(fileMon, "%s.txt", dsHocPhan[m]);
        FILE *fMon = fopen(fileMon, "r");
        if (!fMon) continue;
        
        int slSVInFile;
        if (fscanf(fMon, "%d\n", &slSVInFile) != 1) {
            fclose(fMon);
            continue;
        }
        
        char maF[20], tenTam[100];
        float l1, l2, p1, p2, pr, fi;
        for (k = 0; k < slSVInFile; k++) {
            if (fscanf(fMon, "%s ", maF) != 1) break;
            if (fscanf(fMon, "%[^0-9]", tenTam) != 1) break;
            if (fscanf(fMon, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                
                if (l1 != -1 && l2 != -1 && p1 != -1 && p2 != -1 && pr != -1 && fi != -1) {
                    float tbMon = (l1 + l2 + p1 + p2 + pr + fi) / 6.0;
                    int s;
                    for (s = 0; s < tongSoSV; s++) {
                        if (strcmp(dsMaSV[s], maF) == 0) {
                            dsCPA[s] += tbMon;
                            soMonHocCuaSV[s]++;
                            break;
                        }
                    }
                }
            }
        }
        fclose(fMon);
    }
    
    for (i = 0; i < tongSoSV; i++) {
        if (soMonHocCuaSV[i] > 0) {
            dsCPA[i] = dsCPA[i] / soMonHocCuaSV[i];
        } else {
            dsCPA[i] = 0.0;
        }
    }
    for (i = 0; i < tongSoSV - 1; i++) {
        for (j = i + 1; j < tongSoSV; j++) {
            if (dsCPA[i] < dsCPA[j]) {
                char tempMa[20]; strcpy(tempMa, dsMaSV[i]); strcpy(dsMaSV[i], dsMaSV[j]); strcpy(dsMaSV[j], tempMa);
                char tempTen[50]; strcpy(tempTen, dsTenSV[i]); strcpy(dsTenSV[i], dsTenSV[j]); strcpy(dsTenSV[j], tempTen);
                float tempCPA = dsCPA[i]; dsCPA[i] = dsCPA[j]; dsCPA[j] = tempCPA;
                int tempMon = soMonHocCuaSV[i]; soMonHocCuaSV[i] = soMonHocCuaSV[j]; soMonHocCuaSV[j] = tempMon;
            }
        }
    }
    
    printf("+------+-----------+---------------------+-------------------+------------+\n");
    printf("| HANG |   MSSV    |       Ho Va Ten     |   DIEM TICH LUY   | SO MON HOC |\n");
    printf("+------+-----------+---------------------+-------------------+------------+\n");
    
    for (i = 0; i < tongSoSV; i++) {
        char xlTichLuy = ' ';
        if (soMonHocCuaSV[i] > 0) xlTichLuy = xepLoai(dsCPA[i]);
        
        if (i < 3 && dsCPA[i] >= 8.0) {
            printf("|  %-3d | %-9s | %-19s |     " GREEN "%-5.2f (%c)" RESET "     |     %-6d |\n", i + 1, dsMaSV[i], dsTenSV[i], dsCPA[i], xlTichLuy, soMonHocCuaSV[i]);
        } else if (dsCPA[i] < 4.0 && soMonHocCuaSV[i] > 0) {
            printf("|  %-3d | %-9s | %-19s |     " RED "%-5.2f (%c)" RESET "     |     %-6d |\n", i + 1, dsMaSV[i], dsTenSV[i], dsCPA[i], xlTichLuy, soMonHocCuaSV[i]);
        } else {
            printf("|  %-3d | %-9s | %-19s |     %-5.2f (%c)     |     %-6d |\n", i + 1, dsMaSV[i], dsTenSV[i], dsCPA[i], xlTichLuy, soMonHocCuaSV[i]);
        }
    }
    printf("+------+-----------+---------------------+-------------------+------------+\n");
    
    printf("\n" YELLOW "Nhan phim bat ky de quay lai bang diem chi tiet..." RESET);
    getch();
}

void In() {
    int ch;
    ThongKeHocVu(); 
    
    while (1) {
        if (HocPhan() == 0) return; 
        int loaiLoc = 0; 
        while(1) {
            int demA = 0, demB = 0, demC = 0, demD = 0, demF = 0;
            float maxTB = -1.0;
            char mssvThuKhoa[20] = "", tenThuKhoa[50] = "";
            char dsHocLaiMa[40][20], dsHocLaiTen[40][50];
            float dsHocLaiDiem[40];
            int demHocLai = 0;
            
            system("cls");
            printf("\n" GREEN "---------------------------------- BANG DIEM CHI TIET MON: %-5s -----------------------------------" RESET "\n\n", tenHp);
            
            if (loaiLoc == 1) printf(YELLOW " [CHE DO LOC]: Chi hien thi sinh vien Xep loai A\n\n" RESET);
            else if (loaiLoc == 2) printf(YELLOW " [CHE DO LOC]: Chi hien thi sinh vien Xep loai B\n\n" RESET);
            else if (loaiLoc == 3) printf(YELLOW " [CHE DO LOC]: Chi hien thi sinh vien Xep loai C\n\n" RESET);
            else if (loaiLoc == 4) printf(YELLOW " [CHE DO LOC]: Chi hien thi sinh vien Xep loai D\n\n" RESET);
            else if (loaiLoc == 5) printf(RED " [CHE DO LOC]: Chi hien thi sinh vien Xep loai F\n\n" RESET);

            printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n");
            printf("| STT|   MSSV    |           Ten       | L1   | L2   | PT1  | PT2  | Pre  | Fin  |  TB  | XEP LOAI |\n");
            printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n");
            
            int i, hienThiSTT = 1;
            int coSinhVienThoanMan = 0; 

            for (i = 0; i < n; i++) {
                int coDiem = (lab1[i] != -1 && lab2[i] != -1 && pt1[i] != -1 && pt2[i] != -1 && pre[i] != -1 && final[i] != -1);
                if (coDiem) {
                    float tb = tinhTB(i);
                    char xl = xepLoai(tb);
                    if(xl=='A') demA++; 
                    else if(xl=='B') demB++; 
                    else if(xl=='C') demC++; 
                    else if(xl=='D') demD++; 
                    else demF++;
                    
                    if (tb > maxTB) {
                        maxTB = tb;
                        strcpy(mssvThuKhoa, maSV[i]);
                        strcpy(tenThuKhoa, tenSV[i]);
                    }
                    if (tb < 4.0 || final[i] < 4.0) {
                        strcpy(dsHocLaiMa[demHocLai], maSV[i]);
                        strcpy(dsHocLaiTen[demHocLai], tenSV[i]);
                        dsHocLaiDiem[demHocLai] = (tb < final[i]) ? tb : final[i];
                        demHocLai++;
                    }
                }
            }

            for (i = 0; i < n; i++) {
                int coDiem = (lab1[i] != -1 && lab2[i] != -1 && pt1[i] != -1 && pt2[i] != -1 && pre[i] != -1 && final[i] != -1);
                float tb = coDiem ? tinhTB(i) : 0;
                char xl = coDiem ? xepLoai(tb) : ' ';
                
                if (loaiLoc == 1 && xl != 'A') continue;
                if (loaiLoc == 2 && xl != 'B') continue;
                if (loaiLoc == 3 && xl != 'C') continue;
                if (loaiLoc == 4 && xl != 'D') continue;
                if (loaiLoc == 5 && xl != 'F') continue;

                coSinhVienThoanMan = 1; 

                printf("| %-2d | %-9s | %-19s | ", hienThiSTT++, maSV[i], tenSV[i]);
                if(lab1[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", lab1[i]);
                if(lab2[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", lab2[i]);
                if(pt1[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pt1[i]);
                if(pt2[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pt2[i]);
                if(pre[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pre[i]);
                if(final[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", final[i]);
                
                if (coDiem) {
                    printf("%-4.1f |    %-5c |\n", tb, xl);     
                } else {
                    printf("N/A  |    N/A   |\n");
                }
            }

            if (coSinhVienThoanMan == 0) {
                printf("|    |           | [!] Khong co sinh vien nao thuoc xep loai nay. |      |      |      |      |      |      |      |          |\n");
            }
            printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n"); 
            
            if (loaiLoc == 0) {
                int tongCoDiem = demA + demB + demC + demD + demF;
                printf("\n");
                printCenter(BOLD_CYAN "[ THONG KE TY LE HOC LUC ]" RESET);
                printCenter(CYAN " +----------+----------+----------+----------+----------+----------+" RESET);
                printCenter(CYAN " | Xep loai |    A     |    B     |    C     |    D     |    F     |" RESET);
                printCenter(CYAN " +----------+----------+----------+----------+----------+----------+" RESET);
                if (tongCoDiem > 0) {
                    char s_sl[150], s_tl[150], tempColor[200];
                    sprintf(s_sl, " | So luong |    %-2d    |    %-2d    |    %-2d    |    %-2d    |    %-2d    |", demA, demB, demC, demD, demF);
                    sprintf(s_tl, " | Ty le %%  |  %5.1f%%  |  %5.1f%%  |  %5.1f%%  |  %5.1f%%  |  %5.1f%%  |", 
                            demA*100.0/tongCoDiem, demB*100.0/tongCoDiem, demC*100.0/tongCoDiem, demD*100.0/tongCoDiem, demF*100.0/tongCoDiem);
                    sprintf(tempColor, "%s%s%s", YELLOW, s_sl, RESET); printCenter(tempColor);
                    sprintf(tempColor, "%s%s%s", YELLOW, s_tl, RESET); printCenter(tempColor);
                    printCenter(CYAN " +----------+----------+----------+----------+----------+----------+" RESET);
                    printf("\n");
                    printCenter(HIGHLIGHT_BLUE "=== BAO CAO CHI TIET HOC PHAN ===" RESET);
                    printf("   -> Thu khoa hoc phan : " YELLOW "%s" RESET " - MSSV: %s - Diem TB: " GREEN "%.1f" RESET "\n", 
                           tenThuKhoa, mssvThuKhoa, maxTB);
                    if (demHocLai > 0) {
                        printf("   -> " RED "DANH SACH NGUY CO HOC LAI (%d SV):" RESET "\n", demHocLai);
                        int k;
                        for (k = 0; k < demHocLai; k++) {
                            printf("      + %s - %-20s (Diem thap nhat: " RED "%.1f" RESET ")\n", 
                                   dsHocLaiMa[k], dsHocLaiTen[k], dsHocLaiDiem[k]);
                        }
                    } else {
                        printf("   -> Canh bao hoc lai  : " GREEN "Chuc mung! Lop khong co sinh vien nao nguy co rot mon." RESET "\n");
                    }
                    printCenter(HIGHLIGHT_BLUE "=================================" RESET);
                } else {
                    printCenter(RED " |            Chua co du lieu thong ke cho mon hoc nay               |" RESET);
                    printCenter(CYAN " +----------+----------+----------+----------+----------+----------+" RESET);
                }
            }
            printf("\n");
            printCenter(MAGENTA "--- CONG CU TUONG TAC BANG DIEM TOAN DIEN ---" RESET);
            printCenter("+---------------------------------------------------------+");
            printCenter("| 1: Loc Loai A  | 2: Loc Loai B  | 3: Loc Loai C         |");
            printCenter("| 4: Loc Loai D  | 5: Loc Loai F                          |");
            printCenter("| 6: Xem Bang Diem Toan Lop      | 7: Reset ve mac dinh   |");
            printCenter("| 0: Quay lai menu chon mon hoc                           |");
            printCenter("+---------------------------------------------------------+");
            printf("\n");
            int d;
            for(d = 0; d < 45; d++) printf(" ");
            printf("Nhap lua chon cua ban: ");
            
            int luaChonTuongTac;
            if (scanf("%d", &luaChonTuongTac) != 1) {
                while (getchar() != '\n');
                continue;
            }
            
            if (luaChonTuongTac == 0) break; 
            else if (luaChonTuongTac == 1) loaiLoc = 1; 
            else if (luaChonTuongTac == 2) loaiLoc = 2; 
            else if (luaChonTuongTac == 3) loaiLoc = 3; 
            else if (luaChonTuongTac == 4) loaiLoc = 4; 
            else if (luaChonTuongTac == 5) loaiLoc = 5; 
            else if (luaChonTuongTac == 7) loaiLoc = 0; 
            else if (luaChonTuongTac == 6) {
                InBangDiemToanLop();
            }
        }
    }
}

int main() {
// 1. N?P D? LI?U TÀI KHO?N GI?NG VIÊN VÀO STRUCT (Quan tr?ng nh?t)
    khoiTaoTaiKhoanHeThong(); 

    // 2. N?P DANH SÁCH SINH VIÊN VÀ CÁC L?P 25T_DT1, 25T_DT2 BAN Ð?U
    khoiTaoDuLieuGoc();

    // 3. THI?T L?P TI?NG VI?T VÀ KÍCH THU?C CONSOLE
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    int chon;

    while(1) {
        chooseRoleBox();
        
        if (scanf("%d", &chon) != 1) {
            gotoxy(35, 22); // Ð?t v? trí báo l?i du?i dòng "Nhap lua chon..."
            printf(RED "Vui long chi nhap so!" RESET);
            while(getchar() != '\n'); 
            Sleep(1000);
            continue;
        }

        switch(chon) {
            case 1: { // ÐANG NH?P CHUNG CHO ADMIN & GI?NG VIÊN
                int ketQuaDN = dangNhapHeThong(); 

                // --- TRU?NG H?P LÀ ADMIN ---
                if (ketQuaDN == 1) { 
                    int chonAdmin;
                    int dangTrongMenuAdmin = 1;

                    while(dangTrongMenuAdmin) {
                        menuAdmin();
                        if (scanf("%d", &chonAdmin) != 1) {
                            printf(RED "\nVui long chi nhap so!" RESET);
                            while(getchar() != '\n');
                            Sleep(1000);
                            continue;
                        }

                        switch(chonAdmin) {
                            case 1: /* TaoLopMoi(); */ break;
                            case 2: /* ThemGiangVien(); */ break;
                            case 3: /* PhanLopGiangVien(); */ break;
                            case 4: /* QuanLyHeThong(); */ break;
                            case 5:
                                dangTrongMenuAdmin = 0; // Thoát ra menu chính
                                break;
                            default:
                                printf(RED "\nLua chon khong hop le!" RESET);
                                Sleep(1000);
                                break;
                        }
                    }
                }
                // --- TRU?NG H?P LÀ GI?NG VIÊN ---
                else if (ketQuaDN == 2) { 
                    int chonGV;
                    int dangtrongMenu = 1;

                    while(dangtrongMenu) {
                        menuGiangVien(); // Hàm menu gi?ng viên c?a b?n
                        if (scanf("%d", &chonGV) != 1) {
                            printf(RED "\nVui long chi nhap so!" RESET);
                            while(getchar() != '\n');
                            Sleep(1000);
                            continue;
                        }

                        switch(chonGV) {
                            case 1: Nhap();      break;
                            case 2: Xem();       break;
                            case 3: Sua();       break;
                            case 4: SapXep();    break;
                            case 5: In();        break;
                            case 6:
                                dangtrongMenu = 0; // Thoát ra menu chính
                                break;  
                            default:
                                printf(RED "\nLua chon khong hop le!" RESET);
                                Sleep(1000);
                                break;
                        }
                    } 
                }
                break;
            }

            case 2:
                if(dangNhapSinhVien()) {
                    menuSinhVien(svDangNhap, "", 0); 
                }
                break;

            case 0:
                system("cls");
                exit(0);

            default:
                gotoxy(35, 22);
                printf(RED "Lua chon khong hop le!" RESET);
                Sleep(1000);
                break;
        }
    }

    return 0;
}
