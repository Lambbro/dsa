#include<fstream>
#include"../model.h"

using namespace std;
//Thuốc
NodeMedicine *create_node (Medicine medicine) {
    NodeMedicine *new_node = new NodeMedicine;
    if (new_node == NULL) {
        cout << string(TAB_WIDTH, ' ') << "Khong du bo nho";
        exit(0);
    }
    new_node->medicine = medicine;
    new_node->next = NULL;

    return new_node;
}
//Stack Thuốc
struct StackMedicine {
    NodeMedicine *top;

    void init_stack () {
        top = NULL;
    }

    void push (NodeMedicine *nmed) {
        if (top == NULL) top = nmed; 
        else {
            nmed->next = top;
            top = nmed;
        }
    }

    void pop () {
        NodeMedicine *nmed;
        if (top == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Ngan xep rong";
            return;
        }
        else {
            nmed = top;
            top = top->next;
            delete nmed;
        }
    } 
};
//Hàm cơ chức năng của thuốc
void add_top (StackMedicine &smed) {
    Medicine med; med.input_from_keyboard();
    NodeMedicine *nmed = create_node(med);
    smed.push(nmed);
}
void input_stack (StackMedicine &smed) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong thuoc: "; cin >> n;
    smed.init_stack();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(smed);
        cin.ignore();
    }
}
void output_stack (StackMedicine smed) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH THUOC" << endl;
    cout << string(TAB_WIDTH, ' ') << setw(10) << left << "ID"
		 << setw(25) << left << "Ten thuoc"
		 << setw(25) << left << "Cong dung"
		 << setw(11) << right << "Gia tien"
		 << setw(17) << right << "Lieu luong" << endl;
    for (NodeMedicine *nmed = smed.top; nmed!=NULL; nmed=nmed->next) {
        nmed->medicine.output_screen();
    }
}
NodeMedicine *search_stack (StackMedicine smed, string id) {
    for (NodeMedicine *p = smed.top; p!=NULL; p=p->next) {
        if (p->medicine.id == id) {
            return p;
        }
    }
    return NULL;
}
//Cach cua stack
NodeMedicine *search_stack_s (StackMedicine smed, string id) {
    StackMedicine sm; sm.init_stack();
    while (smed.top != NULL) {
        NodeMedicine *nm = smed.top;
        if (nm->medicine.id == id) {
            return nm;
        }
        sm.push(nm);
        smed.pop();
    }
    return NULL;
}
int size_of (StackMedicine smed) {
    int size = 0;
    for (NodeMedicine *p = smed.top; p!=NULL; p=p->next) {
        size++;
    }
    return size;
}

int sum_price (StackMedicine smed) {
    int sum=0;
    for (NodeMedicine *p = smed.top; p!=NULL; p=p->next) {
        sum += p->medicine.price;
    }
    return sum;
}
//Đọc ghi file thuốc
void input_to_file (StackMedicine smed) {
    fstream f;
    fflush(stdin);
    f.open("Medicine.dat", ios::out);
    if (smed.top != NULL) {
        NodeMedicine *nmed = smed.top;
        while (nmed!=NULL) {
            Medicine med = nmed->medicine;
            f << med.id << "\n";
            f << med.name << "\n";
            f << med.uses << "\n";
            f << med.price << "\n";
            f << med.medication_dosage << "\n";
            smed.pop();
            nmed = smed.top;
        }
        cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <Medicine.dat>";
    }
    f.close();
}

