#include <iostream>
#include <string>
#include <typeinfo>
#include <limits>  
#include <algorithm>
#include <cctype>
#include <vector>
#include <bits/stdc++.h>
int flag = 0;
std::vector<int>borrowList;
class Books{
    private:
        int bId;
        std::string bTitle;
        std::string bAuthor;
        int bYear;
        std::string bStatus;
        int bCount;

    public:
        Books(int id, std::string title, std::string author, int year, std::string status, int count){
            bTitle = title;
            bAuthor = author;
            bYear = year;
            bId = id;
            bStatus = status;
            bCount = count;
        }

        int getId() {
            return bId;
        }
        std::string getTitle(){
            return bTitle;
        }
        std::string getAuthor(){
            return bAuthor;
        }
        std::string getStatus(){
            return bStatus;
        }
        int getCount(){
            return bCount;
        }
        void setCount(int bukcount){
            bCount = bukcount;
        }
        int getYear() {
            return bYear;
        }
        void setStatus(std::string stat){
            bStatus = stat;
        }
};
void searchBook(std::string booksearch, int n, std::vector<Books>&booksList){
    flag = 0;
    for(int i = 0 ; i < n; i++){
        std::string name = booksList[i].getTitle();
        int res = name.find(booksearch);
	    if (res != std::string::npos){
            flag = 1;
          	std::cout<<"Book Id: "<<booksList[i].getId()<<std::endl;
            std::cout<<"Title: "<<booksList[i].getTitle()<<std::endl;
            std::cout<<"Author: "<<booksList[i].getAuthor()<<std::endl;
            std::cout<<"Published Year: "<<booksList[i].getYear()<<std::endl;
            std::cout<<"Status: "<<booksList[i].getStatus()<<std::endl<<"\n";
        }
    }
    if (flag == 0)
        std::cout<<"👉️Book NOT Found!!😥️";
}

int addSearch(int n, std::vector<Books>booksList, std::string title){
     for(int i =0; i<n; i++){
        if(title == booksList[i].getTitle())
            return i;
     }
     return -1;
}
void addBook(int newId,int n, std::vector<Books>&booksList,std::string title){
    
    std::string author;
    int year;
    std::string status = "Available";
    std::transform(title.begin(), title.end(), title.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    int index = addSearch(n, booksList, title);
    if (index == -1){
        std::cout<<"Author Name : "<<std::endl;
        getline(std::cin,author);
        std::transform(author.begin(), author.end(), author.begin(), [](unsigned char c) {
            return std::toupper(c);
        });
        while (true){
            std::cout<<"Published Year : "<<std::endl;
            std::cin>>year;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Wrong Year format: Re-enter"<<std::endl;
            }
            else
                break;
        }
        Books newBook(newId, title, author, year, status,1); 
        booksList.push_back(newBook);
        std::cout<<"Book Added to Library!!😎️"<<std::endl;
    }
    else{
        booksList[index].setCount(booksList[index].getCount()+1);
        std::cout<<"Book already in library!!🤔️\nBook Count Increased!!😎️"<<std::endl;
    }

}

void borrowBook(std::string booksearch, int n, std::vector<Books>&booksList){
    flag = 0;
    searchBook(booksearch, n, booksList);
    if (flag == 1){
        int id, done = 0;
        while (true){
            std::cout<<"\nEnter the Book Id : ";
            std::cin>>id;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Wrong ID format: Re-enter"<<std::endl;
            }
            else
                break;
        }
        std::cout<<"\nBorrowed Book details\n"<< std::string(30, '-')<<std::endl;
        for(int i = 0 ; i < n; i++){
            int bid = booksList[i].getId();
	        if (bid == id && booksList[i].getStatus() == "Available"){
              	std::cout<<"Book Id: "<<booksList[i].getId()<<std::endl;
                std::cout<<"Title: "<<booksList[i].getTitle()<<std::endl;
                std::cout<<"Author: "<<booksList[i].getAuthor()<<std::endl;
                std::cout<<"Published Year: "<<booksList[i].getYear()<<std::endl;
                int cc = booksList[i].getCount()-1;
                booksList[i].setCount(cc);
                if(cc > 0)
                    booksList[i].setStatus("Available");
                else 
                    booksList[i].setStatus("Not Available");
                std::cout<<"Status: "<<booksList[i].getStatus()<<std::endl;
                std::cout<<"Book Count: "<<booksList[i].getCount()<<std::endl<<"\n";
                std::cout<<"👉️Book Borrowed Successfully👈️\n"<<std::endl;
                borrowList.push_back(bid);
                done = 1;
                break;
            }
            else{
                continue;
            }
        }
        if (done == 0)
            std::cout<<"👉️Sorry Book Not Available!!👈️\n";
    }
    else{
        std::cout<<""<<std::endl;
    }
}

