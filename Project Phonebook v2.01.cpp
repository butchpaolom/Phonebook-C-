//started: 2nd week of September 2016
//Finals Project Address book!
//This program is a made by:
//Butch Madahan, Andreian Billones, Tricia Lanto, Zyrus Manalo
//This is an address book that saves, edit and deletes contacts.
//release v2.01(bugkill)
//removed Filipino language
//Color Settings added
//Fixed bug corrupting database when blank input on edit and add contact
//Fixed bug when input anything on delete prompt causes it not to work
//Security added - Hidden file
//Added Save a text copy option
//Added About
//Added text brightness
//Animation Screen updated

#include <iostream>
#include <fstream> //for file handling
#include <cstdio> //for input and output operations
#include <string>
#include <algorithm> // for transformation and replace
#include <unistd.h>	// for timer
#include <windows.h> //for maximize and minimize
#include <iomanip> //setw()

using namespace std;
int language10, c_count, new_c, ndelete, opt_replace, boot_s=1, ndelete_f, brightness=2, spaces, spaces1, verify_a=0, verify_e=0;
string fname, lname, cnum, s_cnum, s_fname, s_lname, s_street, s_baranggay, s_province, s_country, street, baranggay, province, country, quit, color_opt;
string state, n_fname, n_lname, n_street, n_province, n_baranggay, n_country, n_cnum, opt_n, opt_rep;



void ndelete_clear(); //bug fix in delete
void n_replace(); //edit 
void delete_contacts(); //function in main
void delete_specific();
void c_subsearch();
void a_subsearch();
void n_subsearch();
void edit_contact();
void display_contacts();
void color();
void add_contact();
void search();
void delete_all();
void count();
void ext();
void search_cnum();
void n_inputs_upcaps();
void add_inputs_upcaps();
void boot_screen();
void hideit();
void verify_add();//bug fix
void verify_edit();//bug fix
void save();
void about();
void art_delete();
void under_space();
void column();
void countfadd();


