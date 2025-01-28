#include<bits/stdc++.h>
using namespace std;
class Book {
public:
	int Book_id;
	string Book_title;
	string Book_author;
	int total_no_issue;
	Book *next;
};
unordered_set<int>st;
bool return_flag=true;
void traverse(Book *&head,int id,int task) {
	Book *temp=head;
	while(temp->Book_id!=id) {
		temp=temp->next;
	}
	if(task==1) {
		temp->total_no_issue++;
	}
	else if(task==2) {
		if(temp->total_no_issue!=0)temp->total_no_issue--;
		else {
			// Book has no issue
			return_flag=false;
			cout<<"Error: Cannot return a book that hasn't been issued.\n";
		}
	}
	else if(task==3) {
		string title_update,author_update;
		cout<<"[Update] Enter new title for the book: ";
		cin.ignore();
		getline(cin,title_update);
		temp->Book_title=title_update;
		cout<<"[Update] Enter new author for the book: ";
		getline(cin,author_update);
		temp->Book_author=author_update;
	}
	else if(task==4) {
		cout<<"[Search Result] Book found: ID: "<<temp->Book_id<<", Title: "<<temp->Book_title<<", Author: "<<temp->Book_author<<", Issued Count: "<<temp->total_no_issue;
	}
	return;
}
void add_book(Book *&head,Book *&insert_temp,unordered_set<int>&st,bool &flag) {
	Book *newnode=new Book();
	int id;
	string tit,auth;
	cout<<"Enter id: ";
	cin>>id;
	// Book Id is primary key so only one particular book have an unique id
	if(st.find(id)==st.end()) {
		// insert the book id
		st.insert(id);
	}
	else {
		cout<<"Please entered unique id\n";
		flag=false;
		return;
	}
	cin.ignore();
	cout<<"Enter Book Title: ";
	getline(cin,tit);
	cout<<"Enter Author Name: ";
	getline(cin,auth);
	newnode->Book_id=id;
	newnode->Book_title=tit;
	newnode->Book_author=auth;
	newnode->total_no_issue=0;
	newnode->next=NULL;
	if(head==NULL) {
		head=insert_temp=newnode;
	}
	else {
		insert_temp->next=newnode;
		insert_temp=newnode;
	}
	return;
}
void issue_book(Book *&head,bool &flag) {
	int id;
	cout<<"Enter Book Id to issue: ";
	cin>>id;
	if(st.find(id)!=st.end()) {
		traverse(head,id,1);
	}
	else { // It can be possible that entered id is not in Library
		cout<<"Book Not Found\n";
		flag=false;
		return;
	}
	return;
}
void return_book(Book *&head) {
	int id;
	cout<<"Enter Book Id to return: ";
	cin>>id;
	return_flag=true; // reset the flag
	if(st.find(id)!=st.end()) {
		traverse(head,id,2);
	}
	else {
		// Book is not found
		cout<<"Book Not Found\n";
		return_flag=false;
		return;
	}
	return;
}
void display_book(Book *&head) {
    if(head==NULL){
        cout<<"No Books\n";
        return;
    }
	cout<<"[Library Books] List of books:\n";
	Book *temp=head;
	while(temp!=NULL) {
		cout<<"ID: "<<temp->Book_id<<",Title: "<<temp->Book_title<<",Author: "<<temp->Book_author<<",Issued Count: "<<temp->total_no_issue<<"\n";
		temp=temp->next;
	}
	return;
}
void update_book(Book *&head,bool &flag) {
	int id;
	cout<<"Enter Book Id to Update: ";
	cin>>id;
	if(st.find(id)!=st.end()) {
		traverse(head,id,3);
	}
	else { // It can be possible that entered id is not in Library
		cout<<"Book Not Found\n";
		flag=false;
		return;
	}
	return;
}
void search_book(Book *head) {
	int id;
	cout<<"Enter Book Id to Searching: ";
	cin>>id;
	if(st.find(id)!=st.end()) {
		traverse(head,id,4);
	}
	else { // It can be possible that entered id is not in Library
		cout<<"Book Not Found\n";
		return;
	}
	return;
}
void del_thebook(Book *&head,int id,bool &flag){  // If book issue someone then how can u delete that book
    if(head->Book_id==id){
        if(!head->total_no_issue)head=head->next;
        else{
            cout<<"Book Issued Someone then how can u delete\n";
            flag=false;
            return;
        }
    }
    else{
        Book *temp=head;
        while(temp->next->Book_id!=id){  // temp can't be reach at null because it's possible it found id
            temp=temp->next;
        }
        if(!temp->next->total_no_issue)temp->next=temp->next->next;
        else{
            cout<<"Book Issued Someone then how can u delete\n";
            flag=false;
            return;
        }
    }
    return;
}
void delete_book(Book *&head,bool &flag) {
	int id;
	cout<<"Enter Book Id to Delete: ";
	cin>>id;
	if(st.find(id)!=st.end()) {
		del_thebook(head,id,flag);
	}
	else { // It can be possible that entered id is not in Library
		cout<<"Book Not Found\n";
		flag=false;
		return;
	}
	return;
}
int main() {
	Book *head=NULL,*insert_temp=NULL;
	while(true) {
		cout<<"\n\n\n";
		cout<<"------------------------------------------------\n";
		cout<<"           Library Management System            \n";
		cout<<"------------------------------------------------\n";
		cout<<"S.No      Function         Description\n";
		cout<<"\n";
		cout<<"1       Add Book         (Insert New Book)\n";
		cout<<"2       Issue Book       (Issue book by Id)\n";
		cout<<"3       Return Book      (Return issued Book)\n";
		cout<<"4       Display Books    (Display all Book)\n";
		cout<<"5       Update Book      (Update recorded Book)\n";
		cout<<"6       Search Book      (Search Book by Id)\n";
		cout<<"7       Delete Book      (Delete Book by Id)\n";
		cout<<"8       Exit\n";
		int choice;
		cout<<"Enter the choice: ";
		cin>>choice;
		if(choice==1) {
			bool flag=true;
			add_book(head,insert_temp,st,flag);
			if(flag)cout<<"\n<---Book Add Successfully--->\n";
		}
		else if(choice==2) {
			bool flag=true;
			issue_book(head,flag);
			if(flag)cout<<"<---Book Issued Successfully--->\n";
		}
		else if(choice==3) {
			return_book(head);
			if(return_flag)cout<<"<---Book Return Successfully--->\n";
		}
		else if(choice==4) {
			display_book(head);
		}
		else if(choice==5) {
			bool flag=true;
			update_book(head,flag);
			if(flag)cout<<"<---Book Update successfully--->\n";
		}
		else if(choice==6) {
			search_book(head);
		}
		else if(choice==7) {
            bool flag=true;
            delete_book(head,flag);
            if(flag)cout<<"<---Book Delete successfully--->\n";
		}
		else {
			return 0;
		}
	}
}