void returnBook(int n, std::vector<Books>&booksList){
    std::string title;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout<<"Returning Book Title : "<<std::endl;
    getline(std::cin,title);
    std::transform(title.begin(), title.end(), title.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    int index = addSearch(n, booksList, title);
    int bid = booksList[index].getId(); 
    auto it = find(borrowList.begin(), borrowList.end(), bid); 
    if (it!=borrowList.end()){
        std::cout<<"Book Id: "<<booksList[index].getId()<<std::endl;
        std::cout<<"Title: "<<booksList[index].getTitle()<<std::endl;
        std::cout<<"Author: "<<booksList[index].getAuthor()<<std::endl;
        std::cout<<"Published Year: "<<booksList[index].getYear()<<std::endl;
        int cc = booksList[index].getCount()+1;
        booksList[index].setCount(cc);
        booksList[index].setStatus("Available");
        std::cout<<"Status: "<<booksList[index].getStatus()<<std::endl;
        std::cout<<"Book Count: "<<booksList[index].getCount()<<std::endl<<"\n";
        std::cout<<"Book Returned Successfully!!🙏️🫂️"<<std::endl;
        borrowList.erase(it);
    }
    else{
        std::cout<<"👉️Book was not yet borrowed!!😯️\nYou can add this book to library.😊️"<<std::endl;
        addBook(booksList.size()+ 1, n, booksList,title);
    }
}

int main(){

    char proceed = 'y', c;
    int n;
    std::string booksearch ;
    std::string title;
    std::cout<< std::string(29, '-')<<std::endl;
    std::cout<<"| Welcome to the Library |"<<std::endl;
    std::cout<< std::string(29, '-')<<std::endl;
    std::vector<Books> booksList;
    booksList.push_back(Books(1, "WINGS OF FIRE", "Dr.A. P. J. ABDUL KALAM and ARUN TIWARI", 1999, "Available", 1));
    booksList.push_back(Books(2, "GOD OF SMALL THINGS", "ARUNDATHI ROY", 1997, "Available", 1));
    booksList.push_back(Books(3, "THE PSHYCHOLOGY OF MONEY", "MORGAN HOUSEL", 2020, "Available", 1));
    booksList.push_back(Books(4, "THE ALCHEMIST", "PAULO COELHO", 1988, "Available", 1));
    booksList.push_back(Books(5, "MALGUDI DAYS", "R. K. NARAYAN", 1942, "Available", 1));

    while(proceed == 'y' || proceed == 'Y'){
        std::cout<<"\tMenu\n"<< std::string(25, '-') <<"\nAdd Book(a)\nSearch(s)\nBorrow(b)\nReturn(r)\nCatalogue(c)\nExit(y)"<<std::endl;
        std::cout<<"Please Choose one option:";
        std::cin>>c;

        switch(c){
            case 'a':
            case 'A' :
                std::cout<<"\n\tAdd a Book\n"<< std::string(25, '-')<<"\nEnter the details:\n"<<std::endl;
                n = booksList.size();
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Book Title : "<<std::endl;
                getline(std::cin,title);
                addBook(booksList.size()+ 1, n, booksList,title);
                break;
            case 's' :
            case 'S':
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"\n\tSearch a Book\n"<< std::string(25, '-')<<"\nEnter the details:\n"<<std::endl;
                std::cout<<"Which book do you want: "<<std::endl;
                getline(std::cin, booksearch);
                std::transform(booksearch.begin(), booksearch.end(), booksearch.begin(), [](unsigned char c) {
                    return std::toupper(c);
                });
                n = booksList.size();
                searchBook(booksearch, n, booksList);
                break;
            case 'b' :
            case 'B':
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"\n\tBorrow a Book\n"<< std::string(25, '-')<<"\nEnter the details:\n"<<std::endl;
                std::cout<<"Which book do you want: "<<std::endl;
                getline(std::cin, booksearch);
                std::transform(booksearch.begin(), booksearch.end(), booksearch.begin(), [](unsigned char c) {
                    return std::toupper(c);
                });
                n = booksList.size();
                borrowBook(booksearch, n, booksList);
                break;
            case 'r' :
            case 'R':
                //std::cout<<"\n\tReturn Book\n"<< std::string(25, '-')<<"\nEnter the details:\n"<<std::endl;
                n = booksList.size();
                returnBook(n, booksList);
                break;
            case 'c' :
            case 'C':
                std::cout<<"\n\tCatalogue\n"<< std::string(25, '-')<<std::endl;       
                n = booksList.size();
                for(int i =0; i<n; i++){
                    std::cout<<"Book Id: "<<booksList[i].getId()<<std::endl;
                    std::cout<<"Title: "<<booksList[i].getTitle()<<std::endl;
                    std::cout<<"Author: "<<booksList[i].getAuthor()<<std::endl;
                    std::cout<<"Published Year: "<<booksList[i].getYear()<<std::endl;
                    std::cout<<"Status: "<<booksList[i].getStatus()<<std::endl;
                    std::cout<<"Count: "<<booksList[i].getCount()<<std::endl<<"\n";
                }
                break;
            case 'y' :
            case 'Y':
                std::cout<<"THANK YOU 🫂️ !! Visit Again!!❤️🤟️\n";
                proceed = 'n';
                exit(0);
            default:
                std::cout<<"\nWrong Choice 😥️"<<std::endl;
                break;


        }
    }

    return 0;
}
