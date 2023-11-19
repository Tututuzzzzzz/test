#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_SUBJECTS = 10;

struct Subject {
    string name;
    float credit;
    float score;
};


struct Student {
    string name;
    string mssv;
    int credits;
    float gpa;
    Subject subject[MAX_SUBJECTS];
    int num_subjects;
};

int num_students = 0;
Student students[MAX_STUDENTS];


void input_subject(Subject &mh, int i) {
    cout << "Nhap ten mon hoc thu " << i << " : ";
    getline(cin, mh.name);
    do {
        cout << "Nhap so tin chi: ";
        cin >> mh.credit;
        cin.ignore();
    } while (mh.credit <= 0);
    do {
        cout << "Nhap diem : ";
        cin >> mh.score;
        cin.ignore();
    } while (mh.score < 0);
}

void input_MSSV(string &mssv , int i) {
    bool check = true;

    do {
        check = true;
        cout << "Nhap ma sinh vien thu " << i << " : ";
        getline(cin, mssv);
        
        // Kiem tra ma so sinh viên da ton tai hay chua
        for (int j = 1; j < i; j++) {
            if (students[j].mssv == mssv) {
                cout << "Ma so sinh vien da ton tai. Vui long nhap lai." << endl;
                check = false;
                break;
            }
        }
        
    } while (!check);
}

void input_name(string &name,int i) {
    cout << "Nhap ten sinh vien thu " << i << " : ";
    getline(cin, name);
}

void input_student(Student &sv, int i) {
    input_MSSV(sv.mssv,i);
    input_name(sv.name,i);
    sv.gpa = 0;

    do {
        cout << "Nhap so luong mon hoc cua sinh vien thu " << i << " : ";
        cin >> students[i].num_subjects;
        cin.ignore();
    } while (sv.num_subjects <= 0);

    for (int j = 1; j <= sv.num_subjects; j++) {
        input_subject(sv.subject[j], j);
    }
}


void input() {
    do {
        cout << "Nhap so luong sinh vien: ";
        cin >> num_students;
        cin.ignore();
    } while (num_students <= 0);

    for (int i = 1; i <= num_students; i++) {
		input_student(students[i], i);
    }
}

void save_students_info() {
    ofstream outFile("output.txt");
    if(outFile.is_open()) {
        outFile << num_students << endl;
        for (int i = 1; i <= num_students; i++) {
        	outFile << " Sinh Vien Thu " << i << " : ";
            outFile << students[i].mssv << " / ";
            outFile << students[i].name << " / ";
            outFile << students[i].credits << " / ";
            outFile << students[i].gpa << endl;
            outFile << "----------------------------------"<< endl;
                
            }
        outFile.close();
        cout << "Da luu thong tin sinh vien vao file\n";
    }
    else {
        cout << "Khong the tao/mo file de luu thong tin sinh vien\n";
    }
}

void load_students_info() {
    ifstream inFile("input.txt");
    if(!inFile.is_open()) {
 		cout << "Khong the mo file de tai thong tin sinh vien\n";
    } 
	else {
        inFile >> num_students;
        inFile.ignore();
        for (int i = 1; i <= num_students; i++) {
            getline(inFile, students[i].mssv);
            getline(inFile, students[i].name);
            inFile >> students[i].num_subjects;
            inFile.ignore();
            for (int j = 1; j <= students[i].num_subjects; j++) {
                getline(inFile, students[i].subject[j].name);
                inFile >> students[i].subject[j].credit;
                inFile.ignore();
                inFile >> students[i].subject[j].score;
				inFile.ignore();                
            }
    	}
    	inFile.close();
        cout << "Da tai thong tin sinh vien tu file\n";
    }
}


