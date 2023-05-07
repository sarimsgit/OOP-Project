using namespace std;
#pragma warning(disable : 4996);
#include<iostream>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<iomanip>
#include<dos.h>

void display();
void pur();
void showu();
void password();
void showad();
void del();
void modify();
void reorder();
void reorderall();
void change();
void backup();
void menu();

class Number
{
private:
	int ItemNo;
	int BillNo;
public:
	Number() {
		ItemNo = 0;
		BillNo = 0;
	}
	void SetItemNo();
	void SetBillNo();
	int ReadItemNo();
	int ReadBillNo();
};

struct B
{
	int billno;
	char Name[50], Unit[20];
	int Qty;
	float Price, Amount;
	B()
	{
		billno = 0;
		Name[0] = 0;
		Unit[0] = 0;
		Qty = 0;
		Price = 0;
		Amount = 0;
	};
};

//class
class item
{
private:
	int id, reorder, min, stock;
	float profit, price, cp;
	char name[50], unit[10];
public:
	item()
	{
		id = 0;
		reorder = 0;
		min = 0;
		stock = 0;
		profit = 0;
		price = 0;
		cp = 0;
		name[0] = 0;
		unit[0] = 0;
	}
	void enter(int z)
	{
		display();
		Number n;
		if (z == 1)
			id = n.ReadItemNo();
		cout << "\n\nEnter Product Details\n\nProduct id : " << id;
		cin.ignore();
		cout << "\n\nEnter Product Name : "; 
		cin.getline(name, sizeof(name));
		cout << "\nEnter Unit Of Product : "; 
		cin.getline(unit, sizeof(unit));

		// cin.get(unit, 10);
		cout << "\nEnter Cost Price of Product : "; cin >> cp;
		cout << "\nEnter Selling Price of Product : "; cin >> price;
		pro();
		cout << "\nEnter Current Stock "; cin >> stock;
		cout << "\nEnter Minimun Stock upon which to trigger Reorder : "; cin >> min;
		cout << "\nEnter Amount to be Reordered "; cin >> reorder;
		cout << "\n\nNew Product " << name << " Added in Stock ";
		if (z == 1)
			n.SetItemNo();
	}


	/*void itemid()
	{
		item t;int i=0;
		ifstream f("item.dat",ios::binary);
		f.seekg(-76,ios::end);
		f.read((char*)&t,sizeof(t));
		if(t.id<1 || t.id>1000)
			id=1;
		else
			id=(t.id+1);
		f.close();
	}
	   /*	void itemid()
	{
		item t;int i=0;
		display();
		ifstream f("item.dat",ios::binary);
		f.read((char*)&t,sizeof(t));
		while(f)
		{
			++i;
			f.read((char*)&t,sizeof(t));
		}
		id=(i+1);
	}*/
	void pro()
	{
		profit = ((price - cp) * (100 / cp));
		cout << "\t\tProfit : " << profit << " %\n";
	}

	void showu()
	{
		// setwidth is used to print in a standard format
		cout << setw(4) << id << setw(15) << name << setw(15) << price << setw(15) << stock << setw(15) << unit<<setw(15);
	}

	void showad()
	{
		cout << setw(4) << id << setw(15) << name << setw(15) << cp << setw(15) << price << setw(15) << profit << setw(15) << stock << setw(15) << unit << setw(10) << min << setw(15) << reorder;
	}

	int compare(int n)
	{
		if (n == id)
			return 1;
		else
			return 2;
	}

	void order(int n, int z)		// 3 MODES OF REORDER
	{
		int j=0;
		if (n == 0)	// if function gets input of 0... manual reorder in which the admin enters the quantity without checking the current stock
		{
			cout << "\nEnter Number of items with the name of -> " << name << " to be Re-odered : ";
			cin >> j;
			stock += j;
			cout << "\n" << j << " " << unit << " " << name << " Reordered . Updated Stock :" << stock << " " << unit;
			_getch();
		}
		if (n == 1)	// if function gets the input of 1... the system checks the inventory and gives the status
			if (stock < min)
			{
				cout << "\n" << name << " need to be Reordered.  Current Stock : " << stock << " " << unit << " is below Mentioned Min Qty. ";
				z = 1;
			}
		if (n == 2 && stock < min) // stock is replenished about a fixed quantity set by the admin
		{
			stock += reorder;
			cout << "\n" << name << " Reordered "; _getch();
		}
	}

