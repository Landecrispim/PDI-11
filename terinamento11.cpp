#include <iostream>

using namespace std;

int main()
{
    int imagem_erosao[10][10];
    int imagem_dilatacao[10][10];
    int gradiente[10][10];
    int fechamento[10][10];
    int abertura[10][10];

    int img[10][10] = {
        {252, 46, 115, 18, 73, 203, 60, 229, 112, 183},
        {109, 31, 20, 53, 225, 58, 54, 28, 170, 94},
        {99, 73, 116, 115, 183, 146, 177, 88, 14, 141},
        {79, 176, 132, 54, 144, 148, 231, 157, 244, 187},
        {207, 28, 4, 194, 111, 122, 172, 61, 211, 71},
        {185, 199, 124, 123, 40, 195, 134, 112, 17, 194},
        {26, 3, 168, 251, 12, 85, 98, 205, 174, 34},
        {234, 222, 166, 121, 99, 167, 33, 35, 43, 183},
        {237, 102, 254, 45, 206, 234, 49, 144, 1, 70},
        {17, 231, 44, 224, 67, 195, 148, 68, 127, 42}};

    int elemento[7][7] = {
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 10, 1, 0, 0},
        {0, 1, 10, 20, 10, 1, 0},
        {1, 10, 20, 40, 20, 10, 1},
        {0, 1, 10, 20, 10, 1, 0},
        {0, 0, 1, 10, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}};

    //erosao

    int auxmin, kk, ll;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auxmin = 300; // poderia ser qualquer valor acima de 255
            kk = 0;
            for (int k = i - 3; k < i + 3; k++)
            {
                ll = 0;

                for (int l = j - 3; l < j + 3; l++)
                {
                    
                    if (l >= 0 && k >= 0 && l < 10 && k < 10)
                        if (auxmin > (img[k][l] - elemento[kk][ll]))
                        {
                            //cout << "   " << kk << "," << ll;
                            auxmin = img[k][l] - elemento[kk][ll];
                            if (auxmin < 0)
                                auxmin = 0;
                            // cout<<"   "<<kk<<","<<ll;
                        }

                    ll++;
                }
               // cout << endl;
                kk++;
            }

            imagem_erosao[i][j] = auxmin;
        }
    }

    //dilatação

    int auxmax;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auxmax = -1; // poderia ser qualquer valor menor que 0
            kk = 0;
            for (int k = i - 3; k < i + 3; k++)
            {
                ll = 0;

                for (int l = j - 3; l < j + 3; l++)
                {

                    if (l >= 0 && k >= 0 && l < 10 && k < 10)
                        if (auxmax < (img[k][l] + elemento[kk][ll]))
                        {
                            auxmax = img[k][l] + elemento[kk][ll];
                            if (auxmax > 255)
                                auxmax = 255;
                        }

                    ll++;
                }
                kk++;
            }
            imagem_dilatacao[i][j] = (int)auxmax;
        }
    }

    //gradiente

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            gradiente[i][j] = imagem_dilatacao[i][j] - imagem_erosao[i][j];
        }
    }

    //abertura  (dilitação da imagem com erosao)

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auxmax = -1; // poderia ser qualquer valor menor que 0
            kk = 0;
            for (int k = i - 3; k < i + 3; k++)
            {
                ll = 0;

                for (int l = j - 3; l < j + 3; l++)
                {

                    if (l >= 0 && k >= 0 && l < 10 && k < 10)
                        if (auxmax < (imagem_erosao[k][l] + elemento[kk][ll]))
                        {
                            auxmax = imagem_erosao[k][l] + elemento[kk][ll];
                            if (auxmax > 255)
                                auxmax = 255;
                        }

                    ll++;
                }
                kk++;
            }
            abertura[i][j] = (int)auxmax;
        }
    }

    //fechamento (erosao da imagem dilatada)

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auxmin = 300; // poderia ser qualquer valor acima de 255
            kk = 0;
            for (int k = i - 3; k < i + 3; k++)
            {
                ll = 0;

                for (int l = j - 3; l < j + 3; l++)
                {

                    if (l >= 0 && k >= 0 && l < 10 && k < 10)
                        if (auxmin > (imagem_dilatacao[k][l] - elemento[kk][ll]))
                        {
                            auxmin = imagem_dilatacao[k][l] - elemento[kk][ll];
                            if (auxmin < 0)
                                auxmin = 0;
                        }

                    ll++;
                }
                kk++;
            }
            fechamento[i][j] = auxmin;
        }
    }

    cout << "imagem:" << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << img[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "Erosao:" << endl;
    //erosao
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << imagem_erosao[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "dialtação:" << endl;

    //dilação

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << imagem_dilatacao[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "gradiente:" << endl;

    //gradiente
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << gradiente[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "abertura:" << endl;

    //abertura
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << abertura[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;
    cout << "fechamento:" << endl;

    //fechamento
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "  " << fechamento[i][j];
        }
        cout << endl;
    }
}
