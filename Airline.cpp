#include<fstream>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<iostream>
using namespace std;

#include "windows.h"

void gotoxy(int x, int y) 
{ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int select(int x,int y,int z);

void clear(int x,int y)
{int i,j;

       for(i=x;i<=y;i++)
              for(j=2;j<=79;j++){
                     gotoxy(j,i);
                     cout<<' ';
              }
}

struct Flight{
       char to[100],from[100];
       char airline[100], dtime[100];
       int no_seats,seatp,fno;
       };

int flightno(){

       ifstream fin("Flight.dat",ios::binary); 
       Flight f;
       int count=0,fno;

       while(fin.read((char*)&f,sizeof(f)))
              count++;

       fno=1000+count;
       fin.close();

       return fno;
}


void finput(Flight &f){

       cout << "\x1b[2J\x1b[1;1H" << flush;
       gotoxy(21,2); cout<<"Enter From Destination(<10): ";gets(f.from);
       gotoxy(21,4);cout<<"Enter To Destination(<10): ";gets(f.to);
       gotoxy(21,6);cout<<"Enter Name of Airline(<10): ";gets(f.airline);
       gotoxy(21,8);cout<<"Enter Number of Seats: ";cin>>f.no_seats;
       gotoxy(21,10);cout<<"Enter Price of One Seat: ";cin>>f.seatp;
       gotoxy(12,12);cout<<"Enter Departure Date and Time('dd/mm/yyyy at _h_min') as a string: \n";
       gotoxy(15,13);gets(f.dtime);
       f.fno=flightno();
       gotoxy(21,15);cout<<"Flight number: "<<f.fno;

}

void output_tab(Flight f){

       cout<<"\n"<<setw(10)<<f.airline;
       cout<<setw(10)<<f.no_seats;
       cout<<setw(10)<<f.seatp;
       cout<<setw(25)<<f.dtime;
       cout<<setw(10)<<f.fno;
}

void output_this(Flight f)
{
       cout<<"\nAirline:"<<f.airline<<"\n";
       cout<<"No. of Seats: "<<f.no_seats<<"\n";
       cout<<"Seat Price: "<<f.seatp<<"\n";
       cout<<"Departure Date and  Time: "<<f.dtime<<"\n";
       cout<<"Flight Number: "<<f.fno<<"\n";
       cout<<"**************************************\n";

}

void display_flight(){
       
       Flight f;cout << "\x1b[2J\x1b[1;1H" << flush;
       gotoxy(5,3);
       cout<<"\n"<<setw(10)<<"From"<<setw(10)<<"To";

       cout<<setw(10)<<"Seats";
       cout<<setw(10)<<"Price";
       cout<<setw(25)<<"Departure Time";
       cout<<setw(12)<<"  Flight Number";
       ifstream fin("Flight.dat",ios::binary);

       while(fin.read((char*)&f,sizeof(f))){

              cout<<"\n"<<setw(10)<<f.from<<setw(10)<<f.to;

              cout<<setw(10)<<f.no_seats;
              cout<<setw(10)<<f.seatp;
              cout<<setw(25)<<f.dtime;
              cout<<setw(10)<<f.fno;
       }

       getch();
}


class Booking{
       char passport[15], passenger[20];
       int fno; double customer;

public:
       Booking(){
              strcpy(passport,"0");
              strcpy(passenger,"0");
              fno=0; customer=0;
	}

       void enter(int no,double cno,char passenger_name[20],char passport_no[15]){
              
              fno=no;
		customer=cno;
		strcpy(passenger,passenger_name);
		strcpy(passport,passport_no);
	}

	void display(int no){
		if(fno==no)
		       {cout<<setw(25)<<passenger<<setw(20)<<passport<<setw(25)<<customer<<endl;}
	}
 };

class customer{
       char customer_name[26]; 
       int h;
       long double mob_no; double customer_no; char passport_no[15];
       struct history{
              char date[26], to[50], from[50], airline[50], dtime[100];
              float nseats,totalp,fno;
              struct passenger{
                     char passenger_names[10][20], passport_no[10][15];
              }P;
       }H[20];

public:customer(){
       h=0;
       mob_no=0;
       strcpy(passport_no,"0");
       customer_no=0;
       }

       void input();

       void output(){
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(30,3);
              cout<<"Name: "<<customer_name;
              gotoxy(24,4);
              cout<<"Customer Number: "<<customer_no;
              gotoxy(24,5);
              cout<<"Passport Number: "<<passport_no;
              gotoxy(24,7);
              cout<<"Mobile Number: "<<setprecision(8)<<mob_no;
         }


       void plot_history(Flight,float,int,char[][20],char[][15]);
       void show_history();
       double retcustomer_no();
       int rethistory_no();

};

double customer::retcustomer_no()
       {return customer_no;}

int customer::rethistory_no()
       {return h;}

void customer::input(){
       
       char ch;
       int count;
       int return_count();
       
       do{
       cout << "\x1b[2J\x1b[1;1H" << flush;
       gotoxy(31,2);
       cout<<"Enter Name: ";
       gets(customer_name);
       gotoxy(31,3);
       cout<<"Enter 8 Digitmobile No.: ";
       cin>>mob_no;
       gotoxy(31,6);
       cout<<"Enter Passport No.: ";
       cin>>passport_no;
       customer C;

       customer_no=return_count();

       if( strlen(customer_name)>1 && mob_no>9999999 && passport_no!=0 ){
              gotoxy(31,7);

              cout<<"Customer Number : "<<customer_no;
              gotoxy(31,9);
              cout<<"Successful Registration";
              ch='y';
       }
       else{
              gotoxy(30,9);
              cout<<"Sorry,Information Invalid";
              gotoxy(30,10);
              cout<<"Press any Key to Reenter";
              ch='n';
              getch();
       }
       
       }while(ch!='y');
}

void customer::show_history(){
       
       cout << "\x1b[2J\x1b[1;1H" << flush;int j=8; int found=0;
       gotoxy(35,5);
       cout<<"Name: "<<customer_name;
       gotoxy(24,7);
       cout<<"Customer Number: "<<customer_no;

       for(int i=0;i<h;i++){
              found=1;

              gotoxy(24,j); j++;
              cout<<"Date Booked: "<<H[i].date;
              gotoxy(24,j); j++;
              cout<<"To: "<<H[i].to;
              gotoxy(24,j); j++;
              cout<<"From: "<<H[i].from;
              gotoxy(24,j); j++;
              cout<<"Flight Number: "<<H[i].fno;
              gotoxy(24,j); j++;
              cout<<"Departure Time: "<<H[i].dtime;
              gotoxy(24,j); j++;
              cout<<"Number of seats booked: "<<H[i].nseats;
              gotoxy(24,j); j++;
              cout<<"Total Price Paid: "<<H[i].totalp;
              gotoxy(24,j); j++;
              cout<<"PASSENGERS"<<endl;j++;
              cout<<endl<<setw(30)<<"Passenger name"<<setw(20)<<"Passport Number"<<endl;j++;

              for(int m=0;m<H[i].nseats;m++){
                     cout<<setw(30)<<H[i].P.passenger_names[m]<<setw(20)<<H[i].P.passport_no[m]<<endl;j++;
                     }
              
              gotoxy(20,j); j++;
              cout<<"******************************************";
       }

       if(found==0);{
              gotoxy(35,9);cout<<"No Past Bookings Done";
              }
       }

void customer::plot_history(Flight f,float totalp,int seats,char passenger_name[][20],char passport_no[][15]){
       h++;
       cout<<"\nEnter the Date of Booking: ";
       gets(H[h-1].date);
       strcpy(H[h-1].to,f.to);
       strcpy(H[h-1].from,f.from);
       strcpy(H[h-1].dtime,f.dtime);
       H[h-1].totalp=totalp;
       H[h-1].fno=f.fno;
       H[h-1].nseats=seats;                                    
       
       for(int i=0;i<seats;i++){
              strcpy(H[h-1].P.passenger_names[i],passenger_name[i]);
              strcpy(H[h-1].P.passport_no[i],passport_no[i]);
              }
}

void get_password(char ch[]){
       
       int i=0;char t;
       do{
              t=getch();

              if(t=='\b'&&i!=0)
                     {cout<<"\b\b";
                     i=i-1;}
              else if(t!='\r')
                     {ch[i++]=t;
                     cout<<'*';}

       }while(t!='\r');

       ch[i]='\0';
}



class admin{
       char user_name[100],password[100];

public: void input(){
       
       cout << "\x1b[2J\x1b[1;1H" << flush;
       gotoxy(25,3);
       cout<<"Enter Username: ";gets(user_name);
       gotoxy(20,4);
       cout<<"Enter Password(Case Sensitive): ";get_password(password);
       
       }

int check_username(char A[]);

int check_password(char A[]){

       if(strcmp(password,A)==0)
              return 1;
       else
              return 0;
}

void change_password(char A[]){

       strcpy(password,A);
       gotoxy(26,14);
       cout<<"Password Succesfully Changed";
}

char* ret_username();

};

int admin::check_username(char A[]){

       if(strcmp(user_name,A)==0)
              return 1;
       else
              return 0;
}

char* admin::ret_username()
       {return user_name;}

int get_input(admin &A){
       
       A.input();
       admin B;
       int i=0;
       ifstream fin("Admin.dat",ios::binary);
       while(fin.read((char*)&B,sizeof(B)))
              if(A.check_username(B.ret_username())==1)
                     i++;
       
       fin.close();
       return i;
}

void addadmin(){
       
       cout << "\x1b[2J\x1b[1;1H" << flush; 
       int i,achecker();
       admin A;
       char ch='n',user[100],pass[100];

       if(achecker()==0){
              ofstream fout("Admin.dat",ios::binary);
              
              A.input();
              fout.write((char*)&A,sizeof(A));
              fout.close();
       }
       else{
              gotoxy(25,2);cout<<"Enter Details of Pre Existing Admin";
              do{
                     gotoxy(31,5);cout<<"Username: ";
                     gets(user);
                     gotoxy(31,6);cout<<"Password: ";
                     get_password(pass);
                     int count=0;
                     ifstream fin("Admin.dat",ios::binary);
                     gotoxy(31,8);
                     cout<<"Checking Username and Password........";

                     while(fin.read((char*)&A,sizeof(A)))
                            if(A.check_username(user)==1&&A.check_password(pass)==1)
                                   {count=1;gotoxy(29,8);cout<<"Administrator Verified";}

                     fin.close();
                     if(count==1){
                            do{
                                   i=get_input(A);
                                   if(i!=0){
                                          gotoxy(10,12);
                                          cout<<"Admin Already Exists, Press any Key to Re-enter Details";
                                          getch();
                                          A.input();
                                   }
                            }while(i!=0);
                            ch='n';
                            ofstream fout("Admin.dat",ios::binary|ios::out|ios::app);
                            fout.write((char*)&A,sizeof(A));
                            fout.close();
                            gotoxy(25,15);
                            cout<<"Admin Successfully Added";getch();
                     }
                     else if(count==0){
                            gotoxy(29,8);cout<<"Administrator Not Verified";
                            gotoxy(25,10);cout<<"Enter Y to Re-enter and N to exit";
                            cin>>ch;clear(4,18);gotoxy(2,10);
                     }
              }while(ch=='y'||ch=='Y');
       }   
}

void change_password(){

       char ch='n',user[100],pass[100]; 
       admin A;
       char newp[100];
       
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(24,3);cout<<"Enter Pre-existing Username and Password";
              gotoxy(31,5);cout<<"Username: ";gets(user);
              gotoxy(31,6);cout<<"Password: ";get_password(pass);
              int count=0;
              fstream file("Admin.dat",ios::binary|ios::out|ios::in);
              gotoxy(31,8);cout<<"Checking Username and Password........";

              while(file.read((char*)&A,sizeof(A)))
                     if(A.check_username(user)==1&&A.check_password(pass)==1){
                            count=1;ch='n';
                            gotoxy(28,9);cout<<"Administrator Verified";
                            gotoxy(21,11);cout<<"Enter New Password: ";
                            get_password(newp);
                            A.change_password(newp);
                            file.seekg(-sizeof(A),ios::cur);
                            file.write((char*)&A,sizeof(A));
                     }

              file.close();
              if(count==0){
                     gotoxy(27,9);cout<<"Administrator Not Verified";
                     gotoxy(24,11);cout<<"Enter Y to Re-enter and N to exit: ";cin>>ch;
              }

       }while(ch=='y'||ch=='Y');

}

