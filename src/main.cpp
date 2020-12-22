
/**
 * This file is part of Hospital Management System.
 * Code written by Raahim Fareed
 * Registration Number: BSE203039
 * Class: 203 SE 1A
 */

// ==============================================================
// Headers
// ==============================================================

/**
  * #include <iostream> - Used for basic input output operations on stream
  * #include <fstream> - Used for file streams
  * #include <limits> - Has numeric_limits which is being used for cin.ignore()
  */
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <algorithm>

/**
 * Namespaces
 * std - Standard
 */
using namespace std;

// ==============================================================
// Function Declarations
// ==============================================================

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
			if (g_user_precedence < 4)
			{
				cout << Error(8) + '\n' // User needs to login
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}
			break;
		case 'D':
			if (g_user_precedence != 4)
			{
				cout << Error(10) + '\n' // [Restricted access] Only doctors can access this menu
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}
			else
			{
				
			}

			break;
		case 'M':
			if (g_user_precedence >= 8 && g_logged_in)
			{
				bool loop;
				do
				{
					AdminMainMenu(g_username, menu_location, submenu_location);
					cin >> menu_option;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					loop = false;
					switch (toupper(menu_option[0]))
					{
					case 'P':
						AdminSubmenu(g_username, menu_location, submenu_location, "p");
						cin >> menu_option;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						break;
					case 'D':
						AdminSubmenu(g_username, menu_location, submenu_location, "d");
						cin >> menu_option;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						break;
					case 'M':
						AdminSubmenu(g_username, menu_location, submenu_location, "m");
						cin >> menu_option;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				cout << Error(9) + '\n' // [Restricted access]
					 << "Press [Enter/Return] Key to return to main menu\n";
				cin.get();
			}

			break;
		case 'H':
			cout << "Help\n";
			break;
		case 'C':
			cout << "Credits\n";
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

	if (g_user_precedence > 0)
	{
		cout << "\u001b[1;33m[A]\u001b[0m Account\n";
	}

	if (g_user_precedence > 3)
	{
		cout << "\u001b[1;33m[P]\u001b[0m Patients\n"
		  	 << "\u001b[1;33m[D]\u001b[0m Doctors\n";
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
	menu_location = "admin-main-menu";
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
			cout << "\u001b[1;33m[A]\u001b[0m Show all Patients\n"
				 << "\u001b[1;33m[R]\u001b[0m Delete Patients Database \u001b[1;31m[WARNING: IRREVERSIBLE]\u001b[0m\n";
			break;
		case 'D':
			submenu_location = "doctors";

			cout << "\u001b[1;33m[A]\u001b[0m Show all Doctors\n"
				 << "\u001b[1;33m[R]\u001b[0m Delete Doctors Database \u001b[1;31m[WARNING: IRREVERSIBLE]\u001b[0m\n";
			break;
		case 'M':
			submenu_location = "admins";
			cout << "\u001b[1;33m[A]\u001b[0m Show all Admins\n"
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
	system("pause");
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
	menu_location = "account-main-menu";
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
			case 'M':
				
			case 'E':
				patient_loop = false;
				break;
			default:
				break;
		}
	} while (patient_loop);
}

string GetMessages(string username)
{

}
