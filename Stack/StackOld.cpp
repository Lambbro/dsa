#include<iostream>

using namespace std;

/* Quản lý khám bệnh tại phòng khám */
/* THUỐC*/
//Đối tượng thuốc
struct Thuoc {
    string tenThuoc;
    int giaTien, lieuLuong;

    void nhapTT() {
        cout << "Nhap ten thuoc: "; getline(cin, tenThuoc);
        cout << "Nhap gia tien: "; cin >> giaTien;
        cout << "Nhap lieu luong: "; cin >> lieuLuong;
    }
    void hienTT() {
        cout << tenThuoc << "\t" << giaTien << "\t" << lieuLuong << endl;
    }
};

struct StackNode_Thuoc {
    Thuoc info;
    struct StackNode_Thuoc *next;
};
StackNode_Thuoc *CreateNode (Thuoc thuoc) {
    StackNode_Thuoc *newNode = new StackNode_Thuoc;
    if (newNode == NULL) {
        cout << "Ko du bo nho";
        exit(0);
    }
    newNode->info = thuoc;
    newNode->next = NULL;

    return newNode;
}
// Danh sách thuốc dưới dạng stack
struct Stack_Thuoc {
    StackNode_Thuoc *top;

    void InitStack () {
        top = NULL;
    }
    //Đẩy ptu mới vào đầu ds thuốc
    void Push (StackNode_Thuoc *p) {
        if (top == NULL) top = p; 
        else {
            p->next = top;
            top = p;
        }
    }
    //Xóa tt của ptu đầu ds thuốc
    Thuoc Pop () {
        StackNode_Thuoc *p;
        if (top == NULL) {
            cout << "Ngan xep rong";
            exit(1);
        }
        else {
            Thuoc bn;
            bn = top->info;
            p = top;
            top = top->next;
            delete p;
            return bn;
        }
    }
    //Lấy tt thuốc đứng đầu ds
    Thuoc Top () {
        if (top == NULL) {
            cout << "Ngan xep rong";
            exit(1);
        } else
            return top->info;
    }
    //Thêm 1 thuốc vào đầu ds
    void ThemThuoc () {
        cin.ignore();
        Thuoc thuoc; thuoc.nhapTT();
        StackNode_Thuoc *nodeT = CreateNode(thuoc);
        Push(nodeT);
    }
    //Nhập ds thuốc
    void NhapDS () {
        int n;
        cout << "Nhap so luong thuoc: "; cin >> n;
        for (int i=0;i<n;i++) {
            ThemThuoc();
        }
    }
    //Hiện ds thuốc
    void HienDS () {
        cout << "THUOC" << endl;
        for (StackNode_Thuoc *pt=top; pt!=NULL; pt=pt->next) {
            pt->info.hienTT();
        }
    }
    //Tìm kiếm tên thuốc
    StackNode_Thuoc *TK_TH_Ten (string tenTh) {
        StackNode_Thuoc *pth;
        pth = top;
        while (pth!=NULL && pth->info.tenThuoc != tenTh) {
            pth=pth->next;
        }
        return pth;
    }
    //Tính tổng tiền thuốc của 1 ng
    int TongTien_Thuoc () {
        StackNode_Thuoc *pth = top;
        float tongTien=0;
        while (pth != NULL)
        {
            tongTien += pth->info.giaTien;
            pth = pth->next;
        }
        return tongTien;
    }
    //Xóa 1 vị thuốc trong ds của 1 ng
    void Xoa_Thuoc () {
        string tenTh;
        cout << "Nhap ten vi thuoc: "; getline(cin, tenTh);
        Stack_Thuoc newStack; newStack.InitStack();
        StackNode_Thuoc *pth = top;

        if (top->info.tenThuoc == tenTh) {
            Thuoc b=Pop(); return;
        }
        //Đẩy node sang stack mới cho đến khi gặp người cần tìm
        while (pth!=NULL) {
            pth = top;
            Thuoc bn = Pop();
            if (bn.tenThuoc == tenTh) break;
            newStack.Push(CreateNode(bn));
        }
        //Đẩy lại các node từ stack mới về stack cũ
        while (newStack.top != NULL) {
            Thuoc newThuoc = newStack.Pop();
            Push(CreateNode(newThuoc));
        }
    }
    //Chỉnh liều lượng của thuốc
    void ChinhLL_Thuoc () {
        string tenTh;
        int lieuLuong;
        cout << "Nhap ten vi thuoc: "; getline(cin, tenTh);
        StackNode_Thuoc *thuoc = TK_TH_Ten (tenTh);
        if (thuoc == NULL) {
            cout << "Khong tim thay";
            return;
        }
        cout << "Nhap lieu luong can chinh sua"; cin >> lieuLuong;
        thuoc->info.lieuLuong = lieuLuong;
    }
};

