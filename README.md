### Cazacu Alexandru-Dan 312CA 2023-2024
# Editor de imagini

### Incarcarea in memorie a unei imagini
Retinerea in memorie a unei matrici se realizeaza, mai intai prin citirea dintr-un fisier ce 
poate fi de tip Portable PixMap sau Portable GrayMap, in format, fie ascii, fie binar. 
Identificarea acestor informatii se face din antetul fisierului, prin intermediul "magic 
number"-ului. In functie de formatul fisierului, se realizeaza o citire a continutului 
fisierului, reprezentand, in caractere tiparibile, inaltimea, latimea imaginii si o valoare 
maxima in functie de care se poate determina activarea unui pixel, dar si in ascii sau in 
binar, matricea imaginii care cuprinde valoare pixelilor.

### Selectarea unei regiuni a imaginii
Pentru selectarea a unei portiuni din imagine, se citesc coordonatele intre care se vor 
realiza urmatoarele operatii, iar in cazul in care sunt valide, se retin intr-o structura care 
contine toate informatiile necesare despre imagine, precum lungimea, latimea, matricea 
imaginii, dar si formatul ei. In cazul selectarii, intregii imagini, aceasta reprezinta, de fapt, 
un caz particular de selectare a unei regiuni a imaginii, doar ca selectia reprezinta 
imaginea completa.

### Histograma unei imagini
Ca sa se poata calcula o histograma care contine un un numar maxim de linii, cu o 
lungime maxima pe fiecare linie, este nevoie sa se afle numarul de aparitii a fiecarei 
valori pe care o poate avea un pixel (acest numar fiind cuprins intre 0 si valoarea maxima 
a activarii unui pixel). Se face, dupa colectarea acestor informatii, o grupare intre valorile 
pe care le poate avea un pixel, astfel incat numarul de grupuri sa fie egal cu numarul de 
linii pe care trebuie sa le aiba histograma. Un grup este format din valori consecutive pe 
care le poate avea un pixel, adica, pentru un exemplu unde valoarea maxima a unui pixel 
este 255, iar numarul de linii din histograma este 128, se vor grupa doua cate doua 
(valoarea 0 a unui pixel cu 1, 2 cu 3, ... , 254 cu 255) si se va aduna numarul de aparitii a 
fiecarei valori dintr-o grupare, calculandu-se o suma a fiecarei grupe. Pentru fiecare 
dintre acestea, avand in vedere lungimea maxima a unei linii, se va calcula lungimea pe 
care aceasta trebuie sa o aiba in histograma.

### Egalizarea unei imagini
Avand formula cu care se poate egaliza o imagine, ce este in functie de numarul 
aparitiilor fiecarui pixel in poza, aria pozei si valoarea maxima pe care o poate avea un 
pixel, ramane de calculat o suma partiala in felul urmator: intr-un vector se va retine pe 
pozitia i, cati pixeli din poza au valoarea mai mica sau egala decat i. Cu toate aceste 
informatii, trebuie doar calculata noua valoare a pixelului cu formula: noua_valoare[i] = 
(255 / aria_pozei) * suma_partiala[i].

### Taierea unei imagine
Ca sa se poata taia o imagine, stiind coordonatele de selectie, se copiaza elementele din 
interiorul selectiei intr-o matrice ajutatoare care reprezinta, de fapt, poza taiata si se 
copiaza inapoi in matricea principala a imaginii, fiind eliberate resursele care nu mai sunt 
folosite.

### Rotirea unei imagini
Rotirea imaginii se realizeaza in doua feluri: rotirea completa a imaginii sau doar a unei 
regiuni selectate. Avand in vedere ciclitatea la 360 de grade, unghiurile negative sunt 
transformate in unghiuri pozitive. Astfel, matricea se roteste de minim 0 ori sau de 
maxim 4 ori in sensul invers trigonometric, la 90 de grade. In ambele cazuri, rotirea la 90 
de grade se realizeaza cu un acelasi algoritm, doar ca atunci cand selectia este imaginea 
completa, atunci inaltimea si latimea noii imagini poate sa se schimbe. Algoritmul 
presupune faptul ca elementele de pe prima linie se pun pe ultima coloana, elementele 
de pe a doua linie se pun pe a penultima coloana si asa mai departe pana la elementele 
de pe ultima linie care se pun pe prima coloana.

### Aplicarea unui kernel
Pentru a aplica un kernel pe o imagine, se verifica daca un pixel are 8 vecini. In cazul in 
care nu are, ramane nemodificat. Pentru un pixel cu 8 vecini, consideram submatricea 
nxn (in cazul nostru, toate fiind 3x3) in care elementul din centru (daca indexarea se face 
de la [0,0], atunci elementul de pe [1,1]) este pixelul selectat la inceput. Se inmulteste 
fiecare element din kernel cu elementul de pe aceeasi pozitie in submatricea selectata si 
se adauga la un rezultat (noua valoare a pixelului). Pentru a preveni cazurile in care pixelii 
ies din intervalul pe care il poate avea (de la 0 la valoarea maxima citita din fisier), se 
foloseste functia clamp, iar in cazul in care valoarea pixelului nu apartine intervalului, 
aceasta este schimbata cu valoarea celei mai apropiate margini.

### Salvarea unei imagini
Salvarea imaginii se realizeaza in functie de parametrii cititi (numele fisierului si 
formatul). Formatul va fi ascii, doar la aparitia parametrului "ascii", in rest, va fi binar. 
Scrierea in fisier se va face doar la valorile inaltimii, a latimii, a activarii maxime si a 
activarii pixelilor.

### Iesirea din program
Iesirea consta in eliberarea tuturor resurselor si oprirea programului, prin schimbarea 
unei valorii unei variabile care spune daca programul mai trebuie sa ruleze sau nu.
