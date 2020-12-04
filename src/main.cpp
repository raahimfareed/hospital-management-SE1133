
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
void InputPlaceholder(const string& username, const string& menu_location, const string& submenu_location);

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
void MainMenu(const string& username, string& menu_location, string& submenu_location);

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
void LoginMenu(const string& username, string& menu_location, string& submenu_location);

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
void SignupMenu(const string& username, string& menu_location, string& submenu_location);

void Signup(string type);
bool Login(string type);
bool Logout();

string Error(int error_code = 0);

void PrecedenceSet(const char &type = 0);

// Global Constants
// No constants yet

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
						cout << Error(1) + '\n'; // Invalid Option
					}
				} while (loop);
			}
			else
			{
				if (Logout())
				{
					cout << "\u001b[1;32mLogged Out!\u001b[0m\n"
						 << "Press [Enter/Return] key to return to main menu\n";
					cin.ignore();
				}
				else
				{
					cout << Error(6) + '\n' // No User logged in
						 << "Press [Enter/Return] key to return to main menu\n";
					cin.ignore();
				}
			}
			cin.ignore();
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
						cout << Error(1) + '\n'; // Invalid Option
					}
				} while (loop);
			}
			else
			{
				cout << Error(1) + '\n' // Invalid Option
					 << "Press [Enter/Return] key to return to main menu\n";
				cin.ignore();
			}
			break;
		case 'P':
			cout << "Patients\n";
			break;
		case 'D':
			cout << "Doctors\n";
			break;
		case 'M':
			cout << "Management\n";
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
		default:
			cout << Error(1) + '\n';
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
		cout << "\u001b[1;35m[Guest@\u001b[0m";
	else
		cout << "\u001b[1;35m[" + username + "@\u001b[0m";

	cout << "\u001b[1;35m" + menu_location + " " + submenu_location + "]: \u001b[0m";
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

	cout << "\u001b[1;33m[P]\u001b[0m Patients\n"
		 << "\u001b[1;33m[D]\u001b[0m Doctors\n"
		 << "\u001b[1;33m[M]\u001b[0m Management\n"
		 //  << "\u001b[1;33m[S]\u001b[0m Pharmacy\n"
		 << "\u001b[1;33m[H]\u001b[0m Help\n"
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

void Signup(string type)
{
	cin.ignore();

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

	cout << "Press [Enter/Return] key to return to main menu\n";
	cin.ignore();
}

bool Login(string type)
{
	cin.ignore();
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
			 << "Press [Enter/Return] key to return to main menu\n";
		return false;
	}
	else
	{
		if (password == password_data)
		{
			g_logged_in = true;
			g_username = username;
			cout << "\u001b[1;32mLogged In!\u001b[0m\n"
				 << "Press [Enter/Return] key to return to main menu\n";
			PrecedenceSet(tolower(type[0]));
			return true;
		}
		else
		{
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
						 << "Press [Enter/Return] key to return to main menu\n";
					PrecedenceSet(tolower(type[0]));
					return true;
				}
				password_tries++;
			} while (password_tries <= 2);
		}

		cout << Error(5) + '\n' // Exceeded password tries
			 << "Press [Enter/Return] key to return to main menu\n";
		return false;
	}
}

bool Logout()
{
	if (g_logged_in)
	{
		g_logged_in = false;
		g_username.clear();
		return true;
	}
	else
	{
		return false;
	}

	PrecedenceSet();
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
	};

	return "\u001b[1;31m" + errors[error_code] + "\u001b[0m";
}

void PrecedenceSet(const char &type)
{
	switch (tolower(type))
	{
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
