#include <iostream>
#include <string.h>

using namespace std;

char sir[10000];
int sir_k = 0;
bool valid = true; // asumam ca este valid. devine false cand gasim sintaxa invalida

bool isAtom(int id)
{
    return (sir[id] >= 'A' && sir[id] <= 'Z');
}

bool isNega(int id)
{
    return (sir[id] == '-');
}

bool isJnct(int id)
{
    return (sir[id] == '&' || sir[id] == '|');
}

bool isImpl(int id)
{
    return (sir[id] == '=' && sir[id + 1] == '>');
}

bool isEchi(int id)
{
    return (sir[id] == '<' && sir[id + 1] == '=' && sir[id + 2] == '>');
}


void AfisareSir()
{
    cout << endl;
    for (int i = 0; i < sir_k; i++)
        cout << sir[i];
}


void Simplifica(int i)
{
    int aux = 0, v[100], vk = 0; // vectorul merge pana la max 3, dar 100 evita erori de OutOfBounds
    while (sir[i + aux] != ')' && i + aux < sir_k)
    {
        if (sir[i + aux] == '(')
            Simplifica(i + aux + 1);

        if (isAtom(i + aux)) v[vk++] = 0;
        if (isNega(i + aux)) v[vk++] = 1;
        if (isJnct(i + aux)) v[vk++] = 2;
        if (isImpl(i + aux)) { v[vk++] = 2; aux += 1;}
        if (isEchi(i + aux)) { v[vk++] = 2; aux += 2;}

        aux++;
    }

    if (sir[i + aux] != ')') // adica while s-a oprit fara sa gaseasca paranteza inchisa (invalid)
        valid = false;

    if ((v[0] == 0 && v[1] == 2 && v[2] == 0 && vk == 3) || // adica e de forma: "A [conector] B"
        (v[0] == 1 && v[1] == 0 && vk == 2)) // adica e de forma: "[negatie] A"
    {
        // algoritm de simplificare a formulei complexe
        for (int j = 0; j + aux < sir_k; j++)
            sir[i + j] = sir[i + aux + j + 1];

        sir_k -= (aux + 1);

        sir[i - 1] = 'P';
        AfisareSir();
    }
    else
    {
        valid = false; // altfel, sintaxa invalida
    }
}


int main()
{
    cout << "Definim:\n [-] - Negatie\n [&] - Conjunctie\n [|] - Disjunctie\n [=>] - Implicatie\n [<=>] - Echivalenta\n";
    cout << "\n!CARACTERUL ' '[spatiu] NU ESTE SUPORTAT!\n\n";
    cout << "Exemplu: ((-A)=>(B&C))\n";
    cout << "\nIntroduceti sirul de caractere: ";

    cin >> sir;
    sir_k = strlen(sir);

    if (sir[0] == '(')
            Simplifica(1);

    if (valid && sir_k == 1 && isAtom(0))
        cout << "\n\nEste sir valid!";
    else cout << "\n\nNu este sir valid!";
}