/* BỆNH NHÂN */
//Đối tượng bệnh nhân
struct BenhNhan {
    string ten, diaChi, benh;
    int tuoi;
    Stack_Thuoc dsThuoc;
    //Nhập tt 1 bệnh nhân
    void nhapTT() {
        cout << "Nhap ten: "; getline(cin, ten);
        cout << "Nhap tuoi: "; cin >> tuoi;
        cin.ignore();
        cout << "Nhap dia chi: "; getline(cin, diaChi);
        cout << "Nhap cac loai benh: "; getline(cin, benh);
        dsThuoc.InitStack();
        dsThuoc.NhapDS();
    }
    //Hiện tt 1 bệnh nhân
    void hienTT() {
        cout << "\nBENH NHAN" << endl
             << "Ten: " << ten << endl
             << "Tuoi: " << tuoi << endl
             << "Dia chi: " << diaChi << endl
             << "Benh: " << benh << endl;
        dsThuoc.HienDS();
    }
};

//Tạo stack node bệnh nhân
struct StackNode_BN {
    BenhNhan info;
    struct StackNode_BN *next;
};
//Hàm tạo node từ thông tin
StackNode_BN *CreateNode (BenhNhan bn) {
    StackNode_BN *newNode = new StackNode_BN;
    if (newNode == NULL) {
        cout << "Ko du bo nho";
        exit(0);
    }
    newNode->info = bn;
    newNode->next = NULL;

    return newNode;
}
//Hàm danh sách dưới dạng stack
struct Stack_BN {
    StackNode_BN *top;
    
    void InitStack () {
        top = NULL;
    }
    //Đẩy ptu mới lên đầu stack
    void Push (StackNode_BN *p) {
        if (top == NULL) top = p; 
        else {
            p->next = top;
            top = p;
        }
    }
    //Xóa thông tin ptu đầu stack và lưu tt 
    BenhNhan Pop () {
        StackNode_BN *p;
        if (top == NULL) {
            cout << "Ngan xep rong";
            exit(1);
        }
        else {
            BenhNhan bn;
            bn = top->info;
            p = top;
            top = top->next;
            delete p;
            return bn;
        }
    }
    //Lấy thông tin phần tử đứng đầu stack
    BenhNhan Top () {
        if (top == NULL) {
            cout << "Ngan xep rong";
            exit(1);
        } else
            return top->info;
    }
    //Hàm nhập danh sách thông tin bệnh nhân
    void NhapDS () {
        int n;
        cout << "Nhap so luong benh nhan: "; cin >> n;
        for (int i=0;i<n;i++) {
            cin.ignore();
            BenhNhan bn; bn.nhapTT();
            StackNode_BN *nodeBN = CreateNode(bn);
            Push(nodeBN);
        }
    }
    //Hàm hiện thông tin danh sách bệnh nhân
    void HienDS () {
        cout << "\nDANH SACH THONG TIN BENH NHAN" << endl;
        for (StackNode_BN *pbn=top; pbn!=NULL; pbn=pbn->next) {
            pbn->info.hienTT();
        }
    }
    //Thêm 1 bệnh nhân vào đầu danh sách
    void ThemBN_DauDS () {
        BenhNhan them; them.nhapTT();
        Push(CreateNode(them));
    }
    //Tìm kiếm theo tên
    StackNode_BN *TK_BN_Ten (string tenBN) {
        StackNode_BN *p;
        p = top;
        while ((p!=NULL) && (p->info.ten != tenBN)) p=p->next;
        return p;
    }

    StackNode_BN *TT_BN () {
        string tenBN;
        cout << "Nhap ten benh nhan can tim: "; getline(cin, tenBN);
        if (TK_BN_Ten(tenBN)) return TK_BN_Ten(tenBN);
        else {
            cout << "Khong tim thay";
            return NULL;
        }
    }

    //Hiện tt tìm kiếm theo tên
    void TT_TK_BN_Ten () {
        string tenBN;
        cout << "Nhap ten benh nhan can tim: "; getline(cin, tenBN);
        for (StackNode_BN *pbn=top; pbn!=NULL; pbn=pbn->next) {
            if (pbn->info.ten == tenBN)
                pbn->info.hienTT();
        }
    }
    //Tìm kiếm bệnh nhân sử dụng thuốc nào
    void TT_TK_BN_Th () {
        string tenTh; int count=0;
        cout << "Nhap ten thuoc: "; getline(cin, tenTh);
        for (StackNode_BN *pbn=top; pbn!=NULL; pbn=pbn->next) {
            if (pbn->info.dsThuoc.TK_TH_Ten(tenTh)) {
                pbn->info.hienTT();
                count++;
            }
        }
        if (count==0) cout << "Khong tim thay benh nhan nao";
    }
    //Xóa
    void Xoa_BN (string tenBN) {
        Stack_BN newStack; newStack.InitStack();
        StackNode_BN *pbn = top;

        if (top->info.ten == tenBN) {
            BenhNhan b=Pop(); return;
        }
        //Đẩy node sang stack mới cho đến khi gặp người cần tìm
        while (pbn!=NULL) {
            pbn = top;
            BenhNhan bn = Pop();
            if (bn.ten == tenBN) break;
            newStack.Push(CreateNode(bn));
        }
        //Đẩy lại các node từ stack mới về stack cũ
        while (newStack.top != NULL) {
            BenhNhan newBN = newStack.Pop();
            Push(CreateNode(newBN));
        }
    }
    //Xóa ptu
    void Xoa_BN_Ten () {
        string tenBN;
        cout << "Nhap ten benh nhan: "; getline(cin, tenBN);
        Xoa_BN(tenBN);
    }
    //Tổng tiền thuốc của toàn bộ bệnh nhân
    void TongTien_DSBN () {
        StackNode_BN *a = top;
        int tongTienThuoc=0, dem=0;
        while (a != NULL) {
            tongTienThuoc += a->info.dsThuoc.TongTien_Thuoc();
            dem++;
            a=a->next;
        }
        if (dem==0) {
            cout << "Danh sach rong";
            return;
        }
        cout << "Tong tien thuoc ban duoc: " << tongTienThuoc << endl;
    }
};

