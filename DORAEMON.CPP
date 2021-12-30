#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no.";
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		cout<<"\n\n\nBook Created..";
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nBook Name : ";
		puts(bname);
		cout<<"Author Name : ";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};         //class ends here
class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		clrscr();
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin>>admno;
		cout<<"\n\nEnter The Name of The Student ";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nStudent Record Created..";
	}

	void show_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nStudent Name : ";
		puts(name);
		cout<<"\nNo of Book issued : "<<token;
		if(token==1)
			cout<<"\nBook No "<<stbno;
	}

	void modify_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here
fstream fp,fp1;
book bk;
student st;
void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void display_spb(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nStudent does not exist";
	getch();
}
void modify_book()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}
void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


void delete_book()
{
	char n[6];
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}
void display_alls()
{
	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	fp.close();
	getch();
}
void display_allb()
{
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}
void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully";
						cout<<"\n\nPlease Note: Write current datein backside of book and submit within 15 days.";
						cout<<"\nFine-Rs. 1/day after 15 days";
					}
				}
				if(flag==0)
					cout<<"Book no does not exist";
			}
			else
				cout<<"You have not returned the last book ";

		}
	}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	fp.close();
	fp1.close();
}
void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\nBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist...";
	getch();
  fp.close();
  fp1.close();
  }
void intro()
{       textcolor(YELLOW);
	int f1;
	for (f1=2;f1<80;f1++)
		{
		gotoxy(f1,1);
		cprintf("_");
		delay(10);
		}
	for (f1=2;f1<25;f1++)
		{
		gotoxy(80,f1);
		cprintf("|");
		delay(10);
		}
	for (f1=79;f1>1;f1--)
		{
		gotoxy(f1,24);
		cprintf("_");
		delay(10);
		}
	for (f1=24;f1>1;f1--)
		{
		gotoxy(1,f1);
		cprintf("|");
		delay(10);
		}
	 int f2;
	 textcolor(GREEN);
	 for(f2=1;f2<19;f2++)
	 {
	 gotoxy(f2,3);
	 textbackground(YELLOW);
	 cprintf("CHRIST CHURCH BOY'S SENIOR SECONDARY SCHOOL");
	 delay(40);
	 if (f2==18) break;
	 gotoxy(f2,3);
	 textbackground(0);
	 cprintf("                                           ");
	 }
	 gotoxy(1,3);
	 textbackground(0);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(BLUE);
	 for(f2=1;f2<25;f2++)
	 {
	 gotoxy(f2,5);
	 cprintf("A PROJECT ON LIBRARY MANAGEMENT");
	 delay(40);
	 if (f2==24) break;
	 gotoxy(f2,5);
	 cprintf("                                           ");
	 }
	 gotoxy(1,5);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(MAGENTA);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,7);
	 cprintf("==> ANIMESH KANJANI    ROLL NO. 05");
	 delay(40);
	 if (f2==20) break;
	 gotoxy(f2,7);
	 cprintf("                                           ");
	 }
	 gotoxy(1,7);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(MAGENTA);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,9);
	 cprintf("==> GUNEET KAPOOR      ROLL NO. 10");
	 delay(40);
	 if (f2==20) break;
	 gotoxy(f2,9);
	 cprintf("                                           ");
	 }
	 gotoxy(1,9);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(MAGENTA);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,11);
	 cprintf("==> MRINAL NANDI       ROLL NO. 15");
	 delay(40);
	 if (f2==20) break;
	 gotoxy(f2,11);
	 cprintf("                                           ");
	 }
	 gotoxy(1,11);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(RED);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,13);
	 cprintf("==> CLASS              12 A ");
	 delay(40);
	 if (f2==20) break;
	 gotoxy(f2,13);
	 cprintf("                                           ");
	 }
	 gotoxy(1,13);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(CYAN);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,15);
	 cprintf("SUBMITTED TO -         MR. A. MAJUMDAR");
	 delay(40);
	 if (f2==20) break;
	 gotoxy(f2,15);
	 cprintf("                                           ");
	 }
	 gotoxy(1,15);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(WHITE);
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,20);
	 cprintf("START DATE:                                      END DATE:");
	 delay(40);
	 if (f2==10) break;
	 gotoxy(f2,20);
	 cprintf("                                           ");
	 }
	 gotoxy(1,20);
	 textcolor(YELLOW);
	 cprintf("|");
	 for(f2=1;f2<21;f2++)
	 {
	 gotoxy(f2,21);
	 textcolor(WHITE);
	 cprintf("11/08/2018                                       07/11/2018");
	 delay(40);
	 if (f2==10) break;
	 gotoxy(f2,21);
	 cprintf("                                                   ");
	 }
	 gotoxy(1,21);
	 textcolor(YELLOW);
	 cprintf("|");
	 textcolor(MAGENTA);
	 delay(3000);
	 }