void clear_customer(){

       admin A;
       char ch='n',user[100],pass[100];
       
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(24,3);cout<<"Enter Existing Username and Password";
              gotoxy(31,5);cout<<"Username: ";
              gets(user);
              gotoxy(31,6);cout<<"Password: ";
              get_password(pass);
              int count=0;
              ifstream fin("Admin.dat",ios::binary);
              gotoxy(31,8);cout<<"Checking Username and Password..........";

              while(fin.read((char*)&A,sizeof(A)))
                     if(A.check_username(user)==1&&A.check_password(pass)==1){
                            ofstream fout("Customer.dat",ios::binary);
                            count=1;
                            ch='n';
                            fout.close();
                            gotoxy(28,10);
                            cout<<"Administrator Verified";
                            gotoxy(29,11);
                            cout<<"Customer File Cleared";
                            getch();
                     }

              if(count==0){
                     gotoxy(27,8);cout<<"Administrator Not Verified";
                     gotoxy(24,9);cout<<"Enter Y to Re-enter and N to exit: ";
                     cin>>ch;
              }

       }while(ch=='y'||ch=='Y');
}

void clear_flight(){
       
       admin A;char ch='n',user[100],pass[100];
       
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(24,3);cout<<"Enter Existing Username and Password";
              gotoxy(31,5);cout<<"Username: ";
              gets(user);
              gotoxy(31,6);cout<<"Password: ";
              get_password(pass);
              int count=0;
              ifstream fin("Admin.dat",ios::binary);
              gotoxy(31,8);cout<<"Checking Username and Password..........";

              while(fin.read((char*)&A,sizeof(A)))
                     if(A.check_username(user)==1&&A.check_password(pass)==1){
                            ofstream fout("Flight.dat",ios::binary);
                            count=1;ch='n';
                            fout.close();
                            gotoxy(28,10);cout<<"Admin Verified";
                            gotoxy(31,11);cout<<"Flight File Cleared";getch();
                     }

              if(count==0){
                     gotoxy(27,8);cout<<"Administrator Not Verified";
                     gotoxy(24,9);cout<<"Enter Y to Re-enter and N to exit: ";cin>>ch;
              }
              
       }while(ch=='y'||ch=='Y');
}

