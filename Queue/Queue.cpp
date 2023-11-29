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
//Queue Thuốc
struct QueueMedicine {
    NodeMedicine *rear, *front;//rear->...->...->front->NULL
    void init_queue() {
        rear = front = NULL;
    }

    void en_queue (NodeMedicine *node_medicine) {
        if (rear == NULL) {
            rear = front = node_medicine;
        } else {
            node_medicine->next = rear;
            rear = node_medicine;
        }
    }

    void de_queue () {
        if (front == NULL) {
            cout << "Hang doi rong";
            return;
        }
        if (rear->next == NULL) {
            rear = front = NULL;
            return;
        }
        NodeMedicine *p=rear;
        while (p->next != front) p=p->next;
        front = p;
        p = p->next;
        front->next = NULL;
        delete p;
    }

    void delete_first () {
        if (rear == NULL) {
            cout << "Hang doi rong";
            return;
        }
        NodeMedicine *p=rear;
        rear = p->next;
        p->next = NULL;
        delete p;
    }
};
void add_top (QueueMedicine &qmed) {
    Medicine med; med.input_from_keyboard();
    NodeMedicine *nmed = create_node(med);
    qmed.en_queue(nmed);
}
void input_queue (QueueMedicine &qmed) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong thuoc: "; cin >> n;
    qmed.init_queue();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(qmed);
        cin.ignore();
    }
}
void output_queue (QueueMedicine qmed) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH THUOC" << endl;
    cout << string(TAB_WIDTH, ' ') << setw(10) << left << "ID"
		 << setw(25) << left << "Ten thuoc"
		 << setw(25) << left << "Cong dung"
		 << setw(11) << right << "Gia tien"
		 << setw(17) << right << "Lieu luong" << endl;
    for (NodeMedicine *nmed = qmed.rear; nmed!=NULL; nmed=nmed->next) {
        nmed->medicine.output_screen();
    }
}
NodeMedicine *search_queue (QueueMedicine qmed, string id) {
    for (NodeMedicine *p = qmed.rear; p!=NULL; p=p->next) {
        if (p->medicine.id == id) {
            return p;
        }
    }
    return NULL;
}
int size_of (QueueMedicine qmed) {
    int size = 0;
    for (NodeMedicine *p = qmed.rear; p!=NULL; p=p->next) {
        size++;
    }
    return size;
}
//Đọc ghi file thuốc
void input_to_file (QueueMedicine qmed) {
    fstream f;
    fflush(stdin);
    f.open("Medicine.dat", ios::out);
    if (qmed.rear != NULL) {
        NodeMedicine *nmed = qmed.rear;
        while (nmed!=NULL) {
            Medicine med = nmed->medicine;
            f << med.id << "\n";
            f << med.name << "\n";
            f << med.uses << "\n";
            f << med.price << "\n";
            f << med.medication_dosage << "\n";
            nmed = nmed -> next;
        }
        cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <Medicine.dat>";
    }
    f.close();
}
void output_from_file (QueueMedicine &qmed) {
    fstream f;
    fflush(stdin);
    f.open("Medicine.dat", ios::in);
    qmed.init_queue();
    if (f.is_open()) {
        while(!f.eof()) {
            Medicine med;
            getline(f, med.id);
            getline(f, med.name);
            getline(f, med.uses);
            f >> med.price;
            f >> med.medication_dosage; f.ignore();
            NodeMedicine *nmed = create_node(med);
            qmed.en_queue(nmed);
        }
        qmed.delete_first();
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
struct QueuePatient {
    NodePatient *rear, *front;

    void init_queue () {
        rear = front = NULL;
    }

    void en_queue (NodePatient *node_patient) {
        if (rear == NULL) {
            rear = front = node_patient;
        } else {
            node_patient->next = rear;
            rear = node_patient;
        }
    }

    void de_queue () {
        if (front == NULL) {
            cout << "Hang doi rong";
            return;
        }
        if (rear->next == NULL) {
            rear = front = NULL;
            return;
        }
        NodePatient *p=rear;
        while (p->next != front) p=p->next;
        front = p;
        p = p->next;
        front->next = NULL;
        delete p;
    }

    void delete_first () {
        if (rear == NULL) {
            cout << "Hang doi rong";
            return;
        }
        NodePatient *p=rear;
        rear = p->next;
        p->next = NULL;
        delete p;
    }
};
void add_top (QueuePatient &qpat) {
    Patient pat; pat.intput_from_keyboard();
    NodePatient *npat = create_node(pat);
    qpat.en_queue(npat);
}
void input_queue (QueuePatient &qpat) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong benh nhan: "; cin >> n;
    qpat.init_queue();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(qpat);
    }
}
void output_queue (QueuePatient qpat) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH BENH NHAN" << endl;
    for (NodePatient *npat = qpat.rear; npat!=NULL; npat=npat->next) {
        npat->patient.output_screen(); cout << endl;
    }
}
NodePatient *search_queue (QueuePatient qpat, string id) {
    for (NodePatient *p = qpat.rear; p!=NULL; p=p->next) {
        if (p->patient.id == id) {
            return p;
        }
    }
    return NULL;
}
//Đọc ghi file
void input_to_file (QueuePatient qpat) {
    fstream f;
    fflush(stdin);
    f.open("Patient.dat", ios::out);
    if (qpat.rear != NULL) {
        NodePatient *npat = qpat.rear;
        while (npat!=NULL) {
            Patient pat = npat->patient;
            f << pat.id << "\n";
            f << pat.name << "\n";
            f << pat.age << "\n";
            f << pat.address << "\n";
            f << pat.number_phone_of_guardian << "\n";
            f << pat.disease_name << "\n";
            npat = npat -> next;
        }
        cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <Patient.dat>";
    }
    f.close();
}