	void purchase(int& amt, int z)
	{
		// Custormer purchase // checkout stage
		int qty;
		cout << "\n Enter Qty. of " << name << " you want to purchase : ";
		cin >> qty;

		if (qty <= stock)
		{
			cout << "\n\nYou want to purchase " << qty << " " << unit << " of " << name << " at price " << price;
			amt = qty * price;
			cout << "\n\nTotal Amount : " << amt;
			cout << "\n\nConfirm Purchase (y/n) : ";
			char ch = getch();
			if (ch == 'y' || ch == 'Y')
			{
				stock -= qty;
				cout << "\n" << qty << " " << unit << " of " << name << " Purchased ";
				makebill(qty, z);
			}
			else
			{
				cout << " Purchase CANCELLED... ";
				amt = 0;
			}
		}
		else
		{
			cout << "\n" << qty << " " << unit << " " << name << " is not available in stock ";
			cout << "\n\nKindly order Less than " << qty << " " << unit << " or Visit Later ";
			amt = 0;
		}
	}
	void makebill(int Qty, int z)
	{

		ofstream f("bill.dat");
		struct B
		{
			int billno;
			char Name[50], Unit[20];
			int Qty;
			float Price, Amount;
			B() {};
		};
		B bill;

		bill.billno = z;
		// editing bill 
		strcpy_s(bill.Name, name);
		bill.Qty = Qty;
		bill.Price = price;

		bill.Amount = Qty * price;

		strcpy_s(bill.Unit, unit);

		f.write((char*)&bill, sizeof(bill));

		_getch();
		f.close();
	}

};

// inventory main

void add()
{
	display();
	item t;
	ofstream f("item.dat", ios::app | ios::binary);
	//ofstream f("item.dat");
	t.enter(1);
	f.write((char*)&t, sizeof(t));
	f.close();
}
//admin
void admin()
{
	display();
	//change();
	password();
top:
	display();
	cout << "Menu :\n1.Add New Item\n2.Show All Product\n3.Delete Product\n4.Modify Product\n5.Reorder Product\n6.Reorder All\n7.Change Password\n8.Backup or Retrieve Data\n9.Back To Main Menu\n";
	int i;
	i = _getch();
	switch (i)
	{
	case 49: 			 // these are the asci values of the entry data given in the menu above
		add();
		break;
	case 50:
		showad();
		break;
	case 51:
		del();
		break;
	case 52:
		modify();
		break;
	case 53:
		reorder();
		break;
	case 54:
		reorderall();
		break;
	case 55:
		change();
		break;
	case 56:
		backup();
		break;
	case 57:
		menu();
		break;
	default:
		cout << "\nWrong Option :(";
	}
	_getch();
	goto top;
}

// to create Back up of the file 
void backup()
{
	display();
	item t;
	char ch;
	cout << "\n\n1.To Backup Data\n2.To Retrieve Backup Data\n";
	ch = _getch();
	if (ch == '1')
	{
		ifstream org("item.dat", ios::binary);
		ofstream copy("backup.dat", ios::binary);
		while (org.read((char*)&t, sizeof(t)))
		{
			copy.write((char*)&t, sizeof(t));
		}
		cout << "\n\nFile Backed Up ";
		org.close();
		copy.close();
	}
	else if (ch == '2')
	{
		ifstream back("backup.dat", ios::binary);
		ofstream dest("item.dat", ios::binary);
		while (back.read((char*)&t, sizeof(t)))
		{
			dest.write((char*)&t, sizeof(t));
		}
		cout << "\n\nData Retrieved ";
		dest.close();
		back.close();
	}
	else
		cout << "\n\n Invalid Input ..\try again";
	_getch();
}

