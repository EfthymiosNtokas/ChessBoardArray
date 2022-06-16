#include <iostream>
#include <iomanip>
using namespace std;
class ChessBoardArray{
protected:
    class Row{
    public:
        Row(ChessBoardArray &a, int i):nn(i), chh(a){};
        int &operator[](int i)const {
            return chh.select(nn,i);
        }
    private:
        ChessBoardArray &chh;
        int nn;
    };
    class ConstRow{
    public:
        ConstRow(const ChessBoardArray &a, int i):nn(i), chh(a){};
        int operator [](int i) const {
            return chh.select(nn,i);
        }
    private:
        int nn;
        const ChessBoardArray &chh;
    };
public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0):num(size), base(base), data(new int[(size*size+1)/2]){
        for(int i = 0; i < (size*size+1)/2; i++){
            data[i] = 0;
        }
    }
    ChessBoardArray(const ChessBoardArray &a): num(a.num), base(a.base), data(new int[(a.num*a.num+1)/2]){
        for(int i = 0; i < (a.num*a.num+1)/2; i++){
            data[i] = a.data[i];
        }
    }
    ~ChessBoardArray(){delete [] data;};

    ChessBoardArray &operator=(const ChessBoardArray &a){
        num = a.num; base = a.base;
        delete [] data;
        data = new int[(a.num *a.num+1)/2];
        for(int i = 0; i < (a.num*a.num+1)/2; i++){
            data[i] = a.data[i];
        }
    }
    int &select(int i, int j){
        return data[loc(i,j)];
    }
    int select(int i, int j) const{
        return data[loc(i,j)];
    }
    const Row operator[](int i){
        return Row(*this, i);
    }
    const ConstRow operator[](int i) const{
        return ConstRow(*this, i);
    }

    friend ostream &operator <<(ostream &out, const ChessBoardArray &a) {
        //sets the width between to 4
        int r = 0;
        for(int i = 0; i < a.num; i++){
            out << setw(4); //dinei xwro mexri 4 digits
            for(int j = 0; j < a.num-1; j++){
                if((i+j) % 2 ==1){out << 0 << setw(4);}
                else {
                    out << a.data[r++] << setw(4);
                }

            }
            if((i+a.num-1) % 2 ==1){out << 0 ;}
            else {
                out << a.data[r++];
            }
            out << "\n";

        }
        return out;
    }
private:
    unsigned int loc(int i, int j) const throw(out_of_range){

        if(i < base || i > num+base-1 || j < base || j > num+base-1 || (i+j) %2 == 1){
            throw out_of_range("well");
        }else{
            return ((i-base)*num+j-base)/2;
        }

    };
    int *data;
    unsigned int num;
    int base;

};
int main() {
    ChessBoardArray a (4,1);

    a[3][1] = 42;
    a[4][4] = 17;
    a[2][2] = 19;
    ChessBoardArray b(a);
    try{a[0][1] = 7;}
    catch(out_of_range &e){cout<< "out" << "\n";}
    ChessBoardArray c;
    c = b;
    cout << a;
    cout << b;
    cout << c;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


