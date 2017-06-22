#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
#include<stdlib.h>
#include<iomanip.h>

/* DESIGNATION */
class designation
{
 private:
 //char dname[50];
 struct dosdate_t d;
 float salary;
 public:
 char dname[50];
 void getdata();
 void display();
 void displays()
 {
  cout<<"SALARY:"<<salary<<endl<<endl;
 }
 friend void deleted();
 friend void edit();
 friend void disburse();
 //friend class employee;
};
void designation::getdata()
{
 cout<<"ENTER DESIGNATION:";
 cin>>dname;
 cout<<"\nENTER SALARY:";
 cin>>salary;
 _dos_getdate(&d);
}
void designation::display()
{
 int dd=d.day; int mm=d.month;
 cout<<setiosflags(ios::right);
 cout<<setw(15)<<dname<<"\t"<<setw(15)<<salary<<"\t\t"<<dd<<"/"<<mm<<"/"<<d.year<<endl;
}
designation obj1;
// INSERT IN DESIG.TXT
void insert()
{
 fstream wr("desig.txt", ios::app);
 obj1.getdata();
 wr.write((char *)&obj1,sizeof(obj1));
 cout<<"\nDATA WRITTEN SUCCESSFULLY"<<endl;
 wr.close();
}
// VIEW DESIG.TXT
void view()
{
 cout<<"***************************** DESIGNATION DETAILS *************************"<<endl;
 cout<<"---------------------------------------------------------------------------"<<endl;
 cout<<setiosflags(ios::right);
 cout<<"SNo. "<<setw(15)<<"DESIGNATION"<<"\t"<<setw(15)<<"SALARY"<<"\t\t"<<"UPDATE"<<endl;
 cout<<"---------------------------------------------------------------------------"<<endl;
 fstream rd("desig.txt", ios::in);
 rd.seekg(0,ios::end);
 int p=rd.tellg();
 p=p/sizeof(obj1);
 rd.seekg(0,ios::beg);
 for(int i=1; i<=p; i++)
 {
	cout<<"   "<<i<<" ";
	rd.read((char*) &obj1,sizeof(obj1));
	obj1.display();
 }
 rd.close();
}
// EDIT DESIGNATION
void edit()
{
 char up[50];
 cout<<"ENTER THE DESIGNATION FOR EDITING:";
 gets(up);
 fstream fp1,fp2;
 fp1.open("desig.txt", ios::in);
 fp2.open("temp.txt", ios::out);
 fp1.seekg(0,ios::end);
 int p=fp1.tellg()/sizeof(obj1);
 fp1.seekg(0,ios::beg);
 int x=0;
 for(int i=1; i<=p; i++)
 {
	fp1.read((char *)&obj1,sizeof(obj1));
	if(stricmp(up,obj1.dname)==0)         //this will not be case-sensitive
	{
		insert();
		x=1;
	}
	fp2.write((char *)&obj1,sizeof(obj1));

 }
 fp1.close();
 fp2.close();
 if(x==0)
 {
	cout<<"\n-----------DETAILS NOT FOUND-------"<<endl;
 }
 else
 {
	fstream f1,f2;
	f1.open("desig.txt", ios::out);
	f2.open("temp.txt", ios::in);
	for(int j=1; j<=p; j++)
	{
		f2.read((char *)&obj1,sizeof(obj1));
		f1.write((char *)&obj1,sizeof(obj1));
	}
	f1.close();
	f2.close();
 }
}
// DELETE DESIGNATION
void deleted()
{
 char dl[50];
 cout<<"ENTER THE DESIGNATION TO BE REMOVED:";
 gets(dl);
 fstream fp1,fp2;
 fp1.open("desig.txt", ios::in);
 fp2.open("temp.txt", ios::out);
 fp1.seekg(0,ios::end);
 int p=fp1.tellg()/sizeof(obj1);
 fp1.seekg(0,ios::beg);
 int x=0;
 for(int i=1; i<=p; i++)
 {
	fp1.read((char *)&obj1,sizeof(obj1));
	if(stricmp(dl,obj1.dname)==0)         //this will not be case-sensitive
	{
		cout<<"\nDELETION SUCCESSFULL"<<endl;
		x=1;
	}
	else
	{
		fp2.write((char *)&obj1,sizeof(obj1));
	}
 }
 fp1.close();
 fp2.close();
 if(x==0)
 {
	cout<<"\n----------DETAILS NOT FOUND--------"<<endl;
 }
 else
 {
	fstream f1,f2;
	f1.open("desig.txt", ios::out);
	f2.open("temp.txt", ios::in);
	for(int j=1; j<=p-1; j++)
	{
		f2.read((char *)&obj1,sizeof(obj1));
		f1.write((char *)&obj1,sizeof(obj1));
	}
	f1.close();
	f2.close();
 }
}
/* EMPLOYEE CLASS */
class employee
{
 private:
 long int empid;
 char ename[50];
 char design[50];
 char mobile[12];
 public:
 void getdata();
 void display();
 friend void searchname();
 friend void searchid();
 friend void deleteemp();
 friend void updateemp();
 friend void disburse();
};
employee obj2;
int y=1;
void employee::getdata()
{
 int eid;
 cout<<"ENTER EMPLOYEE-ID:";
 cin>>eid;
 fstream e("emp2017.txt",ios::in);
 e.seekg(0,ios::end);
 int q=e.tellg()/sizeof(obj2);
 e.seekg(0,ios::beg);
 for(int k=1; k<=q; k++)
 {
  e.read((char *)&obj2,sizeof(obj2));
  if(eid==obj2.empid)
  {
   cout<<"\n------ALREADY EXISTED ID-----";
   y--;
   return;
  }
 }
 empid=eid;
 cout<<"\nENTER EMPLOYEE NAME:";
 gets(ename);
 cout<<"\nENTER DESIGNATION:";
 gets(design);
 fstream rd;
 rd.open("desig.txt", ios::in);
 rd.seekg(0, ios::end);
 int p=rd.tellg()/sizeof(obj1);
 int x=1;
 while(x)
 {
  rd.seekg(0,ios::beg);
  for(int i=1; i<=p; i++)
  {
   rd.read((char *)&obj1,sizeof(obj1));
   //cout<<obj1.dname;
   if(stricmp(design,obj1.dname)==0)
   {
    x--;
    break;
   }
  }
 // cout<<"x="<<x<<endl;
 if(x==1)
 {
	cout<<"\n*INVALID DESIGNATION*\nENTER DESIGNATION AGAIN:";
	gets(design);
 }
 }
// rd.close();
 cout<<"\nENTER MOBILE NUMBER:";
 gets(mobile);
}
void employee::display()
{
 cout<<setiosflags(ios::right);
 cout<<setw(11)<<empid<<"\t"<<setw(20)<<ename<<"\t"<<setw(13)<<design<<"\t"<<setw(13)<<mobile<<endl;
}
// ADD EMPLOYEE
void addemp()
{
 fstream wr("emp2017.txt",ios::app);
 obj2.getdata();
 if(y<=0)
 {
  y=1;
  return;
 }
 wr.write((char *)&obj2,sizeof(obj2));
 wr.close();
 cout<<"\nEMPLOYEES DATA ADDED SUCCESSFULLY";
}
// VIEW EMPLOYEE
void viewemp()
{
 cout<<setiosflags(ios::right);
 cout<<"****************************** EMPLOYEES DETAILS ******************************"<<endl;
 cout<<"-------------------------------------------------------------------------------"<<endl;
 cout<<"SNo. "<<setw(11)<<"EMPLOYEE-ID"<<"\t"<<setw(20)<<"NAME"<<"\t"<<setw(13)<<"DESIGNATION"<<"\t"<<setw(13)<<"MOBILE NUMBER"<<endl;
 cout<<"------------------------------------------------------------------------------"<<endl;
 fstream rd("emp2017.txt", ios::in);
 rd.seekg(0,ios::end);
 int p=rd.tellg();
 p=p/sizeof(obj2);
 rd.seekg(0,ios::beg);
 for(int i=1; i<=p; i++)
 {
	cout<<"   "<<i<<" ";
	rd.read((char*) &obj2,sizeof(obj2));
	obj2.display();
       //	cout<<"--------------------------------------------------------------------"<<endl;
 }
 rd.close();
}
// SEARCH BY NAME
void searchname()
{
 char n[50];
 cout<<"ENTER THE NAME OF EMPLOYEE:";
 gets(n);
 fstream fp;
 fp.open("emp2017.txt", ios::in);
 fp.seekg(0,ios::end);
 int p=fp.tellg();
 p=p/sizeof(obj2);
 fp.seekg(0, ios::beg);
 int x=1;
 for(int i=1; i<=p; i++)
 {
  fp.read((char*) &obj2,sizeof(obj2));
  if(stricmp(obj2.ename,n)==0)
  {
   obj2.display();
   x--;
  }
 }
 if(x==1)
 {
	cout<<"\n-----NAME NOT FOUND----";
 }
 fp.close();
}
// SEARCH BY ID
void searchid()
{
 long int n;
 cout<<"ENTER THE EMPLOYEE-ID:";
 cin>>n;
 fstream fp;
 fp.open("emp2017.txt", ios::in);
 fp.seekg(0,ios::end);
 int p=fp.tellg();
 p=p/sizeof(obj2);
 fp.seekg(0, ios::beg);
 int x=1;
 for(int i=1; i<=p; i++)
 {
  fp.read((char*) &obj2,sizeof(obj2));
  if(obj2.empid==n)
  {
   obj2.display();
   x--;
  }
 }
 if(x==1)
 {
	cout<<"\n-----EMPLOYEE NOT FOUND----";
 }
 fp.close();
}
// DELETE EMPLOYEE
void deleteemp()
{
 char dl[50];
 cout<<"ENTER THE EMPLOYEE NAME TO BE REMOVED:";
 gets(dl);
 fstream fp1,fp2;
 fp1.open("emp2017.txt", ios::in);
 fp2.open("temp1mp.txt", ios::out);
 fp1.seekg(0,ios::end);
 int p=fp1.tellg()/sizeof(obj2);
 fp1.seekg(0,ios::beg);
 int x=0;
 for(int i=1; i<=p; i++)
 {
	fp1.read((char *)&obj2,sizeof(obj2));
	if(stricmp(dl,obj2.ename)==0)         //this will not be case-sensitive
	{
		cout<<"\nDELETION SUCCESSFULL"<<endl;
		x=1;
	}
	else
	{
		fp2.write((char *)&obj2,sizeof(obj2));
	}
 }
 fp1.close();
 fp2.close();
 if(x==0)
 {
	cout<<"\n--------DETAILS NOT FOUND------"<<endl;
 }
 else
 {
	fstream f1,f2;
	f1.open("emp2017.txt", ios::out);
	f2.open("tempemp.txt", ios::in);
	for(int j=1; j<=p-1; j++)
	{
		f2.read((char *)&obj2,sizeof(obj2));
		f1.write((char *)&obj2,sizeof(obj2));
	}
	f1.close();
	f2.close();
 }
}
// UPDATE EMPLOYEE
void updateemp()
{
 char up[50];
 cout<<"ENTER THE EMPLOYEE NAME FOR UPDATING:";
 gets(up);
 cout<<"\n updation of employee-id is compulsory"<<endl;
 fstream fp1,fp2;
 fp1.open("emp2017.txt", ios::in);
 fp2.open("tempemp.txt", ios::out);
 fp1.seekg(0,ios::end);
 int p=fp1.tellg()/sizeof(obj2);
 fp1.seekg(0,ios::beg);
 int x=0;
 for(int i=1; i<=p; i++)
 {
	fp1.read((char *)&obj2,sizeof(obj2));
	if(stricmp(up,obj2.ename)==0)         //this will not be case-sensitive
	{
		addemp();
		x=1;
	}
	fp2.write((char *)&obj2,sizeof(obj2));

 }
 fp1.close();
 fp2.close();
 if(x==0)
 {
	cout<<"\n----------DETAILS NOT FOUND--------"<<endl;
 }
 else
 {
	fstream f1,f2;
	f1.open("emp2017.txt", ios::out);
	f2.open("tempemp.txt", ios::in);
	for(int j=1; j<=p; j++)
	{
		f2.read((char *)&obj2,sizeof(obj2));
		f1.write((char *)&obj2,sizeof(obj2));
	}
	f1.close();
	f2.close();
 }
}
/* TRANSACTION CLASS */
class tran
{
 private:
 char date[10];
 char month[12];
 char year[5];	      //char year[5] 5th for NULL character
 float salary;
 int empid;
 public:
 void getdata(int e, float s);
 void display();
 friend void viewsalary();
 friend void record();
};
void tran::getdata(int e, float s)
{
 cout<<"ENTER DATE(1-31):";
 gets(date);
 cout<<"\nENTER MONTH(january-december):";
 gets(month);
 cout<<"\nENTER YEAR(2000-):";
 gets(year);
 empid=e;
 salary=s;
}