void output_from_file (StackMedicine &smed) {
    fstream f;
    fflush(stdin);
    f.open("Medicine.dat", ios::in);
    smed.init_stack();
    if (f.is_open()) {
        while(!f.eof()) {
            Medicine med;
            getline(f, med.id);
            getline(f, med.name);
            getline(f, med.uses);
            f >> med.price;
            f >> med.medication_dosage; f.ignore();
            NodeMedicine *nmed = create_node(med);
            smed.push(nmed);
        }
        smed.pop();
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu tu file <Medicine.dat>" << endl;
}
//Bệnh nhân
NodePatient *create_node (Patient patient) {
    NodePatient *new_node = new NodePatient;
    if (new_node == NULL) {
        cout << string(TAB_WIDTH, ' ') << "Khong du bo nho";
        exit(0);
    }
    new_node->patient = patient;
    new_node->next = NULL;

    return new_node;
}
//Stack Bệnh nhân
struct StackPatient {
    NodePatient *top;

    void init_stack () {
        top = NULL;
    }

    void push (NodePatient *nmed) {
        if (top == NULL) top = nmed; 
        else {
            nmed->next = top;
            top = nmed;
        }
    }

    void pop () {
        NodePatient *nmed;
        if (top == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Ngan xep rong";
            return;
        }
        else {
            nmed = top;
            top = top->next;
            delete nmed;
        }
    } 
};
//Hàm cơ chức năng của bệnh nhân
void add_top (StackPatient &spat) {
    Patient pat; pat.intput_from_keyboard();
    NodePatient *npat = create_node(pat);
    spat.push(npat);
}
void input_stack (StackPatient &spat) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong benh nhan: "; cin >> n;
    spat.init_stack();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(spat);
    }
}
void output_stack (StackPatient spat) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH BENH NHAN" << endl;
    for (NodePatient *npat = spat.top; npat!=NULL; npat=npat->next) {
        npat->patient.output_screen(); cout << endl;
    }
}
NodePatient *search_stack (StackPatient spat, string id) {
    for (NodePatient *p = spat.top; p!=NULL; p=p->next) {
        if (p->patient.id == id) {
            return p;
        }
    }
    return NULL;
}

//Đọc ghi file
void input_to_file (StackPatient spat) {
    fstream f;
    fflush(stdin);
    f.open("Patient.dat", ios::out);
    if (spat.top != NULL) {
        NodePatient *npat = spat.top;
        while (npat!=NULL) {
            Patient pat = npat->patient;
            f << pat.id << "\n";
            f << pat.name << "\n";
            f << pat.age << "\n";
            f << pat.address << "\n";
            f << pat.number_phone_of_guardian << "\n";
            f << pat.disease_name << "\n";
            spat.pop();
            npat = spat.top;
        }
        cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <Patient.dat>";
    }
    f.close();
}

