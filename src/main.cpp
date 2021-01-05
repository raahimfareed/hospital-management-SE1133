/**
 * @file main.cpp
 * @author Raahim Fareed - BSE203039 (bse203039@cust.pk)
 * @brief This program is a hospital management system and will store patient and doctor information and provide means of communication
 * @version 1.0
 * @date 2021-01-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
  * HEADERS
  * #include <iostream> - Used for basic input output operations on stream
  * #include <fstream> - Used for file streams
  * #include <limits> - Has numeric_limits which is being used for cin.ignore()
  */
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdlib.h>
#include <ctime>

/**
 * Namespaces
 * std - Standard
 */
using namespace std;

/**
 * Header
 *
 * Displays the header of the program
 *
 * @returns void
 */
void Header();

/**
 * InputPlaceholder
 *
 * Displays the input text i.e the username and the breadcrumb
 *
 * @param string username - Takes the username of the user otherwise defaults as guest
 * @param string menu_location - Takes the location of the menu for the breadcrumb
 *
 * @returns void
 */
void InputPlaceholder(const string &username, const string &menu_location, const string &submenu_location);

/**
 * MainMenu
 *
 * Displays the main menu options
 * Calls InputPlaceHolder as well
 * @param string username - Takes the username of the user otherwise defaults as guest
 * @param string &menu_location - Takes the location of the menu for the breadcrumb and
 * changes it to main-menu
 * @returns void
 */
void MainMenu(const string &username, string &menu_location, string &submenu_location);

/**
 * LoginMenu
 *
 * Displays the login menu options
 * Calls InputPlaceHolder as well
 * @param string username - Takes the username of the user otherwise defaults as guest
 * @param string &menu_location - Takes the location of the menu for the breadcrumb and
 * changes it to main-menu
 * @returns void
 */
void LoginMenu(const string &username, string &menu_location, string &submenu_location);

/**
 * SignupMenu
 *
 * Displays the signup menu options
 * Calls InputPlaceHolder as well
 * @param string username - Takes the username of the user otherwise defaults as guest
 * @param string &menu_location - Takes the location of the menu for the breadcrumb and
 * changes it to main-menu
 * @returns void
 */
void SignupMenu(const string &username, string &menu_location, string &submenu_location);

void AdminMainMenu(const string &username, string &menu_location, string &submenu_location);

void AdminSubmenu(const string &username, string &menu_location, string &submenu_location, string submenu_type);

void Signup(string type);
bool Login(string type);
bool Logout();

string Error(int error_code = 0);

void PrecedenceSet(const char &type = 'g');

void PatientMenu(const string &username, string &menu_location, string &submenu_location);
void Patient(const string &username, string &menu_location, string &submenu_location);
void GetUserMessages(const string &username);
void GetDoctorsAvailable();
void GetUserInformation(const string &username);
void ManagePatientsMenu(const string &username, string &menu_location, string &submenu_location);
void ManagePatients(const string &username, string &menu_location, string &submenu_location);
void GetTotalPendingAppointments();
void MessageUser();
void GetAllPatients();
void Admin(string &menu_location, string &submenu_location);
void AdminGetUserMessages();
void ClearPatientsDb();
void GetAllDoctors();
void ClearDoctorsDb();
void AdminGetAppointments();
void GetAllAdmins();
void FormatProgram();
void GetLog();
char *GetCurrentTime();
void CreateLog(const string &user, char *time, char type);
string Credits();
string Help();
void RemoveAppointment();

// Structs
struct PatientAppointment
{
	string username;
	string query;
};

struct PatientMessage
{
	string doctor;
	string patient;
	string message;
};

// Global Constants
// No constants yet
int const c_total_patient_message_limit = 1000;
int const c_total_patient_appointment_limit = 1000;

// Global Variables
bool g_logged_in = false;
string g_username;

/**
 * 0 - Guest
 * 2 - Patient
 * 4 - Doctor
 * 8 - Management
 */
int g_user_precedence = 0;

int g_total_appointments = 0;
PatientAppointment Appointments[c_total_patient_appointment_limit];
int g_total_messages = 0;
PatientMessage PatientMessages[c_total_patient_message_limit];