int main() {
		hideit();
		system("title Welcome!");
		if (boot_s==1){
		ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
		boot_screen();}
		ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
		system("cls"); 
		count();
		new_c=c_count+1;
		string option;
		system("title Address book Program");	
		cout << "This Address book currently holds " << "( " << c_count << " / 100 )" << " contacts.\t    Brightness: (" << brightness << "). Input (+/-) to increase/decrease\t\t\t\t\t\t\t\t\t\t\tthe brightness of text.\n";
		cout << "What would you like to do?\n"<< "1. Add Contact\n2. Edit Contact\n3. Delete Contacts\n"; 
		cout << "4. View Contacts\n5. Search Address Book\n6. Color Settings\n7. Save .txt copy of contacts\n8. About \n9. Exit\n\nEnter the number of your option: ";
		cin >> option;
		system("cls");
		{
			if (option=="1")	{
				if (c_count<=100)
				{
				add_contact();
				}
				else
				{
				system("title No more spaces for new contacts!");
					cout << "The Address book is full (" << c_count << "/100), please delete some contacts.\n";
					system("pause>null");
				}
			}
			else if (option=="2")	{
				edit_contact();
			}
			else if (option=="3")	{
				delete_contacts();
			}
			else if (option=="4")	{
				system("title View all");
				cout << "Just press any key to return to Menu.\n\n";
				display_contacts();
				system("pause>null");
				main();
			}
			else if (option=="5")	{		
				search();
			}
			else if (option=="6")	{
				color();
			}
			else if (option=="7")	{
					save();
				}
			else if (option=="8")	{
					about();
			}
			else if (option=="9")	{
					ext();
					return 0;
			}
			else if (option=="+")	{
				if (brightness==2){
				system("color 0F");}
				else if (brightness==1){
				system("color 07");}
				else if (brightness==3){
				brightness-=1;}
				brightness+=1;
				main();
			}
			else if (option=="-")	{
				if (brightness==2){
				system("color 08");}
				else if (brightness==3){
				system("color 07");}
				else if (brightness==1){
				brightness+=1;}
				brightness-=1;
				main();
			}	
			else	{
					main();
				}	
	}
}
void countfadd(){
	{
		if ((fname.length()+lname.length())>30||(street.length()+baranggay.length()+country.length()+province.length()>60)||(cnum.length()>11))
		{
			system("cls");
			cout << "The maximum characters for name is only 30, 60 for address and 11 for contacts spaces not included.\n";
			system("title Exceeded maximum input!");
			verify_a=1;
			system("pause>null");
		}
	}
}
void art_delete(){
	 {
    	system("title Deleting.");
    	usleep(300000);
    	system("title Deleting..");
    	usleep(300000);
    	system("title Deleting...");
    	usleep(300000);
    	system("title Deleting Success!");
	}
}
void about(){
	system("title About ( •_•)");
	system("cls");
	cout << "\t       \tChangelogs for Phonebook v2.01 (10/07/2016)\n\n*Fixed bug that causes database to be corrupted when blank input on edit and add contact.";
	cout << "\n*Fixed bug when input anything on delete prompt causes it not to work.\n*Color settings added.\n*Basic security for the database by hiding added.\n*Removed language setting.\n*About added on the main screen.";
	cout << "\n*Save a copy of .txt file added.\n*Text brightness added.\n*Better display of all contacts.\n*Loading screen animation updated.";
	cout << "\n\n\t\t\t      (c)2016 TheGroup4\n\n    Developers: Butch Madahan, Andreian Billones, Tricia Lanto, Zyrus Manalo";
	cout << "\n\n\t\t\tPress any key to return to Menu.";
	system("pause>0");
	main();
}
void column(){
	spaces=30-(lname.length() + fname.length());
	spaces1=60-(street.length()+baranggay.length()+province.length()+country.length());
}
void save(){
	system("title Save a copy");
	system("cls");
	ifstream save("database.txt");
	string prompt_save;
	cout << "Are you sure you want a copy? Input Yes if you want, else type anything to go to Menu : ";
	cin.sync();
	getline(cin,prompt_save);
	transform( prompt_save.begin(), prompt_save.end(), prompt_save.begin(), ::toupper);
	if (prompt_save=="YES"){
	remove("Contacts.txt");
			{
			system("title Saving");
			usleep(300000);
			system("title Saving.");
			usleep(300000);
			system("title Saving..");
			usleep(300000);
			system("title Saving...");
			usleep(300000);
			system("title Saved!");			
			}
	while (save >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
		if (state == "1"){
			ofstream copy("Contacts.txt", ios::app);
			under_space();
			copy << new_c << ". Name:      " << fname << ' ' << lname << endl << "   Address:   #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl << "   Contact #: " << cnum << endl << endl << "----------------\n\n";
			copy.close();}
		}
		system("cls");
		cout << "A file named 'Contacts.txt' is successfully made in the location of the program.\n\nPress any key to return to Menu";
		system("pause>null");	
		}
    	save.close();
	main();	
	}
