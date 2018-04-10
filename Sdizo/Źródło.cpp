#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}


struct list
{
	int value;
	list* next;
	list* back;
};

void showList(list *head)
{
	struct list* Tmp = (struct list*) malloc(sizeof(struct list));
	Tmp = head;
	cout << endl;
	do
	{
		cout << Tmp->value;
		if (Tmp->next != NULL)
		{
			cout << "->";
		}
		Tmp = Tmp->next;
	} while (Tmp != NULL);
}

void addOnFrontList(list *head, int val)
{
	struct list* new_node = (struct list*) malloc(sizeof(struct list));
	struct list* Tmp = (struct list*) malloc(sizeof(struct list));
	new_node->value = val;
	*Tmp = *head;
	*head = *new_node;
	head->next = Tmp;
	Tmp->back = head;
	head->back = NULL;
}

void addOnBackList(list *head, int val) 
{
	bool in = false;
	struct list *new_node = (struct list*) malloc(sizeof(struct list));
	struct list *Tmp = (struct list*) malloc(sizeof(struct list));
	new_node->value = val;
	*Tmp = *head;
	while (Tmp->next != NULL)
	{
		in = true;
		Tmp = Tmp->next;
	}
	if (!in)
	{
		head->next = new_node;
		new_node->next = NULL;
		new_node->back = head;
		return;

	}
	Tmp->next = new_node;
	new_node->next = NULL;
	new_node->back = Tmp;

}

void addOnIndexList(list *head, int val, int index)
{
	if (index < 0)
	{
		cout << "\nZly index!\n";
		return;
	}
	if (index == 0)
	{
		addOnFrontList(head, val);
		return;
	}
	bool bad = false;
	struct list* new_node = (struct list*) malloc(sizeof(struct list));
	struct list* Tmp = (struct list*) malloc(sizeof(struct list));
	new_node->value = val;
	*Tmp = *head;
	for (int i = 0; i < index; i++)
	{
		if (Tmp->next != NULL)
		{
			Tmp = Tmp->next;
		}
		else
		{
			bad = true;
			if (i == index - 1)
			{
				addOnBackList(head, val);
				bad = true;
				return;
			}
			cout << "\nZly index!\n";
			return;
		}
	}
	if (bad == true)
	{
		return;
	}
	Tmp->back->next = new_node;
	new_node->next = Tmp;

	new_node->back = Tmp->back;
	Tmp->back = new_node;




}

void deleteOnFrontList(list *head)
{
	*head = *head->next;
}

void deleteOnBackList(list *head)
{
	/*struct list *Tmp = (struct list*) malloc(sizeof(struct list));
	*Tmp = *head;
	while (Tmp->next != NULL)
	{
		Tmp = Tmp->next;
	}
	Tmp->back->next = NULL;*/
	struct list *Tmp = (struct list*) malloc(sizeof(struct list));
	*Tmp = *head;
	do
	{

		if (Tmp->next->next == NULL)
		{
			Tmp->next = NULL;
			return;
		}
		else
		{
			Tmp = Tmp->next;
		}

	} while (Tmp);
}

void deleteOnIndexList(list* head, int index)
{
	if (index < 0)
	{
		cout << "\nZly index!\n";
		return;
	}
	if (index == 0)
	{
		deleteOnFrontList(head);
		return;
	}
	bool bad = false;
	struct list* Tmp = (struct list*) malloc(sizeof(struct list));
	*Tmp = *head;
	for (int i = 0; i < index; i++)
	{
		if (Tmp->next != NULL)
		{
			Tmp = Tmp->next;
		}
		else
		{
			bad = true;
			if (i == index - 1)
			{
				deleteOnBackList(head);
				bad = true;
				return;
			}
			cout << "\nZly index!\n";
			return;
		}
	}
	if (bad == true)
	{
		return;
	}
	
	Tmp->back->next = Tmp->next;
	Tmp->next->back = Tmp->back;

}

