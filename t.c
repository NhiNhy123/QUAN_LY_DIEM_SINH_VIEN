#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define mx 40
#define mx_hp 20
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"
#define HIGHLIGHT_BLUE "\033[46;30m"
#define HIGHLIGHT_YELLOW "\033[43;30m"
#define BOLD_CYAN "\033[1;36m" 
#define MAGENTA "\033[1;35m"

char maSV[mx][20] = {
    "102250001","102250002","102250003","102250004","102250005","102250006","102250007","102250008","102250009","102250010",
    "102250011","102250012","102250013","102250014","102250015","102250016","102250017","102250018","102250019","102250020",
    "102250021","102250022","102250023","102250024","102250025","102250026","102250027","102250028","102250029","102250030",
    "102250031","102250032","102250033","102250034","102250035","102250036","102250037","102250038","102250039","102250040"
};

char tenSV[mx][30] = {
    "Nguyen Van An","Tran Thi Ngoc Anh","Mai Thi Ngoc Chau","Le Van Chanh","Pham Thuy Duong","Hoang Van Thai Duy",
    "Nguyen Thi Danh","Le Thi Mai Giang","Tran Van Hoang","Pham Van Huy","Hoang Thi Hong Hoa",
    "Nguyen Van Khanh","Tran Thi Khanh","Le Tuan Kiet","Le Van Luc","Pham Thi Linh","Hoang Van Lanh",
    "Nguyen Thi My","Le Thi Minh","Nguyen Thi Nhi","Le Thi Nhim","Tran Van Cong Nhat","Tran Van Nhan","Pham Van Nhat","Hoang Thai U Ninh",
    "Nguyen Van Oanh","Tran Thi Phai","Le Thien Phong","Pham Thi Quyen","Hoang Van Quy",
    "Nguyen Thi Sinh","Le Thi Thy","Tran Van Tien", "Le Thanh Thu", "Hoang Mai Truc","Pham Van Thai","Hoang Thi Hong Vy",
    "Nguyen Van Cong Vy","Tran Thi Thieu Vy","Le Van Vinh"
};

float lab1[mx], lab2[mx], pt1[mx], pt2[mx], pre[mx], final[mx];

int n = 40;

char dsHocPhan[mx_hp][30] = {"CTDL", "PPT", "TRR"};
int soHp = 3;

char tenHp[30];
char tenFile[50];

void taoTenFile() {
    sprintf(tenFile, "%s.txt", tenHp);
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
}

