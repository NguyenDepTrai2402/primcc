#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int n;
    int a[MAX][MAX];
} DOTHI;

typedef struct {
    int u, v, value;
} CANH;

int ChuaXet[MAX];
CANH T[MAX];

/* ========== Hàm kiểm tra liên thông (theo sách) ========== */
void timDinhLienThong(DOTHI g, int nhan[MAX], int i) {
    for (int j = 0; j < g.n; j++) {
        if (g.a[i][j] != 0 && nhan[i] != nhan[j]) {
            nhan[j] = nhan[i];
            timDinhLienThong(g, nhan, j);
        }
    }
}

int soTPLienThong(DOTHI g) {
    int nhan[MAX];
    int soTPLT = 0;

    for (int i = 0; i < g.n; i++)
        nhan[i] = 0;

    for (int i = 0; i < g.n; i++) {
        if (nhan[i] == 0) {
            soTPLT++;
            nhan[i] = soTPLT;
            timDinhLienThong(g, nhan, i);
        }
    }
    return soTPLT;
}

/* ========== Thuật toán Prim (đúng theo sách trang 60-61) ========== */
void Prim(DOTHI g) {
    // Nếu đồ thị không liên thông thì dừng
    if (soTPLienThong(g) != 1) {
        printf("Do thi khong lien thong, dung thuat toan Prim\n");
        return;
    }

    int nT = 0;                         // số cạnh đã chọn

    // Đánh dấu tất cả đỉnh chưa xét
    for (int i = 0; i < g.n; i++)
        ChuaXet[i] = 0;

    ChuaXet[0] = 1;                     // Bắt đầu từ đỉnh 0

    while (nT < g.n - 1) {
        CANH CanhNhoNhat;
        int GiaTriNhoNhat = 1000;       // giá trị khởi tạo lớn

        // Duyệt các đỉnh đã xét
        for (int i = 0; i < g.n; i++) {
            if (ChuaXet[i] == 1) {
                // Tìm cạnh nhỏ nhất từ i đến một đỉnh chưa xét
                for (int j = 0; j < g.n; j++) {
                    if (ChuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriNhoNhat > g.a[i][j]) {
                        GiaTriNhoNhat = g.a[i][j];
                        CanhNhoNhat.u = i;
                        CanhNhoNhat.v = j;
                        CanhNhoNhat.value = g.a[i][j];
                    }
                }
            }
        }

        // Nếu không tìm được cạnh nào → đồ thị không liên thông
        if (GiaTriNhoNhat == 1000) {
            printf("Do thi khong lien thong\n");
            return;
        }

        // Thêm cạnh nhỏ nhất vào cây khung
        T[nT++] = CanhNhoNhat;
        ChuaXet[CanhNhoNhat.v] = 1;     // đánh dấu đỉnh v đã xét
    }

    // Xuất kết quả
    int trongSoCuaCayKhung = 0;
    printf("Cay khung nho nhat cua do thi la\n");
    for (int i = 0; i < nT; i++) {
        printf("(%d,%d), ", T[i].u, T[i].v);
        trongSoCuaCayKhung += T[i].value;
    }
    printf("\nTong trong so cay khung la %d\n", trongSoCuaCayKhung);
}

/* ========== Hàm main ========== */
int main() {
    DOTHI g;
    FILE *fp = fopen("test1.txt", "r");   // đổi tên file nếu cần

    if (fp == NULL) {
        printf("Khong mo duoc file test\n");
        return 1;
    }

    fscanf(fp, "%d", &g.n);
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            fscanf(fp, "%d", &g.a[i][j]);

    fclose(fp);

    Prim(g);
    return 0;
}