int main()
{
	char main_loop = 'Y';
	string menu_option;
	string menu_location = "main-menu";
	string submenu_location = "~";

	do
	{
		MainMenu(g_username, menu_location, submenu_location);
		cin >> menu_option;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (toupper(menu_option[0]))
		{
		case 'L':
			if (!g_logged_in)
			{
				bool loop;

				do
				{
					LoginMenu(g_username, menu_location, submenu_location);
					cin >> menu_option;
					loop = false;
					switch (toupper(menu_option[0]))
					{
					case 'P':
						Login("p");
						break;
					case 'D':
						Login("d");
						break;
					case 'M':
						Login("m");
						break;
					case 'H':
						loop = true;
						break;
					default:
						if (toupper(menu_option[0]) == 'E')
						{
							break;
						}
						loop = true;
						cout << Error(1) + '\n' // Invalid option
							 << "Press [Enter/Return] Key to continue\n";
						cin.get();
					}
				} while (loop);
			}
			else
			{
				if (Logout())
				{
					cout << "\u001b[1;32mLogged Out!\u001b[0m\n"
						 << "Press [Enter/Return] Key to return to main menu\n";
					cin.get();
				}
				else
				{
					cout << Error(6) + '\n' // No User logged in
						 << "Press [Enter/Return] Key to return to main menu\n";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin.get();
				}
			}

			break;
		case 'S':
			if (!g_logged_in)
			{
				bool loop;

				do
				{
					SignupMenu(g_username, menu_location, submenu_location);
					cin >> menu_option;
					loop = false;
					switch (toupper(menu_option[0]))
					{
					case 'P':
						Signup("p");
						break;
					case 'D':
						Signup("d");
						break;
					case 'M':
						Signup("m");
						break;
					case 'H':
						loop = true;
						break;
					default:
						if (toupper(menu_option[0]) == 'E')
							break;

						loop = true;
						cout << Error(1) + '\n' // Invalid option
							 << "Press [Enter/Return] Key to return to main menu\n";
						cin.get();
					}
				} while (loop);
			}
			else
			{
				cout << Error(1) + '\n' // Invalid Option
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}
			break;
		case 'P':
			if (g_user_precedence < 2)
			{
				cout << Error(8) + '\n' // User needs to login
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}
			else if (g_user_precedence == 4)
			{
				ManagePatients(g_username, menu_location, submenu_location);
			}
			break;
		case 'D':
			if (g_user_precedence != 4)
			{
				cout << Error(10) + '\n' // [Restricted access] Only doctors can access this menu
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}

			break;
		case 'M':
			if (g_user_precedence >= 8 && g_logged_in)
			{
				Admin(menu_location, submenu_location);
			}
			else
			{
				cout << Error(9) + '\n' // [Restricted access]
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}

			break;
		case 'H':
			cout << Help()
				 << "Press [Enter/Return] Key to return to main menu\n";
			cin.get();
			break;
		case 'C':
			cout << Credits();
			cin.get();
			break;
		case 'E':
			main_loop = 'N';
			break;
		case 'A':
			if (g_user_precedence > 0)
			{
				if (g_user_precedence == 2)
				{
					Patient(g_username, menu_location, submenu_location);
				}
				break;
			}
		default:
			cout << Error(1) + '\n' // Invalid option
				 << "Press [Enter/Return] Key to return to main menu\n";
			cin.get();
		}

	} while (toupper(main_loop) == 'Y');

	return 0;
}

void Header()
{
	cout << "=== \u001b[1;7;32mHospital Management System\u001b[0m ===\n";
}

void InputPlaceholder(const string &username, const string &menu_location, const string &submenu_location)
{
	if (!g_logged_in)
		cout << "\u001b[1;31m[Guest@\u001b[0m";
	else
		cout << "\u001b[1;31m[" + username + "@\u001b[0m";

	cout << "\u001b[1;31m" + menu_location + " " + submenu_location + "]: \u001b[0m";
}