void tran::display()
{
 cout<<setw(4)<<date<<setw(12)<<month<<setw(6)<<year<<"\t"<<setw(15)<<empid<<"\t"<<setw(15)<<salary<<endl;
}
tran obj3;
// DISBURSE
void disburse()
{
 long int e;
 cout<<"ENTER EMPLOYEE-ID:";
 cin>>e;
 fstream fp;
 fp.open("emp2017.txt", ios::in);
 fp.seekg(0,ios::end);
 int p=fp.tellg();
 p=p/sizeof(obj2);
 fp.seekg(0, ios::beg);
 int x=1;
 cout<<endl<<setw(11)<<"EMPLOYEE-ID"<<"\t"<<setw(20)<<"NAME"<<"\t"<<setw(13)<<"DESIGNATION"<<"\t"<<setw(13)<<"MOBILE NUMBER"<<endl;
 for(int i=1; i<=p; i++)
 {
  fp.read((char*) &obj2,sizeof(obj2));
  if(obj2.empid==e)
  {
   obj2.display();
   x--;
   break;
  }
 }
 if(x==1)
 {
	cout<<"\n-----INVALID EMPLOYEE ID----";
 }
 else
 {
  fstream rd;
  rd.open("desig.txt",ios::in);
  rd.seekg(0,ios::end);
  int p=rd.tellg();
  p=p/sizeof(obj1);
  rd.seekg(0, ios::beg);
  for(int k=1; k<=p; k++)
  {
   rd.read((char*)&obj1,sizeof(obj1));
   if(stricmp(obj1.dname,obj2.design)==0)
   {
    cout<<endl;
    obj1.displays();
    break;
   }
  }
  obj3.getdata(e,obj1.salary);
  fstream wr("tran2017.txt",ios::app);
  wr.write((char *)&obj3,sizeof(obj3));
  cout<<"\n--------SALARY DISBURSED---------";
  rd.close();
  wr.close();
  fp.close();
 }
}
//  VIEW SALARY
void viewsalary()
{
 char m[12],y[5];
 cout<<"ENTER MONTH(january-december):";
 gets(m);
 cout<<"ENTER YEAR(2000-):";
 gets(y);
 fstream rd("tran2017.txt",ios::in);
 rd.seekg(0,ios::end);
 int p=rd.tellg()/sizeof(obj3);
 int x=0;
  rd.seekg(0,ios::beg);
  cout<<setw(4)<<"DATE"<<setw(12)<<"MONTH"<<setw(6)<<"YEAR"<<"\t"<<setw(15)<<"EMPLOYEE-ID"<<"\t"<<setw(15)<<"SALARY"<<endl;
  for(int j=1; j<=p; j++)
  {
   rd.read((char *)&obj3,sizeof(obj3));
   if(stricmp(obj3.month,m)==0 && stricmp(obj3.year,y)==0)
   {
    x++;
    obj3.display();
   }
  }
  if(x==0)
  {
   cout<<"\nNo Salary For "<<m<<" "<<y<<endl;
  }
  rd.close();
}
// RECORD OF SALARY PAID
void record()
{
 int eid;
 cout<<"ENTER EMPLOYEE-ID:";
 cin>>eid;
 fstream rd("tran2017.txt",ios::in);
 rd.seekg(0,ios::end);
 int p=rd.tellg();
 p=p/sizeof(obj3);
 rd.seekg(0, ios::beg);
 int x=1;
 cout<<setw(4)<<"DATE"<<setw(12)<<"MONTH"<<setw(6)<<"YEAR"<<"\t"<<setw(15)<<"EMPLOYEE-ID"<<"\t"<<setw(15)<<"SALARY"<<endl;
 for(int i=1; i<=p; i++)
 {
  rd.read((char*) &obj3,sizeof(obj3));
  if(obj3.empid==eid)
  {
   obj3.display();
   x--;
  }
 }
 if(x==1)
 {
	cout<<"\n-----INVALID EMPLOYEE-ID----";
 }
 rd.close();
}
// MAIN
void main()
{
 clrscr();
 cout<<endl<<endl<<"------------------------******** SALARY MANAGEMENT ********---------------------";
 cout<<"\n\tFUNCTIONS PERFORMED"<<endl;
 while(1)
 {
  cout<<endl<<"1.ADD DESIGNATION\n2.VIEW ALL DESIGNATION\n3.EDIT A DESIGNATION\n4.DELETE A DESIGNATION"<<endl;
  cout<<"5.ADD NEW EMPLOYEE\n6.VIEW ALL EMPLOYEE\n7.SEARCH EMPLOYEE BY NAME\n8.SEARCH EMPLOYEE BY ID\n9.DELETE EMPLOYEE\n10.UPDATE EMPLOYEE"<<endl;
  cout<<"11.DISBURSE SALARY\n12.VIEW SALARY MONTH-WISE\n13.RECORD OF SALARY PAID\n14.EXIT"<<endl;
  cout<<endl<<"Enter your choice:";
  int ch;
  cin>>ch;
  if(ch>14)
  {
  cout<<"INVALID CHOICE"<<endl;
  delay(1000);
  clrscr();
  continue;
  }
  switch(ch)
  {
	case 1:
		clrscr();
		cout<<endl;
		insert();
		break;
	case 2:
		clrscr();
		cout<<endl;
		view();
		getch();
		break;
	case 3:
		clrscr();
		cout<<endl;
		edit();
		break;
	case 4:
		clrscr();
		cout<<endl;
		deleted();
		break;
	case 5:
		clrscr();
		cout<<endl;
		addemp();
		break;
	case 6:
		clrscr();
		cout<<endl;
		viewemp();
		getch();
		break;
	case 7:
		clrscr();
		cout<<endl;
		searchname();
		break;
	case 8:
		clrscr();
		cout<<endl;
		searchid();
		break;
	case 9:
		clrscr();
		cout<<endl;
		deleteemp();
		break;
	case 10:
		clrscr();
		cout<<endl;
		updateemp();
		break;
	case 11:
		clrscr();
		cout<<endl;
		disburse();
		break;
	case 12:
		clrscr();
		cout<<endl;
		viewsalary();
		getch();
		break;
	case 13:
		clrscr();
		cout<<endl;
		record();
		getch();
		break;
	case 14:
		cout<<endl<<"\n******************************** THANK YOU **********************************\n";
		delay(1000);
		exit(0);
  }
  cout<<"\n\n\nPLEASE WAIT...\n";
  sleep(2);
 // getch();
  clrscr();
 }
}