void clear_booking(){
       
       admin A;
       char ch='n',user[100],pass[100];
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(24,3);cout<<"Enter Existing Username and Password";
              gotoxy(31,5);cout<<"Username: ";
              gets(user);
              gotoxy(31,6);cout<<"Password: ";
              get_password(pass);
              int count=0;
              ifstream fin("Admin.dat",ios::binary);
              gotoxy(31,8);cout<<"Checking Username and Password..........";

              while(fin.read((char*)&A,sizeof(A)))
                     if(A.check_username(user)==1&&A.check_password(pass)==1){
                            ofstream fout("Booking.dat",ios::binary);
                            count=1;ch='n';
                            fout.close();
                            gotoxy(28,10);cout<<"Admin Verified";
                            gotoxy(31,11);cout<<"Booking File Cleared";getch();
                     }

              if(count==0){
                     gotoxy(27,8);cout<<"Administrator Not Verified";
                     gotoxy(24,9);cout<<"Enter Y to Re-enter and N to exit: ";cin>>ch;
              }
       }while(ch=='y'||ch=='Y');
}

int return_count(){
       
       ifstream fin("Customer.dat",ios::binary); 
       customer c;
       int count=1000;

       while(fin.read((char*)&c,sizeof(c)))
              count++;

       fin.close();
       return count;
}