void MainMenu(const string &username, string &menu_location, string &submenu_location)
{
	menu_location = "main-menu";
	system("cls");

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mMain Menu\u001b[0m\n"
		 << "----------------------------------\n";

	if (!g_logged_in)
	{
		cout << "\u001b[1;33m[L]\u001b[0m Log in\n"
			 << "\u001b[1;33m[S]\u001b[0m Sign up\n";
	}

	if (g_user_precedence == 2)
	{
		cout << "\u001b[1;33m[A]\u001b[0m Account\n";
	}

	if (g_user_precedence > 3 && g_user_precedence < 8)
	{
		cout << "\u001b[1;33m[P]\u001b[0m Patients\n";
	}

	if (g_user_precedence > 7)
	{
		cout << "\u001b[1;33m[M]\u001b[0m Management\n";
	}

	cout << "\u001b[1;33m[H]\u001b[0m Help\n"
		 << "\u001b[1;33m[C]\u001b[0m Credits\n";

	if (g_logged_in)
	{
		cout << "\u001b[1;33m[L]\u001b[0m Log Out\n";
	}

	cout << "\u001b[1;33m[E]\u001b[0m Exit\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void LoginMenu(const string &username, string &menu_location, string &submenu_location)
{
	system("cls");
	menu_location = "login-menu";

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mLogin Menu\u001b[0m\n"
		 << "----------------------------------\n"
		 << "\u001b[1;33m[P]\u001b[0m Patient Login\n"
		 << "\u001b[1;33m[D]\u001b[0m Doctor Login\n"
		 << "\u001b[1;33m[M]\u001b[0m Management Login\n"
		 << "\u001b[1;33m[H]\u001b[0m Help\n"
		 << "\u001b[1;33m[E]\u001b[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void SignupMenu(const string &username, string &menu_location, string &submenu_location)
{
	system("cls");
	menu_location = "signup-menu";

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mSignup Menu\u001b[0m\n"
		 << "----------------------------------\n"
		 << "\u001b[1;33m[P]\u001b[0m Patient Signup\n"
		 << "\u001b[1;33m[D]\u001b[0m Doctor Signup\n"
		 << "\u001b[1;33m[M]\u001b[0m Management Signup\n"
		 << "\033[1;33m[H]\033[0m Help\n"
		 << "\033[1;33m[E]\033[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void AdminMainMenu(const string &username, string &menu_location, string &submenu_location)
{
	system("cls");
	menu_location = "admin-main-menu";
	submenu_location = "~";

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mAdmin Main Menu\u001b[0m\n"
		 << "----------------------------------\n"
		 << "\u001b[1;33m[P]\u001b[0m Patients\n"
		 << "\u001b[1;33m[D]\u001b[0m Doctors\n"
		 << "\u001b[1;33m[M]\u001b[0m Admins\n"
		 << "\033[1;33m[H]\033[0m Help\n"
		 << "\033[1;33m[E]\033[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void AdminSubmenu(const string &username, string &menu_location, string &submenu_location, string submenu_type)
{
	system("cls");
	menu_location = "admin-menu";
	int menu_level = submenu_type.length();

	Header();

	cout << "----------------------------------\n"
		 << "\u001b[1;36mAdmin Main Menu\u001b[0m\n"
		 << "----------------------------------\n";

	switch (menu_level)
	{
	case 1:
		switch (toupper(submenu_type[0]))
		{
		case 'P':
			submenu_location = "patients";
			cout << "\u001b[1;33m[P]\u001b[0m Show all Patients\n"
				 << "\u001b[1;33m[M]\u001b[0m Show all Messages\n"
				 << "\u001b[1;33m[A]\u001b[0m Show all Appointments\n"
				 << "\u001b[1;33m[R]\u001b[0m Delete Patients Database \u001b[1;31m[WARNING: IRREVERSIBLE]\u001b[0m\n";
			break;
		case 'D':
			submenu_location = "doctors";
			cout << "\u001b[1;33m[A]\u001b[0m Show all Doctors\n"
				 << "\u001b[1;33m[P]\u001b[0m Remove an appointment\n"
				 << "\u001b[1;33m[R]\u001b[0m Delete Doctors Database \u001b[1;31m[WARNING: IRREVERSIBLE]\u001b[0m\n";
			break;
		case 'M':
			submenu_location = "admins";
			cout << "\u001b[1;33m[A]\u001b[0m Show all Admins\n"
				 << "\u001b[1;33m[L]\u001b[0m Show Log\n"
				 << "\u001b[1;33m[X]\u001b[0m Format Program \u001b[1;31m[WARNING: ALL DATA WILL BE DELETED!!!]\u001b[0m\n";

			break;
		}
		break;

	case 2:
		break;
	}

	cout << "\033[1;33m[E]\033[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void Signup(string type)
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	bool user_exists = false;

	string username;
	string password;
	string user_data;
	string delimiter = ";";
	string path = type + "_accounts.db";

	ifstream users_file_i(path, ios::in);

	cout << "Please enter username: ";
	getline(cin, username);
	cout << "Please enter password: ";
	getline(cin, password);

	while (password.length() < 8)
	{
		cout << Error(7) + '\n'
			 << "Please enter your password again: ";
		getline(cin, password);
	}

	while (getline(users_file_i, user_data))
	{
		string username_data = user_data.substr(0, user_data.find(delimiter));
		// string password_data = user_data.erase(0, user_data.find(delimiter) + delimiter.length());

		// cout << username_data + '\n' + password_data << '\n';

		if (username == username_data)
		{
			user_exists = true;
			break;
		}
	}
	users_file_i.close();

	if (user_exists)
	{
		cout << "\u001b[1;31m" + username + " already exists!\u001b[0m\n";
	}
	else
	{
		ofstream users_file_o(path, ios::out | ios::app);
		users_file_o << username + string(";") + password + '\n';
		users_file_o.close();
		cout << "\u001b[1;32m" + username + " created!\u001b[0m\n";
	}

	cout << "Press [Enter/Return] Key to return to main menu\n";
	cin.get();
}

bool Login(string type)
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bool user_exists = false;
	string username;
	string password;
	string user_data;
	string delimiter = ";";
	// "%appdata%\MyFolder\test.txt"
	// string path = "C:\\HospitalManagementSystem\\db\\" + type + string("_accounts.db");
	string path = type + "_accounts.db";

	ifstream users_file_i(path);

	cout << "Please enter username: ";
	getline(cin, username);
	cout << "Please enter password: ";
	getline(cin, password);

	string username_data;
	string password_data;
	while (getline(users_file_i, user_data))
	{
		username_data = user_data.substr(0, user_data.find(delimiter));
		password_data = user_data.erase(0, user_data.find(delimiter) + delimiter.length());

		// cout << username_data + '\n' + password_data << '\n';

		if (username == username_data)
		{
			user_exists = true;
			break;
		}
	}
	users_file_i.close();

	if (!user_exists)
	{
		cout << "\u001b[1;31m" + username + " doesn't exist!\u001b[0m\n"
			 << "Press [Enter/Return] Key to return to main menu\n";
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		return false;
	}
	else
	{
		if (password == password_data)
		{
			g_logged_in = true;
			g_username = username;
			cout << "\u001b[1;32mLogged In!\u001b[0m\n"
				 << "Press [Enter/Return] Key to return to main menu\n";
			PrecedenceSet(tolower(type[0]));
			CreateLog(username, GetCurrentTime(), type[0]);
			// cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			return true;
		}

		int password_tries = 1;
		do
		{
			cout << Error(4) + '\n' // Invalid Password
				 << "Please enter your password again: ";
			getline(cin, password);
			if (password == password_data)
			{
				g_logged_in = true;
				g_username = username;
				cout << "\u001b[1;32mLogged In!\u001b[0m\n"
					 << "Press [Enter/Return] Key to return to main menu\n";
				PrecedenceSet(tolower(type[0]));
				CreateLog(username, GetCurrentTime(), type[0]);
				// cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
				return true;
			}
			password_tries++;
		} while (password_tries <= 2);

		cout << Error(5) + '\n' // Exceeded password tries
			 << "Press [Enter/Return] Key to return to main menu\n";
		// cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		return false;
	}
}

bool Logout()
{
	g_username.clear();
	PrecedenceSet('g');
	if (g_logged_in)
	{
		g_logged_in = false;
		return true;
	}
	else
	{
		return false;
	}
}

string Error(int error_code)
{
	string errors[] = {
		"An error occurred!",								  // 0
		"Invalid Option!",									  // 1
		"User already exists!",								  // 2
		"User does not exist!",								  // 3
		"Incorrect Password!",								  // 4
		"Too many incorrect tries!",						  // 5
		"No user logged in!",								  // 6
		"Your password should be greater than 8 characters!", // 7
		"You need to be logged in!",						  // 8
		"Restricted Access",								  // 9
		"You need to be a doctor to access this",			  // 10
		"Your message cannot be empty!",					  // 11
	};

	return "\u001b[1;31m" + errors[error_code] + "\u001b[0m";
}

void PrecedenceSet(const char &type)
{
	switch (tolower(type))
	{
	case 'g':
		g_user_precedence = 0;
		break;
	case 'p':
		g_user_precedence = 2;
		break;
	case 'd':
		g_user_precedence = 4;
		break;
	case 'm':
		g_user_precedence = 8;
		break;
	default:
		g_user_precedence = 0;
		break;
	}
}

void PatientMenu(const string &username, string &menu_location, string &submenu_location)
{
	system("cls");
	menu_location = "account-menu";
	submenu_location = "~";

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mAccount\u001b[0m\n"
		 << "----------------------------------\n"
		 << "\u001b[1;33m[R]\u001b[0m Request Appointment\n"
		 << "\u001b[1;33m[D]\u001b[0m Doctors Information\n"
		 << "\u001b[1;33m[U]\u001b[0m User Information\n"
		 << "\u001b[1;33m[M]\u001b[0m Messages\n"
		 << "\033[1;33m[H]\033[0m Help\n"
		 << "\033[1;33m[E]\033[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void Patient(const string &username, string &menu_location, string &submenu_location)
{
	bool patient_loop = true;
	string patient_menu;
	do
	{
		PatientMenu(username, menu_location, submenu_location);
		cin >> patient_menu;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (toupper(patient_menu[0]))
		{
		case 'R':
			if (g_total_appointments <= 1000)
			{
				Appointments[g_total_appointments].username = username;
				cout << "Please enter your condition/query: ";
				getline(cin, Appointments[g_total_appointments].query);
				g_total_appointments++;
				cout << "Check your messages occasionally for a reply from the doctor\n"
					 << "Press [Enter/Return] Key to return back to menu\n";
				cin.get();
			}
			else
			{
				cout << Error(0) + '\n' // Error occurred
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}
			break;
		case 'D':
			GetDoctorsAvailable();
			cout << "Press [Enter/Return] Key to continue\n";
			cin.get();
			break;
		case 'U':
			GetUserInformation(username);
			cout << "Press [Enter/Return] Key to continue\n";
			cin.get();
			break;
		case 'M':
			GetUserMessages(username);
			cout << "Press [Enter/Return] Key to continue\n";
			cin.get();
			break;
		case 'E':
			patient_loop = false;
			break;
		default:
			break;
		}
	} while (patient_loop);
}

void GetUserMessages(const string &username)
{
	bool no_messages = true;
	cout << "Doctor name\t\tMessage\n";
	cout << "----------------------------------\n";
	for (int i = 0; i < g_total_messages; i++)
	{
		if (PatientMessages[i].patient == username)
		{
			no_messages = false;
			cout << PatientMessages[i].doctor + "\t\t" + PatientMessages[i].message + '\n';
		}
	}

	if (no_messages)
	{
		cout << "There are no messages available\n";
	}
}

void GetDoctorsAvailable()
{
	// bool no_doctors = true;
	string path = "d_accounts.db";
	string user_data;
	string delimiter = ";";
	int id = 1;

	ifstream doctors_file_i(path);
	string username_data;
	cout << "Id\t\tName\n";
	cout << "----------------------------------\n";
	while (getline(doctors_file_i, user_data))
	{
		username_data = user_data.substr(0, user_data.find(delimiter));
		cout << to_string(id) + "\t\t" + username_data + '\n';
		id++;
	}
	doctors_file_i.close();
}

void GetUserInformation(const string &username)
{
	int total_appointments = 0;
	int total_messages = 0;

	for (int i = 0; i < c_total_patient_appointment_limit; i++)
	{
		if (Appointments[i].username == username)
		{
			total_appointments++;
		}
	}

	for (int i = 0; i < c_total_patient_message_limit; i++)
	{
		if (PatientMessages[i].patient == username)
		{
			total_messages++;
		}
	}
	cout << "Your username: " + username + '\n'
		 << "Total Appointment Requests: " + to_string(total_appointments) + '\n'
		 << "Total Messages in Inbox: " + to_string(total_messages) + '\n';
}

void ManagePatientsMenu(const string &username, string &menu_location, string &submenu_location)
{
	system("cls");
	menu_location = "doctors-menu";
	submenu_location = "patients";

	Header();
	cout << "----------------------------------\n"
		 << "\u001b[1;36mPatients\u001b[0m\n"
		 << "----------------------------------\n"
		 << "\u001b[1;33m[A]\u001b[0m Pending Appointments\n"
		 << "\u001b[1;33m[R]\u001b[0m Remove Appointments\n"
		 << "\u001b[1;33m[M]\u001b[0m Send Message to Patient\n"
		 << "\u001b[1;33m[P]\u001b[0m Patient Info\n"
		 << "\033[1;33m[H]\033[0m Help\n"
		 << "\033[1;33m[E]\033[0m Previous Menu\n"
		 << "----------------------------------\n";

	InputPlaceholder(username, menu_location, submenu_location);
}

void ManagePatients(const string &username, string &menu_location, string &submenu_location)
{
	bool patient_loop = true;
	string patient_menu;
	do
	{
		ManagePatientsMenu(username, menu_location, submenu_location);
		cin >> patient_menu;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (toupper(patient_menu[0]))
		{
		case 'A':
			GetTotalPendingAppointments();
			cout << "Press [Enter/Return] Key to continue\n";
			cin.get();
			break;
		case 'P':
			GetAllPatients();
			cout << "Press [Enter/Return] Key to continue\n";
			cin.get();
			break;
		case 'M':
			MessageUser();
			break;
		case 'E':
			patient_loop = false;
			break;
		default:
			break;
		}
	} while (patient_loop);
}

void GetTotalPendingAppointments()
{
	cout << "----------------------------------\n"
		 << "Id\t\tPatient\t\tQuery\n"
		 << "----------------------------------\n";

	for (int i = 0; i < g_total_appointments; i++)
	{
		if (Appointments[i].username == "-") continue;
		cout << to_string(i) + "\t\t" + Appointments[i].username + "\t\t" + Appointments[i].query + '\n';
	}
}

void MessageUser()
{
	string message;
	string patient;
	string user_data;
	string delimiter = ";";
	string path = "p_accounts.db";
	string patient_check;
	bool patient_exists = false;
	bool first_try = true;

	do
	{
		if (!first_try)
		{
			cout << "Press [0] to exit to menu\n";
		}
		cout << "Please enter your patient's username: ";
		getline(cin, patient);
		if (patient == "0")
			return;
		ifstream users_file_i(path);
		while (getline(users_file_i, user_data))
		{
			patient_check = user_data.substr(0, user_data.find(delimiter));

			if (patient == patient_check)
			{
				patient_exists = true;
				break;
			}
		}
		users_file_i.close();

		if (!patient_exists)
		{
			first_try = false;
			cout << Error(3) + '\n'
				 << "Press [Enter/Return] Key to return to retry\n";
			cin.get();
		}
	} while (!patient_exists);
	first_try = true;
	do
	{
		if (!first_try)
		{
			cout << "Press [0] to exit to menu\n";
		}
		cout << "Please enter your message: ";
		getline(cin, message);
		if (message == "0")
			return;
		if (message.empty())
		{
			first_try = false;
			cout << Error(11) + '\n'
				 << "Press [Enter/Return] Key to return to retry\n";

			cin.get();
		}
	} while (message.empty());

	PatientMessages[g_total_messages].doctor = g_username;
	PatientMessages[g_total_messages].patient = patient;
	PatientMessages[g_total_messages].message = message;
	g_total_messages++;

	cout << "Message sent to " + patient + '\n'
		 << "Press [Enter/Return] Key to return to menu\n";
	cin.get();
}

void GetAllPatients()
{
	string user_data;
	string delimiter = ";";
	string patient_username;
	string path = "p_accounts.db";
	cout << "----------------------------------\n"
		 << "Patient Name\n"
		 << "----------------------------------\n";
	ifstream users_file_i(path);
	while (getline(users_file_i, user_data))
	{
		patient_username = user_data.substr(0, user_data.find(delimiter));
		cout << patient_username + '\n';
	}
	users_file_i.close();
}

void GetAllDoctors()
{
	string user_data;
	string delimiter = ";";
	string doctor_username;
	string path = "d_accounts.db";
	cout << "----------------------------------\n"
		 << "Doctor Name\n"
		 << "----------------------------------\n";
	ifstream users_file_i(path);
	while (getline(users_file_i, user_data))
	{
		doctor_username = user_data.substr(0, user_data.find(delimiter));
		cout << doctor_username + '\n';
	}
	users_file_i.close();
}

void GetAllAdmins()
{
	string user_data;
	string delimiter = ";";
	string admin_username;
	string path = "m_accounts.db";
	cout << "----------------------------------\n"
		 << "Admin Name\n"
		 << "----------------------------------\n";
	ifstream users_file_i(path);
	while (getline(users_file_i, user_data))
	{
		admin_username = user_data.substr(0, user_data.find(delimiter));
		cout << admin_username + '\n';
	}
	users_file_i.close();
}

void Admin(string &menu_location, string &submenu_location)
{
	menu_location = "admin-menu";
	bool loop;
	char menu_option;
	do
	{
		AdminMainMenu(g_username, menu_location, submenu_location);
		cin >> menu_option;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		loop = false;
		switch (toupper(menu_option))
		{
		case 'P':
			AdminSubmenu(g_username, menu_location, submenu_location, "p");
			cin >> menu_option;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (toupper(menu_option))
			{
				case 'P':
					GetAllPatients();
					cout << "Please press [Enter/Return] key to return to menu";
					cin.get();
					break;
				case 'R':
					ClearPatientsDb();
					break;
				case 'M':
					AdminGetUserMessages();
					break;
				case 'A':
					AdminGetAppointments();
					break;
				default:
					cout << Error(1) + '\n'
						 << "Please press [Enter/Return] key to return to menu";
			}
			break;
		case 'D':
			AdminSubmenu(g_username, menu_location, submenu_location, "d");
			cin >> menu_option;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (toupper(menu_option))
			{
				case 'A':
					GetAllDoctors();
					cout << "Please press [Enter/Return] key to return to menu";
					cin.get();
					break;
				case 'P':
					RemoveAppointment();
					break;
				case 'R':
					ClearDoctorsDb();
					break;
			}
			break;
		case 'M':
			AdminSubmenu(g_username, menu_location, submenu_location, "m");
			cin >> menu_option;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (toupper(menu_option))
			{
				case 'A':
					GetAllAdmins();
					cout << "Please press [Enter/Return] key to return to menu";
					cin.get();
					break;
				case 'L':
					GetLog();
					cout << "Please press [Enter/Return] key to return to menu";
					cin.get();
					break;
				case 'X':
					FormatProgram();
					break;
			}
			break;
		case 'H':
			loop = true;
			break;
		case 'E':
			loop = false;
			break;
		default:
			loop = true;
			cout << Error(1) + '\n' // Invalid option
				 << "Press [Enter/Return] Key to continue\n";
			cin.get();
		}
	} while (loop);
}

void ClearPatientsDb()
{
	char confirmation;
	cout << "Are you sure you want to delete all user data? (Y/N) ";
	cin >> confirmation;
	cin.ignore();
	if (toupper(confirmation) == 'Y')
	{
		ofstream file;
		file.open("p_accounts.db", ofstream::out | ofstream::trunc);
		file.close();
		cout << "All patient data has been deleted!\n";
	}
	else
	{
		cout << "Aborted operation\n";
		
	}
	

	cout << "Press [Enter/Return] Key to return to main menu\n";
	cin.get();
}

void ClearDoctorsDb()
{
	char confirmation;
	cout << "Are you sure you want to delete all doctor data? (Y/N) ";
	cin >> confirmation;
	cin.ignore();
	if (toupper(confirmation) == 'Y')
	{
		ofstream file;
		file.open("d_accounts.db", ofstream::out | ofstream::trunc);
		file.close();
		cout << "All doctor data has been deleted!\n";
	}
	else
	{
		cout << "Aborted operation\n";
	}

	cout << "Press [Enter/Return] Key to return to main menu\n";
	cin.get();
}

void AdminGetUserMessages()
{
	cout << "----------------------------------\n"
		 << "Id\t\tDoctor\t\tPatient\t\tMessage\n"
		 << "----------------------------------\n";
	for (int i = 0; i < g_total_messages; i++)
	{
		cout << i + 1 << "\t\t" + PatientMessages[i].doctor + "\t\t" + PatientMessages[i].patient + "\t\t" + PatientMessages[i].message + '\n';
	}
	cout << "----------------------------------\n";
	cout << "Press [Enter/Return] Key to return to menu\n";
	cin.get();
}

void AdminGetAppointments()
{
	cout << "----------------------------------\n"
		 << "Id\t\tPatient\t\tQuery\n"
		 << "----------------------------------\n";
	for (int i = 0; i < g_total_appointments; i++)
	{
		if (Appointments[i].username == "-") continue;
		cout << i + 1 << "\t\t" + Appointments[i].username + "\t\t" + Appointments[i].query + '\n';
	}
	cout << "----------------------------------\n";
	cout << "Press [Enter/Return] Key to return to menu\n";
	cin.get();
}

void FormatProgram()
{
	char confirmation;
	cout << "Are you sure you want to format the program? It is irreversible. All data and all accounts will be deleted forever! (Y/N) ";
	cin >> confirmation;
	cin.ignore();
	if (toupper(confirmation) == 'Y')
	{
		ofstream file;
		file.open("p_accounts.db", ofstream::out | ofstream::trunc);
		file.close();
		file.open("d_accounts.db", ofstream::out | ofstream::trunc);
		file.close();
		file.open("m_accounts.db", ofstream::out | ofstream::trunc);
		file.close();
		file.open("log.db", ofstream::out | ofstream::trunc);
		file.close();
		cout << "Program has been formatted!\n"
			 << "Program needs to be restarted to complete the process\n"
			 << "Press [Enter/Return] key to continue and close the program.\n";
		cin.get();
		exit(EXIT_SUCCESS);
	}
	else
	{
		cout << "Aborted operation\n"
			 << "Press [Enter/Return] Key to return to main menu\n";
		cin.get();
	}

}

void GetLog()
{
	string log_data;
	string delimiter = ";";
	string username;
	string type;
	string time;
	string path = "log.db";
	cout << "----------------------------------\n"
		 << "Type\t\tUser\t\tTime of Login\n"
		 << "----------------------------------\n";
	ifstream file_i(path);
	while (getline(file_i, log_data))
	{
		username = log_data.substr(0, log_data.find(delimiter));
		time = log_data.erase(0, log_data.find(delimiter) + delimiter.length());
		switch(toupper(username[0]))
		{
			case 'M':
				type = "Admin";
				break;
			case 'D':
				type = "Doctor";
				break;
			case 'P':
				type = "Patient";
				break;
		}		
		username = username.replace(0, 1, "");
		cout << type + "\t\t" + username + "\t\t" + time + '\n';
	}
	file_i.close();
}

char *GetCurrentTime()
{
	// current date/time based on current system
	// time_t is a struct used in ctime header
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   return dt;
}

void CreateLog(const string &user, char *time, char type)
{
	type = (char) toupper(type);
	ofstream log_file("log.db", ios::out | ios::app);
	string log_line = type + user + string(";") + time;
	log_file << log_line;
	log_file.close();
}

string Credits()
{
	string credits = string("Made by Raahim Fareed - BSE203039\n") +
		   			 string("SE1133 - Introduction to Programming\n") +
		   			 string("C++14, GCC and VSCode was used in the making\n") +
		   			 string("Press [Enter/Return] key to return to menu");
	return credits;
}

string Help()
{
	return "For help and documentation please visit https://github.com/raahimfareed/hospital-management-SE1133\n";
}

void RemoveAppointment()
{
	GetTotalPendingAppointments();
	cout << "Enter Id of appointment you want end: ";
	int id;
	cin >> id;
	cin.ignore();
	if (id < g_total_appointments)
	{
		if (Appointments[id].username == "-")
		{
			cout << "That is not a valid ID\n";
		}
		else
		{
			Appointments[id].username = "-";
			Appointments[id].query = "-";
			cout << "Appointment removed!\n";
		}
	}
	else
	{
		cout << "That is not a valid ID\n";
	}
	cout << "Press [Enter/Return] key to return to menu\n";
	cin.get();
}