void searchList(list* head, int val)
{
	bool found = false;
	struct list* Tmp = (struct list*) malloc(sizeof(struct list));
	*Tmp = *head;
	do
	{	
		if(Tmp->value == val)
		{
			cout << "\nZnaleziono!\n";
			found = true;
		}
		Tmp = Tmp->next;
	} while (Tmp != NULL);
	if (!found)
	{
		cout << "\nNie znaleziono!\n";
	}

}

void saveList(list* head)
{
	ofstream Out;
	Out.open("ZapisLista.txt");
	struct list *Tmp = (struct list*) malloc(sizeof(struct list));
	*Tmp = *head;
	if (Tmp == NULL)
	{
		Out << "Pusta";
		return;
	}
	while (Tmp != NULL)
	{
		Out << Tmp->value << endl;
		Tmp = Tmp->next;
	}
	Out.close();
}

void openList(list* head)
{
	ifstream In;
	In.open("ZapisLista.txt");
	int Temp;
	In >> Temp;
	head->value = Temp;
	head->next = NULL;
	while (In)
	{
		In >> Temp;
		struct list *new_node = (struct list*) malloc(sizeof(struct list));
		new_node->value = Temp;
		head->next = new_node;
		new_node->back = head;
		head = head->next;
	}
	head->back->next = NULL;
	In.close();
}

void randList(list* head, int index)
{
	head->value = rand() % 100;
	head->next = NULL;
	for (int i = 0; i < index-1; i++)
	{
		int _Tmp = rand() % 100;
		addOnFrontList(head, _Tmp);
	}
}


struct Array
{
	int *data;
	int size;
};

void showArray(Array **Arr)
{
	if ((*Arr)->size == 0)
	{
		cout << "\nPusta tablica!\n";
		return;
	}
	cout << endl << " ";
	for (int i = 0; i<(*Arr)->size; i++)
	{
		cout << *(((*Arr)->data) + i) << " | ";
	}
	cout << endl;
}

void addOnFrontArray(Array **Arr, int val)
{
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	for (int i = (*Arr)->size; i >= 0; i--)
	{

		*(((*Arr)->data) + i + 1) = *(((*Arr)->data) + i);
	}
	(*(*Arr)->data) = val;
	(*Arr)->size++;
}

void addOnBackArray(Array **Arr, int val)
{
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	*(((*Arr)->data) + (*Arr)->size) = val;
	(*Arr)->size++;
}

void addOnIndexArray(Array **Arr, int index, int val)
{
	if (index > (*Arr)->size)
	{
		cout << "\nZly index!\n";
		return;
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size + 1) * sizeof((*Arr)->data));
	for (int i = (*Arr)->size; i >= index; i--)
	{

		*(((*Arr)->data) + i + 1) = *(((*Arr)->data) + i);
	}
	*(((*Arr)->data) + index) = val;
	(*Arr)->size++;
}