int cchecker(){
       customer C; int count=0;
       ifstream fin("Customer.dat",ios::binary);
       while(fin.read((char*)&C,sizeof(C)))
              count++;
       fin.close();

       if(count==0)
              return 0;
       else
              return 1;
}

int achecker(){
       admin A; 
       int count=0;
       ifstream fin("Admin.dat",ios::binary);
       while(fin.read((char*)&A,sizeof(A)))
              count++;
       fin.close();
       
       if(count==0)
              return 0;
       else
              return 1;
}

int fchecker(){
       
       Flight F; int count=0;
       ifstream fin("Flight.dat",ios::binary);
       while(fin.read((char*)&F,sizeof(F)))
              count++;
       fin.close();
       if(count==0)
              return 0;
       else
              return 1;
}

int bchecker(){
       
       Booking b; int count=0;
       ifstream fin("Booking.dat",ios::binary);
       while(fin.read((char*)&b,sizeof(b)))
              count++;
       fin.close();
       if(count==0)
              return 0;
       else
              return 1;
}

void add(){
       cout << "\x1b[2J\x1b[1;1H" << flush;
       Flight F;
       fstream file("Flight.dat",ios::binary|ios::app);
       finput(F);
       file.write((char*)&F,sizeof(F));
       file.close();gotoxy(20,16);
       cout<<"Flight added sucessfully";getch();
}

