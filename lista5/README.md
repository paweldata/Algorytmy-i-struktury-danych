# Algorytmy-i-struktury-danych
## Lista 5

### Zadanie 1
Program symuluje działanie kolejki priorytetowej zaimplementowanej na kopcu binarnym

#### Zaimplelemtowane fukncje:
- insert x p
- empty
- top
- pop
- priority x p
- print

#### Przykład

```Shell
$ make
$ ./zad1
$ 3
$ insert 5 4
$ insert 3 2
$ print
(3, 2), (5, 4),
```

### Zadanie 2
Program realizuje algorytm Dijkstry  
Przykładowe dane: data/dijkstra.txt

### Zadanie 3
Program znajduje minimalne drzewa rozpinające  
Przykładowe dane: data/mst.txt

### Zadanie 4
Program symuluje poruszanie się po pełnym grafie 3 sposobami:
	- błądzenie losowe
	- wybór ścieżki o najniższej wadze
	- chodzenie po obliczeniu MST
Przykladowe dane: data/travel.txt
