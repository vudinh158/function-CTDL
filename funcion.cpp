#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct SinhVien {
	string maSV;
	string hoTen;
};

struct MonHoc {
	string maMH;
	string monHoc;
};

struct DangKyLopTinChi {
	string maMH;
	string monHoc;
	int nhom;
	int soSV;
	int soSlotTrong;
};

struct LopHoc {
	string maLop;
	string lopMH;
	SinhVien* danhSachSV;
	MonHoc* danhsachMH;
	
	int soluongMH;
	int memory;
	
	int soLuongSV;
	int capacity;
	
	
	LopHoc(string ma, int cap) : maLop(ma), capacity(cap) {
		danhsachMH = new MonHoc[memory];
		danhSachSV = new SinhVien[capacity];
		soLuongSV = 0;
		soluongMH = 0;
	}
	
	~LopHoc() {
		delete[] danhSachSV;
		delete[] danhsachMH;
	}
	
	void addSV() {
		string ma;
		string ten;
		cin.ignore();
//		cout<<"Nhap ma sinh vien: ";
//		getline(cin, ma);
		
		while(soLuongSV < capacity) {
			cout<<"Nhap ho va ten SV: ";
			getline(cin, ten);
			cout<<"Nhap ma SV: ";
			getline(cin, ma);
			danhSachSV[soLuongSV].maSV = ma;
			danhSachSV[soLuongSV].hoTen = ten;
			
			soLuongSV++;
			
			
		}
		pushData();
	}
	
	void addMH() {
		string ma;
		string tenMH;
		cin.ignore();
		
		while(soluongMH < memory) {
			cout<<"Nhap ten mon hoc: ";
			getline(cin, tenMH);
			cout<<"Nhap ma mon hoc: ";
			getline(cin,ma);
			danhsachMH[soluongMH].maMH = ma;
			danhsachMH[soluongMH].monHoc = tenMH;
			
			soLuongSV++;
		}
	}
	
	void deleteSV() {
		string ma;
		cout<<"Nhap ma SV can xoa: ";
		getline(cin, ma);
		
		int index = -1;
		
		for(int i = 0; i < soLuongSV; i++) {
			if(danhSachSV[i].maSV == ma) {
				index = i;
				break;
			}
		}
		if(index != -1) {
			danhSachSV[index] = danhSachSV[soLuongSV - 1];
			soLuongSV--;
		} else {
			cout<<"Khong tim thay ma SV can xoa"<<endl;
		}
		pushData();
	}
	
	void hieuChinhSV() {
		string ma, ten;
		cout<<"Nhap ma SV can sua: ";
		getline(cin, ma);
		
		for(int i = 0; i < soLuongSV; i++) {
			if(danhSachSV[i].maSV == ma) {
				cout<<"Nhap ho va ten SV moi: ";
				getline(cin, ten);
				danhSachSV[i].hoTen = ten;
				pushData();
				return;
			}
		}
		
		cout<<"Khong tim thay ma SV can xoa"<<endl;
		pushData();
	}
	
	void inDanhSach() {
        for (int i = 0; i < soLuongSV - 1; ++i) {
            for (int j = 0; j < soLuongSV - i - 1; ++j) {
                if ((danhSachSV[j].hoTen + danhSachSV[j].maSV) > (danhSachSV[j + 1].hoTen + danhSachSV[j + 1].maSV)) {
                    // Swap
                    SinhVien temp = danhSachSV[j];
                    danhSachSV[j] = danhSachSV[j + 1];
                    danhSachSV[j + 1] = temp;
                }
            }
        }

        std::cout << "Danh sach SV cua lop " << maLop << ":\n";
        for (int i = 0; i < soLuongSV; ++i) {
            std::cout << "Ma SV: " << danhSachSV[i].maSV << ", Ho ten: " << danhSachSV[i].hoTen << std::endl;
        }
    }
    
    ////// Xu ly mon hoc ////////
    
    
    
    ////// Xu ly du lieu ////////
    
    void pushData() {
    	ofstream outFile("sinhvien.txt");
    	
    	if(outFile.is_open()) {
    		outFile << maLop <<endl;
    		outFile << soLuongSV << endl;
    		
    		for(int i = 0; i < soLuongSV; i++) {
    			outFile << danhSachSV[i].maSV << endl;
    			outFile << danhSachSV[i].hoTen << endl;
			}
			
			outFile.close();
			cout<<"Da luu tru vao File.....\n";
		} else {
			cerr<<"Can't open data file.....\n";
		}
	}
	
	void readFile() {
		ifstream inFile("sinhvien.txt");
		
		if(inFile.is_open()) {
			getline(inFile, maLop);
			inFile>>soLuongSV;
			inFile.ignore();
			
			for(int i = 0; i < soLuongSV; i++) {
				getline(inFile, danhSachSV[i].maSV);
				getline(inFile, danhSachSV[i].hoTen);
			}
			
			inFile.close();
			cout<<"Da doc file....\n";
		} else {
			cerr<<"Khong the mo file doc...\n";
		}
	}
};

//////hieu chinh mon hoc////////////

