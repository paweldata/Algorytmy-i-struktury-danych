# Algorytmy-i-struktury-danych
## Lista 4

### Zadanie 1
Program symuluje działanie 4 struktur danych przechowujących ciągi znaków:
- drzewa binarnego
- drzewa czerowno czarnego
- mapy haszującej metodą łańcuchową przechowującą w jednej komórce dane w liście priorytetowej lub drzewie czerowno czarnym zależnie od wielkości
- fitru Blooma

#### Zaimplelemtowane fukncje:
- insert
- load
- delete
- find
- min
- max
- successor
- inorder

#### Parametry
- --type bst | rbt | hmap | bloom  
bst - drzewo binarne  
rbt - drzewo czerowno czarne  
hmap - mapa haszująca  
bloom - filtr Blooma

#### Przykład

```Shell
$ make
$ ./main --type rbt <data.txt
```

Przykładowe dane znajdują się w folderze data