int no()
{
	B t;
	int i = 0, billno;

	fstream f("bill.dat", ios::binary | ios::in | ios::out);
	cout << "\n\n " << sizeof(t);

	f.seekg((-6), ios::end);
	f.read((char*)&t, sizeof(t));

	if (t.billno < 1 || t.billno>1000)
		billno = 1;
	else
		billno = (t.billno + 1);
	f.close();
	return billno;
}
/*void makebill(int amt)
{
	bill b;
	b.billno=no();
	b.amt=amt;
	cout<<"\n constructing Bill Number "<<b.billno<<"  "<<b.amt;
	fstream f("bill.dat",ios::binary|ios::app|ios::in|ios::out);
	f.write((char*)&b,sizeof(b));
	f.close();
} */

void showbill(int BillNumber)
{
	B b;
	int Final = 0;
	int k = 1;
	ifstream f("bill.dat", ios::binary);
	display();
	cout << "Here's Your Bill\n";
	cout << "*******************************************************************************\n";
	cout << setw(42) << "LIAQUAT Grocerry Shop\n";
	cout << setw(40) << "TIN No. 123456789\n\n";
	cout << "Bill Number : " << BillNumber << "\n";
	cout << "--------------------------------------------------------------------------------\n";
	cout << "S. No." << setw(10) << "Name" << setw(13) << "Qty" << setw(10) << "Price" << setw(10) << "Amount\n";
	cout << "--------------------------------------------------------------------------------\n";
	while (f.read((char*)&b, sizeof(b)))
	{
		if (BillNumber == b.billno)
		{
			cout << setw(6) << k << setw(10) << b.Name << setw(10) << b.Qty << " " << b.Unit << setw(10) << b.Price << setw(10) << b.Amount << "\n";
			Final += b.Amount;
			k++;
		}
	}
	cout << "--------------------------------------------------------------------------------\n";
	cout << "Total" << setw(44) << Final << "\n";
	cout << "--------------------------------------------------------------------------------\n";
	cout << "" << setw(40) << "Thank You\n" << setw(43) << "Please Visit Again\nTHANKS FOR SHOPPING\n";
	cout << "********************************************************************************\n";
	f.close();
}

void bill() {
	display();
	cout << "Enter Bill Number ";
	int n, k = 0;
	cin >> n;
	ifstream f("bill.dat", ios::binary);
	B b;
	while (f.read((char*)&b, sizeof(b)))
	{
		if (n == b.billno)
		{
			k++;
		}
	}
	if (k != 0)
		showbill(n);
	else
		cout << " Bill No. Does Not Exist ";
	_getch();
}

// customer menu
void customer() {

top:					// tag

	display();				// displays time and date

	cout << "Menu :\n1.Purchase Item\n2.Show All Product\n3.View Bill\n4.Back To Main Menu\n";

	int i;
	i = _getch();

	switch (i)
	{
	case 49:			// asci equivalent values
		pur();
		break;
	case 50:
		showu();
		break;
	case 51:
		bill();
		break;
	case 52:
		menu();
		break;
	default:
		cout << "\nWrong Option :(";
	}
	_getch();
	goto top;
}
// Delete
void del()
{
	ifstream f("item.dat", ios::binary);
	ofstream j("temp.dat", ios::binary);
	int n, k = 0;
	item s;
	display();
	showad();
	cout << "\n\nItem Id To be Deleted ";
	cin >> n;
	while (f.read((char*)&s, sizeof(s)))
	{
		if (s.compare(n) != 1)
			j.write((char*)&s, sizeof(s));
		else
			k = 1;
	}
	if (k == 0)
		cout << "\nItem Id Does Not Exist ";
	else
		cout << "\nItem No " << n << " deleted ";
	f.close();
	j.close();
	remove("item.dat");
	rename("temp.dat", "item.dat");
}
void display()
{
	system("CLS");
	cout << "\t\t\tInventory Management ";
	cout << "\n\n";
	time_t now = time(0);
	char* dt = ctime(&now);

	cout << "\n\n The local date and time is: " << dt << endl; // sturday//12:00
}
void menu()
{
back: 		// tag

	display();

	cout << "Menu:\n\n1.Admin Login\n2.Customer Menu\n3.Exit\n";

	int i;

	i = _getch();

	if (i == 49)				// asci equivalent values
		admin();
	if (i == 50)
		customer();
	if (i == 51)
		exit(0);
	cout << "\nWrong Option :`( ";
	_getch();
	goto back;
}

