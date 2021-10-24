#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int d;

struct entity
{
	int AS;
	int DS;
	int HP;
	int LUCK;
	char name[25];

	entity() {}
	entity(int AS, int DS, int HP, int LUCK) {}

	void init(int _AS, int _DS, int _HP, int _LUCK)
	{
		AS = _AS;
		DS = _DS;
		HP = _HP;
		LUCK = _LUCK;
	}

	bool isdead ()
	{
		if (HP <= 0) 
			return true;
		return false;
	}

	void view()
	{
		cout << name << " (" << AS << " " << DS << " " << HP << " " << LUCK << ")" << endl;
	}
};



struct taskforce
{
	char name[50];
	entity v [1000];
	int n;
	int ghp;
	int GHP;
	
	taskforce ()
	{
		n = 0;
	}
	void add(entity A)
	{
		v[n] = A;
		n++;
	}

	void del ()
	{
		bool ok;
		do
		{
			ok = true;
			for (int i = 0; i < n ; i ++ )
				if (v[i].isdead())
				{
					n--;
					for (int j = i + 1 ; j < n + 1 ; j ++ )
						v [j - 1] = v[j]; 
					ok = false;
					break;
				}
		}while (!ok);
	}
	
	void view()
	{
		cout << "taskforce is : " << name << endl;
		for (int i = 0; i < n; i++)
				v[i].view();
		cout << endl;
	}

};

bool AMC2(int a, int b)
{
	srand(time(0));
	int t, r;
	t = a + b;
	r = rand() % t;
	if (r < a) return true;
	return false;
}

void battle(entity& A, entity& B)
{
	if (AMC2(A.AS, B.DS))
	{
		int tor = rand() % A.LUCK;
		if (tor == 0 && tor != B.LUCK)
		{
			d = 5;
			cout << "LUCKY STRIKE!!!" << A.name << endl;
		}
		else
			d = 1;
	}
	B.HP -= d;
	d = 1;
}

void raid(taskforce& A, taskforce& B)
{
	for (int i = 0; i < A.n; i++)
	{
		battle(A.v[i], B.v[rand() % B.n]);
	}
	for (int i = 0; i < B.n; i++)
	{
		battle(B.v[i], A.v[rand() % A.n]);
	}
}

void clear (taskforce& A, taskforce& B)
{
	A.del ();
	B.del ();
}


int main()
{
//----------------------------------------------HOME TEAM--------------------------------------------
	taskforce Humans;
	strcpy_s(Humans.name, "Humans");

	char toAdd[25];

	while (cin.getline (toAdd , 25))
	{
		entity person;
		strcpy_s(person.name, toAdd);
		if (!strcmp(toAdd, "knight"))
			person.init(8, 8, 12, 10);
		else
			if (!strcmp(toAdd, "wizard"))
				person.init(11, 5, 7, 6);
			else
				if (!strcmp(toAdd, "mace"))
					person.init(9, 15, 8, 10);
				else
					if (!strcmp(toAdd, "squire"))
						person.init(11, 4, 8, 6);
					
		Humans.add(person);
		Humans.view();
	}

//---------------------------------------ENEMY TEAM------------------------------------------------

	taskforce Enemies;
	strcpy_s(Enemies.name, "Enemies");

	entity badguy;
	strcpy_s(badguy.name, "Th'ksf");
	badguy.init(10, 10, 25, 40);
	Enemies.add(badguy);

	entity altbadguy;
	strcpy_s(altbadguy.name, "Tkkksp");
	altbadguy.init(15, 15, 15, 15);
	Enemies.add(altbadguy);

	
//------------------------------------------RAID----------------------------------------------------
		 while (Humans.n > 0  && Enemies.n > 0 )
		{
			Humans.view();
			Enemies.view();
			raid(Humans , Enemies);
			clear (Humans , Enemies);
			Humans.view();
			Enemies.view();
			getchar();
		}

		if(Humans.n <= 0)
			cout << "The Humans are dead"<< endl;
		if(Enemies.n <= 0)
			cout << "The oposing team is dead"<<endl;
		


	getchar();
	getchar();

}