/* MENU */
void Menu_DS () {
    cout << "\nQUAN LY DANH SACH BENH NHAN" << endl;
    cout << "1. Nhap danh sach benh nhan moi" << endl
         << "2. Hien danh sach benh nhan" << endl
         << "3. Them benh nhan vao dau danh sach" << endl
         << "4. Xoa thong tin benh nhan theo ten" << endl
         << "5. Tim thong tin benh nhan theo ten" << endl
         << "6. Tim cac benh nhan theo ten thuoc su dung" << endl
         << "7. Tong so tien thuoc da ban" << endl
         << "8. Sap xep benh nhan theo so luong thuoc mua (tang dan)" << endl
         << "9. " << endl
         << "10. Dieu chinh thong tin 1 benh nhan" << endl
         << "11. Luu file" << endl
         << "12. Nhap file" << endl;
}

void Menu_BN() {
    cout << "\nQUAN LY THONG TIN BENH NHAN" << endl;
    cout << "1. Hien thong tin benh nhan" << endl
         << "2. Them don thuoc cho benh nhan" << endl
         << "3. Xoa thuoc theo ten thuoc cho benh nhan" << endl
         << "4. Chinh lieu luong thuoc" << endl
         << "5. In tong so tien trong don thuoc" << endl
         << "6. " << endl
         << "7. " << endl
         << "8. Xoa thong tin benh nhan" << endl;   
}

/* QUẢN LÝ BỆNH NHÂN TẠI PHÒNG KHÁM */
void QLPhongKham_Stack() {
    Stack_BN dsbn;
    int chon, chonBN;
    StackNode_BN *bn;

    do {
        Menu_DS();
        cout << "Chon: "; cin >> chon;
        switch (chon)
        {
        case 1://Nhập ds mới
            dsbn.InitStack();
            dsbn.NhapDS();
            break;
        case 2://Hiện ds
            dsbn.HienDS();
            break;
        case 3://Đẩy vào đầu ds
            cin.ignore();
            dsbn.ThemBN_DauDS();
            dsbn.HienDS();
            break;
        case 4://Xóa bn theo tên
            cin.ignore();
            dsbn.Xoa_BN_Ten();
            dsbn.HienDS();
            break;
        case 5://Tìm bệnh nhân theo tên
            cin.ignore();
            dsbn.TT_TK_BN_Ten();
            break;
        case 6://Tìm ds bệnh nhân theo tên thuốc
            cin.ignore();
            dsbn.TT_TK_BN_Th();
            break;
        case 7://Tổng số tiền thuốc đã bán (của toàn bộ bệnh nhân)
            dsbn.TongTien_DSBN();
            break;
        case 8://Sắp xếp bệnh nhân theo số lượng thuốc tăng dần
            break;
        case 9://
            break;
        
        case 10://Điều chỉnh tt bệnh nhân
            do {
                bn = dsbn.TT_BN();
            } while (bn == NULL);

            do {
                Menu_BN();
                cout << "Chon: "; cin >> chonBN;
                switch (chonBN)
                {
                case 1://Hiện lại thông tin bệnh nhân
                    bn->info.hienTT();
                    break;
                case 2://Thêm thuốc
                    bn->info.dsThuoc.ThemThuoc();
                    break;
                case 3://Xóa thuốc
                    bn->info.dsThuoc.Xoa_Thuoc();
                    break;
                case 4://Chỉnh liều lượng thuốc
                    bn->info.dsThuoc.ChinhLL_Thuoc();
                    break;
                case 5://Hiện tổng tiền thuốc
                    bn->info.dsThuoc.TongTien_Thuoc();
                    break;
                case 6://
                    break;
                case 7://
                    break;
                case 8://Xóa bệnh nhân
                    dsbn.Xoa_BN(bn->info.ten);
                    chon = 0;
                    break;

                default:
                    break;
                }
            } while (chonBN != 0);
            break;

        case 11://Lưu vào file
            break;
        case 12://Xuất từ file ra
            break;

        default:
            break;
        }
    } while (chon != 0);
}

int main() {
    QLPhongKham_Stack();

    return 0;
}