void deleteOnFrontArray(Array **Arr)
{
	for (int i = 0; i < (*Arr)->size; i++)
	{
		*(((*Arr)->data) + i) = *(((*Arr)->data) + i + 1);
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;
}

void deleteOnBackArray(Array **Arr)
{
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;
}

void deleteOnIndexArray(Array **Arr, int index)
{
	if (index > (*Arr)->size-1)
	{
		cout << "\nZly index!\n";
		return;
	}
	for (int i = index; i < (*Arr)->size; i++)
	{
		*(((*Arr)->data) + i) = *(((*Arr)->data) + i + 1);
	}
	(*Arr)->data = (int*)realloc((*Arr)->data, ((*Arr)->size - 1) * sizeof((*Arr)->data));
	(*Arr)->size--;

}

void searchArray(Array **Arr, int val)
{
	bool found = false;
	if ((*Arr)->size == 0)
	{
		cout << "\nPusta tablica!\n";
		return;
	}
	cout << endl << " ";
	for (int i = 0; i<(*Arr)->size; i++)
	{
		if(val == *(((*Arr)->data) + i))
		{
			cout << "\nZnaleziono!\n";
			found = true;
		}
	}
	if (!found)
	{
		cout << "\nNie znaleziono!\n";
	}
}

void saveArray(Array **Arr)
{
	ofstream Out;
	Out.open("ZapisTablica.txt");
	if ((*Arr)->size == 0) 
	{
		Out << "Pusta!";
		return;
	}
	Out << (*Arr)->size << endl;
	for (int i = 0; i < (*Arr)->size; i++)
	{
		Out << *(((*Arr)->data) + i) << endl;
	}
	Out.close();
}

void openArray(Array **Arr)
{
	ifstream In;
	int i = 0;
	int temp = 0;
	In.open("ZapisTablica.txt");
	In >> temp;
	while (In)
	{
		In >> temp;
		addOnBackArray(Arr, temp);
	}
	In.close();
	deleteOnBackArray(Arr);
}

void randArray(Array **Arr, int index)
{
	for (int i = 0; i < index; i++)
	{
		int _Tmp = rand() % 100;
		addOnBackArray(Arr, _Tmp);
	}
}


struct binar
{
	int *Tab;
	int Size;
};

void showBinary(string sp, string sn, int v, binar *head)
{
	string cr, cl, cp;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	string s;

	if (v < head->Size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		showBinary(s + cp, cr, 2 * v + 2, head);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << head->Tab[v] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		showBinary(s + cp, cl, 2 * v + 1, head);
	}
}

void reBuild(binar *head, int s)
{
	int pos = s - 1;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s - 1;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s - 2;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}
	pos = s;
	while (pos>0 && head->Tab[pos / 2]<head->Tab[pos])
	{
		int y = head->Tab[pos];
		head->Tab[pos] = head->Tab[pos / 2];
		head->Tab[pos / 2] = y;
		pos = pos / 2;
	}

}

void addToBinar(binar *head, int _Value)
{
	head->Tab = (int*)realloc(head->Tab, (head->Size + 1) * sizeof(int));
	head->Size++;
	head->Tab[head->Size - 1] = _Value;
	head->Tab[head->Size] = NULL;
	reBuild(head, head->Size);
}

void emptyBinar(binar *head)
{
	head->Size = 0;
	head->Tab = NULL;
}

void deleteBinaryIndex(binar *head, int index)
{
	for (int i = 0; i < head->Size; i++)
	{
		if (i == index)
		{
			for (int q = i; q < head->Size - 1; q++)
			{
				head->Tab[q] = head->Tab[q + 1];
			}
			break;
		}
	}
	head->Size--;
	head->Tab[head->Size] = NULL;
	reBuild(head, index);
}

void saveBinary(binar *head)
{
	ofstream Out;
	Out.open("ZapisBinary.txt");
	for (int i = 0; i < head->Size; i++)
	{
		Out << head->Tab[i] << endl;
	}
	Out.close();
}

void openBinary(binar *head)
{
	emptyBinar(head);
	ifstream In;
	In.open("ZapisBinary.txt");
	int Temp = 0;
	int count = 0;
	while (In)
	{
		In >> Temp;
		addToBinar(head, Temp);
		count++;
	}
	head->Size = count-1;
	In.close();
}

void searchBinary(binar *head, int val)
{

	for (int i = 0; i < head->Size; i++)
	{
		if (head->Tab[i] == val)
		{
			cout << "\nZnalaziono!\n";
			i = head->Size;
			return;
			return;
		}
	}
}

void randBinary(binar *head, int _Value)
{
	int _Tmp;
	head->Tab = (int*)realloc(head->Tab, (_Value) * sizeof(int));
	head->Size = _Value;
	//head->Tab[head->Size - 1] = _Value;
	//head->Tab[head->Size] = NULL;
	//reBuild(head, head->Size);
	for (int i = 0; i < _Value; i++)
	{
		_Tmp = rand() % 100;
		head->Tab[i] = _Tmp;
		reBuild(head, i);
	}
}