void remove(){
       cout << "\x1b[2J\x1b[1;1H" << flush;Flight f;int no,count=0; gotoxy(10,5);
       cout<<"Enter Flight Number to remove: ";
       cin>>no;
       ifstream fin("Flight.dat",ios::binary);
       ofstream fout("temp.dat",ios::binary);
       while(fin.read((char*)&f,sizeof(f)))
              if(f.fno!=no)
                     {fout.write((char*)&f,sizeof(f));}
       else
              count++;
       
       if(count==0)
              {gotoxy(10,6);cout<<"Flight Number "<<no<<" does not exist, and therefore was not deleted";}
       else
              {gotoxy(10,6);cout<<"Flight Number "<<no<<" deleted";}

       fin.close();fout.close();
       remove("Flight.dat");
       rename("temp.dat","Flight.dat");
 }

void flight_specs(){
       Flight f;
       int opt;

       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(30,10);
              cout<<"***FLIGHT MENU***"<<endl;
              gotoxy(20,11);
              cout<<"1. Search Flights By Destinations"<<endl;
              gotoxy(20,12);
              cout<<"2. Display All Available Flights"<<endl;
              gotoxy(20,13);
              cout<<"3. Return to Display Menu"<<endl;
              gotoxy(20,14);
              cout<<"4. EXIT"<<endl;
              opt=select(11,14,18);
              switch(opt){
                     case 1:
                            {char to[50],from[50];
                            cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(20,5);
                            cout<<"Enter To and From Locations";
                            gotoxy(15,7);
                            cout<<"TO: ";
                            gets(to);
                            gotoxy(15,8);
                            cout<<"FROM: ";
                            gets(from);
                            gotoxy(5,10);
                            cout<<"\n"<<setw(10)<<"Airline";
                            cout<<setw(10)<<"Seats";
                            cout<<setw(10)<<"Price";
                            cout<<setw(25)<<"Departure Time";
                                   cout<<setw(10)<<"  Flight Number";
                            ifstream fin("Flight.dat",ios::binary);
                            while(fin.read((char*)&f,sizeof(f)))
                            if(strcmpi(f.to,to)==0&&strcmpi(f.from,from)==0)
                                          output_tab(f);
                            getch();
                            fin.close();}
                            break;
                     case 2: cout << "\x1b[2J\x1b[1;1H" << flush;display_flight();
                            break;
                     case 3:break;
                     case 4:exit(0);
              }
       }while(opt!=3);

}