void modify()
{
	int n, k = 0, j = 0;
	item s;
	display();
	showad();
	cout << "\n\nEnter Product ID of Product To be Modified : ";
	cin >> n;
	fstream f("item.dat", ios::binary | ios::in | ios::out);
	f.read((char*)&s, sizeof(s));
	while (f)
	{
		if (s.compare(n) == 1)
		{
			s.showad(); _getch();
			f.seekg(k * sizeof(s), ios::beg);
			s.enter(0);
			f.seekp(k * sizeof(s), ios::beg);
			f.write((char*)&s, sizeof(s));
			j++;
		}
		f.read((char*)&s, sizeof(s));
		k++;
	}
	if (j == 0) {
		cout << "\n\nProduct ID Does Not Exist ";
	}
	
}

// Numbering

void Number::SetItemNo()
{
	//int item;
	ifstream f("default.dat", ios::binary);
	Number No;
	f.read((char*)&No, sizeof(No));
	No.ItemNo++;
	f.close();
	ofstream m("default.dat", ios::binary);
	m.write((char*)&No, sizeof(No));
	m.close();
}
void Number::SetBillNo()
{
	//int item;
	ifstream f("default.dat", ios::binary);
	Number No;
	f.read((char*)&No, sizeof(No));
	No.BillNo++;
	f.close();
	ofstream m("default.dat", ios::binary);
	m.write((char*)&No, sizeof(No));
	m.close();
}
int Number::ReadBillNo()
{
	//int item;
	ifstream f("default.dat", ios::binary);
	Number No;
	f.read((char*)&No, sizeof(No));
	return ++No.BillNo;
}
int Number::ReadItemNo()
{
	//int item;
	ifstream f("default.dat", ios::binary);
	Number No;
	f.read((char*)&No, sizeof(No));
	return ++No.ItemNo;
}
// password
void encrypt(char s[]);
void decrypt(char s[]);

void enter(char str[20])
{
	char ch;
	int i;
	for (i = 0;; i++)
	{
		ch = _getch();

		if (ch != '\r')
		{
			str[i] = ch;
			if (str[i] == '\b') {
				cout << '\b' << " " << '\b';
				i -= 2;
			}
			else {
				cout << "*";
			}


		}
		else
			goto out;
	}
out:
	str[i] = '\0';
}
void change()
{
	ofstream r("password.txt");
	char s[20], re[20];
retry:
	display();
	cout << "\nEnter New Password ";
	enter(s);
	cout << "\n\nReConfirm Password ";
	enter(re);
	if ((strcmp(s, re)) == 0)
	{
		encrypt(s);
		r << s;
		cout << "\n\n Password Succesfully Changed ";
	}
	else
	{
		cout << "\nPassword MisMatch\n\tPlz Retry ";
		_getch();
		goto retry;
	}
	r.close();
}
void password()
{
	char str[20], pass[20];
	int i, k = 0;
back:
	display();
	cout << "\nEnter Password ";
	enter(str);

	ifstream f("password.txt");
	f >> pass;

	decrypt(pass);

	i = strcmp(pass, str);
	if (i == 0)
		cout << endl << "Succesful LOgin !!";
	else
	{
		cout << endl << "failed....Retry" << endl;
		_getch();
		k++;
		if (k > 2)
			menu();
		goto back;  //if pass incorrect then it goes back to line 612
	}
	_getch();
	f.close();
}
void encrypt(char s[])
{
	int i, j;
	i = strlen(s);
	for (j = 0; j < i; j++)
	{
		s[j] = int(s[j]) + 50;
	}
	s[++j] = '\0';
}
void decrypt(char s[])
{
	int i, j;
	i = strlen(s);
	for (j = 0; j < i; j++)
	{
		s[j] = int(s[j]) - 50;
	}
	s[++j] = '\0';
}
// purchase
void pur()
{
	int n, amt = 0, bill = 0;

	item s;					// item class

	Number no; 				// NUMBER class

	int BillNumber = no.ReadBillNo();

again:				// tag if the customer wants to purchase again

	int j = 0, k = 0;

	display();     // shows time and date
	showu();

	cout << "\n\nEnter Product ID of Product You Want To Purchase : ";
	cin >> n;

	fstream f("item.dat", ios::binary | ios::in | ios::out); // filing mode function

	f.read((char*)&s, sizeof(s)); // size of class

	while (f) // while the file ends or the EOF is reached
	{
		if (s.compare(n) == 1) // this function compares the item number entered to every item number written in file
		{
			//s.showad();getch();
			f.seekg(k * sizeof(s), ios::beg);
			s.purchase(amt, BillNumber);
			f.write((char*)&s, sizeof(s));
			j = 1;  // j becomes true if item is found
		}
		f.read((char*)&s, sizeof(s));
		k++;
	}
	if (j == 0)
		cout << "\n\nProduct ID Does Not Exist ";
	bill += amt;
	_getch();
	cout << "\n\nDo You want To Purchase More (y/n) : ";
	char ch = _getch();
	if (ch == 'y' || ch == 'Y')
		goto again;
	/*if(amt!=0)
		s.makebill(amt);*/
	showbill(BillNumber);
	no.SetBillNo();

}