void edit_info() {
    string id;
    cout << "Nhap ma so sinh vien muon sua: ";
    getline(cin, id);

    bool found = false;
    for (int i = 1; i <= num_students; i++) {
        if (students[i].mssv == id) {
            found = true;

            int choice;
            do {
                cout << "Chon thong tin muon sua: " << endl;
                cout << "1. Ten" << endl;
                cout << "2. Mon hoc" << endl;
                cout << "0. Thoat" << endl;
                cout << "Nhap lua chon: ";
                cin >> choice;

                cin.ignore();

                switch (choice) {
                    case 1: {
                        cout << "Nhap lai ten: ";
                        getline(cin, students[i].name);
                        break;
                    }
                    case 2: {
                        int num_subjects = students[i].num_subjects;
                        int subject_choice;

                        do {
                            cout << "Nhap ma mon hoc muon sua (1-" << num_subjects << "): ";
                            cin >> subject_choice;

                            cin.ignore();

                            if (subject_choice < 1 || subject_choice > num_subjects) {
                                cout << "Lua chon khong hop le, vui long nhap lai\n";
                            }
                        } while (subject_choice < 1 || subject_choice > num_subjects);

                        cout << "Nhap lai ten mon hoc: ";
                        getline(cin, students[i].subject[subject_choice - 1].name);

                        cout << "Nhap lai so tin chi: ";
                        cin >> students[i].subject[subject_choice - 1].credit;

                        cout << "Nhap lai diem so: ";
                        cin >> students[i].subject[subject_choice - 1].score;

                        cin.ignore();
                        break;
                    }
                    case 0: {
                        break;
                    }
                    default: {
                        cout << "Lua chon khong hop le, vui long nhap lai\n";
                        break;
                    }
                }
            } while (choice != 0);

            cout << "Da cap nhat thong tin cho ma so sinh vien " << id << endl;

            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien co ma so " << id << endl;
    }
}

void cal_gpa(){
    for(int i = 1 ; i <= num_students ; i++ ){
    	int totalScore = 0;
    	int totalCredit = 0;
	    for (int j = 1; j <= students[i].num_subjects; j++) {
	      totalScore += students[i].subject[j].score * students[i].subject[j].credit;
	      totalCredit += students[i].subject[j].credit;
	    }
	    double averageScore = (double)totalScore / (double)totalCredit;
	
	    students[i].gpa = averageScore ;
	    students[i].credits = totalCredit;
		}

}

void print_student(Student& sv) {
			cout << setw(13) << left << sv.mssv;
			cout << setw(20) << left << sv.name;
			cout << setw(22) << left << sv.num_subjects;
			cout << setw(13) << left << sv.credits;
			cout << setw(15) << left << sv.gpa << endl;
}

void print() {
	cout << setw(13) << left << "MSSV";
	cout << setw(20) << left << "Ho va ten";
	cout << setw(22) << left << "Tong so mon hoc";
	cout << setw(13) << left << "Tong so tin chi";	
	cout << setw(15) << left << "GPA" << endl;
    for (int i = 1; i <= num_students; i++) {
        print_student(students[i]);
        cout << "---------------------------------------------------------" << endl;
    }
}

void search() {
    string id;
    cout << "Nhap ma sinh vien can tim kiem: ";
    getline(cin,id);
    for (int i = 1; i <= num_students; i++) {
        if (students[i].mssv == id) {
            print_student(students[i]);
            return;
        }
    }
    cout << "Khong tim thay sinh vien co ma " << id << endl;
}

void remove() {
    string id;
    cout << "Nhap ma sinh vien can xoa: ";
	getline(cin,id);
    for (int i = 1; i <= num_students; i++) {
        if (students[i].mssv == id) {
            for (int j = i; j <= num_students - 1; j++) {
                students[j] = students[j + 1];
            }
            num_students--;
            cout << "Da xoa sinh vien co ma " << id << endl;
            return;
        }
    }
    cout << "Khong tim thay sinh vien co ma " << id << endl;
}

void statistics() {
    float gpa_max = 0, gpa_min = 10, gpa_avg = 0;
    string name_max, name_min, mssv_max, mssv_min;
    for (int i = 1; i <= num_students; i++) {
        gpa_avg += students[i].gpa / num_students;
        if (students[i].gpa > gpa_max) {
            gpa_max = students[i].gpa;
            name_max = students[i].name;
            mssv_max = students[i].mssv;
        }
        if (students[i].gpa < gpa_min) {
            gpa_min = students[i].gpa;
            name_min = students[i].name;
            mssv_max = students[i].mssv;
        }
    }
    cout << "Thong ke:\n";
    cout << "Diem TB cao nhat: " << gpa_max <<", ma so: " << mssv_max << ", sinh vien: " << name_max << endl;
    cout << "Diem TB thap nhat: " << gpa_min <<", ma so: " << mssv_min << ", sinh vien: " << name_min << endl;
}



int main() {
    int option;
    
    do {
        cout << "========== MENU ==========\n";
        cout << "1. Nhap sinh vien\n";
        cout << "2. Luu thong tin sinh vien vao tep tin\n";
        cout << "3. Tai thong tin sinh vien tu tep tin\n";
        cout << "4. Sua thong tin sinh vien\n";
        cout << "5. Tim kiem sinh vien\n";
        cout << "6. Xoa sinh vien\n";
        cout << "7. Thong ke\n";
        cout << "8. Xem danh sach sinh vien\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Ban chon: ";
        cin >> option;
        cin.ignore();
        switch (option) {
            case 1:
                input();
                cal_gpa();
                break;
            case 2:
                save_students_info();
                break;
            case 3:
                load_students_info();
				cal_gpa();
                break;
            case 4:
                edit_info();
                cal_gpa();
                break;
            case 5:
                search();
                break;
            case 6:
                remove();
                break;
            case 7:
            	statistics();
            	break;
            case 8:
            	print();
            	break;
            case 0:
            	break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (option != 0);

    return 0;
}
            	

