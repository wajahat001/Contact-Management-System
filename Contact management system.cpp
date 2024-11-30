#include <iostream>
#include <string>
#include <fstream>

#define MAX_USERS 100
using namespace std;

class Contact {
public:
    string First_Name;
    string Last_Name;
    string phoneno;
    string email;
    Contact* next;
    Contact* prev;

    Contact(string fn,string ln, string p,string e) {
        First_Name = fn;
        Last_Name = ln;
        phoneno = p;
        email = e;
        next = NULL;
        prev = NULL;
    }
};

class CMS {
public:
    Contact* head;

    CMS(){
		head = NULL;
	}

    void insert_Node(string fn,string ln, string p,string email) {
        Contact* new_node = new Contact(fn,ln, p,email);

        if (!head) {
            head = new_node;
        } else {
            Contact* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        ofstream OFile;
	    OFile.open("information.txt", ios::app);
	    OFile << fn <<" " << ln << " " << p << " " << email<< endl;
	    OFile.close();
    }

    // Delete a contact
    void delete_contact_from_file(const string& first, const string& last) {
    ifstream inputFile("information.txt",ios::in | ios::out);
    ofstream tempFile("temp.txt",ios::app);

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        size_t pos = 0;
        string token;
        string contactInfo[4];  
        
        for (int i = 0; i < 4; ++i) {
            pos = line.find(' ');
            token = line.substr(0, pos);
            contactInfo[i] = token;
            line.erase(0, pos + 1);
        }

        if (contactInfo[0] == first && contactInfo[1] == last) {}
        else {
            tempFile << contactInfo[0] << " " << contactInfo[1] << " " << contactInfo[2] << " " << contactInfo[3] << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the old file and rename the temp file
    remove("information.txt");
    rename("temp.txt", "information.txt");
}

	void delete_contact(string first, string last) {
	    if (!head) {
	        cout << "\nContact not found!!!";
	        return;
	    }
	
	    if (head->First_Name == first && head->Last_Name == last) {
	        Contact* temp = head;
	        head = head->next;
	        delete temp;
	        delete_contact_from_file(first, last);  // Delete from file
	        cout << "\nContact deleted successfully.";
	        return;
	    }
	
	    Contact* current = head;
	    while (current->next && (current->next->First_Name != first || current->next->Last_Name != last)) {
	        current = current->next;
	    }
	
	    if (current->next) {
	        Contact* temp = current->next;
	        current->next = current->next->next;
	
	        delete_contact_from_file(first, last);  // Delete from file
	
	        delete temp;
	        cout << "\nContact deleted successfully.";
	    } else {
	        cout << "\nContact not found!!!";
	    }
}

    // Search a contact
    void search_Node(string search) {
        Contact* temp = head;
        int number = 1;

        while (temp != nullptr) {
            if (temp->First_Name == search) {
                cout << "\nContact with name " << search << " Found at Node " << number << endl << endl;
                return;
            }
            temp = temp->next;
            number++;
        }

        cout << "'" << search << "' not found in the list." << endl;
    }

    // Update a contact
    void update_contact(string contacttoupdate) {
        Contact* temp = head;

        while (temp != NULL) {
            if (temp->First_Name == contacttoupdate) {
                cout << "\nContact with name " << contacttoupdate << " Found";
                cout << " Please enter a new phone number: ";
                cin >> temp->phoneno;
                cout << "Contact updated successfully.";
                return;
            }
            temp = temp->next;
        }

        cout << "'" << contacttoupdate << "' not found in the list." << endl;
    }

    // Display phonebook
    void display_phonebook() {
        Contact* temp = head;
        cout << endl;
        cout << "\tFirst Name: \tLast Name: \tPhone Number: \tEmail:" << endl;
        while (temp != NULL) {
            cout << "\t " << temp->First_Name << "\t" << temp->Last_Name <<  "\t " << temp->phoneno << "\t " << temp->email;
            cout << endl;
            temp = temp->next;
            delete_contact_from_file(temp->First_Name,temp-> Last_Name); 
        }
        cout << endl;
    }
};

class User {
	private:
    	string UserID;
   	    string loginPassword;
    	CMS phonebook; // Each user has their own phonebook

	public:
		
		User() : UserID(""), loginPassword("") {}
		
	    User(const string& userCINC, const string& userPassword) {
	        UserID = userCINC;
	        loginPassword = userPassword;
	    }
	
	    bool login(const string& enteredid, const string& enteredPassword) {
	        return (UserID == enteredid && loginPassword == enteredPassword);
	    }
	    
	    string getLoginPassword() const {
        return loginPassword;
    	}
    	
    	bool check_user_data(string id_check, string pass_check) {
        bool status = false;
        ifstream IFile;
        IFile.open("User.txt", ios::in | ios::out);
        while (!IFile.eof()) {
            IFile >> UserID >> loginPassword;
            if ((pass_check == loginPassword) && (id_check == UserID)) {
                cout << "You have Logged in: " << endl;
                status = true;
                break;
            } else if (id_check != UserID) {
                cout << "Invalid ID " << endl;
                break;
            } else if (pass_check != loginPassword) {
                cout << "Invalid Password " << endl;
                break;
            }
        }
        IFile.close();
        return status;
    }
		
		string getid() const {
        return UserID;
    	}
    
	    void usePhonebook() {
	    	system("cls");
	        int choice;
	        string fname,lname, phoneno, nametodel, contacttoupdate, ch,email;
	        do {
	        	ABC:{
	            cout << "\n======Phonebook menu=======" << endl;
	            cout << "1. Add Contact" << endl;
	            cout << "2. Search Contact" << endl;
	            cout << "3. Update Contact" << endl;
	            cout << "4. Delete Contact" << endl;
	            cout << "5. Display Contacts" << endl;
	            cout << "6. Exit" << endl;
	            cin >> choice;
	            while (choice < 1 || choice > 6) {
            		cout << "Invalid Choice. Enter again: ";
            		cin >> choice;
        		}
        	}
	            while (true) {
	        	    cout<<endl;
					switch(choice) {
	    			    case 1:
	    			        cout << "Enter First Name of person: ";
	    			        cin>>fname;
	    			        cout << "Enter Last Name of person: ";
	    			        cin>>lname;
	    			        cout << "Enter PhoneNo of person: ";
	    			        cin>>phoneno;
	    			        cout << "Enter email of preson: ";
	    			        cin>>email;
	    			        phonebook.insert_Node(fname,lname, phoneno,email);
	    			        cout<<endl;
	    			        goto ABC;
	    			        break;
	    					
	    			    case 2:
	    			        cout << "Enter the name of the Contact to Search: ";
	    			        cin>>fname;
	    			        phonebook.search_Node(fname);
	    			        cout<<endl;
	    			        goto ABC;
	    			        break;
	    			
	    			    case 3:
	    			        cout << "Enter name to update contact: ";
	    			        cin >> contacttoupdate;
	    			        phonebook.update_contact(contacttoupdate);
	    			        cout<<endl;
	    			        goto ABC;
	    			        break;
	    			
	    			    case 4:
	    			        cout << "Enter First name to delete: ";
	    			        cin >> fname;
	    			        cout << "Enter Last name to delete: ";
	    			        cin >> lname;
	    			        phonebook.delete_contact(fname,lname);
	    			        cout<<endl;
	    			        goto ABC;
	    			        break;
	    			
	    			    case 5:
	    			        cout << "Phone Book : ";
	    			        phonebook.display_phonebook();
	    			        cout<<endl;
	    			        goto ABC;
	    			        break;
	    			
	    			    case 6:
	    			        cout << "Exiting Phonebook." << endl;
	    			        return;
	    			
	    			    default:
	    			        cout << "Invalid choice. Please try again." << endl;
	     			}
	     			cout<<endl;
	       		}
	
	            cout << "Do you want to continue (y/n): ";
	            cin >> ch;
	            
	        } while (ch == "y" || ch=="Y");
	    }
	    
	    void displayUserInfo() {
		    cout << "UserId: " << UserID << endl;
		    cout << "Password: " << loginPassword << endl;
		    cout << "Phonebook contacts:" << endl;
		    phonebook.display_phonebook();
	   }
  
};

class CircularQueue {
	private:
    	User users[MAX_USERS];
    	int front, rear, itemCount;

	public:
    	CircularQueue() : front(0), rear(-1), itemCount(0) {}

	    bool isFull() {
    	    return itemCount == MAX_USERS;
    	}

	    bool isEmpty() {
    	    return itemCount == 0;
    	}

	    void enqueue(const User& newUser) {
    	    if (!isFull()) {
        	    rear = (rear + 1) % MAX_USERS;
            	users[rear] = newUser;
            	itemCount++;
        	}
			
			 else {
            	cout << "Queue is full. Cannot add more users." << endl;
        	}
    	}

	    User dequeue() {
    	    if (!isEmpty()) {
        	    User dequeuedUser = users[front];
            	front = (front + 1) % MAX_USERS;
            	itemCount--;
            	return dequeuedUser;
        	} 
			else {
            	cout << "Queue is empty." << endl;
            	return User(); // Returning a default User object in case of an empty queue
        	}
    	}

	    User peekFront() {
	        if (!isEmpty()) {
	            return users[front];
	        } 
			else {
	            cout << "Queue is empty." << endl;
	            return User(); // Returning a default User object in case of an empty queue
	        }
	    }
	
	    void displayQueue() {
	        int count = itemCount;
	        int i = front;
	        while (count > 0) {
	            cout << "UserId: " << users[i].getid() << ", ";
	            cout << "Password: " << users[i].getLoginPassword() << endl;
	            count--;
	            i = (i + 1) % MAX_USERS;
	        }
    	}
};

class Admin {
	private:
    	string AdminID;
	    string password;
    	CircularQueue userQueue; // Circular queue to store users
	
	public:
	    Admin() {
	        AdminID = "224769";
	        password = "Defender";
	    }
	
	    void addUser(const string& id, const string& loginPassword) {
	        User newUser(id, loginPassword);
	        userQueue.enqueue(newUser);
	        write_member_data(id,loginPassword);
	        cout << "User added successfully." << endl;
	    	}
	    	void write_member_data(string UserID,string Password) {
		        ofstream OFile;
		        OFile.open("User.txt", ios::app);
		        OFile << UserID << " " << Password << endl;
		        OFile.close();
	    	}	
	
		    void accessUserInfo() {
		        string idToView;
				int i=0;
				
		        cout << "Enter ID of the user to view details: ";
		        cin >> idToView;
		
		        bool userFound = false;
		        CircularQueue tempQueue = userQueue; // Create a temporary queue for traversal
		        while (!tempQueue.isEmpty()) {
		            User currentUser = tempQueue.dequeue();
		            if (currentUser.getid() == idToView) {
		                cout << "\nUser details:" << endl;
		                currentUser.displayUserInfo();
		                userFound = true;
		                break;
		            }
		            tempQueue.enqueue(currentUser);
		            i++;
		            if(i==100){
		            	cout << "Invalid ID. User not found." << endl;
		            	return;
		            }
		    	}
		    	
		        if (!userFound) {
		            cout << "User not found." << endl;
		            return;
		        }
    	}
    	
    	bool check_admin_data(string id, string pass_check) {
	        bool status = false;
	            if ((pass_check == password) && (AdminID == id)) {
	                cout << "You have Logged in: " << endl;
	                status = true;
	            } else if (AdminID != id) {
	                cout << "Invalid ID " << endl;
	            } else if (pass_check != password) {
	                cout << "Invalid Password " << endl;
	            }
	        return status;
	    }
		
	    void adminMenu() {
	    	system("cls");
	    	int choice, k;
	    	string ID,pass;	            
			while (true) {
	            	
				cout<<"\n=======ADMIN MENU========"<<endl;
	 	    	cout<<"1. Add User"<<endl;
	 	    	cout<<"2. Access User Information"<<endl;
	 	    	cout<<"3. Change Password"<<endl;
	 	    	cout<<"4. Exit"<<endl;				
	            cin >> choice;
	            while (choice < 0 || choice > 4) {
			        cout << "Invalid Choice. Enter again: ";
			        cin >> choice;
		    	}
				
				system("cls");
				
			switch (choice) {
	 			    
				case 1: {
	 		        cout << "Enter Id for new user: ";
	 		        cin >> ID;
	 		        cout << "Enter password for new user: ";
	 		        cin >> pass;
	 		        addUser(ID, password);
	 		        break;
	 		       }
	 		    
				case 2:
	 		        accessUserInfo();
	 		        break;
	 		   
	 		    case 3:{
	 		    	cout<<"Enter your ID"<<endl;
	 		    	cin>>ID;
	 		    	if(ID==AdminID){
	 		    		cout<<"Enter Your new password"<<endl;
	 		    		cin>>password;
					 }
					break;
				}
					
			    case 4:
	 		        cout << "\nExiting admin panel." << endl;
	 		        return;
	 		        
	 		   	default:
	 		        cout << "Invalid choice. Please try again." << endl;
	 		      
	 			}
	 			
	 		}
	    }
	  
	    void adminLogin() {
    	    string name, pass;
    	    bool loginSuccessful = false;
    	
			cout<<"\t==Admin Login=="<<endl;
    	    
			while (!loginSuccessful) {
    	        
    	        cout << "Enter NAME for login: ";
    	        cin >> name;
    	        cout << "Enter password for login: ";
    	        cin >> pass;
    	
    	        if (name == AdminID && pass == this->password) {
    	            loginSuccessful = true;
    	            cout << "Login successful. Welcome!" << endl;
    	        } 
				else {
    	            cout << "Invalid name or password. Login failed." << endl;
    	            cout<<"Try Again"<<endl;
    	            cin.clear();
    	            
    	            cout<<endl;
    	        }
    	    }
    	    adminMenu();
    }
	   
	    void userLogin() {
	    	int i = 0;
		    cout << "\t==User Login==" << endl;
		    string id, enteredPassword;
		    cout << "Enter ID for login: ";
		    cin >> id;
		    cout << "Enter password for login: ";
		    cin >> enteredPassword;
		
		    bool userFound = false;
		    CircularQueue tempQueue = userQueue;
		    User foundUser;
		
		    while (!tempQueue.isEmpty()) {
		        User currentUser = tempQueue.peekFront(); 
		        if (currentUser.getid() == id && currentUser.getLoginPassword() == enteredPassword) {
		            userFound = true;
		            foundUser = currentUser;
		            break;
		        }
		        tempQueue.dequeue();
		        tempQueue.enqueue(currentUser); 
		        i++;
		        if (i==100) {
            		cout << "Invalid ID or password. Login failed." << endl;
            		return;
		    	}
			}
		
		    if (userFound) {
		        cout << "Login successful. Welcome!" << endl;
		        foundUser.usePhonebook(); // Access the user's phonebook
		        return;
		    }
		}
};

int main() {
	system("color B4");
    User user;
    Admin admin;
    int choice = 0, choice1 = 0;
    bool check = false;
	string id;
	string pass;
    cout << "\n\n\t=======CONTACT MANAGEMENT SYSTEM========" << endl;

    ABC:{
	    cout << "1. User:" << endl;
	    cout << "2. Admin:" << endl;
	    cout << "0. Exit" << endl;
	    cin >> choice;
	 }
    while (choice < 0 || choice > 2) {
        cout << "Invalid Choice. Enter again: ";
        goto ABC;
    }
    
    switch (choice) {
    case 1:
    	XYZ:
        cout << "1. New User:" << endl;
        cout << "2. Old User:" << endl;
        cout << "3. Exit" << endl;
        cin >> choice1;

        while (choice1 < 1 || choice1 > 3) {
            cout << "Invalid Choice. Enter again: ";
            goto XYZ;
        }

        switch (choice1) {
	        case 1:{
	            cout << "Enter user ID: ";
        		cin >> id;
        		cout << "Enter user password: ";
        		cin >> pass;
        		admin.addUser(id, pass);
        		admin.userLogin();
	            goto ABC;
				break;
			}
	        case 2:{
	        	MNO:
	        	cout << "Enter your Id: ";
	            cin >> id;
	            cout << "Enter your Password: ";
	            cin >> pass;
				check = user.check_user_data(id, pass);
	            if (check) {
	                admin.userLogin();
	        	}
	        	else{
	        		cout<<"Incorrect Id or password"<<endl;
	        		goto MNO;
				}
	            admin.userLogin();
	           
	            goto ABC;
				break;
			}
			
	        case 3:{
	            goto ABC;
	            break;
				}
        }

	    case 2:
	        cout << "Enter your Id: ";
	        cin >> id;
	        cout << "Enter your Password: ";
	        cin >> pass;
	        check = admin.check_admin_data(id, pass);
	        if (check) {
	            admin.adminMenu();
	        }
	        break;
	
	    case 0:
	        cout << "Exiting..." << endl;
	        break;
	    }

    return 0;
}