void customer_specs(){
       cout << "\x1b[2J\x1b[1;1H" << flush;double cno,count=0; customer c;
       gotoxy(10,10);
       cout<<"Enter Customer Number of Customer To Be Searched: ";
       cin>>cno;
       ifstream fin("Customer.dat",ios::binary);

       while(fin.read((char*)&c,sizeof(c)))
              if(cno==c.retcustomer_no())
                     {c.output();count++;}

       if(count==0){
              cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,10);
              cout<<"Customer Does Not Exist, PRESS ANY KEY TO RETURN TO DISPLAY MENU";}
       getch();
       fin.close();
}

void history_customer(){
       ifstream fin("Customer.dat",ios::binary);
       customer c;double cno;
       cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,15);
       cout<<"Enter Customer Number of Customer To Be Searched: ";
       cin>>cno;

       while(fin.read((char*)&c,sizeof(c)))
              if(cno==c.retcustomer_no())
                     c.show_history();

       getch();
       fin.close();
}

void booked_on_flight(){

       cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,5);
       int no,count=0;
       Booking b; ifstream fin("Booking.dat",ios::binary);
       cout<<"Enter the Flight Number: ";cin>>no;
       cout<<endl<<setw(25)<<"Passenger Name"<<setw(20)<<"Passport No."<<setw(25)<<"Reg. by Customer No."<<endl;

       while(fin.read((char*)&b,sizeof(b)))
              {b.display(no);count++;}

       if(count==0)
              cout<<"\n\n\tNo Passengers Booked on Flight";

       getch();
       fin.close();

}

void display_Menu(){
       
       int opt;
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(35,13);
              cout<<"***DISPLAY MENU***";
              gotoxy(20,15);
              cout<<"1. Display Flights By Specification"<<endl;
              gotoxy(20,16);
              cout<<"2. Display Particular Customer's Information"<<endl;
              gotoxy(20,17);
              cout<<"3. Display History of a  Particular Customer"<<endl;
              gotoxy(20,18);
              cout<<"4. Show the Info of All Passengers on a Flight"<<endl;
              gotoxy(20,19);
              cout<<"5. Return to Main Menu"<<endl;
              gotoxy(20,20);
              cout<<"6. EXIT";
              opt=select(15,20,18);
              switch(opt){
                     case 1:
                            if(fchecker()==1)
                                   flight_specs();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;
                                   gotoxy(15,15);
                                   cout<<"ERROR: FILE EMPTY";
                                   getch();}
                            break;

                     case 2: if(cchecker()==1)
                            customer_specs();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;
                                   gotoxy(15,15);
                                   cout<<"ERROR: FILE EMPTY";
                                   getch();}
                            break;

                     case 3:if(cchecker()==1)
                                   history_customer();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;
                                   gotoxy(15,15);
                                   cout<<"ERROR: FILE EMPTY";
                                   getch();}
                            break;

                     case 4:if(bchecker()==1)
                                   booked_on_flight();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;
                                   gotoxy(15,15);
                                   cout<<"ERROR: FILE EMPTY";
                                   getch();}

                     case 5: break;

                     case 6:exit(0);
              }
       }while(opt!=5);
}


void admin_Menu(){
       int opt;

       do     
              {cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(25,13);
              cout<<"*****ADMINISTRATOR MENU*****";
              gotoxy(20,15);
              cout<<"1. Add an Administrator"<<endl;
              gotoxy(20,16);
              cout<<"2. Change Password"<<endl;
              gotoxy(20,17);
              cout<<"3. Clear Customer File"<<endl;
              gotoxy(20,18);
              cout<<"4. Clear Flight File"<<endl;
              gotoxy(20,19);
              cout<<"5. Clear Booking File"<<endl;
              gotoxy(20,20);
              cout<<"6. Return to Main Menu"<<endl;
              gotoxy(20,21);
              cout<<"7. EXIT"<<endl;
              opt=select(15,20,19);

              switch(opt){
                     case 1:addadmin();
                            break;
                     case 2:if(achecker()!=0)
                                   change_password();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(2,15);
                                   cout<<setw(52)<<"ERROR: FIRST REGISTER AN ADMIN";
                                   getch();}

                            break;
                     case 3:if(achecker()!=0)
                                   clear_customer();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(2,15);
                                   cout<<setw(52)<<"ERROR: FIRST REGISTER AN ADMIN";
                                   getch();}

                            break;
                     case 4:if(achecker()!=0)
                                   clear_flight();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(2,15);
                                   cout<<setw(52)<<"ERROR: FIRST REGISTER AN ADMIN";
                                   getch();}

                            break;
                     case 5:if(achecker()!=0)
                                   clear_booking();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(2,15);
                                   cout<<setw(52)<<"ERROR: FIRST REGISTER AN ADMIN";
                                   getch();}
                     case 6:break;
                     case 7:exit(0);
              }
       }while(opt!=6);
}