void output_from_file (QueuePatient &qpat) {
    fstream f;
    fflush(stdin);
    f.open("Patient.dat", ios::in);
    qpat.init_queue();
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
            qpat.en_queue(npat);
        }
        qpat.delete_first ();
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu tu file <Patient.dat>" << endl;
}
//Hồ sơ bệnh án
struct MedicalRecord : MedicalRecordBase {
    QueueMedicine queue_medicine ;

    void input(QueuePatient qp, QueueMedicine qm) {
        if (qp.rear == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Danh sach benh nhan rong"; return;
        }
        if (qm.rear == NULL) {
            cout << string(TAB_WIDTH, ' ') << "Danh sach thuoc rong"; return;
        }

        input_from_keyboard();

        do {
            cout << string(TAB_WIDTH, ' ') << "Nhap id benh nhan: "; getline(cin, patient.id);
            if (search_queue(qp, patient.id)) {
                patient = search_queue(qp, patient.id)->patient;
                break;
            }
            cout << string(TAB_WIDTH, ' ') << "Xin moi nhap lai!!!" << endl;
        } while (true);

        int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong thuoc: "; cin >> n;
        queue_medicine.init_queue();
        cin.ignore();
        for (int i=0;i<n;i++) {
            Medicine med;
            do {
                cout << string(TAB_WIDTH, ' ') << "Nhap id thuoc: "; getline(cin, med.id);
                if (search_queue(qm, med.id)) {
                    med = search_queue(qm, med.id)->medicine;
                    break;
                }
                cout << string(TAB_WIDTH, ' ') << "Xin moi nhap lai!!!" << endl;
            } while (true);
            
            NodeMedicine *nmed = create_node(med);
            queue_medicine.en_queue(nmed);
        }
    }
    void output() {
        cout << "\n";
        output_screen();
        patient.output_screen();
        output_queue(queue_medicine);
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
//Queue HSBA
struct QueueMedicalRecord
{
    NodeMedicalRecord *rear, *front;

    void init_queue () {
        rear = front = NULL;
    }

    void en_queue (NodeMedicalRecord *node_medical_record) {
        if (rear == NULL) {
            rear = front = node_medical_record;
        } else {
            node_medical_record->next = rear;
            rear = node_medical_record;
        }
    }

    void de_queue () {
        if (front == NULL) {
            cout << "Hang doi rong";
            return;
        }
        if (rear->next == NULL) {
            rear = front = NULL;
            return;
        }
        NodeMedicalRecord *p=rear;
        while (p->next != front) p=p->next;
        front = p;
        p = p->next;
        front->next = NULL;
        delete p;
    }
    void delete_first () {
        if (rear == NULL) {
            cout << "Hang doi rong";
            return;
        }
        NodeMedicalRecord *p=rear;
        rear = p->next;
        p->next = NULL;
        delete p;
    }
};
void add_top (QueueMedicalRecord &qmr, QueuePatient qp, QueueMedicine qm) {
    MedicalRecord mr; mr.input(qp,qm);
    NodeMedicalRecord *nmr = create_node(mr);
    qmr.en_queue(nmr);
}
void input_queue (QueueMedicalRecord &qmr, QueuePatient qp, QueueMedicine qm) {
    int n; cout << string(TAB_WIDTH, ' ') << "Nhap so luong ho so: "; cin >> n;
    qmr.init_queue();
    cin.ignore();
    for (int i=0;i<n;i++) {
        add_top(qmr, qp, qm);
    }
}
void output_queue (QueueMedicalRecord qmr) {
    cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO BENH AN" << endl;
    for (NodeMedicalRecord *nmr = qmr.rear; nmr!=NULL; nmr=nmr->next) {
        nmr->medical_record.output();
    }
}
NodeMedicalRecord *search_queue (QueueMedicalRecord qmr, string id) {
    for (NodeMedicalRecord *p = qmr.rear; p!=NULL; p=p->next) {
        if (p->medical_record.id == id) {
            return p;
        }
    }
    return NULL;
}
//Xóa HSBA
void delete_by_id (QueueMedicalRecord &qmr) {
    QueueMedicalRecord new_queue; new_queue.init_queue();
    string id;
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);

    while (qmr.front!=NULL) {
        MedicalRecord p = qmr.front->medical_record;
        qmr.de_queue();
        if (p.id != id) {
            new_queue.en_queue(create_node(p));
        }
    }
    qmr.init_queue(); qmr = new_queue;
    cout << string(TAB_WIDTH, ' ') << "Da xoa (neu co)" << endl;
}
//Sửa thông tin HSBA
void edit_information (QueueMedicalRecord &qmr, QueuePatient qp, QueueMedicine qm) {
    string id;
    int chon_hs;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id hsba can sua: "; getline(cin, id);
    QueueMedicalRecord new_queue; new_queue.init_queue();

    NodeMedicalRecord *p = search_queue(qmr, id);
    if (p==NULL) {
        cout << string(TAB_WIDTH, ' ') << "Khong tim thay ho so" << endl;
        return;
    } else {
        MedicalRecord new_med;
        new_med.input(qp, qm);

        p->medical_record = new_med;
    }
    cout << string(TAB_WIDTH, ' ') << "HO SO BENH AN SAU KHI SUA" << endl;
    p->medical_record.output();
}
//Sắp xếp theo thứ tự tăng dần id khi in ra
void sort_queue (QueueMedicalRecord &qmr) {
    for (NodeMedicalRecord *p=qmr.rear;p->next!=NULL;p=p->next) {
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
void search_mr_by_patient_id (QueueMedicalRecord qmr, QueuePatient qp) {
    string id;
    cout << string(TAB_WIDTH, ' ') << "Nhap id benh nhan: "; cin.ignore(); getline(cin, id);

    if (!search_queue(qp,id)) {
        cout << string(TAB_WIDTH, ' ') << "Khong tim thay benh nhan" << endl;
        return;
    }
    cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO CUA BENH NHAN " << id << endl;
    QueueMedicalRecord new_queue; new_queue.init_queue();
    while (qmr.front!=NULL) {
        MedicalRecord mr = qmr.front->medical_record;
        if (mr.patient.id == id) 
            mr.output();
        qmr.de_queue();
        new_queue.en_queue(create_node(mr));
    }
    qmr.init_queue(); qmr = new_queue;
}
//Đọc ghi file
void input_to_file (QueueMedicalRecord qmr) {
    fstream f;
    fflush(stdin);
    f.open("MedicalRecord.dat", ios::out);
    if (qmr.rear != NULL) {
        NodeMedicalRecord *nmr = qmr.rear;
        while (nmr!=NULL) {
            MedicalRecord mr = nmr->medical_record;
            f << mr.id << "\n";
            f << mr.date_of_creation << "\n";
            f << mr.patient.id << "\n";
            f << size_of (mr.queue_medicine) << "\n";
            for (NodeMedicine *p = mr.queue_medicine.rear; p!=NULL; p=p->next) {
                f << p->medicine.id << "\n";
            }
            nmr = nmr->next;
        }
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu ra file <MedicalRecord.dat>" << endl;
}
void output_from_file (QueueMedicalRecord &qmr, QueuePatient qp, QueueMedicine qm) {
    fstream f;
    fflush(stdin);
    f.open("MedicalRecord.dat", ios::in);
    qmr.init_queue();
    int n, i;
    if (f.is_open()) {
        while(!f.eof()) {
            MedicalRecord mr;
            mr.queue_medicine.init_queue();
            getline(f,mr.id);
            getline(f,mr.date_of_creation);
            getline(f,mr.patient.id);
            if (mr.patient.id == "") break;
            mr.patient = search_queue(qp, mr.patient.id)->patient;
            f >> n;f.ignore();
            for (i=0; i<n; i++) {
                Medicine med;
                getline(f,med.id);
                med = search_queue(qm, med.id)->medicine;
                mr.queue_medicine.en_queue(create_node(med));
            }
            NodeMedicalRecord *nmr = create_node(mr);
            qmr.en_queue(nmr);
        }
    }
    f.close();
    cout << endl << string(TAB_WIDTH, ' ') << "Da xuat du lieu tu file <MedicalRecord.dat>" << endl;
}
//Ham bo sung
void delete_by_id(QueuePatient &qp, QueueMedicalRecord qmr) {
    string id;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);
    //Xoa hsba co benh nhan id day
    QueueMedicalRecord new_queue; new_queue.init_queue();

    while (qmr.front!=NULL) {
        MedicalRecord mr = qmr.front->medical_record;
        qmr.de_queue();
        if (mr.patient.id != id) {
            new_queue.en_queue(create_node(mr));
        }
    }
    while (new_queue.front!=NULL) {
        MedicalRecord mr = new_queue.front->medical_record;
        new_queue.de_queue();
        qmr.en_queue(create_node(mr));
    }
    //Xoa benh nhan 
    QueuePatient nqp; nqp.init_queue();

    while (qp.front!=NULL) {
        Patient p = qp.front->patient;
        qp.de_queue();
        if (p.id == id) break;
        nqp.en_queue(create_node(p));
    }
    while (nqp.front!=NULL) {
        Patient p = nqp.front->patient;
        new_queue.de_queue();
        qp.en_queue(create_node(p));
    }

    cout << string(TAB_WIDTH, ' ') << "Da xoa (neu co)" << endl;
}
void delete_by_id(QueueMedicine &qm, QueueMedicalRecord qmr) {
    string id;
    cin.ignore();
    cout << string(TAB_WIDTH, ' ') << "Nhap id: "; getline (cin, id);  
    //Xoa thuoc trong ho so
    for (NodeMedicalRecord *p=qmr.rear;p!=NULL;p=p->next) {
        QueueMedicine qmed; qmed.init_queue();

        while (p->medical_record.queue_medicine.front!=NULL) {
            Medicine med = p->medical_record.queue_medicine.front->medicine;
            p->medical_record.queue_medicine.de_queue();
            if (med.id != id) {
                qmed.en_queue(create_node(med));
            }
        }
        while (qmed.front!=NULL) {
            Medicine med = qmed.front->medicine;
            p->medical_record.queue_medicine.en_queue(create_node(med));
            qmed.de_queue();
        }
    }
    //Xoa thuoc
    QueueMedicine nqm; nqm.init_queue();

    while (qm.front!=NULL) {
        Medicine med = qm.front->medicine;
        qm.de_queue();
        if (med.id == id) break;
        nqm.en_queue(create_node(med));
    }
    while (nqm.front!=NULL) {
        Medicine med = nqm.front->medicine;
        nqm.de_queue();
        qm.en_queue(create_node(med));
    }
}
//Menu
void menu () {
    cout << endl << string(TAB_WIDTH, ' ')  << string(97, '-') << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "QUAN LY PHONG KHAM" << "|" << endl;
    cout << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "1. Quan ly ho so benh an" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "2. Quan ly benh nhan" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "3. Quan ly thuoc" << "|" << endl;
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
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "6. Sap xep ho so benh an theo id" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "7. Tim kiem ho so cua benh nhan" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "8. Luu file" << "|" << endl
         << string(TAB_WIDTH, ' ') << "|" << string(TAB_WIDTH, ' ') << setw(WIDTH_MENU) << left << "9. Doc file" << "|" << endl;
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
void queue_qly_hsba (QueueMedicalRecord &qmr, QueuePatient qp, QueueMedicine qm) {
    
    int chon_hsba;
    do {
        menu_medical_record();
        cout << string(31, ' ') << "Chon: "; cin >> chon_hsba;
        switch (chon_hsba)
        {
        case 1:
            input_queue(qmr, qp, qm);
            break;
        case 2:
            output_queue(qmr);
            break;
        case 3:
            cin.ignore();
            add_top(qmr, qp, qm);
            break;
        case 4:
            cin.ignore();
            delete_by_id(qmr);
            break;
        case 5:
            edit_information(qmr,qp,qm);
            break;
        case 6:
            sort_queue(qmr);
            cout << string(TAB_WIDTH, ' ') << "DANH SACH HO SO SAU KHI SAP XEP" <<endl;
            output_queue(qmr);
            break;
        case 7:
            search_mr_by_patient_id (qmr, qp);
            break;
        case 8:
            input_to_file(qmr);
            break;
        case 9:
            output_from_file(qmr,qp,qm);
            break;
        
        default:
            break;
        }
    } while (chon_hsba != 0);
}
void queue_qly_bn (QueuePatient &qp, QueueMedicalRecord qmr, QueueMedicine qm) {
    int chon_p;
    do {
        menu_patient();
        cout << string(31, ' ') << "Chon: "; cin >> chon_p;
        switch (chon_p)
        {
        case 1:
            input_queue(qp);
            break;
        case 2:
            output_queue(qp);
            break;
        case 3:
            cin.ignore();
            add_top(qp);
            break;
        case 4:
            delete_by_id(qp, qmr);
            break;
        case 5:
            input_to_file(qp);
            break;
        case 6:
            output_from_file(qp);
            break;
        
        default:
            break;
        }
    } while (chon_p != 0);
}
void queue_qly_thuoc (QueueMedicine &qm, QueueMedicalRecord qmr) {
    int chon_m;
    do {
        menu_medicine();
        cout << string(31, ' ') << "Chon: "; cin >> chon_m;
        switch (chon_m)
        {
        case 1:
            input_queue(qm);
            break;
        case 2:
            output_queue(qm);
            break;
        case 3:
            cin.ignore();
            add_top(qm);
            break;
        case 4:
            delete_by_id(qm,qmr);
            break;
        case 5:
            input_to_file(qm);
            break;
        case 6:
            output_from_file(qm);
            break;
        
        default:
            break;
        }
    } while (chon_m != 0);
}
void queue_qly_phong_kham() {
    QueueMedicine q_medicine; q_medicine.init_queue(); output_from_file(q_medicine);
    QueuePatient q_patient; q_patient.init_queue(); output_from_file(q_patient);
    QueueMedicalRecord q_medical_record; 
    q_medical_record.init_queue(); 
    output_from_file(q_medical_record,q_patient,q_medicine);
    
    int chon;

    do {
        menu();
        cout << string(31, ' ') << "Chon: "; cin >> chon;
        switch (chon)
        {
        case 1:
            queue_qly_hsba(q_medical_record, q_patient, q_medicine);
            break;
        case 2:
            queue_qly_bn(q_patient, q_medical_record, q_medicine);
            break;
        case 3:
            queue_qly_thuoc(q_medicine, q_medical_record);
            break;
        
        default:
            break;
        }
    } while (chon != 0);
}

int main() {
    queue_qly_phong_kham();
    
    return 0;
}