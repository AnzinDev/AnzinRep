#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class image{
    int mx, my, data[100000] = {0};

    public:

    int kx, ky, color, p = 1;
    int Get_mx(){
        int p = 1;
        cout << "   Enetr x: ";
        while(p){
          cin >> mx;  
          if(mx <= 300){
              p = 0;
          }
          else{
              cout << "   mx value is too big." << endl;
          }
        }
        kx = mx;
        return mx;
    }
    
    int Get_my(){
        int p = 1;
        cout << "   Enetr y: ";
        while(p){
            cin >> my;
            if(my <= 300){
                p = 0;
            }
            else{
                cout << "   my value is too big." << endl;
            }
        }
        ky = my;
        return my;
    }

    int get(int cx, int cy){
        if(p == 1){ 
            srand(time(0) + cx - cy); //обновление зерна генерации и рандомное присвоение значений цвета
            p = 0;
        }
        color = rand() % 2;
        return color; 
    }

    void set(int cx, int cy, int color){
        data[(mx * cy) + cx] = color;
    }

    void show(){
        int i, k = 0;
        cout << endl << "   ";
        for(i = 0; i < mx * my; i++){
            cout << data[i];
            k ++;
            if(k == mx){
                cout << endl << "   ";
                k = 0;
            } 
        }
    }

    void line_hor(int mx, int my){
        int k = 1;
        while(k < mx * my){
            if(k >= mx * my - mx){
                data[k] = 1;
            }
            k++;
        }
    }

    void line_vert(int mx, int my){         
        for(int k = 1; k < mx * my; k++){
            data[k * mx - 1] = 1;
        }
    }
    void file_pbm(){
        char file_name[50];
        cout << "Enter file name to save image in format: name.pbm : ";
        cin >> file_name;
        FILE *fa = fopen(file_name, "w+");
        if(fa != NULL){
            int i = 0;
            fprintf(fa, "P1\n%d %d\n", mx, my);
            for(int k = 0; k < mx * my; k++){
                fprintf(fa, "%d", data[k]);
                i++;
                if(i == mx){
                    fprintf(fa, "\n");
                    i = 0;
                }
            }
            cout << "   Exported in file." << endl;
        }
        else{
            cout << "   Can't open file." << endl;
        }
        fclose(fa);
    }
};

image a;

int main(){
    int var;
    int vx = 0, vy = 0;
    cout << "   Press 1 to random image.\n   Press 2 to draw horizontal line.\n   Press 3 to draw vertical line.\n";
    cout << "   And export in file then.\n   ";
    cin >> var;
    switch(var){
        case 1:{
            a.Get_mx();
            a.Get_my();
            for(int k = 0; k < a.kx * a.ky; k++){
                a.get(vx, vy);
                a.set(vx, vy, a.color);
                vx++;
                if(k == (a.kx - 1)){
                    vy++;
                    vx = 0;
                }
            }
            int p;
            cout << "   Do you want to show in console? [1/0]   " << endl;
            cin >> p;
            if(p == 1){
                a.show(); 
            }
            a.file_pbm();
        break;
        }
        
        case 2:{
        cout << "   Horizontal line." << endl;
            a.Get_mx();
            a.Get_my();
            a.line_hor(a.kx, a.ky);
            int p;
            cout << "   Do you want to show in console? [1/0]   " << endl;
            cin >> p;
            if(p == 1){
                a.show(); 
            }
            a.file_pbm();
        break;
        }

        case 3:{
            cout << "   Vertical line." << endl;
            a.Get_mx();
            a.Get_my();
            a.line_vert(a.kx, a.ky);
            int p;
            cout << "   Do you want to show in console? [1/0]   " << endl;
            cin >> p;
            if(p == 1){
                a.show(); 
            }
            a.file_pbm();
        break;
        }

        default:
            cout << "   Invalid case." << endl;
        break;
    };
    return 0;
}