int select(int x,int y,int z){
       int i=x,opt;char ch;
       gotoxy(z,i);
       cout<<">";
       do{
              ch=getch();
              ch=tolower(ch);
              if(ch=='w'&&i!=x)
                     {gotoxy(z,i);
                     cout<<" ";
                     gotoxy(z,--i);
                     cout<<">";
                            }
              else if(ch=='w'&&i==x)
                     {gotoxy(z,i);
                     cout<<" ";
                            i=y;
                     gotoxy(z,i);
                     cout<<">";
                            }
              else if(ch=='s'&&i==y)
                     {gotoxy(z,i);
                     cout<<" ";
                            i=x;
                     gotoxy(z,i);
                     cout<<">";
                            }
              else if(ch=='s'&&i!=y)
                     {gotoxy(z,i);
                     cout<<" ";
                     gotoxy(z,++i);
                     cout<<">";
                            }
       }while(ch!='\r');
       opt=i-x+1;
       return opt;
}


void book_flight(){
       Flight f; Booking b; customer c;
       double cno; int count=0,seats;
       float totalp;
       char to[50],from[50],passenger_name[10][20],passport_no[10][15];
       int no;

       fstream f2("Customer.dat",ios::binary|ios::in|ios::out);

       cout << "\x1b[2J\x1b[1;1H" << flush;  gotoxy(15,5);
       cout<<"Enter the Customer Number of Customer: ";
       cin>>cno;

       while(f2.read((char*)&c,sizeof(c))){
              if(cno==c.retcustomer_no()){
                     c.output();

                     cout<<"\nEnter TO Location: ";
                     gets(to);

                     cout<<"Enter FROM Location: ";
                     gets(from);

                     cout<<"\n"<<setw(10)<<"Airline";
                     cout<<setw(10)<<"Seats";
                     cout<<setw(10)<<"Price";
                     cout<<setw(25)<<"Departure Time";
                     cout<<setw(20)<<"Flight Number";
                     fstream file("Flight.dat",ios::binary|ios::in|ios::out);
                     while(file.read((char*)&f,sizeof(f)))
                            if(strcmpi(f.to,to)==0&&strcmpi(f.from,from)==0)
                                   {output_tab(f);count++;}
                     file.close();

                     if(count==0)
                            {cout<<"\n\nNo Flights with Those Specifications is Available";break;}
                     count=0;
                     cout<<"\n\nEnter Flight Number Of Desired Flight: ";
                     cin>>no;


                     file.open("Flight.dat",ios::binary|ios::in|ios::out);

                     int found=0;
                     while(file.read((char*)&f,sizeof(f))){
                            if(no==f.fno){
                                   found=1;
                                   cout<<"\nEnter No. Of Seats To be Booked(<=10): ";
                                   cin>>seats;
                                   if(seats<=f.no_seats&&seats<=10)
                                          {output_this(f);
                                          cout<<endl<<"Travel in this Flight?(y/n)"<<endl;
                                          char ch;
                                          cin>>ch;

                                          if(ch=='n'||ch=='N')
                                                 break;

                                          ofstream fout("Booking.dat",ios::binary|ios::app);
                                          for(int i=0;i<seats;i++)
                                                 {cout<<"\n Enter Information of Passenger Number "<<(i+1);
                                                 cout<<": \n\tPassenger Name: "; gets(passenger_name[i]);
                                                 cout<<"\n\tPassport Number: ";gets(passport_no[i]);
                                                 b.enter(no,cno,passenger_name[i],passport_no[i]);
                                                 fout.write((char*)&b,sizeof(b));
                                                 }

                                   totalp=seats*f.seatp;
                                   f.no_seats=f.no_seats-seats;
                                   cout<<endl<<"Total Price: "<<totalp;
                                   c.plot_history(f,totalp,seats,passenger_name,passport_no);				
                                   f2.seekg(-sizeof(c),ios::cur);
                                   file.seekg(-sizeof(f),ios::cur);
                                   f2.write((char*)&c,sizeof(c));
                                   file.write((char*)&f,sizeof(f));

                            fout.close();
                            f2.close();
                            file.close();

                            cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,10);
                            cout<<"Booking done";
                            getch();break;
                            }
                            else{
                                   cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,10);
                                   if(seats>f.no_seats)
                                          {cout<<"Not Enough Seats On Flight";getch();break;}
                                   else if(seats>10)
                                          {cout<<"Exceeded The Possible Number of Passengers That can be Carried in One Booking"; getch();break;}
                            }

                            }
                     }
              if(found==0){
                     cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,10);
                     cout<<"No Flight Of That Number Exist";getch(); break;
                     }
              }
              else{
                     cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(15,10);
                     cout<<"Customer Does Not Exist";getch();break;
              }
       }
}