bool checkMonHoc(const vector<MonHoc>& danhSachMonHoc, const string& maMH) {
	for(int i = 0; i < danhSachMonHoc.size(); i++) {
		if(danhSachMonHoc[i].maMH == maMH) {
			return true;
		}
	}
	return false;
}



void moLopTinChi(std::vector<DangKyLopTinChi>& danhSachLopTinChi, vector<MonHoc>& danhSachMonHoc) {
    DangKyLopTinChi lop;
    std::cout << "Nhap ma MH: ";
    std::cin >> lop.maMH;
    
    if(!checkMonHoc(danhSachMonHoc, lop.maMH)) {
    	MonHoc monHoc;
    	monHoc.maMH = lop.maMH;
    	cout<<"Nhap ten mon hoc: ";
    	cin.ignore();
    	getline(cin, monHoc.monHoc);
    	danhSachMonHoc.push_back(monHoc);
	}
    
    std::cout << "Nhap ten MH: ";
    std::cin.ignore();
    std::getline(std::cin, lop.monHoc);
    std::cout << "Nhap nhom: ";
    std::cin >> lop.nhom;
    std::cout << "Nhap so luong SV: ";
    std::cin >> lop.soSV;
    std::cout << "Nhap so slot trong: ";
    std::cin >> lop.soSlotTrong;

    danhSachLopTinChi.push_back(lop);
}

vector<MonHoc> deteleMonHoc(vector<MonHoc>& danhSachMonHoc	, const string& maMH) {
	vector<MonHoc> newDanhSachMonHoc;
	
	bool daXoa = false;
	size_t i = 0;
    while (i < danhSachMonHoc.size()) {
        if (danhSachMonHoc[i].maMH != maMH) {
            newDanhSachMonHoc.push_back(danhSachMonHoc[i]); // Sao chép các ph?n t? không ph?i là môn h?c c?n xóa
            ++i;
        } else {
            daXoa = true;
            ++i; // Chuy?n sang ph?n t? ti?p theo mà không sao chép
        }
    }
	if(daXoa) {
		return newDanhSachMonHoc;
	} else {
		return danhSachMonHoc;
	}
}

void hienThiMonHoc(vector<MonHoc>& danhSachMonHoc) {
	cout<<"Danh sach mon hoc:\n";
	size_t i = 0;
    while (i < danhSachMonHoc.size()) {
        const MonHoc& monHoc = danhSachMonHoc[i];
        std::cout << "Ma MH: " << monHoc.maMH << ", Ten MH: " << monHoc.monHoc << std::endl;
        ++i;
    }
}

void hienChinhMonHoc(vector<DangKyLopTinChi>& danhSachLopTinChi, vector<MonHoc>& danhSachMonHoc) {
	
	
	int choice;
	do {
		cout<<"=======HIEU CHINH MON HOC=======\n";
		cout<<"1. Mo lop tin chi\n";
		cout<<"2. Hien thi danh sach mon\n";
		cout<<"3. Xoa mon hoc\n";
		cout<<"0. Quay lai\n";
		cout<<"Nhap lua chon cua ban: ";
		cin>>choice;
		
		switch (choice) {
            case 1:
                moLopTinChi(danhSachLopTinChi, danhSachMonHoc);
                break;
            case 2:
                hienThiMonHoc(danhSachMonHoc);
                break;
            case 3: {
                std::string maMH;
                std::cout << "Nhap ma MH can xoa: ";
                std::cin >> maMH;
                deteleMonHoc(danhSachMonHoc, maMH);
                break;
            }
            case 0:
                std::cout << "Thoat hien chinh.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
	} while (choice != 0);
}


int main() {
	string maLop;
	vector<DangKyLopTinChi> danhSachLopTinChi;
	vector<MonHoc> danhSachMonHoc;
	cout<<"Nhap ma lop: ";
	getline(cin, maLop);
	
	int capacity;
	cout<<"Nhap so luong SV toi da: ";
	cin>>capacity;
	
	LopHoc lop(maLop, capacity);
	
	int choice;
	do {
		cout<<"==================Menu==================\n";
		cout<<"1. Them sinh vien\n";
		cout<<"2. Xoa sinh vien\n";
		cout<<"3. Hieu chinh sinh vien\n";
		cout<<"4. In danh sach sinh vien\n";
		cout<<"5. Mo lop tin chi\n";
		cout<<"6. In danh sach mon hoc\n";
		cout<<"7. Dang ky lop tin chi\n";
		cout<<"8. Huy lop tin chi\n";
		cout<<"0. Thoat!!!!!\n";
		cout<<"Nhap lua chon cua ban: ";
		cin>>choice;
		
		cin.ignore();
		
		switch(choice) {
			case 1:
				lop.addSV();
				break;
			case 2:
				lop.deleteSV();
				break;
			case 3:
				lop.hieuChinhSV();
				break;
			case 4:
				lop.inDanhSach();
				break;
			case 5:
				hienChinhMonHoc(danhSachLopTinChi,danhSachMonHoc);
				break;
		}
	} while (choice != 0);
	return 0;
}