void menu();
void admin_menu(int x)
{       if (x==0)
	{
	clrscr();
	int ch2;
	gotoxy(33,1);
	textcolor(GREEN+BLINK);
	cprintf("ADMINISTRATOR MENU");
	gotoxy(15,3);
	textcolor(RED);
	cprintf ( "1.CREATE STUDENT RECORD");
	gotoxy(15,5);
	cprintf ( "2.DISPALY ALL STUDENT RECORD");
	gotoxy(15,7);
	cprintf ( "3.DISPLAY SPECIFIC STUDENT RECORD");
	gotoxy(15,9);
	cprintf ( "4.MODIFY STUDENT RECORD");
	gotoxy(15,11);
	cprintf ( "5.DELETE STUDENT RECORD");
	gotoxy(15,13);
	cprintf ( "6.CREATE BOOK");
	gotoxy(15,15);
	cprintf ( "7.DISPLAY ALL BOOKS");
	gotoxy(15,17);
	cprintf ( "8.DISPLAY SPECIFIC BOOK ");
	gotoxy(15,19);
	cprintf ( "9.MODIFY BOOK ");
	gotoxy(15,21);
	cprintf ( "10.DELETE BOOK ");
	gotoxy(15,23);
	cprintf ( "11.BACK TO STUDENT MENU");
	gotoxy(15,24);
	textcolor(CYAN);
	cprintf("Please Enter Your Choice (1-11) ");
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_student();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The book No. ";
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_book();break;
		case 10: delete_book();break;
		case 11: menu();
		default:cout<<"\a";
	}
	admin_menu(x);
	}
	else
	{
	if (x==1) write_student();
	if (x==2) display_allb();
	if (x==3)
	{top:
	clrscr();
	cout<<"Press 1 for all students records\n";
	cout<<"Press 2 for all books records\n";
	int tl;cin>>tl;
	if (tl==1 || tl==2)
	{
	if (tl==1) display_alls();
	if (tl==2) display_allb();
	}
	else
	{
	clrscr();
	textcolor(RED);
	gotoxy(10,12);
	cprintf("Wrong Input Sir. Please Try Again. Press any Key To Continue");
	textcolor(WHITE);
	getch();
	goto top;
	}
	}
	}
	}
char s[] ={"                                                "};
void erase()
{
textbackground(0);
gotoxy(25,23);
cout<<s;
}
void sen(char *s)
{
window(27,22,67,23);
textcolor(BLUE);
textbackground(WHITE);
cprintf(s);
erase();
window(1,1,80,25);
textcolor(WHITE);
textbackground(BLACK);
}
char f[6][40] = {
				{"To create new Library Card"},
				{"To see Book Availability"},
				{"To Issue Books"},
				{"To Return Books"},
				{"Types of Display"},
				{"To Exit Program "}
				};
		char item[6][40]={
				 {"Creation of new library card no."},
				 {"Books availability chart"},
				 {"Issuing of Books"},
				 {"Returning of Books" },
				 {"Different Types of Display"},
				 {"Exit the program "}
				 };
void menu()
	{
	textbackground(0);
	textmode(BW80);
	clrscr();
	int i,j,k;
	float a,b;
	char ch;
	textcolor(GREEN);
	gotoxy(33,5);
	cprintf("MAIN MENU");
	int r=8 ;
	for(i=0;i<=5;i++)
		{
		gotoxy(22,r);
		textcolor(MAGENTA);
		cprintf("%i -> ",i+1);
		textcolor(2);
		gotoxy(27,r);
		cprintf(item[i]);
		r=r+2;
		}
	r=8;
	gotoxy(27,8);
	textbackground(4);
	cprintf(item[0]);
	sen(f[0]);
	int c;
	do
	{
	if(r==8) c=0;
	else c=(r/2)-4;
	ch=getch();
	switch(ch)
		{
		case 72:if(r<=8)
			{
			gotoxy(27,8);
			textbackground(0);
			textcolor(2);
			cprintf (item[0]);
			sen(f[0]);
			r=18;
			gotoxy(27,r);
			textbackground(4);
			textcolor(2);
			cprintf(item[5]);
			sen(f[5]);
			}
			else
			{
			gotoxy(27,r);
			textbackground(0);
			textcolor(2);
			cprintf(item[c]);
			r=r-2;
			c=c-1;
			gotoxy(27,r);
			textbackground(4);
			textcolor(2);
			cprintf(item[c]);
			sen(f[c]);
			}
			break;

	  case 80:if(r>=18)
		  {
		  gotoxy(27,18);
		  textbackground(0);
		  textcolor(2);
		  cprintf(item[5]);
		  r=8;
		  gotoxy(27,r);
		  textbackground(4);
		  textcolor(2);
		  cprintf(item[0]);
		  sen(f[0]);
		  }
		  else
		  {
		  gotoxy(27,r);
		  textbackground(0);
		  textcolor(2);
		  cprintf(item[c]);
		  r=r+2;
		  c=c+1;
		  gotoxy(27,r);
		  textbackground(4);
		  textcolor(2);
		  cprintf(item[c]);
		  sen(f[c]);
		  }
		  break;
		}
	}
	while(ch !=13);
	textbackground(0);
	textcolor(7);
	c++;
	switch(c)
	{
	case 1:
	clrscr();
	admin_menu(1);
	menu();
	case 2:
	clrscr();
	admin_menu(2);
	menu();
	case 3:
	clrscr();
	book_issue();
	menu();
	case 4:
	clrscr();
	book_deposit();
	menu();
	case 5:
	clrscr();
	admin_menu(3);
	menu();
	case 6:
	clrscr();
	gotoxy(25,12);
	textcolor(RED);
	cprintf("Thank You for using the program");
	getch();
	exit(0);
	default :cout<<"\a";
	}
	}
void main()
{
	char ch;
	clrscr();
	intro();
	top:
	clrscr();
	cout<<"Do You Want to Enter Administrator Menu(y/n)?\n";
	char a;
	cin>>a;
	if (a=='N' || a=='n' || a=='Y' || a=='y')
	{
	if (a=='Y' || a=='y') admin_menu(0);
	else menu();
	}
	else
	{
	clrscr();
	gotoxy(10,12);
	textcolor(RED);
	cprintf("Wrong Input. Please Try Again. Press Any Key To Continue");
	getch();
	goto top;
	}
	}