void output_from_file (StackPatient &spat) {
    fstream f;
    fflush(stdin);
    f.open("Patient.dat", ios::in);
    spat.init_stack();
    if (f.is_open()) {
        while(!f.eof()) {
            Patient pat;
            getline(f, pat.id);
            getline(f, pat.name);
            f >> pat.age;
            f.ignore();
            getline(f, pat.address);
            getline(f, pat.number_phone_of_guardian);
            getline(f, pat.disease_name);

            NodePatient *npat = create_node(pat);
            spat.push(npat);
        }
        spat.pop();
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu tu file <Patient.dat>" << endl;
}

//Hồ sơ bệnh án
struct MedicalRecord : MedicalRecordBase {
    StackMedicine stack_medicine ;

    void input(StackPatient sp, StackMedicine sm) {
        if (sp.top == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Danh sach benh nhan rong"; return;
        }
        if (sm.top == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Danh sach thuoc rong"; return;
        }

        input_from_keyboard();

        do {
            cout << string(TAB_WIDTH, ' ') << "Nhap id benh nhan: "; getline(cin, patient.id);
            if (search_stack(sp, patient.id)) {
                patient = search_stack(sp, patient.id)->patient;
                break;
            }
            cout << string(TAB_WIDTH, ' ') << "Xin moi nhap lai!!!" << endl;
        } while (true);

        int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong thuoc: "; cin >> n;
        stack_medicine.init_stack();
        cin.ignore();
        for (int i=0;i<n;i++) {
            Medicine med;
            do {
                cout << string(TAB_WIDTH, ' ') << "Nhap id thuoc: "; getline(cin, med.id);
                if (search_stack(sm, med.id)) {
                    med = search_stack(sm, med.id)->medicine;
                    break;
                }
                cout << string(TAB_WIDTH, ' ') << "Xin moi nhap lai!!!" << endl;
            } while (true);
            
            NodeMedicine *nmed = create_node(med);
            stack_medicine.push(nmed);
        }
    }
    void output() {
        cout << "\n";
        output_screen();
        patient.output_screen();
        output_stack(stack_medicine);
    }
};

struct NodeMedicalRecord {
    MedicalRecord medical_record;
    NodeMedicalRecord *next;
};

NodeMedicalRecord *create_node (MedicalRecord medical_record) {
    NodeMedicalRecord *new_node = new NodeMedicalRecord;
    if (new_node == NULL) {
        cout << string(TAB_WIDTH, ' ') << "Khong du bo nho";
        exit(0);
    }
    new_node->medical_record = medical_record;
    new_node->next = NULL;

    return new_node;
}
//Stack HSBA
struct StackMedicalRecord
{
    NodeMedicalRecord *top;

    void init_stack () {
        top = NULL;
    }

    void push (NodeMedicalRecord *nmr) {
        if (top == NULL) top = nmr; 
        else {
            nmr->next = top;
            top = nmr;
        }
    }

    void pop () {
        NodeMedicalRecord *nmr;
        if (top == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Ngan xep rong";
            return;
        }
        else {
            nmr = top;
            top = top->next;
            delete nmr;
        }
    } 
};
//Thêm vào đầu stack
void add_top (StackMedicalRecord &smr, StackPatient sp, StackMedicine sm) {
    MedicalRecord mr; mr.input(sp, sm);
    NodeMedicalRecord *nmr = create_node(mr);
    smr.push(nmr);
}
void input_stack (StackMedicalRecord &smr, StackPatient sp, StackMedicine sm) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong ho so: "; cin >> n;
    smr.init_stack();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(smr, sp, sm);
    }
}
void output_stack (StackMedicalRecord smr) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO BENH AN" << endl;
    for (NodeMedicalRecord *nmr = smr.top; nmr!=NULL; nmr=nmr->next) {
        nmr->medical_record.output();
    }
}
NodeMedicalRecord *search_stack (StackMedicalRecord smr, string id) {
    for (NodeMedicalRecord *p = smr.top; p!=NULL; p=p->next) {
        if (p->medical_record.id == id) {
            return p;
        }
    }
    return NULL;
}
//Xóa HSBA
void delete_by_id (StackMedicalRecord &smr) {
    StackMedicalRecord new_stack; new_stack.init_stack();
    string id;
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);

    while (smr.top!=NULL) {
        MedicalRecord p = smr.top->medical_record;
        smr.pop();
        if (p.id == id) break;
        new_stack.push(create_node(p));
    }
    while (new_stack.top!=NULL) {
        MedicalRecord p = new_stack.top->medical_record;
        new_stack.pop();
        smr.push(create_node(p));
    }
    cout << string(TAB_WIDTH, ' ') << "Da xoa (neu co)" << endl;
}
//Sửa thông tin HSBA
void edit_information (StackMedicalRecord &smr, StackPatient sp, StackMedicine sm) {
    string id;
    int chon_hs;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id hsba can sua: "; getline(cin, id);
    StackMedicalRecord new_stack; new_stack.init_stack();

    NodeMedicalRecord *p = search_stack(smr, id);
    if (p==NULL) {
        cout << string(TAB_WIDTH, ' ') << "Khong tim thay ho so" << endl;
        return;
    } else {
        MedicalRecord new_med;
        new_med.input(sp, sm);

        p->medical_record = new_med;
    }
    cout << string(TAB_WIDTH, ' ') << "HO SO BENH AN SAU KHI SUA" << endl;
    p->medical_record.output();
}
//Sắp xếp theo thứ tự tăng dần id khi in ra
void sort_stack (StackMedicalRecord &smr) {
    for (NodeMedicalRecord *p=smr.top;p->next!=NULL;p=p->next) {
        for (NodeMedicalRecord *q=p->next;q!=NULL;q=q->next) {
            if (p->medical_record.id < q->medical_record.id) {
                MedicalRecord tmp = p->medical_record;
                p->medical_record = q->medical_record;
                q->medical_record = tmp;
            }
        }
    }
}
//Tìm kiếm thông tin hồ sơ theo id bệnh nhân
void search_mr_by_patient_id (StackMedicalRecord smr, StackPatient sp) {
    string id;
    cout << string(TAB_WIDTH, ' ') << "Nhap id benh nhan: "; cin.ignore(); getline(cin, id);

    if (!search_stack(sp,id)) {
        cout << string(TAB_WIDTH, ' ') << "Khong tim thay benh nhan" << endl;
        return;
    }
    cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO CUA BENH NHAN " << id << endl;
    StackMedicalRecord new_stack = smr;
    while (new_stack.top!=NULL) {
        if (new_stack.top->medical_record.patient.id == id) 
            new_stack.top->medical_record.output();
        new_stack.pop();
    }
}
//Tinh tong tien theo id
void sum_price_by_id (StackMedicalRecord smr) {
    string id; int sum=0;
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; cin.ignore(); getline(cin, id);

    for (NodeMedicalRecord *p=smr.top;p!=NULL;p=p->next) {
        if (p->medical_record.id == id) {
            sum = sum_price(p->medical_record.stack_medicine);
            break;
        }
    }
    cout << string(TAB_WIDTH, ' ') << "Tong tien cua ho so " << id << ": " << sum <<"d"<<endl;
}
//Đọc ghi file
void input_to_file (StackMedicalRecord smr) {
    fstream f;
    fflush(stdin);
    f.open("MedicalRecord.dat", ios::out);
    if (smr.top != NULL) {
        NodeMedicalRecord *nmr = smr.top;
        while (nmr!=NULL) {
            MedicalRecord mr = nmr->medical_record;
            f << mr.id << "\n";
            f << mr.date_of_creation << "\n";
            f << mr.patient.id << "\n";
            f << size_of (mr.stack_medicine) << "\n";
            for (NodeMedicine *p = mr.stack_medicine.top; p!=NULL; p=p->next) {
                f << p->medicine.id << "\n";
            }
            smr.pop();
            nmr = smr.top;
        }
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <MedicalRecord.dat>" << endl;
}

void output_from_file (StackMedicalRecord &smr, StackPatient sp, StackMedicine sm) {
    fstream f;
    fflush(stdin);
    f.open("MedicalRecord.dat", ios::in);
    smr.init_stack();
    int n, i;
    if (f.is_open()) {
        while(!f.eof()) {
            MedicalRecord mr;
            mr.stack_medicine.init_stack();
            getline(f,mr.id);
            getline(f,mr.date_of_creation);
            getline(f,mr.patient.id);
            if (mr.patient.id == "") break;
            mr.patient = search_stack(sp, mr.patient.id)->patient;
            f >> n;f.ignore();
            for (i=0; i<n; i++) {
                Medicine med;
                getline(f,med.id);
                med = search_stack(sm, med.id)->medicine;
                mr.stack_medicine.push(create_node(med));
            }
            NodeMedicalRecord *nmr = create_node(mr);
            smr.push(nmr);
        }
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu tu file <MedicalRecord.dat>" << endl;
}

//Ham bo sung
void delete_by_id(StackPatient &sp, StackMedicalRecord smr) {
    string id;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);
    //Xoa hsba co benh nhan id day
    StackMedicalRecord new_stack; new_stack.init_stack();

    while (smr.top!=NULL) {
        MedicalRecord a = smr.top->medical_record;
        smr.pop();
        if (a.patient.id != id) {
            new_stack.push(create_node(a));
        }
    }
    while (new_stack.top!=NULL) {
        MedicalRecord a = new_stack.top->medical_record;
        new_stack.pop();
        smr.push(create_node(a));
    }
    //Xoa benh nhan 
    StackPatient nsp; nsp.init_stack();

    while (sp.top!=NULL) {
        Patient b = sp.top->patient;
        sp.pop();
        if (b.id == id) break;
        nsp.push(create_node(b));
    }
    while (nsp.top!=NULL) {
        Patient b = nsp.top->patient;
        new_stack.pop();
        sp.push(create_node(b));
    }

    cout << string(TAB_WIDTH, ' ') << "Da xoa (neu co)" << endl;
}

void delete_by_id(StackMedicine &sm, StackMedicalRecord smr) {
    string id;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);  
    //Xoa thuoc trong ho so
    for (NodeMedicalRecord *p=smr.top;p!=NULL;p=p->next) {
        StackMedicine smed; smed.init_stack();

        while (p->medical_record.stack_medicine.top!=NULL) {
            Medicine med = p->medical_record.stack_medicine.top->medicine;
            p->medical_record.stack_medicine.pop();
            if (med.id != id) {
                smed.push(create_node(med));
            }
        }
        while (smed.top!=NULL) {
            Medicine med = smed.top->medicine;
            p->medical_record.stack_medicine.push(create_node(med));
            smed.pop();
        }
    }
    //Xoa thuoc
    StackMedicine nsm; nsm.init_stack();

    while (sm.top!=NULL) {
        Medicine med = sm.top->medicine;
        sm.pop();
        if (med.id == id) break;
        nsm.push(create_node(med));
    }
    while (nsm.top!=NULL) {
        Medicine med = nsm.top->medicine;
        nsm.pop();
        sm.push(create_node(med));
    }

}