void docFile() {
    int i;
    for(i = 0; i < n; i++) {
        lab1[i] = lab2[i] = pt1[i] = pt2[i] = pre[i] = final[i] = -1;
    }
    FILE *f = fopen(tenFile, "r");
    if (!f) return;

    int sl;
    fscanf(f, "%d\n", &sl); 

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
        strcpy(dsHocPhan[0], "CTDL");
        strcpy(dsHocPhan[1], "PPT");
        strcpy(dsHocPhan[2], "TRR");
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

void themHp() {
    char tenMoi[50];
    int i, exists;
    system("cls");
    printf("\n");
    printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
    printCenter(BOLD_CYAN "|             THEM HOC PHAN MOI            |" RESET);
    printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
    while (1) {
        if (soHp >= mx_hp) {
            printCenter("DANH SACH HOC PHAN DA DAY!");
            getch();
            return;
        }
        printf("%75s", "Nhap ten hoc phan moi (0 de thoat): ");
        scanf(" %s", tenMoi);
        if (strcmp(tenMoi, "0") == 0) return;
        exists = 0;
        for (i = 0; i < soHp; i++) {
            if (strcmp(dsHocPhan[i], tenMoi) == 0) {
                exists = 1;
                break;
            }
        }
        if (exists) {
            xoaDongVuaNhap(); 
        } else {
            xoaDongVuaNhap();
            strcpy(tenHp, tenMoi);
            strcpy(dsHocPhan[soHp++], tenHp);
            luuDanhSachMon();
            taoTenFile();
            FILE *f = fopen(tenFile, "w");
            if (f) {
                fprintf(f, "0\n");
                fclose(f);
            }
            printf(GREEN "%30s %s" RESET, "DA THEM THANH CONG:", tenHp);
            printf("\n\n%50s", "Nhan phim bat ky de quay lai...");
            getch();
            break; 
        }
    }
}

void menuChinh() {
    system("cls");
    int d;
    for(d = 0; d < 10; d++) printf("\n");

    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    printCenter(CYAN "|                QUAN LY DIEM SINH VIEN                    |" RESET);
    printCenter(CYAN "+----------------------------------------------------------+" RESET);
    printCenter("|  1. Nhap diem moi                                        |");
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

int menuHocPhan() {
    int chon;
    char line[100];
    while (1) {
        system("cls");
        int d;
        for(d = 0; d < 8; d++) printf("\n"); 

        printf(CYAN);
        printCenter("+-------------------------------------------+");
        printCenter("|           CHON HOC PHAN DAO TAO           |");
        printCenter("+-------------------------------------------+");
        printf(RESET);

        int i;
        for (i = 0; i < soHp; i++) {
            sprintf(line, "|    %d. %-33s   |", i + 1, dsHocPhan[i]);
            printCenter(line);
        }

        printCenter("|-------------------------------------------|");
        sprintf(line, "|    %d. Tao hoc phan moi                    |", soHp + 1);
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
        if (chon >= 1 && chon <= soHp) {
            strcpy(tenHp, dsHocPhan[chon - 1]);
            taoTenFile();
            docFile();
            return 1;
        } else if (chon == soHp + 1) {
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

float tinhTB(int i) {
    if (lab1[i] == -1 || lab2[i] == -1 || pt1[i] == -1 || 
        pt2[i] == -1 || pre[i] == -1 || final[i] == -1) {
        return -1.0; 
	}
    return (lab1[i] + lab2[i] + pt1[i] + pt2[i] + pre[i] + final[i]) / 6.0;
}

char xepLoai (float tb) {
    if (tb>=8.5) return 'A';
    if (tb>=7) return 'B';
    if (tb>=5) return 'C';
    if (tb>=4) return 'D';
    return 'F';
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

float NhapMotCotDiem(char tenCot[]) {
    char s[20];
    float diem;
    while(1) {
        printf("Nhap %s (Go 'q' de ngung nhap) : ", tenCot);
        scanf("%s", s);
        if (strcmp(s, "q") == 0 || strcmp(s, "Q") == 0) {
            return -2.0; 
		}
        diem = atof(s);
        if (strcmp(s, "0") == 0 || strcmp(s, "0.0") == 0) {
            return 0.0;
        }
        if (diem > 0.0 && diem <= 10.0) {
            return diem;
        }
        printf(RED " (!) Diem khong hop le hoac khong phai lenh thoat. Thu lai!\n" RESET);
        while(getchar() != '\n');
        Sleep(800);
        xoaDongVuaNhap(); 
        xoaDongVuaNhap();
    }
}

int NhapDiemMotSV(int k) {
    float tam;
    printf(HIGHLIGHT_YELLOW "\n>>> TIEP TUC CAP NHAT DIEM CHO: %s\n" RESET, tenSV[k]);
    if (lab1[k] == -1) {
        tam = NhapMotCotDiem("Lab1");
        if (tam == -2.0) return 0;
        lab1[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + Lab1 : " GREEN "%.1f" RESET "\n", lab1[k]);
    } else {
        printf("   + Lab1 : " CYAN "%.1f (Da nhap)" RESET "\n", lab1[k]);
    }
    if (lab2[k] == -1) {
        tam = NhapMotCotDiem("Lab2");
        if (tam == -2.0) return 0;
        lab2[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + Lab2 : " GREEN "%.1f" RESET "\n", lab2[k]);
    } else {
        printf("   + Lab2 : " CYAN "%.1f (Da nhap)" RESET "\n", lab2[k]);
    }
    if (pt1[k] == -1) {
        tam = NhapMotCotDiem("Pt1");
        if (tam == -2.0) return 0;
        pt1[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + PT1  : " GREEN "%.1f" RESET "\n", pt1[k]);
    } else {
        printf("   + PT1  : " CYAN "%.1f (Da nhap)" RESET "\n", pt1[k]);
    }
    if (pt2[k] == -1) {
        tam = NhapMotCotDiem("Pt2");
        if (tam == -2.0) return 0;
        pt2[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + PT2  : " GREEN "%.1f" RESET "\n", pt2[k]);
    } else {
        printf("   + PT2  : " CYAN "%.1f (Da nhap)" RESET "\n", pt2[k]);
    }
    if (pre[k] == -1) {
        tam = NhapMotCotDiem("Pre");
        if (tam == -2.0) return 0;
        pre[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + Pre  : " GREEN "%.1f" RESET "\n", pre[k]);
    } else {
        printf("   + Pre  : " CYAN "%.1f (Da nhap)" RESET "\n", pre[k]);
    }
    if (final[k] == -1) {
        tam = NhapMotCotDiem("Final");
        if (tam == -2.0) return 0;
        final[k] = tam;
        luuFile();
        xoaDongVuaNhap();
        printf("   + Final: " GREEN "%.1f" RESET "\n", final[k]);
    } else {
        printf("   + Final: " CYAN "%.1f (Da nhap)" RESET "\n", final[k]);
    }
    if (lab1[k] != -1 && lab2[k] != -1 && pt1[k] != -1 && pt2[k] != -1 && pre[k] != -1 && final[k] != -1) {
        printf("   ==> " BOLD_CYAN "DIEM TRUNG BINH : %.1f" RESET "\n", tinhTB(k));
        printf(YELLOW "\nDa hoan thanh nhap full diem cho sinh vien nay!" RESET);
    } else {
        printf(YELLOW "\nTam thoi dung nhap diem cho sinh viên nay." RESET);
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
            DanhSachSV(0); 
            
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
                        Sleep(900);
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
                DanhSachSV(0);
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

int binary_search(char *ma) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int m = (left + right)/2;
        int k = strcmp(maSV[m],ma);
        if (k == 0) return m;
        else if (k < 0) left = m + 1;
            else right = m - 1;
    }
    return -1;
}

void XemDiemMotSV(char maTruyenVao[], char monSua[], int cotSua) {
    char ma[20];
    int i, j, k, d, cheDoXemDocLap = 0; 
    float l1, l2, p1, p2, pr, fi, tb;
    if (strcmp(maTruyenVao, "") == 0) {
        cheDoXemDocLap = 1; 
    } else {
        strcpy(ma, maTruyenVao); 
    }
    while (1) {
        if (cheDoXemDocLap) {
            system("cls");
            printf("\n");
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
            printCenter(BOLD_CYAN "|      XEM DIEM CHI TIET MOT SINH VIEN     |" RESET);
            printCenter(BOLD_CYAN "+------------------------------------------+" RESET);       
            while (1) {
                printf("\n");
                for(d = 0; d < 40; d++) printf(" ");
                printf(YELLOW "Vui long nhap MSSV (0 de huy): " RESET);
                scanf("%s", ma);
                if (strcmp(ma, "0") == 0) return;
                k = binary_search(ma); 
                if (k == -1) xoaDongVuaNhap(); else break;
            }
        } else {
            k = binary_search(ma);
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
        printCenter(BOLD_CYAN "------------------- BANG DIEM CUA SINH VIEN -------------------" RESET);
        printf("\n");
        printCenter("+------------+------+------+------+------+------+-------+-------+");
        printCenter("|  Hoc phan  | Lab1 | Lab2 | PT1  | PT2  | Pre  | Final |  TB   |");
        printCenter("+------------+------+------+------+------+------+-------+-------+");

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
                		if (strcmp(maF, ma) == 0) { found = 1; break; }
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
                sprintf(row, "| %-10s | %-4s | %-4s | %-4s | %-4s | %-5s | %-5s | %-4s |", 
                        dsHocPhan[i], sL1, sL2, sP1, sP2, sPr, sFi, sTb);
            } else {
                sprintf(row, "| %-10s | %-4s | %-4s | %-4s | %-4s | %-4s | %-5s | %-4s |", 
                        dsHocPhan[i], "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A");
            }
            printCenter(row);
        }
        printCenter("+------------+------+------+------+------+------+-------+-------+");
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
        DanhSachSV(0); 
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
    char ma[20];
    char chonMon[20];
    int chonCot, tiep;
    char box[150];
    int i, j, k, d;
    while (1) {
        system("cls");
        printf(YELLOW);
        printCenter("------- CHINH SUA DIEM SINH VIEN -------\n");
        printf(RESET);
        DanhSachSV(0); 
        printCenter(BOLD_CYAN "+------------------------------------------+" RESET);
        printCenter(BOLD_CYAN "|           CHINH SUA DIEM TONG HOP        |" RESET);
        printCenter(BOLD_CYAN "+------------------------------------------+" RESET);      
        while (1) {
            printf("\n");
            for(d = 0; d < 40; d++) printf(" ");
            printf(YELLOW "Nhap MSSV can sua (0 de thoat): " RESET);
            scanf("%s", ma);
            if (strcmp(ma, "0") == 0) return;
            k = binary_search(ma);
            if (k == -1) { xoaDongVuaNhap(); continue; }
            int daCoItNhatMotDauDiem = 0;
            
            for (i = 0; i < soHp; i++) {
                char fileCheck[50];
                sprintf(fileCheck, "%s.txt", dsHocPhan[i]);
                FILE *fCheck = fopen(fileCheck, "r");
                if (fCheck) {
                    int slCheck;
                    if (fscanf(fCheck, "%d\n", &slCheck) == 1) {
                        char maF[20], tenT[100];
                        float l1, l2, p1, p2, pr, fi;
                        for (j = 0; j < slCheck; j++) {
                            if (fscanf(fCheck, "%s ", maF) != 1) break;
                            if (fscanf(fCheck, "%[^0-9]", tenT) != 1) break;
                            if (fscanf(fCheck, "%f %f %f %f %f %f\n", &l1, &l2, &p1, &p2, &pr, &fi) == 6) {
                                if (strcmp(maF, ma) == 0) {
                                    if ((l1 != 1.0 && l1 != -1.0) || 
                                        (l2 != 1.0 && l2 != -1.0) || 
                                        (p1 != 1.0 && p1 != -1.0) || 
                                        (p2 != 1.0 && p2 != -1.0) || 
                                        (pr != 1.0 && pr != -1.0) || 
                                        (fi != 1.0 && fi != -1.0)) {
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
    			xoaDongVuaNhap();
    			printCenter(RED "   (!) Sinh vien nay chua duoc nhap bat ky dau diem nao. Khong the sua!\n" RESET);
    			fflush(stdout); 
    			Sleep(1000); 
    			xoaDongVuaNhap();
    			xoaDongVuaNhap(); 
    			continue; 
            }
            break; 
        }
        while (1) {
            system("cls");
            XemDiemMotSV(ma, "", 0);
            int indexMonCanSua = -1;
            while (1) {
                printf(YELLOW "Nhap TEN MON muon sua (Vi du: CTDL, PPT, TRR): " RESET);
                scanf("%s", chonMon);
                strupr(chonMon);
                for (i = 0; i < soHp; i++) {
                    if (strcmp(dsHocPhan[i], chonMon) == 0) { indexMonCanSua = i; break; }
                }
                if (indexMonCanSua != -1) break;
                xoaDongVuaNhap();
            }
            char fileSua[50];
            sprintf(fileSua, "%s.txt", chonMon);
            int slTam;
            char maTam[40][20], tenTam[40][100];
            float bL1[40], bL2[40], bP1[40], bP2[40], bPr[40], bFi[40];
            float diemHienTai = -1.0;
            int timThaySVTrongFile = 0;

            FILE *fIn = fopen(fileSua, "r");
            if (fIn) {
                fscanf(fIn, "%d\n", &slTam);
                for (i = 0; i < slTam; i++) {
                    fscanf(fIn, "%s ", maTam[i]);
                    fscanf(fIn, "%[^0-9]", tenTam[i]);
                    fscanf(fIn, "%f %f %f %f %f %f\n", &bL1[i], &bL2[i], &bP1[i], &bP2[i], &bPr[i], &bFi[i]);
                    if (strcmp(maTam[i], ma) == 0) {
                        timThaySVTrongFile = 1;
                        k = i; 
                    }
                }
                fclose(fIn);
            }

            if (!timThaySVTrongFile) {
                printf(RED "(!) Sinh vien khong co trong lop hoc phan %s.\n" RESET, chonMon);
                getch();
                continue; 
            }

            printf(GREEN "CHON COT CAN SUA CUA MON %s:" RESET "\n", chonMon);
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
                if (diemHienTai == 1.0 || diemHienTai == -1.0) {
                    xoaDongVuaNhap(); 
                    printf(RED "   (!) Cot nay chua co diem (N/A), khong the sua! Vui long chon cot khac.\n" RESET);
                    Sleep(1000);
                    xoaDongVuaNhap(); 
                    continue; 
                }

                break; 
            }

            printf("\n");
            float diem = NhapMotCotDiem("diem moi");
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

            FILE *fOut = fopen(fileSua, "w");
            if (fOut) {
                fprintf(fOut, "%d\n", slTam);
                for (i = 0; i < slTam; i++) {
                    fprintf(fOut, "%s %s%.1f %.1f %.1f %.1f %.1f %.1f\n", 
                            maTam[i], tenTam[i], bL1[i], bL2[i], bP1[i], bP2[i], bPr[i], bFi[i]);
                }
                fclose(fOut);
            }

            if (strcmp(chonMon, tenHp) == 0) {
                int indexSV = binary_search(ma);
                if (indexSV != -1) {
                    switch(chonCot) {
                        case 1: lab1[indexSV] = diem; break;
                        case 2: lab2[indexSV] = diem; break;
                        case 3: pt1[indexSV] = diem; break;
                        case 4: pt2[indexSV] = diem; break;
                        case 5: pre[indexSV] = diem; break;
                        case 6: final[indexSV] = diem; break;
                    }
                }
            }

            system("cls");
            printf("\n" GREEN "--- KET QUA SAU KHI SUA (DIEM DOI MAU XANH) ---" RESET "\n");
            XemDiemMotSV(ma, chonMon, chonCot); 
            printf(GREEN "[THANH CONG] Da cap nhat va dong bo vao file!\n" RESET);
            break; 
        }

        printf("\n");
        sprintf(box, "%s+------------------------------------------+%s", BOLD_CYAN, RESET); printCenter(box);
        sprintf(box, "%s|      [1] Tiep tuc sua sinh vien khac     |%s", BOLD_CYAN, RESET); printCenter(box);
        sprintf(box, "%s|      [0] Quay lai Menu chinh             |%s", BOLD_CYAN, RESET); printCenter(box);
        sprintf(box, "%s+------------------------------------------+%s", BOLD_CYAN, RESET); printCenter(box);
        printf("\n");
        for(d = 0; d < 48; d++) printf(" "); 
        printf(GREEN "LUA CHON: " RESET);
        scanf("%d", &tiep);
        if (tiep != 1) break;
    }
}

void InbangSapXep() {
    int demA = 0, demB = 0, demC = 0, demD = 0, demF = 0;
    int i, j;
    system("cls");
    printf("\n" BOLD_CYAN "------------------------------------------ BANG DIEM MON %s -------------------------------------------" RESET "\n\n", tenHp);
    printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);
    printf("| STT |  Ma so SV  |       Ho va ten     | Lab1 | Lab2 | PT1  | PT2  |  Pre  | Final |  TB   | XEP LOAI |\n");
    printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);
    for (i = 0; i < n; i++) {
        float diem[6] = {lab1[i], lab2[i], pt1[i], pt2[i], pre[i], final[i]};
        int daydu = 1;
        for (j = 0; j < 6; j++) {
            if (diem[j] == -1) {
                daydu = 0;
                break;
            }
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
            if (xl == 'A') demA++;
            else if (xl == 'B') demB++;
            else if (xl == 'C') demC++;
            else if (xl == 'D') demD++;
            else demF++;
        } else {
            printf("%-5s |    %-5s |\n", "N/A", "N/A");
        }
    }
    printf(CYAN "+-----+------------+---------------------+------+------+------+------+-------+-------+-------+----------+\n" RESET);
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
    int chon;
    int k;
    while(1) {
        if (HocPhan() == 0) return; 
        for (k = 0; k < n; k++) {
            temp_dtb[k] = tinhTB(k);
        }
        while(1) {
            system("cls");
            int d;
            for(d = 0; d < 10; d++) printf("\n");
            printf(BOLD_CYAN);
            sprintf(line, "--- SAP XEP (Hoc phan: %s) ---", tenHp);
            printCenter(line);
        	printf(RESET);
        	printCenter("+------------------------------------------+");
        	printCenter("|  1. Diem trung binh Tang dan             |");
        	printCenter("|  2. Diem trung binh Giam dan             |");
        	printCenter("|  0. Quay lai Menu chinh                  |");
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
                QuickSort(0, n - 1, chon);
                InbangSapXep();
                printf("\n");
                printCenter(GREEN "=> DA SAP XEP THANH CONG!" RESET);
                printCenter("Nhan phim bat ky de tiep tuc...");
                getch();
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
    printCenter(YELLOW "Nhan phim bat ky de in danh sach cac mon..." RESET);
    getch();
}

void In() {
    int ch;
    ThongKeHocVu();
    while (1) {
        if (HocPhan() == 0) return; 
        int demA = 0, demB = 0, demC = 0, demD = 0, demF = 0;
        float maxTB = -1.0;
        char mssvThuKhoa[20] = "", tenThuKhoa[50] = "";
        char dsHocLaiMa[40][20], dsHocLaiTen[40][50];
        float dsHocLaiDiem[40];
        int demHocLai = 0;
        system("cls");
        printf("\n" GREEN "---------------------------------- BANG DIEM CHI TIET MON: %-5s -----------------------------------" RESET "\n\n", tenHp);
        printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n");
        printf("| STT|   MSSV    |          Ten        | L1   | L2   | PT1  | PT2  | Pre  | Fin  |  TB  | XEP LOAI |\n");
        printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n");
        
        int i;
        for (i = 0; i < n; i++) {
            int coDiem = (lab1[i] != -1 && lab2[i] != -1 && pt1[i] != -1 && pt2[i] != -1 && pre[i] != -1 && final[i] != -1);
            printf("| %-2d | %-9s | %-19s | ", i + 1, maSV[i], tenSV[i]);
            if(lab1[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", lab1[i]);
            if(lab2[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", lab2[i]);
            if(pt1[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pt1[i]);
            if(pt2[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pt2[i]);
            if(pre[i] == -1)  printf("N/A  | "); else printf("%-4.1f | ", pre[i]);
            if(final[i] == -1) printf("N/A  | "); else printf("%-4.1f | ", final[i]);
            if (coDiem) {
                float tb = tinhTB(i);
                char xl = xepLoai(tb);
                printf("%-4.1f |    %-5c |\n", tb, xl);     
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
            } else {
                printf("N/A  |    N/A   |\n");
            }
        }
        printf("+----+-----------+---------------------+------+------+------+------+------+------+------+----------+\n"); 
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
            printCenter(RED " |            Chua co du lieu thong ke cho mon hoc nay             |" RESET);
            printCenter(CYAN " +----------+----------+----------+----------+----------+----------+" RESET);
        }
        printf("\n");
        printCenter(YELLOW "Nhan phim bat ky de quay lai chon hoc phan..." RESET);
        getch();
    }
}

int main() {
	docDanhSachMon();
    int chon;
    while(1) {
        menuChinh();
        if (scanf("%d", &chon) != 1) {
            while (getchar() != '\n'); 
    		chon = -1;   
		}
        switch(chon) {
            case 1: Nhap(); break;
            case 2: Xem(); break;
            case 3: Sua(); break;
            case 4: SapXep(); break;
            case 5: In(); break;
            case 6: return 0;
        }
    }
}