void reorder()
{
	int n, k = 0, j = 0;
	item s;
	display();
	
	showad();
	cout << "\n\nEnter Product ID of Product To be Reorder : ";
	cin >> n;
	fstream f("item.dat", ios::binary | ios::in | ios::out);
	if (!f) {
		cout << "Error opening file!" << endl;
		return;
	}
	f.read((char*)&s, sizeof(s));
	while (f.good()) // check if the read was successful and the end of the file has not been reached
	{
		if (s.compare(n) == 1)
		{
			f.seekg(k * sizeof(s), ios::beg);
			s.order(0, 0);
			f.write((char*)&s, sizeof(s));
			j++;
		}
		k++;
		f.read((char*)&s, sizeof(s));
	}
	f.close();
	if (j == 0)
		cout << "\n\nProduct ID Does Not Exist ";
}

void reorderall()
{
	int k = 0, z = 0;
	item s;
	display();
	showad();
	//cout<<"\n\nEnter Product ID of Product To be Reorder : ";
	//cin>>n;
	fstream f("item.dat", ios::binary | ios::in | ios::out);
	f.read((char*)&s, sizeof(s));
	while (f)
	{
		f.seekg(k*sizeof(s),ios::beg);
		s.order(1, z);
		f.read((char*)&s, sizeof(s));
	}
	f.close();
	if (z == 1)
	{
		cout << "\n\n Do You Want To Reorder All Listed Item (y/n)";
		char ch;
		ch = _getch();
		if (ch == 'y' || ch == 'Y')
		{
			fstream f("item.dat", ios::in | ios::out | ios::binary);
			f.read((char*)&s, sizeof(s));
			while (f)
			{
				s.order(2,0);
				f.seekg(k * sizeof(s), ios::beg);
				f.write((char*)&s, sizeof(s));
				f.read((char*)&s, sizeof(s));
				k++;
			}
			f.close();
		}
	}
}

//this functions shows you all the lsit of registered items in the mart
void showu() {
	item t;

	display();
	ifstream f("item.dat", ios::binary);
	cout << setw(4) << "ItemID" << setw(15) << "ProductName" << setw(15) << "Price" << setw(15) << "StockAvailable" << setw(15) << "Unit" << setw(15) << endl;
	while (f.read((char*)&t, sizeof(t))) // while end of file
	{
		t.showu();
		cout << endl;
	};
}


void showad() {
	item t;
	display();
	ifstream f("item.dat", ios::binary);
	cout << setw(4) << "ID" << setw(15) << "Name" << setw(15) << "Cost" << setw(15) << "Price" << setw(15) << "Profit%" << setw(15) << "In Stock" << setw(15)<<"Unit"<<setw(15) << "Min Qty" << setw(15) << "Reorder Qty\n\n";
	while (f.read((char*)&t, sizeof(t)))
	{
		t.showad();
		cout << endl;
	};
}


int main()
{
	/*textbackground(WHITE);
	textcolor(BLACK);
	sound(12000,15000,10);*/

	//getch();
	menu();

	return 1;
}