void replace_id(){
		if(opt_replace==1){
			fname=n_fname;}
			else if(opt_replace==2){
			lname=n_lname;}
			else if(opt_replace==3){
			lname=n_lname;
			fname=n_fname;}
			else if(opt_replace==4){
			street=n_street;}
			else if(opt_replace==5){
			baranggay=n_baranggay;}
			else if(opt_replace==6){
			province=n_province;}
			else if(opt_replace==7){
			country=n_country;}
			else if(opt_replace==8){
			province=n_province;
			country=n_country;
			street=n_street;
			baranggay=n_baranggay;}
			else if(opt_replace==9){
			cnum=n_cnum;}
			else if(opt_replace==10){
			lname=n_lname;
			fname=n_fname;	
			province=n_province;
			country=n_country;
			street=n_street;
			cnum=n_cnum;
			baranggay=n_baranggay;}
			else{
			main();}		
}
void n_replace() {	
	display_contacts();
	cout << "\nWhat do you want to replace in line '" << ndelete <<"' ?\n1. Name\n2. Address\n3. Contact\n4. All\n\nInput the number of your option: ";
	cin.sync();
	getline(cin,opt_rep);
	system("cls");
	display_contacts();
	cout << "\nPlease use space for separation.\n" << endl;
	if (opt_rep=="1"){
		cout << "What do you want to replace in line '" << ndelete <<"'?\n1. First name\n2. Last name\n3. First and Last name\n\nInput the number of your option: ";
		getline(cin,opt_n);
		if (opt_n=="1"){
			cout << "Input the new First name: ";
			getline(cin,n_fname);
			opt_replace=1;
		}
		else if (opt_n=="2"){
			cout << "Input the new Last name: ";
			getline(cin,n_lname);
			opt_replace=2;
		}
		else if (opt_n=="3"){
			cout << "Input the new First name: ";
			getline(cin,n_fname);
			cout << "Input the new Last name: ";
			getline(cin,n_lname);
			opt_replace=3;
		}
		else{
		system("cls");
		n_replace();	
		}
		}
	else if(opt_rep=="2"){
		cout << "What do you want to replace in line '" << ndelete <<"'?\n1. Street and Street number\n2. Baranggay\n3. Province\n4. Country\n5. Whole Address\n\nInput the number of your option: ";
		getline(cin,opt_n);
		if (opt_n=="1"){
			cout << "Input the new Street and Street number: #";
			getline(cin,n_street);
			opt_replace=4;
		}
		else if (opt_n=="2"){
			cout << "Input the new Baranggay: ";
			getline(cin,n_baranggay);
			opt_replace=5;
		}
		else if (opt_n=="3"){
			cout << "Input the new City/Town and Province: ";
			getline(cin,n_province);
			opt_replace=6;
		}
		else if (opt_n=="4"){
			cout << "Input the new Country: ";
			getline(cin,n_country);
			opt_replace=7;
		}
		else if (opt_n=="5"){
			cout << "Input the new Street and Street number: #";
			getline(cin,n_street);
			cout << "Input the new Baranggay: ";
			getline(cin,n_baranggay);
			cout << "Input the new City/Town and Province: ";
			getline(cin,n_province);
			cout << "Input the new Country: ";
			getline(cin,n_country);
			opt_replace=8;
		}
		else {
			system("cls");
			n_replace();
		}		
	}
	else if (opt_rep=="3"){
		opt_n="1";
		cout << "Input the new Contact number for line '" << ndelete <<"': ";
		getline(cin,n_cnum);
		opt_replace=9;
	}
	else if	(opt_rep=="4"){
		cout << "Editting all inputs in line '" << ndelete << "'.\n\nInput the new First name: ";
		getline(cin,n_fname);
		cout << "Input the new Last name: ";
		getline(cin,n_lname);
		cout << "Input the new Street and Street number: #";
		getline(cin,n_street);
		cout << "Input the new Baranggay: ";
		getline(cin,n_baranggay);
		cout << "Input the new City/Town and Province: ";
		getline(cin,n_province);
		cout << "Input the new Country: ";
		getline(cin,n_country);
		cout << "Input the new Contact number: ";
		getline(cin,n_cnum);
		opt_replace=10;
	}
	else{
		verify_e=2;
	}
	n_inputs_upcaps();
}
void under_space(){
	replace( fname.begin(), fname.end(), '_', ' ');
	replace( lname.begin(), lname.end(), '_', ' ');
	replace( baranggay.begin(), baranggay.end(), '_', ' ');
	replace( street.begin(), street.end(), '_', ' ');
	replace( province.begin(), province.end(), '_', ' ');
	replace( country.begin(), country.end(), '_', ' ');
	replace( cnum.begin(), cnum.end(), '_', ' ');	
}
void n_inputs_upcaps(){
	replace( n_fname.begin(), n_fname.end(), ' ', '_');
	transform( n_fname.begin(), n_fname.end(), n_fname.begin(), ::toupper);
	replace( n_lname.begin(), n_lname.end(), ' ', '_');
	transform( n_lname.begin(), n_lname.end(), n_lname.begin(), ::toupper);
	replace( n_street.begin(), n_street.end(), ' ', '_');
	transform( n_street.begin(), n_street.end(), n_street.begin(), ::toupper);
	replace( n_baranggay.begin(), n_baranggay.end(), ' ', '_');
	transform( n_baranggay.begin(), n_baranggay.end(), n_baranggay.begin(), ::toupper);
	replace( n_province.begin(), n_province.end(), ' ', '_');
	transform( n_province.begin(), n_province.end(), n_province.begin(), ::toupper);
	replace( n_country.begin(), n_country.end(), ' ', '_');
	transform( n_country.begin(), n_country.end(), n_country.begin(), ::toupper);
	replace( n_cnum.begin(), n_cnum.end(), ' ', '_');
	transform( n_cnum.begin(), n_cnum.end(), n_cnum.begin(), ::toupper);
}	
void ndelete_clear()
{	
	if(ndelete==0||ndelete>c_count)
	{
	verify_e=1;
	}
	else if (ndelete<=100&&ndelete!=0)
	{
	ndelete_f=ndelete;
	}
	else{
	verify_e=1;}
	
}
void edit_contact() {
		verify_e=0;
		system("title Edit Contact");
		cout << "Entering a non-existent number will turn back to Menu.\n\n";
		ifstream show("database.txt", ios::app);
		display_contacts();
		cout << "\nEnter the number of the contact you want to replace: ";
		cin >> ndelete;
		cin.clear();
		ndelete_clear();
		if (verify_e==1){
			show.close(),
			verify_e=0,
			main();}
		system("cls");
		n_replace();
		verify_edit();
		if (verify_e==1||verify_e==2){
			show.close();
			verify_e=0;
			main();}
		string sure;
		cout << "\nAre you sure? (Yes or No): ";
		getline(cin,sure);
		transform(sure.begin(), sure.end(), sure.begin(), ::toupper);
		if (sure=="YES"){
		while (show >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
			if (ndelete == new_c){
			ofstream change("database1.txt", ios::app);
			replace_id();
			change << fname << ' ' << cnum << ' ' << street << ' ' << baranggay << ' ' << province << ' ' << country << ' ' << lname << ' ' << new_c << ' ' << state << endl;
			}
			if (ndelete != new_c){
			ofstream change("database1.txt", ios::app);	
			change << fname << ' ' << cnum << ' ' << street << ' ' << baranggay << ' ' << province << ' ' << country << ' ' << lname << ' ' << new_c << ' ' << state << endl;
			change.close();
			}
		}
		show.close();
		remove("database.txt");
    	rename("database1.txt","database.txt");
   		system("cls");
   		system("title Succesfully Replaced!");
   		cout << "The contact you selected is succesfully replaced.\nPress any key to return to Menu.\n";
   		system("pause>null");
		main();	
		}
		else if (sure=="NO"){
		show.close();	
		system("cls");
		system("title Contact not replaced");
		cout << "Operation cancelled, the selected contact is not replaced.\n\nPress any key to go back in Editting Contacts.";
		system("pause>null");
		system("cls");
		edit_contact();
		}
		else{
			show.close();
			main();
		}
}
void ext() {
	system("title Exit?");
	cout << "Are you sure you want to exit? (If you are sure enter Yes. If not, enter anything): ";
					cin >> quit;
					transform( quit.begin(), quit.end(), quit.begin(), ::toupper);
					if (quit=="YES")
					{
						system("title Saved succesfully!");
						system("cls");
						usleep(300000);
						cout << "Your informations are saved! Press any key to finally exit.\n";
						system("pause>null");
						hideit();
					}
					else 
					{
						main();
					}
}
void count() {	
	c_count=0;
	ifstream contacts("database.txt");
	while (contacts >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state)
	{
	if (state == "1")
	c_count+=1;
	}	
}
void display_contacts() {
	column();
	ifstream contacts("database.txt");
	cout << "#. Name " << setw(33) << "- Address " << setw(72) << "- Contact Number\n\n";
	if (spaces<=30&&spaces>0){
	while (contacts >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
		if (state == "1"){
		under_space();
		column();
		cout << new_c << ". " << fname << ' ' << lname << setw(spaces) << " - #" << street << ' ' << baranggay << ' ' << province << ' ' << country << setw(spaces1) << " - " << cnum << endl;
	}
	}
	}
	contacts.close();
}
void delete_specific()
	{	display_contacts();
		ifstream show("database.txt");
		cout << "\nEnter the number of the contact you want to delete: ";
		cin >> ndelete;
		cin.clear();
		{if(ndelete==0||ndelete>c_count)	{
			show.close();
			main();	}
		else if (ndelete<=100&&ndelete!=0)	{
		ndelete_f=ndelete;	}
		else	{
		show.close();	
		main();}}
	//	ndelete_clear();
		string sure;
		cout << "\nAre you sure? (Yes or No): ";
		cin.ignore();
		getline(cin,sure);
		transform(sure.begin(), sure.end(), sure.begin(), ::toupper);
		if (sure=="YES"){
		while (show >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
			if (ndelete_f != new_c){
			ofstream change("database1.txt", ios::app);	
			state='1';
			if (new_c > ndelete_f){
				new_c-=1;
			}
			change << fname << ' ' << cnum << ' ' << street << ' ' << baranggay << ' ' << province << ' ' << country << ' ' << lname << ' ' << new_c << ' ' << state << endl;
			change.close();
			}
		}
		show.close();
		remove("database.txt");
   		rename("database1.txt","database.txt");
   		system("cls");
   		art_delete();
   		system("title Succesfully Removed!");
   		cout << "The contact you selected is succesfully removed.\nPress any key to return to Menu.\n";
   		system("pause>null");
		main();	
		}
		else if (sure=="NO"){
		show.close();	
		system("cls");
		system("title Contact not deleted");
		cout << "Operation cancelled, the selected contact is not deleted.\n\nPress any key to go back in Deleting Contacts.";
		system("pause>null");
		system("cls");
		delete_contacts();
		}
		else{
			show.close();
			main();
		}
	}