//Menu
void menu () {
    cout << endl << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "QUAN LY PHONG KHAM" << "|" << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "1. Quan ly ho so benh an" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "2. Quan ly benh nhan" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "3. Quan ly thuoc" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "4. Doc toan bo file" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "5. Luu toan bo ra file" << "|" << endl;
    cout <<  string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
}
void menu_medical_record () {
    cout << endl << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "QUAN LY DANH SACH HO SO BENH AN" << "|" << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "1. Nhap danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "2. Hien danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "3. Them ho so benh an" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "4. Xoa ho so benh an" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "5. Sua ho so benh an theo ID" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "6. Sap xep ho so benh an theo ID" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "7. Tim kiem ho so cua benh nhan" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "8. Tong tien cua hoa don theo ID" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "9. Luu file" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "10. Doc file" << "|" << endl;
    cout << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
}

void menu_medicine () {
    cout << endl << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "QUAN LY DANH SACH THUOC" << "|" << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "1. Nhap danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "2. Hien danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "3. Them thuoc" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "4. Xoa thuoc" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "5. Luu file" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "6. Doc file" << "|" << endl;
    cout << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
}

void menu_patient () {
    cout << endl << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "QUAN LY DANH SACH BENH NHAN" << "|" << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "1. Nhap danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "2. Hien danh sach" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "3. Them ho so benh an" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "4. Xoa benh nhan" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "5. Luu file" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "6. Doc file" << "|" << endl;
    cout << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
}
//Chương trình
void stack_qly_hsba (StackMedicalRecord &smr, StackPatient sp, StackMedicine sm) {
    
    int chon_hsba;
    do {
        menu_medical_record();
        cout << string(31, ' ') << "Chon: "; cin >> chon_hsba;
        switch (chon_hsba)
        {
        case 1:
            input_stack(smr, sp, sm);
            break;
        case 2:
            output_stack(smr);
            break;
        case 3:
            cin.ignore();
            add_top(smr, sp, sm);
            break;
        case 4:
            cin.ignore();
            delete_by_id(smr);
            break;
        case 5:
            edit_information(smr,sp,sm);
            break;
        case 6:
            sort_stack(smr);
            cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO SAU KHI SAP XEP" <<endl;
            output_stack(smr);
            break;
        case 7:
            search_mr_by_patient_id (smr, sp);
            break;
        case 8:
            sum_price_by_id(smr);
            break;
        case 9:
            input_to_file(smr);
            break;
        case 10:
            output_from_file(smr,sp,sm);
            break;
        
        default:
            break;
        }
    } while (chon_hsba != 0);
}
void stack_qly_bn (StackPatient &sp, StackMedicalRecord smr, StackMedicine sm) {
    int chon_p;
    do {
        menu_patient();
        cout << string(31, ' ') << "Chon: "; cin >> chon_p;
        switch (chon_p)
        {
        case 1:
            input_stack(sp);
            break;
        case 2:
            output_stack(sp);
            break;
        case 3:
            cin.ignore();
            add_top(sp);
            break;
        case 4:
            delete_by_id(sp, smr);
            break;
        case 5:
            input_to_file(sp);
            break;
        case 6:
            output_from_file(sp);
            break;
        
        default:
            break;
        }
    } while (chon_p != 0);
}
void stack_qly_thuoc (StackMedicine &sm, StackMedicalRecord smr) {
    int chon_m;
    do {
        menu_medicine();
        cout << string(31, ' ') << "Chon: "; cin >> chon_m;
        switch (chon_m)
        {
        case 1:
            input_stack(sm);
            break;
        case 2:
            output_stack(sm);
            break;
        case 3:
            cin.ignore();
            add_top(sm);
            break;
        case 4:
            delete_by_id(sm,smr);
            break;
        case 5:
            input_to_file(sm);
            break;
        case 6:
            output_from_file(sm);
            break;
        
        default:
            break;
        }
    } while (chon_m != 0);
}
void stack_qly_phong_kham() {
    StackMedicine s_medicine; s_medicine.init_stack(); 
    StackPatient s_patient; s_patient.init_stack();
    StackMedicalRecord s_medical_record; 
    s_medical_record.init_stack(); 
    
    int chon;

    do {
        menu();
        cout << string(31, ' ') << "Chon: "; cin >> chon;
        switch (chon)
        {
        case 1:
            stack_qly_hsba(s_medical_record, s_patient, s_medicine);
            break;
        case 2:
            stack_qly_bn(s_patient, s_medical_record, s_medicine);
            break;
        case 3:
            stack_qly_thuoc(s_medicine, s_medical_record);
            break;
        case 4:
            output_from_file(s_medicine);
            output_from_file(s_patient);
            output_from_file(s_medical_record,s_patient,s_medicine);
            break;
        case 5:
            input_to_file(s_medicine);
            input_to_file(s_patient);
            input_to_file(s_medical_record);
            break;
        default:
            break;
        }
    } while (chon != 0);
}

int main() {
    stack_qly_phong_kham();

    return 0;
}