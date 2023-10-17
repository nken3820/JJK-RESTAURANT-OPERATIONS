#include "main.h"

class imp_res : public Restaurant
{
public:
	int counter;
	int counterQueue;
	customer *first;
	customer *X;
	customer *firstQueue;
	customer *lastQueue;
	customer *firstHistory;
	customer *lastHistory;
	customer *tempfirstHistory;
	customer *templastHistory;
	customer *copyHis;

public:
	imp_res()
	{
		counter = 0;
		counterQueue = 0;
	};

	customer *removeFirstQueue()
	{
		customer *del = firstQueue;
		firstQueue = firstQueue->next;
		del->next = nullptr;
		counterQueue--;
		return del;
	}

	customer *removeFirstHistory()
	{
		customer *del = firstHistory;
		firstHistory = firstHistory->next;
		del->next = nullptr;
		return del;
	}

	customer *removeCOPYFirstHistory()
	{
		customer *del = copyHis;
		copyHis = copyHis->next;
		del->next = nullptr;
		return del;
	}

	customer *copylist(customer *cus, int num)
	{
		customer *current = cus;
		customer *copy = new customer(current->name, current->energy, current->next, NULL);
		customer *const head = copy;
		current = current->next;
		for (int i = 1; i < counter - num; i++)
		{
			copy = copy->next = new customer(current->name, current->energy, NULL, NULL);
			current = current->next;
		}
		while (current != NULL)
		{
			copy = copy->next = new customer(current->name, current->energy, NULL, NULL);
			// copy = copy->next;
			current = current->next;
		}
		return head;
	}

	customer *find_RES(customer *cus)
	{
		int RES = abs(first->energy - cus->energy);
		customer *a = first;
		customer *result = a;
		int index = 0;
		while (index < counter)
		{
			if (abs(a->energy - cus->energy) > RES)
			{
				RES = abs(a->energy - cus->energy);
				result = a;
			}
			a = a->next;
			index++;
		}
		return result;
	}

	bool checkname(customer *cus)
	{
		customer *a = first;
		int index = 0;
		while (index < counter)
		{
			if (a->name == cus->name)
				return false;
			a = a->next;
			index++;
		}
		return true;
	}

	void logicRED(customer *cusInput)
	{
		customer *cus = new customer(cusInput->name, cusInput->energy, nullptr, nullptr);
		if (cus->energy == 0)
		{
			return;
		}
		else
		{
			if (counter == 0)
			{
				first = cus;
				counter++;
			}
			else
			{
				if (counter == 1)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						first->next = cus;
						first->prev = cus;
						cus->next = first;
						cus->prev = first;
						counter++;
					}
				}
				else if (counter < MAXSIZE / 2)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						if (cus->energy >= X->energy)
						{
							customer *N = X->next;
							X->next = cus;
							cus->prev = X;
							cus->next = N;
							N->prev = cus;
							X = X->next;
							counter++;
						}
						else
						{
							customer *N = X->prev;
							X->prev = cus;
							cus->next = X;
							cus->prev = N;
							N->next = cus;
							X = X->prev;
							counter++;
						}
					}
				}
				else if (counter < MAXSIZE)
				{
					if (!(checkname(cus)))
					{
						return;
					}
					else
					{
						X = find_RES(cus);
						int RES = cus->energy - X->energy;
						if (RES >= 0)
						{
							customer *N = X->next;
							X->next = cus;
							cus->prev = X;
							cus->next = N;
							N->prev = cus;
							X = X->next;
							counter++;
						}
						else
						{
							customer *N = X->prev;
							X->prev = cus;
							cus->next = X;
							cus->prev = N;
							N->next = cus;
							X = X->prev;
							counter++;
						}
					}
				}
				else if (counter == MAXSIZE && counterQueue == 0)
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						lastQueue = cus;
						firstQueue = cus;
						counterQueue = 1;
					}
				}
				else
				{
					if (!checkname(cus))
					{
						return;
					}
					else
					{
						if (counterQueue == MAXSIZE)
						{
							return;
						}
						else
						{
							lastQueue->next = cus;
							lastQueue = cus;
							counterQueue++;
						}
					}
				}
			}
		}
		customer *histemp = new customer(cusInput->name, cusInput->energy, nullptr, nullptr);
		if (counter == 1)
		{
			firstHistory = histemp;
			lastHistory = histemp;
		}
		else
		{
			lastHistory->next = histemp;
			lastHistory = histemp;
		}
		return;
	}

	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
		logicRED(cus);
	}

	void BLUE(int num)
	{
		if (num >= counter)
		{
			const int index = counterQueue;
			first = nullptr;
			counter = 0;
			if (counterQueue <= MAXSIZE)
			{
				for (int i = 0; i < index; i++)
				{
					customer *templ = removeFirstQueue();
					logicRED(templ);
				}
			}
		}
		else
		{
			const int index2 = counter;
			for (int i = 0; i < num; i++)
			{
				customer *del = removeFirstHistory();
				counter--;
				delete del;
			}
			first = nullptr;
			counter = 0;
			copyHis = copylist(firstHistory, index2 - num);
			firstHistory = nullptr;
			for (int j = 0; j < index2 - num; j++)
			{
				customer *templ = removeCOPYFirstHistory();
				logicRED(templ);
			}
			for (int k = 0; k < num; k++)
			{
				customer *templ = removeFirstQueue();
				logicRED(templ);
			}
		}
	}

	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
	}
	void SHOW()
	{
		cout << "--------------danh sach trong ban--------------" << endl;
		customer *a = first;
		int max = 1;
		while (max <= counter)
		{
			cout << a->name << " " << a->energy << endl;
			a = a->next;
			max++;
		}
		cout << "--------------danh sach trong queue-------------" << endl;
		customer *b = firstQueue;
		int mx = 1;
		while (b != nullptr)
		{
			cout << b->name << " " << b->energy << endl;
			b = b->next;
			mx++;
		}
		cout << "--------------danh sach trong history-------------" << endl;
		customer *c = firstHistory;
		int m = 1;
		while (c != nullptr)
		{
			cout << c->name << " " << c->energy << endl;
			c = c->next;
			m++;
		}
	}
};