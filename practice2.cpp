#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Image{
    
    T mx, my, *data;
    
    public:
    Image(int max_x, int max_y)
    {
        cout << "constructor " << this << endl;
        this->mx = max_x;
        this->my = max_y;
        this->data = new T[max_x*max_y];
    }

    ~Image()
    {
        cout << "destructor " << this << endl;
        delete[] data;
    }

    Image(const Image& other) // перегрузка конструктора копирования
    {
        cout << "copy constructor " << this << endl;
        this->mx = other.mx;
        this->my = other.my;
        this->data = new T[mx * my];
        for(int i = 0; i < mx * my; i++)
        {
            this->data[i] = other.data[i];
        }
    }

    Image& operator = (const Image& other) // перегрузка оператора присваивания
    {
        cout << "operator = " << this << endl;
        this->mx = other.mx;
        this->my = other.my;

        delete[] this->data;

        this->data = new T[mx * my];
        for(int i = 0; i < mx * my; i++)
        {
            this->data[i] = other.data[i];
        }
        return *this;  
    }
    
    bool operator == (const Image& other) // перегрузка оператора сравнения
    {
        if(this->mx == other.mx && this->my == other.my)
        {
            for(int k = 0; k < mx * my; k++)
            {
                if(this->data[k] != other.data[k])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void Set()
    {
        srand(time(NULL));
        for(int k = 0; k < mx * my; k++)
        {
            data[k] = rand() % 2;
        }

   }

   void Set_hor_line(int y)
   {
        for(int i = 0; i < mx * my; i++)
        {
           if((i >= mx * (y - 1)) && (i < mx * y))
           {
               this->data[i] = 1;
           }
           else
           {
               this->data[i] = 0;
           }
           
        }
   }

   void Set_vert_line(int x)
   {
       int p = 1;
       for(int i = 0; i < mx * my; i++)
       {
           this->data[i] = 0;
       }
       for(int i = 0; i < mx * my; i += x - 1)
       {
           if(p != 1)
           {
               x = mx + 1;
               this->data[i] = 1;
           }
           p = 0;
       }
   }

    void Show()
    {
        if(data != nullptr)
        {
            int p = 0;
            if(typeid(T) == typeid(int))
            {
                cout << "P1" << endl << mx << " " << my << endl;
            }
            for(int k = 0; k < mx * my; k++)
            {
                cout << data[k];
                p++;
                if(p == mx)
                {
                    cout << endl;
                    p = 0;
                }
            }
        }
        else
        {
            throw "Object isn`t initialized.";
        }
    }

    void File_pbm()
    {
        char file_name[50];
        cout << "Enter file name to save image in format: name.pbm : ";
        cin >> file_name;
        FILE *fa = fopen(file_name, "w+");
        if(fa != NULL)
        {
            int i = 0;
            fprintf(fa, "P1\n%d %d\n", mx, my);
            for(int k = 0; k < mx * my; k++)
            {
                fprintf(fa, "%d", data[k]);
                i++;
                if(i == mx)
                {
                    fprintf(fa, "\n");
                    i = 0;
                }
            }
            cout << "   Exported in file." << endl;
        }
        else
        {
            cout << "   Can't open file." << endl;
        }
        fclose(fa);
    }
};

int main(){
    Image<int> img1(10, 10);
    img1.Set();
    try
    {
        img1.Show();
    }
    catch(const char *p)
    {
        cout << p << endl;
    }
    Image<int> img2(img1); 
    Image<char> img3(10, 10);
    img3.Set();
    try
    {
        img3.Show();
    }
    catch(const char *p)
    {
        cout << p << endl;
    }
    Image<int> img4(5, 5);
    img4 = img1;
    try
    {
        img4.Show();
    }
    catch(const char *p)
    {
        cout << p << endl;
    }
    Image<int> img5(10, 10);
    img5.Set_hor_line(4);
    img5.Show();
    img5.Set_vert_line(5);
    img5.Show();
    bool compare = img1 == img5;
    cout << "img1 == img5 ??? " << compare << endl;
    compare = img1 == img2;
    cout << "img1 == img2 ??? " << compare << endl;
    Image<int> img6(10, 10);
    img6.Set_vert_line(6);
    img6.File_pbm();

    return 0;
}
