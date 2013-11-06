EGC - Tema 1

Geometry Wars
Florina Spataru 333CA

	1. Cerinta

Se doreste un fel de nava care sa folosesca o arma sa
distruga inamici. In absenta armei, inamicii distrug 
nava. Trebuie afisate cate vieti mai are nava si scorul.
	

	2.Utilizare

Nu exista fisiere de intrare sau comenzi speciale, se 
foloseste interfata grafica

2.3 Butoane

[W] 	deplasare inainte
[S] 	deplasare inapoi
[A] 	rotire spre stanga
[D] 	rotire spre dreapta
[W+A]	deplasare inainte + rotire spre stanga
[W+D] 	deplasare inainte + rotire spre dreapta
[S+A]	deplasare inapoi + rotire spre stanga
[S+D]	deplasare inapoi + rotire spre dreapta
[SPACE]	activare "arma" (deschide gura)
[ESC]	iesire din joc


	3.Implementare

Windows 7 Professional x32
Visual Studio Ultimate 2012
Framework-ul din laboratorul 2 de EGC (exercitiul 1)

Pentru ca tema oferea o oarecare libertate, am ales sa
fac in loc de nava un Pacman si in loc de arma, sa 
deschid gura Pacman-ului. 

	Clase implementate de mine:
Player2D 	- Imi creeaza Pacman-ul si contine toate 
		functionalitatile necesare, adica 
		functiile pentru miscare, vieti, scor,
		utilizarea "gurii"

Enemy2D		- Pot apela constructorul cu un parametru
		de tip. In functie de tip, mi se creeaza
		3 inamici diferiti
		- Contine functiile pentru miscarea 
		inamicilor(urmarirea Pacman-ului) precum
		si coliziunea cu acesta

Celelalte clase sunt exact ca in framework cu exceptia 
faptului ca in DrawingWindow am adaugat functia
	glutKeyboardUpFunc(keyboardUpFunction); 
care verifica daca se ridica mana de pe o tasta.


	4.Testare

Am testat tema pe aceeasi platforma pe care am implementat.
Scenariile testate au fost:
- coliziune intre inamic si player(gura inchisa)
- coliziune intre inamic si spatele player-uli(gura deschisa)
- coliziune intre inamic si gura player-ului(gura deschisa)
- coliziune intre player si pereti(gura inchisa/deschisa)

Nu am testat coliziune intre inamic si pereti, dar este un
scenariu care nu cred ca se poate intampla, dar m-am asigurat
oricum ca inamicii sa nu iasa din ecran.


	5.Probleme aparute

- coliziunea nu e tocmai exacta

- coliziunea a fost cel mai greu de implementat pentru ca
as fi vrut sa fie ceva de genul: daca imi intra efectiv in gura, 
sa moara, si daca ma loveste oriunde altundeva sa mor eu.
Usor de zis, greu de facut, din pacate. Nu prea pot sa explic
in cuvinte, ar fi mai usor un desen. Ideea e ca am pierdut 
foarte mult timp incercand sa fac asta. Am renuntat si am facut-o
cu metoda simpla, am considerat un cerc mai mic in triunghiul
ce formeaza gura

- o alta problema este apasarea tastelor multiple. Am facut asta
in felul urmator: am o functie care verifica ce taste au fost 
apasate si ce taste eliberate si un vector de bool cat setul ascii.
Daca o tasta e apasata, atunci key['w'] = true, altfel false.
Merge binisor asta, cu o singura exceptie: daca apas up+left merge 
cum mi-as fi dorit, dar daca dau drumul la left, se opreste, desi
eu tin apasat up. Nu prea imi dau seama de ce, daca va dati seama
spune-ti-mi si mie va rog, sunt curioasa.

- o alta problema a aparut la miscarile de baza. Aparent, a fost 
nevoie sa creez toate obiecte in (0,0) si apoi sa translatez unde
vroiam. Metoda creez in (200,200), translate(-200,-200), rotate, 
translate(200,200) nu prea pare sa mearga in cazul asta. Poate 
faceam eu ceva gresit, cert e ca nu mi-a mers deloc asta si am
modificat ca sa creez obiectele in origine.
- ultima problema a fost o neatentie din partea mea. cos si sin 
se calculeaza pe unghi in radiani, nu in grade. Eu decisesem sa 
lucrez in grade asa ca m-am incurcat putin in asta.

	6.Continutul arhivei

Tema1.slm	
		- proiectul din Visual Studio
Tema1.sdf
Debug		
		- contine freeglut.dll
lab2		
	>Debug
	>dependinte
	>Framework 
		- contine clasele de la laborator
		- in plus, Player2D.cpp si .h
		- si Enemy.cpp si .h
	>lab2.vcsproj.filters
	>lab2.vcxproj
	>main.cpp 
		- where the magic happens

	7.Functionalitati

Functionalitati standard
- miscare sus, rotatie stanga/dreapta
- deschidere gura 
	- cand deschide gura, este incetinit
- afisare vieti
- aparitia a 3 monstrii diferiti pe harta in pozitii prestabilite
- coliziune cu monstrii/pereti
	- la coliziunea cu pereti, efectiv dadeam player-ul inapoi,
	nu se intampla altceva
	- la coliziunea cu inamici, am folosit metoda "cerc cu cerc"
	adica daca distanta dintre centrele celor doua cercuri este
	mai mica decat razele lor adunate -> coliziune.
	- pentru "gura" am considerat ca exista un cerc in gura lui
	si i-am aflat centrul, apoi am folosit aceeasi metoda ca mai
	sus.

Functionalitati suplimentare
- miscare inapoi
- posibilitatea miscarii inainte + rotatie in acelasi timp (la
fel si pentru inapoi)

Fuctionalitati bonus
- monstrii vin dupa jucator (am facut asta pentru ca e foarte usor
de implementat)

	8.Altceva
Feedback: a fost o tema foarte fun, daca aveam mai mult timp chiar
ar fi putut sa iasa ceva foarte frumos. Stiu multe persoane care
au facut strictul necesar si atat, si evident, ala nu prea seamana
cu un joc pe bune.

Ce as fi vrut sa mai implementez: as fi vrut sa fac montrii sa apara
in continuu si ar fi fost bine sa fac coliziunea aia cu gura sa fie
perfecta.