void intro(){
       gotoxy(30,5);
       cout<<"CARMEL SCHOOL KUWAIT";
       gotoxy(31,10);
       cout<<"Airline Ticketing Agency";
       gotoxy(15,11);
       cout<<"By Hussain Manasi, Unati Sharma, Albert and Sancia";
       gotoxy(3,17);
       cout<<"This program stores details of various flights and their seats availability.\n";
       cout<<"It also stores details of customers and maintains a record of transactions\n made by the customer";
       getch();
}


int main()
{
       char ch; Flight f; customer c; admin A;
       int opt,no;
       intro();
       do{
              cout << "\x1b[2J\x1b[1;1H" << flush;
              gotoxy(35,10);
              cout<<"ULTIMA TRAVEL AGENCY";
              gotoxy(25,13);
              cout<<"**************MENU***************";
              gotoxy(25,15);
              cout<<"1. Add a Flight"<<endl;
              gotoxy(25,16);
              cout<<"2. Delete a Flight"<<endl;
              gotoxy(25,17);
              cout<<"3. Book Tickets"<<endl;
              gotoxy(25,18);
              cout<<"4. Add a Customer"<<endl;
              gotoxy(25,19);
              cout<<"5. Display Menu"<<endl;
              gotoxy(25,20);
              cout<<"6. Administrator Menu"<<endl;
              gotoxy(25,21);
              cout<<"7. EXIT"<<endl;
              gotoxy(25,24);
              cout<<"Press W to Move Up and S to Move Down";
              opt=select(15,21,23);

              switch(opt){
                     case 1: add();
                            break;
                     case 2: if(fchecker()!=0)
                                   remove();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;
                                   gotoxy(20,20);
                                   cout<<"Error: Flight file empty";}
                            break;
                     case 3: if(cchecker()==1)
                                   book_flight();
                            else
                                   {cout << "\x1b[2J\x1b[1;1H" << flush;gotoxy(20,10);
                                   cout<<"First Add a Customer";
                                   }
                            break;
                     case 4:{cout << "\x1b[2J\x1b[1;1H" << flush;
                            ofstream fout("Customer.dat",ios::binary|ios::app);
                            c.input();
                            fout.write((char*)&c,sizeof(c));
                            break;}
                     case 5: display_Menu();
                            break;
                     case 6: admin_Menu();
                            break;
                     case 7: exit(0);}
                            getch();
       }while(opt!=9);

       return 0;
}
