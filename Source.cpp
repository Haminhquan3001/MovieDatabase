/*	10/17/2020 

		Based on the given database, the program will populate the 
	database by reading in information from a file whose name 
	will be enter by the user with a specifc format.
	The program will then ask the user to search for the movie
	in the database. 
	If it's found the movie information will be displayed 
	Otherwise it displays an error message. The program also ask
	user if they want to save their searches 
	and save into a file which is favorite.txt
*/

#include <iostream>
#include<string>
#include<fstream>
using namespace std;



//declaring a struct for storing variables
struct Movie {
	//Declaring movie database
	string Title; 
	double grossTotal = 0;
	string directorName;
	string DateRelease;
	int RunTime = 0;
};

//Function Prototype

int numberOfLines(ifstream& inputFiles);
void populateMovieFromFile(ifstream& FileInput, Movie& movie);
void displayMovie(const Movie& movie);
bool caseInsensitiveCmp(string str1, string str2);
void findMovie(Movie* ptrMovie, int numMovies);
void saveToFile(const Movie& movie);
bool promptToContinue();
void displayFavorites();



//This function accepts an input file and return an integer
//which is the number of lines in the file

int numberOfLines(ifstream& inputFiles) {
	//declaring the inputFiles, number of line and tempvalue
	string tempvalue;
	//while loop to count the number of lines in the file
	int numLines = 0;
	if (inputFiles) {
		while (getline(inputFiles, tempvalue)) {
			numLines++;
		}
	}
	//Set the cursor to the beginning of the file 
		inputFiles.clear();
		inputFiles.seekg(0, ios::beg);
		return numLines;
}



//This function accepts and input file and struct Movie 
//and It populates a single object in the file
//it has no return since it is a void function

void populateMovieFromFile(ifstream& FileInput, Movie& movie) {
	//Declaring FileInput, Movie struct and temp variables for
	//double and int
	string grossTotalTemp, runTimeTemp;
	//Populate each elements of the Movie from File
		getline(FileInput, movie.Title, ',');
		getline(FileInput, grossTotalTemp, ',');
		movie.grossTotal =stod(grossTotalTemp); 
		getline(FileInput, movie.directorName, ',');
		getline(FileInput, movie.DateRelease, ',');
		getline(FileInput, runTimeTemp);
		movie.RunTime = stoi(runTimeTemp);
}



//This function accepts a constant movie object 
//It display the information of the object and has no return
//since it is a void function

void displayMovie(const Movie& movie) {
	//Displaying Movie information
	cout << "Title: " << movie.Title << endl;
	cout << "Gross Total: " << movie.grossTotal << endl;
	cout << "Director: " << movie.directorName << endl;
	cout << "Release Date: " << movie.DateRelease << endl;
	cout << "Runtime: " << movie.RunTime << endl;
}



/*This function firstly prompt the user to enter to input 
a valid file name. The user will need to input until 
it is a valid file.
It accepts the numLines and then create an array of Movie objects
on the heap and store each movie in the array. 
It return a pointer	to the array of Movie objects
*/

Movie* createDatabase(int& NumLines);
Movie* createDatabase(int& NumLines) {
	ifstream inputFile;
	string FileName;
	//loop to prompt the user until a valid file is entered. 
	do {
		cout << "Please enter file name: ";
		cin >> FileName;
		inputFile.open(FileName);
		if (!inputFile) {
			cout << "Invalid File. Please enter again" << endl;
		}
	} while (!inputFile);
	//Determine the number of Lines
		NumLines = numberOfLines(inputFile);
	//create array of Movie objects on the heap
		Movie* ptr = new Movie[NumLines];
	//for loop to store movie into each index
		for (int i = 0; i < NumLines; i++) {
			populateMovieFromFile(inputFile, ptr[i]);
		}
		// returning file and closing file
		return ptr;
		//closing file
		inputFile.close();
}



/*This function accepts to strings and make
a comparison on the two and return whether it is true 
or false
*/

bool caseInsensitiveCmp(string str1, string str2) {
	//first loop to change all the characters
	//in the first string to lowercase
	for ( int x = 0; x < str1.length();x++) {
		char s1 = tolower(str1[x]);
		str1[x] = s1;
	}
	//second loop to change all the characters 
	//in the second string to lowercase
	for ( int y = 0; y < str2.length();y++) {
		char s2 = tolower(str2[y]);
		str2[y]= s2;
	}
	//comparison for two strings and return true or false
	if (str1 == str2) {
		return true;
	}
	else {
		return false;
	}
}