int main()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	cout << "\n1. Lista\n2. Tablica\n3. Kopiec binarny\nWybieram:";
	int answer, N, I;

	cin>>answer;
	list *lista = (struct list*) malloc(sizeof(list));
	lista->back = NULL;
	lista->next = NULL;
	lista->value = 2;
	Array* tab;
	tab = (Array*)malloc(0 * sizeof(Array));
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	struct binar *A = (struct binar*) malloc(sizeof(struct binar));
	emptyBinar(A);

	switch (answer)
	{
	case 1:
		do
		{
			cout << "\n1. Wyswietl liste\n2. Wygeneruj losowa liste o rozmiarze N\n3. Dodaj element na poczatku listy\n4. Dodaj element na koncu listy\n5. Dodaj element do listy o indeksie\n";
			cout << "6. Usun element na poczatku listy\n7. Usun element na koncu listy\n8. Usun element listy o indeksie\n9. Zapisz do pliku\n10. Otworz z pliku\n11. Szukaj w liscie\n12. Wyjscie\nWybieram:";
			cin>>answer;
			system("CLS");
			switch (answer)
			{
			case 2:				
				cout << "Podaj rozmiar listy N=";
				cin>>N;
				system("CLS");
				start = read_QPC();
				randList(lista, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;
				
				system("pause");
				system("CLS");
				break;

			case 1:
				system("CLS");
				start = read_QPC();
				showList(lista);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnFrontList(lista, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnBackList(lista, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				cout << "Podaj wartosc nowego elementu listy=";
				cin >> N;
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				addOnIndexList(lista, N, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				system("CLS");
				start = read_QPC();
				deleteOnFrontList(lista);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				system("CLS");
				start = read_QPC();
				deleteOnBackList(lista);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 8:
				cout << "\nPodaj wartosc indexu=";
				cin >> I;				
				system("CLS");
				start = read_QPC(); deleteOnIndexList(lista, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 9:
				system("CLS");
				start = read_QPC();
				saveList(lista);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 10:
				system("CLS");
				start = read_QPC();
				openList(lista);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 11:
				cout << "\nPodaj wartosc szukanej=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				searchList(lista, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			default:
				cout << "\nZly wybor\n";
			}
		} while (answer!=12);
		break;

	case 2:
		
		do
		{
			cout << "\n1. Wyswietl Tablice\n2. Wygeneruj losowa Tablice o rozmiarze N\n3. Dodaj element na poczatku Tablicy\n4. Dodaj element na koncu Tablicy\n5. Dodaj element do Tablicy o indeksie\n";
			cout << "6. Usun element na poczatku Tablicy\n7. Usun element na koncu Tablicy\n8. Usun element Tablicy o indeksie\n9. Zapisz do pliku\n10. Otworz z pliku\n11. Szukaj w Tablicy\n12. Wyjscie\nWybieram:";
			cin >> answer;
			switch (answer)
			{
			case 2:
				tab = (Array*)malloc(0 * sizeof(Array));
				tab->size = 0;
				tab->data = (int*)malloc(0 * sizeof(int));
				cout << "Podaj rozmiar Tablicy N=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				randArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;
				system("pause");
				system("CLS");
				cin.get();
				break;

			case 1:
				system("CLS");
				start = read_QPC();
				showArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnFrontArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addOnBackArray(&tab, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				cout << "Podaj wartosc nowego elementu Tablicy=";
				cin >> N;
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				addOnIndexArray(&tab, I, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				system("CLS");
				start = read_QPC();
				deleteOnFrontArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				system("CLS");
				start = read_QPC();
				deleteOnBackArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 8:
				cout << "\nPodaj wartosc indexu=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				deleteOnIndexArray(&tab, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 9:
				system("CLS");
				start = read_QPC();
				saveArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;


			case 10:
				system("CLS");
				start = read_QPC();
				openArray(&tab);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 11:
				cout << "\nPodaj wartosc szukanej=";
				cin >> I;
				system("CLS");
				start = read_QPC();
				searchArray(&tab, I);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			default:
				cout << "\nZly wybor\n";
			}
		} while (answer != 12);
		break;

	case 3:
		do
		{
			cout << "\n1. Pokaz kopiec\n";
			cout << "2. Dodaj do kopca\n";
			cout << "3. Usun z kopca\n";
			cout << "4. Zapisz\n";
			cout << "5. Otworz\n";
			cout << "6. Wyszukaj\n";
			cout << "7. Rand Binar\n";
			cout << "8. Wyjscie\nWybieram:";

			cin >> answer;
			switch (answer)
			{
			case 2:
				cout << "Podaj wartosc nowego elementu Kopca=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				addToBinar(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 1:
				system("CLS");
				start = read_QPC();
				showBinary("", "", 0, A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 3:
				cout << "Podaj wartosc indeksu=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				deleteBinaryIndex(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 4:
				system("CLS");
				start = read_QPC();
				saveBinary(A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 5:
				system("CLS");
				start = read_QPC();
				openBinary(A);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 6:
				cout << "Podaj szukana wartosc=";
				cin >> N;
				system("CLS");
				start = read_QPC();
				searchBinary(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;

				system("pause");
				system("CLS");
				break;

			case 7:
				cout << "Podaj rozmiar kopca N=";
				cin >> N;
				system("CLS");
				int _Tmp;
				start = read_QPC();
				/*emptyBinar(A);
				for (int i = 0; i < N; i++)
				{
					_Tmp = rand() % 100;
					addToBinar(A, _Tmp);
				}*/
				randBinary(A, N);
				elapsed = read_QPC() - start;
				cout << "\nTime [ms] = " << setprecision(3) << (1000.0 * elapsed) /
					frequency << endl;
				system("pause");
				system("CLS");
				cin.get();
				break;
			default:
				cout << "\nZly wybor\n";
			}
		} while (answer != 8);
		break;

	default:
		cout << "Zly wybor\n";
	}





		




						
	/*struct binar *A = (struct binar*) malloc(sizeof(struct binar));
	emptyBinar(A);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, rand() % 98);
	addToBinar(A, 6);
	addToBinar(A, rand() % 98);
	saveBinary(A);
	showBinary("", "", 0, A);
	openBinary(A);
	showBinary("", "", 0, A);
	searchBinary(A,6);
	addToBinar(A, 5);
	showBinary("", "", 0, A);*/


	/*Array* tab;
	tab = (Array*)malloc(0 * sizeof(Array));
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	showArray(&tab);
	addOnFrontArray(&tab, 1);
	addOnFrontArray(&tab, 4);
	addOnFrontArray(&tab, 7);
	addOnFrontArray(&tab, 8);
	addOnFrontArray(&tab, 4);
	showArray(&tab);
	addOnBackArray(&tab, 99);
	showArray(&tab);
	addOnIndexArray(&tab, 7, 21);
	showArray(&tab);
	deleteOnFrontArray(&tab);
	showArray(&tab);
	deleteOnBackArray(&tab);
	showArray(&tab);
	deleteOnIndexArray(&tab,1);
	showArray(&tab);
	searchArray(&tab, 0);
	saveArray(&tab);
	tab->data = (int*)malloc(0 * sizeof(int));
	tab->size = 0;
	showArray(&tab);
	openArray(&tab);
	showArray(&tab);
	tab->size = 0;
	tab->data = (int*)malloc(0 * sizeof(int));
	randArray(&tab, 10);
	showArray(&tab);*/






	//list *lista = (struct list*) malloc(sizeof(list));
	//lista->back = NULL;
	//lista->next = NULL;
	//lista->value = 9;
	//addOnBackList(lista, 99);
	//addOnFrontList(lista, 88);
	//randList(lista, 20);
	//showList(lista);




	cin.get();
	return 0;
}