void delete_all() {
	system("title Delete contacts");
    string decision, prompt_1;
    cout << "Are you sure you want to delete all contacts?\n(if you want to delete entry input Yes, else enter anything to go back to Menu) : ";
	cin.sync();
    getline(cin,decision);
    transform( decision.begin(), decision.end(), decision.begin(), ::toupper);
    if (decision == "YES"){
    system("cls");
    system("title Warning!");
    do {
	cout << "Warning!\nAll the informations will be permanently deleted! \nDo you want to proceed? (Yes or No) : ";
    getline(cin,prompt_1);
    transform( prompt_1.begin(), prompt_1.end(), prompt_1.begin(), ::toupper);
    if (prompt_1=="YES")
    {
    remove("database.txt");
   	system("cls");
   	art_delete();
    cout << "Contacts successfully deleted." << endl;
    system("pause>null");
    main();
    }
	else if (prompt_1=="NO")
	{
		system("title Deleting cancelled");
		system("cls");
		cout << "The informations are not deleted.\n" << "Press any key to return to Nenu.\n";
		system("pause>null");
		main(); 
	}
	else
	{
		system("cls");
		cout << "Please input (Yes or no).\n";
	}
	} while (prompt_1!="YES"||prompt_1!="NO");
	} 
    else{
         main();
         }
}
void color() {
	{
	system("title Color Settings");
			cout << "Input anything if you want to reset to default and go back to Menu.\n\nBrightness setting will not work if you will use color schemes.\n\nPick Color Scheme\n1. Cookies and Cream\n2. Banana\n3. Stars\n4. Watermelon\n5. Blue Screen of Death\n\nEnter the number your option: ";
			cin >> color_opt;
			if (color_opt=="1")
			{
				system("color F0");	
			}
			else if (color_opt=="2")
			{
				system("color E0");
			}
			else if (color_opt=="3")
			{
				system("color 0E");
			}
			else if (color_opt=="4")
			{
				system("color 4A");
			}
			else if (color_opt=="5")
			{
				system("color 1F");
			}
			else
			{
				system("color 07");
				brightness=2;
				main();
			}
			if (color_opt=="5","4","3","2","1"){
			brightness=0;}
			main();
}
}
void add_inputs_upcaps(){
	replace( fname.begin(), fname.end(), ' ', '_');
	transform( fname.begin(), fname.end(), fname.begin(), ::toupper);
	replace( lname.begin(), lname.end(), ' ', '_');
	transform( lname.begin(), lname.end(), lname.begin(), ::toupper);
	replace( street.begin(), street.end(), ' ', '_');
	transform( street.begin(), street.end(), street.begin(), ::toupper);
	replace( baranggay.begin(), baranggay.end(), ' ', '_');
	transform( baranggay.begin(), baranggay.end(), baranggay.begin(), ::toupper);
	replace( province.begin(), province.end(), ' ', '_');
	transform( province.begin(), province.end(), province.begin(), ::toupper);
	replace( country.begin(), country.end(), ' ', '_');
	transform( country.begin(), country.end(), country.begin(), ::toupper);
	replace( cnum.begin(), cnum.end(), ' ', '_');
	transform( cnum.begin(), cnum.end(), cnum.begin(), ::toupper);
}
void add_contact() {
	{
	system("title Add Contact");
	ofstream add_contact("database.txt", ios::app);
	system("cls");
	cout << "Please use SPACE for separation.\n\nEnter First name: ";
	cin.ignore();
	getline(cin,fname);
	cout << "Enter Last name: ";
	getline(cin,lname);
	cout << "\nFor Address.\nEnter Street number and Street: #";
	getline(cin,street);
	cout << "Enter Baranggay: ";
	getline(cin,baranggay);
	cout << "Enter City/Town and Province: ";
	getline(cin,province);
	cout << "Enter Country: ";
	getline(cin,country);
	cout << "\nEnter Contact number: ";
	getline(cin,cnum);
	verify_add();
	countfadd();
	if (verify_a==1){
		add_contact.close();
		verify_a=0;
		main();}
	string cont;
	cout << "\nAre you sure you want to add this contact? \nInput Yes if you want to continue, else type anything to go back to Menu: ";
	getline(cin,cont);
	transform(cont.begin(), cont.end(), cont.begin(), ::toupper);
	if (cont == "YES"){
		system("cls");
		usleep(300000);
		system("title Adding Contact.");
		usleep(300000);
		system("title Adding Contact..");
		usleep(300000);
		system("title Adding Contact...");
		usleep(300000);
		cout << "Contact added!\n";
		system("title Contact succesfully added!");		
	cout << "Press any key to return to menu.\n";	
	system("pause>null");
	add_inputs_upcaps();
	state = '1';
	add_contact << fname << ' ' << cnum << ' ' << street << ' ' << baranggay << ' ' << province << ' ' << country << ' ' << lname << ' ' << new_c << ' ' << state << endl;
	add_contact.close();	}
	else if (cont == "NO"){
		system("cls");
		system("title Not Added!");
		cout << "Contact not added! \n\nPress any key to return to Menu.";
		system("pause>null");
		add_contact.close();
	}
	else{
		add_contact.close();
	}
	main();
}
}
void c_subsearch(){
	{
		int id=0;
		ifstream search("database.txt");
			system("title Search Contacts by Contact number");
			cout << "Enter Contact Number: ";
			cin.sync();
			getline(cin,s_cnum);
			system("cls");
			{
				system("title Searching.");
				usleep(300000);
				system("title Searching..");
				usleep(300000);
				system("title Searching...");
				usleep(300000);
				system("title Searching done");
			}
			while (search >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
				if (cnum == s_cnum){
					under_space();
					cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
					cout << "Contact Number: " << cnum << endl << endl;
					cout << "Press any key for more results of '" << s_cnum << "'.\n";
					system("pause>null");
					system("cls");
					id=1;
				}
				}
			if (id==0){
				id=0,
				cout << "No Results.\n";
			}
			else if (id!=0){
				cout << "No more results.\n";
			}
				cout << "Press any key to return to Menu.";
				system("pause>null");
				search.close();
				main();
		}
		
}
void a_subsearch(){
{
	int id=0;
	ifstream search("database.txt");
		system("title Search Contacts by Address");
		cout << "Please use SPACE for separation to achieve better results.\n\nEnter Street number and Street: #";
		cin.sync();
		getline(cin,s_street);
		replace( s_street.begin(), s_street.end(), ' ', '_');
		transform( s_street.begin(), s_street.end(), s_street.begin(), ::toupper);
		cout << "Enter Baranggay: ";
		getline(cin,s_baranggay);
		replace( s_baranggay.begin(), s_baranggay.end(), ' ', '_');
		transform( s_baranggay.begin(), s_baranggay.end(), s_baranggay.begin(), ::toupper);
		cout << "Enter City/town and Province: ";
		getline(cin,s_province);
		replace( s_province.begin(), s_province.end(), ' ', '_');
		transform( s_province.begin(), s_province.end(), s_province.begin(), ::toupper);
		cout << "Enter Country: ";
		getline(cin,s_country);
		replace( s_country.begin(), s_country.end(), ' ', '_');
		transform( s_country.begin(), s_country.end(), s_country.begin(), ::toupper);
		system("cls");
		string include_c;
		cout << "Include country in search? If you want input Yes, else input no or anything : ";
		getline(cin,include_c);
		transform( include_c.begin(), include_c.end(), include_c.begin(), ::toupper);
		{
			system("cls");
			system("title Searching.");
			usleep(300000);
			system("title Searching..");
			usleep(300000);
			system("title Searching...");
			usleep(300000);
			system("title Searching done");
		}
		if (include_c=="YES"){
		while (search >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
			if (street == s_street&&baranggay == s_baranggay&&province == s_province&&country == s_country){
				under_space();
				cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
				cout << "Contact Number: " << cnum << endl << endl;
				replace( s_country.begin(), s_country.end(), '_', ' ');
				replace( s_street.begin(), s_street.end(), '_', ' ');
				replace( s_province.begin(), s_province.end(), '_', ' ');
				replace( s_baranggay.begin(), s_baranggay.end(), '_', ' ');
				cout << "Press any key to see more results for '#" << s_street << "' , '" << s_baranggay << "' , '" << s_province << "' and '" << s_country << "'.";
				replace( s_country.begin(), s_country.end(), ' ', '_');
				replace( s_street.begin(), s_street.end(), ' ', '_');
				replace( s_province.begin(), s_province.end(), ' ', '_');
				replace( s_baranggay.begin(), s_baranggay.end(), ' ', '_');
				system("pause>null");
				system("cls");
				id=1;
			}
			else if (street == s_street||baranggay == s_baranggay||province == s_province||country == s_country){		
				under_space();
				cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
				cout << "Contact Number: " << cnum << endl << endl;
				id=2;
			}
			}
			}
			else {
		while (search >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
			if (street == s_street&&baranggay == s_baranggay&&province == s_province){
				under_space();
				cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
				cout << "Contact Number: " << cnum << endl << endl;
				replace( s_country.begin(), s_country.end(), '_', ' ');
				replace( s_street.begin(), s_street.end(), '_', ' ');
				replace( s_province.begin(), s_province.end(), '_', ' ');
				replace( s_baranggay.begin(), s_baranggay.end(), '_', ' ');
				cout << "Press any key to see more results for '#" << s_street << "' , '" << s_baranggay << "' , '" << s_province << "' and '" << s_country << "'.";
				replace( s_country.begin(), s_country.end(), ' ', '_');
				replace( s_street.begin(), s_street.end(), ' ', '_');
				replace( s_province.begin(), s_province.end(), ' ', '_');
				replace( s_baranggay.begin(), s_baranggay.end(), ' ', '_');
				system("pause>null");
				system("cls");
				id=1;
			}
			else if (street == s_street||baranggay == s_baranggay||province == s_province){		
				under_space();
				cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
				cout << "Contact Number: " << cnum << endl << endl;
				id=2;
			}
			}
			}
		if (id==0){
			id=0,
			cout << "No Results.\n";
		}
		else if (id!=0){
			cout << "No more results.\n";
		}
			cout << "Press any key to return to Menu.";
			system("pause>null");
			search.close();
			main();
		}
}
void n_subsearch(){
	{
		int id=0;
		ifstream search("database.txt");
			system("title Search Contacts by Name");
			cout << "Enter First name: ";
			cin.sync();
			getline(cin,s_fname);
			replace( s_fname.begin(), s_fname.end(), ' ', '_');
			transform( s_fname.begin(), s_fname.end(), s_fname.begin(), ::toupper);
			cout << "Enter Last name: ";
			getline(cin,s_lname);
			replace( s_lname.begin(), s_lname.end(), ' ', '_');
			transform( s_lname.begin(), s_lname.end(), s_lname.begin(), ::toupper);
			system("cls");
			{
				system("title Searching.");
				usleep(300000);
				system("title Searching..");
				usleep(300000);
				system("title Searching...");
				usleep(300000);
				system("title Searching done");
			}
			while (search >> fname >> cnum >> street >> baranggay >> province >> country >> lname >> new_c >> state){
				if (lname == s_lname&&s_fname == fname){
					under_space();
					cout << "Name: " << fname << ' ' << lname << endl << "Address: #" << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
					cout << "Contact Number: " << cnum << endl << endl;
					replace( s_fname.begin(), s_fname.end(), '_', ' ');
					replace( s_lname.begin(), s_lname.end(), '_', ' ');
					cout << "Press any key to see more results for '" << s_fname << "' and '" << s_lname << "'.";
					replace( s_fname.begin(), s_fname.end(), ' ', '_');
					replace( s_lname.begin(), s_lname.end(), ' ', '-');
					system("pause>null");
					system("cls");
					id=1;
				}
				else if (fname==s_fname||lname==s_lname){		
					under_space();
					cout << "Name: " << fname << ' ' << lname << endl << "Address: " << street << ' ' << baranggay << ' ' << province << ' ' << country << endl; 
					cout << "Contact Number: " << cnum << endl << endl;
					id=2;
				}
				}
			if (id==0){
				id=0,
				cout << "No Results.\n";
			}
			else if (id!=0){
				cout << "No more results.\n";
			}
				cout << "Press any key to return to Menu.";
				system("pause>null");
				search.close();
				main();
		}
}
void delete_contacts()
{
	system("title Delete Contacts");
	cout << "Input anything if you want to back to Menu.\n\nPlease select an option.\n\n1. Delete by selecting specific contact\n2. Delete all contacts\n\nEnter the number of your option: ";
	string opt_d;
	cin.sync();
	getline(cin,opt_d);
	system("cls");
	if (opt_d=="1")
	{
		delete_specific();
	}
	else if (opt_d=="2")
	{
		delete_all();
	}
	else
	{
		main();
	}
}
void search() {
	system("title Search Contact");
	system("cls");
	char opt;
	cout << "Input anything if you want to return to menu.\n" << "\nPlease select category to search the contact by: \n" << "1. Name\n" <<  "2. Contact number\n"; 
	cout << "3. Address\n\nPlease input the number of your option: ";
	cin.ignore();
	cin >> opt;
	system("cls");
	switch (opt)
	{
		case '1':
			n_subsearch();
			break;
		case '2':
			c_subsearch();
			break;
		case '3':
			a_subsearch();
			break;
		default: 
			main();
			break;
	}
}
text_anim1(char a[200]){
	int i;
	double k;
	for(i-0;a[i]!='\0';++i)
	{
		for(k=0;k<200000;++k);
		cout << a[i];
	}
}
void boot_screen(){
	text_anim1
	(
	"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n			 	||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
	"		     		||         |  |||||  |         |    ||||  |        |       |||         |         |  ||||||  ||\n"
	"		     		||         |  |||||  |         |    ||||  |        |        ||         |         |  |||||  |||\n"
	"			 	||  |||||  |  |||||  |  |||||  |  |  |||  |  |||||||  |||||  |  |||||  |         |  ||||  ||||\n"
	"			 	||  |||||  |  |||||  |  |||||  |  |  |||  |  |||||||  |||||  |  || ||  |  |||||  |  |||  |||||\n"
	"			 	||         |         |  |||||  |  ||  ||  |        |        ||  || ||  |  || ||  |      ||||||\n"	
	"			 	||         |         |  |||||  |  ||  ||  |        |        ||  |||||  |  || ||  |      ||||||\n"
	"			 	||  ||||||||  |||||  |  |||||  |  |||  |  |  |||||||  |||||  |  |||||  |  |||||  |  |||  |||||\n"
	"		 	 	||  ||||||||  |||||  |  |||||  |  |||  |  |  |||||||  |||||  |         |  |||||  |  ||||  ||||\n"
	"			 	||  ||||||||  |||||  |         |  ||||    |        |        ||         |         |  |||||  |||\n"
	"			 	||  ||||||||  |||||  |         |  ||||    |        |       |||         |         |  ||||||  ||\n"
	"			 	||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
	);
	cout << "\n					 			  Press any key to start";
	boot_s=0;
	system("pause>null");
}
void hideit(){
	int attr = GetFileAttributes("database.txt");
	if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
   	SetFileAttributes("database.txt", attr | FILE_ATTRIBUTE_HIDDEN);}
}
void verify_add(){
	if (fname==""||lname==""||cnum==""||street==""||baranggay==""||province==""||country=="")
	{
		system("cls");
		cout << "Some fields are empty.\n\nPress any key to return to menu.";
		system("title Not added");
		system("pause>null");
		verify_a=1;
	}
}
void verify_edit(){
	if ((opt_n=="1"&&opt_rep=="1")&&(n_fname=="")){
		verify_e=1;
	}
	else if ((opt_n=="1"&&opt_rep=="3")&&(n_cnum=="")){
		verify_e=1;
		}
	else if ((opt_n=="5"&&opt_rep=="2")&&(n_street==""||n_baranggay==""||n_province==""||n_country=="")){
		verify_e=1;
	}	
	else if ((opt_n=="4"&&opt_rep=="2")&&(n_country=="")){
		verify_e=1;
	}
	else if ((opt_n=="6"&&opt_rep=="2")&&(n_province=="")){
		verify_e=1;
	}
	else if ((opt_n=="2"&&opt_rep=="2")&&(n_baranggay=="")){
		verify_e=1;
	}
	else if ((opt_n=="1"&&opt_rep=="2")&&(n_street=="")){
		verify_e=1;
	}
	else if ((opt_n=="3"&&opt_rep=="1")&&(n_lname==""||n_fname=="")){
		verify_e=1;		
	}
	else if ((opt_n=="2"&&opt_rep=="1")&&(n_lname=="")){
		verify_e=1;
	}
	else if (opt_rep=="4"&&(n_fname==""||n_lname==""||n_cnum==""||n_street==""||n_baranggay==""||n_province==""||n_country=="")){
		verify_e=1;	
	}
	else{
	}
	if (verify_e==1){
		system("cls");
		cout << "Some fields are empty.\n\nPress any key to return to menu." << opt_n << opt_rep;
		system("title Not Saved");
		system("pause>null");}
}
