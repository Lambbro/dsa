#pragma once

#include<iostream>
#include<iomanip>
#include<string.h>

#define TAB_WIDTH 15
#define WIDTH_MENU 80
#define SNGLBENHNHAN "SNGLBENHNHAN.dat"
#define SNGLTHUOC "SNGLTHUOC.dat"

using namespace std;

// define struct
struct Patient { // Benh nhan
	string id, name, address, number_phone_of_guardian, disease_name;
	int age;

	inline void intput_from_keyboard () {
		cout << string(TAB_WIDTH, ' ') << "Id benh nhan: "; getline(cin, id);
		cout << string(TAB_WIDTH, ' ') << "Ten benh nhan: "; getline(cin, name);
		do {
			cout << string(TAB_WIDTH, ' ') << "Nhap tuoi benh nhan: "; cin >> age;
			if (age <= 0 || age >= 150) {
				cout << string(TAB_WIDTH, ' ') << "Tuoi benh nhan khong hop le! Vui long nhap lai." << endl;
			}
		} while (age <= 0 || age >= 150);
		cin.ignore();
		cout << string(TAB_WIDTH, ' ') << "Dia chi: "; getline(cin, address);
		cout << string(TAB_WIDTH, ' ') << "SDT nguoi than: "; getline(cin, number_phone_of_guardian);
		cout << string(TAB_WIDTH, ' ') << "Benh: "; getline(cin, disease_name);
	}
	inline void output_screen () {
		cout << string(TAB_WIDTH, ' ') << "BENH NHAN " << id << endl;
		cout << string(TAB_WIDTH, ' ') << "Ten: " << name << endl
			 << string(TAB_WIDTH, ' ') << "Tuoi: " << age << endl
			 << string(TAB_WIDTH, ' ') << "Dia chi: " << address << endl
			 << string(TAB_WIDTH, ' ') << "SDT nguoi than: " << number_phone_of_guardian << endl
			 << string(TAB_WIDTH, ' ') << "Bi benh: " << disease_name << endl;
	}
};

struct Medicine { // Thuoc
	string id, name, uses;
	float price, medication_dosage;
	
	inline void input_from_keyboard () {
		cout << string(TAB_WIDTH, ' ') << "ID: "; getline(cin, id);
		cout << string(TAB_WIDTH, ' ') << "Ten: "; getline(cin, name);
		cout << string(TAB_WIDTH, ' ') << "Cong dung: "; getline(cin, uses);
		cout << string(TAB_WIDTH, ' ') << "Gia tien: "; cin >> price;
		cout << string(TAB_WIDTH, ' ') << "Lieu luong: "; cin >> medication_dosage;
	}
	inline void output_screen () {
		cout << string(TAB_WIDTH, ' ') << setw(10) << left << id
			<< setw(25) << left << name
			<< setw(25) << left << uses
			<< setw(10) << right << price <<"d"
			<< setw(15) << right << medication_dosage << "ml" << endl;
	}
};

// define struct node
struct NodePatient {
	Patient patient;
	NodePatient *next;
};
struct NodeMedicine {
	Medicine medicine;
	NodeMedicine *next;
};

struct MedicalRecordBase { // ho so benh an
	string id, date_of_creation;
	Patient patient;
	float discount;
	
	inline void input_from_keyboard () {
		cout << string(TAB_WIDTH, ' ') << "ID: "; getline(cin, id);
		cout << string(TAB_WIDTH, ' ') << "Ngay kham: "; getline(cin, date_of_creation);
	}
	inline void output_screen () {
		cout << string(TAB_WIDTH, ' ') << "HO SO BENH AN " << id << endl
			 << string(TAB_WIDTH, ' ') << "Ngay kham: " << date_of_creation << endl;
	}
};