/*This function accepts a constant Movie object 
and save it into a new file which is "favorite.txt"
It return nothing since it is a void function
*/

void saveToFile(const Movie& movie) {
	//Open file
	ofstream outputfile;
	outputfile.open("Favorites.txt", ios::app);
	//check if it open sucessfully
	if (outputfile) {
		//save it into a new file which is "favorite.txt"
		outputfile << "\nTitle: " << movie.Title << endl;
		outputfile << "Gross Total: " << movie.grossTotal << endl;
		outputfile << "Director: " << movie.directorName << endl;
		outputfile << "Date Release: " << movie.DateRelease << endl;
		outputfile << "Runtime: " << movie.RunTime << endl;
		outputfile << endl;
	}
	else {
		cout << "Open unsuccesfully";
	}
	//closing file
	outputfile.close();
}



/* This function accepts nothing and it determine whether or not 
the user wants to continue using the program.
Return false if the user don't want to continue using it
Return true if the user wish to continue
*/

bool promptToContinue() {
	//Prompting the user if he/she would like to exit
	char Choices;
	cout << "\nWould you like to exit? (Y / N): ";
	cin >> Choices;
	cin.ignore();
	//If statements to return true or false
	if (Choices == 'y' || Choices == 'Y'){
		return false;
	}
	else {
		return true;
	}
}



/* This function accepts and returns nothing.
It displayed all the information of the saved movies
If there is nothing to display, it will display an error
*/

void displayFavorites() {
	//open favorite.txt
	ifstream favorite;
	string content;
	favorite.open("Favorites.txt");
	//displaying favorite
	cout << "\nYour saved movies are: " << endl;
	//check if it is open or not
	if (favorite) {
		while (getline(favorite, content)) {
			cout << content << endl;
		}
	}
	else {
		cout << "Nothing to display";
	}
	//closing file
	favorite.close();
}



/* This function accepts a pointer to an array of Movie obejct
and numLines which is also numMovies since the database contains
one movie each line. 
It prompts the user to enter a movie to search
If it is matched with the movie in the database,
it will display the information of the movie 
and ask user if they want to save or not
If it is not matched, it will display an error
Then it will ask the user if they want 
to continue searching or not
After the user no longer wish to continue,
It will then display all the saves movies.
It returns nothing
*/

void findMovie(Movie* ptrMovie, int numMovies) {
	string userEnter;
	char userChoice;

	//Declaring a bool and set it default value to true 
	//if Continue is false then the user no longer want
	//to continue the program
	//otherwise, it will keep iterating
	bool Continue = true;
	cin.ignore();
	//While loop to iterate if the user wish to continues
	while (Continue == true) {
		cout << "\nEnter a movie title to search for: ";
		getline(cin, userEnter);
		//declaring a bool and set the default value to false
		//if the result isSame is true then the movie is found
		//otherwise it is False which is not found
		bool isFound = false;
		for (int i = 0; i < numMovies;++i) {
			//Delcaring another bool to check particularly
			//the result of the comparison
			bool isSame = caseInsensitiveCmp(userEnter, 
				ptrMovie[i].Title);
			//If statements when the movie is found
			if (isSame == true) {
				//set the isFound to true because the result is true
				isFound = true;
				//displaying the information of the found movie
				displayMovie(ptrMovie[i]);
				//prompt the user to save the movie or not
				cout << "\nWould you like to save "
					"the above movie? (Y or N): ";
				cin >> userChoice;
				//If statements for the userchoice
				if (userChoice == 'y' || userChoice == 'Y') {
					//Saving the choices to the favorite.txt
					saveToFile(ptrMovie[i]);
					cout << "Successfully saved to Favorites.txt" 
						<< endl;
					//promt the user if they want to continue or not
					Continue = promptToContinue();
				
				}
				else {
					//prompt the user if they want to continue or not
					Continue = promptToContinue();
				}
			}
		}
		//If there is not movie found
		if (isFound == false) {
			//display an error message
			cout << "Error: " << "'" << userEnter << "'" <<
				" not found in database. Please try again" << endl;
				Continue = promptToContinue();
		}
	}
	//If the user no longer wants to use the program
	if (Continue == false) {
		//display the saved movies
		displayFavorites();
	}
}



//Main function
//Running functions and clean the heap

int main() {
	ifstream FileName;
	int NumMovie = numberOfLines(FileName);
	Movie* ptrMovie = createDatabase(NumMovie);
	findMovie(ptrMovie, NumMovie);

	ofstream Favor; 
	Favor.open("Favorites.txt", ios::out);
	Favor.close();
	delete[] ptrMovie;
	ptrMovie = nullptr;
}

