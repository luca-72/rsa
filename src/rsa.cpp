#include "rsa.h"
#include "bigint.h"
#include "primality.h"

#include<random>
#include<ctime>
#include<string>
#include<iostream>

using namespace std;

string string_to_string10(string s){

    int i, lg1, lg2=0, nr, lgnr, j;
    string rez, aux;

    lg1 = s.size();

    for(i=0;i<lg1;i++){

        nr = int((unsigned char)s[i]); // 97

        lgnr = 0;
        aux.clear();

        while(nr){
            lgnr++;
            aux.push_back(char(nr%10+'0')); // 79
            nr/=10;
        }

        rez.push_back(char(lgnr+'0'));
        for(j=aux.size()-1;j>=0;j--)
            rez.push_back(aux[j]);

    }

    return rez;

}

void string10_to_NrMare(NrMare rez, string s){

    AtribMic(rez, 0);
    rez[0] = 0;

    int i, lg = s.size(), j, aux;

    for(i=lg-1;i>=0;i-=8){

        aux = 0;

        for(j=i-7;j<=i;j++){

            if(j >= 0)
                aux = aux * 10 + (s[j] - '0');

        }

        rez[++rez[0]] = aux;

    }

}

string NrMare_to_string10(NrMare a){

    int i, j;
    string rez, aux;
    NrMare aa;

    AtribMare(aa, a);

    for(i=a[0];i>0;i--){
        aux.clear();
        while(a[i]){
            aux.push_back(char(a[i] % 10 + '0')); a[i] /= 10;
        }

        if(i != a[0])                   // every limb except the top one...
            while(aux.size() < 8)
                aux.push_back('0');         // must be exactly 8 digits

                for(j=aux.size()-1;j>=0;j--)
                    rez.push_back(aux[j]);
    }

    AtribMare(a, aa);

    return rez;

}

string string10_to_string(string s){

    string rez;
    int i, lg=s.size(), j, aux, len;

    for(i=0;i<lg;i++){

        aux=0;
        len = s[i] - '0';

        for(j=i+1;j<=i+len;j++){
            aux = aux*10 + (s[j] - '0');
        }

        //cout << aux << "\n";

        i = j-1;

        rez.push_back(char(aux));

    }

    return rez;

}

void read(NrMare message, string s){

    s = string_to_string10(s);
    string10_to_NrMare(message, s);

}

void write(NrMare a){

    string s;

    s = NrMare_to_string10(a);
    s = string10_to_string(s);

    cout << s;

}

NrMare p, N, p1, q1, p2, phi, phi2, d, e;

void setup(){

    AtribMic(e, 65537);

    //AtribMic(message, 12345678);

    NrMare phi22, e2, q, r, aux;

    NrMare doi; AtribMic(doi, 2);
    NrMare unu; AtribMic(unu, 1);
    NrMare zero; AtribMic(zero, 0);



    while(true){

        randomPrime64(p); // AtribMic(p, 53);
        randomPrime64(q);// AtribMic(q, 73);
        AtribMare(N, p); ProdusMare(N,q);

        //cout << "N = "; Afis(N);

        //cout << "unu = ";Afis(unu);

        //cout << "p = "; Afis(p);

        //cout << "q = "; Afis(q);



        AtribMare(p1, p); Scadere(p1, unu);
        AtribMare(q1, q); Scadere(q1, unu);
        AtribMare(p2, p); Scadere(p2, doi);

        //cout << "p1 = "; Afis(p1);

        AtribMare(phi, p1);  ProdusMare(phi, q1);

        AtribMare(phi22, phi);
        AtribMare(e2, e);

        divideMare(phi22, e2, q, r);

        if(Compara(r,zero) != 0)
            break;

    }
    //cout << "phi = "; Afis(phi);

    AtribMare(phi2, phi); Scadere(phi2, doi);

    AtribMare(d, e);
    //cout << "phi = "; Afis(phi);


    invers_modular(d, phi, aux); AtribMare(d, aux); //Expo(d, phi2,phi);

    //cout << "d = "; Afis(d);

}

void encrypt(NrMare ct, string s){

    NrMare message;

    read(message, s);

    AtribMare(ct, message);
    Expo(ct, e, N);

    //cout << "criptat : "; Afis(ct);

}

void decrypt(NrMare pt, NrMare ct){

    AtribMare(pt, ct);
    Expo(pt, d, N);

    //cout << "decriptat : "; write(pt); //Afis(pt);

}
