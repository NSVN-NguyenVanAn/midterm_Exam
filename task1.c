#include<stdio.h>

struct Address{
    char name[50];
    char phone[20];
    char email[50];
};

typedef struct Address Address;

Address arr[100];
Address ifNotFound;
void sort_array(Address arr[], int n);

// read data file
void readFile(){
    FILE* file = fopen("input.txt", "r");
    for(int i=0; i<10; i++){
        fgets(arr[i].name, sizeof(arr[i].name), file);
        if(arr[i].name[strlen(arr[i].name) - 1] == '\n') arr[i].name[strlen(arr[i].name) - 1] = '\0';
        fgets(arr[i].phone, sizeof(arr[i].phone), file);
        fgets(arr[i].email, sizeof(arr[i].email), file);
    }
    sort_array(arr, 10);
}


// array
Address binarySearch_array(Address arr[], int n, char name[]){
    int left = 0, right = n - 1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(strcmp(arr[mid].name, name) == 0) return arr[mid];
        if(strcmp(arr[mid].name, name) > 0){
            right = mid - 1;
        } else{
            left = mid + 1;
        }
    }
    return ifNotFound; // ko tim thay
}

void sort_array(Address arr[], int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(strcmp(arr[i].name, arr[j].name) > 0){
                Address a = arr[i];
                arr[i] = arr[j];
                arr[j] = a;
            }
        }
    }
}

// linkedlist
typedef struct Node
{
	Address address;
	struct _PhoneBookItem* next;
} Node;

Node* root = NULL;
Node* cur = NULL;

void Sort()
{
	Node* tmp = root;
	Node* prev = NULL;
	while (tmp != NULL)
	{
		Node* next = tmp->next;
		while (next != NULL)
		{
			if (strcmp(tmp->address.name, next->address.name) > 0)
			{
				if (root == tmp)
				{
					root = next;
				}

				tmp->next = next->next;
				next->next = tmp;
				if (prev != NULL)
				{
					prev->next = next;
				}
				tmp = next;
			}
			next = next->next;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void Insert(char* name, char* phone, char* email)
{
	if (cur != NULL)
	{
		Node* newItem =
		(Node*)calloc(1, sizeof(Node));
		strcpy(newItem->address.name, name);
		strcpy(newItem->address.phone, phone);
		strcpy(newItem->address.email, email);
		newItem->next = NULL;
		cur->next = newItem;
		cur = newItem;
	}else{
		Node* newItem =
		(Node*)calloc(1, sizeof(Node));
		strcpy(newItem->address.name, name);
		strcpy(newItem->address.phone, phone);
		strcpy(newItem->address.email, email);
		newItem->next = NULL;
		root = newItem;
		cur = newItem;
	}
}

struct Node* middle(Node* start, Node* last)
{
    if (start == NULL)
        return NULL;

    struct Node* slow = start;
    struct Node* fast = start -> next;

    while (fast != last)
    {
        fast = fast -> next;
        if (fast != last)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
    }

    return slow;
}

struct Node* binarySearch_linkedlist(Node *head, char *name)
{
    struct Node* start = head;
    struct Node* last = NULL;

    do
    {
        Node* mid = middle(start, last);


        if (mid == NULL)
            return NULL;

        if (strcmp(mid->address.name, name) == 0)
            return mid;

        else if (strcmp(mid->address.name, name) < 0)
            start = mid -> next;

        else
            last = mid;

    } while (last == NULL ||
             last != start);

    return NULL;
}


// queue

// my queue
const int MAX_SIZE_QUEUE = 10;
struct queue{
    Address array[10];
    int size;
};

typedef struct queue queue;
queue q;

void pushIgnoreOver(Address a){
    if(q.size == 10){
        removeFirst();
    }
    q.array[q.size] = a;
    q.size++;
}

void removeFirst(){
    for(int i=0; i<9; i++){
        q.array[i] = q.array[i + 1];
    }
    q.size--;
}

Address search_(char name[]){
    for(int i=0; i<q.size; i++){
        if(strcmp(q.array[i].name, name) == 0) return q.array[i];
    }
    return ifNotFound;
}

int main(){
    readFile();
    printf("danh sach:\n");
    for(int i=0; i<10; i++){
        printf("%s\n%s%s\n", arr[i].name, arr[i].phone, arr[i].email);
    }

    for(int i=0; i<10; i++){
        Insert(arr[i].name, arr[i].phone, arr[i].email);
    }

    for(int i=0; i<10; i++){
        pushIgnoreOver(arr[i]);
    }


    int choose;
    while(1){
        printf("\n-----------------\n");
        printf("1. array\n");
        printf("2. linkedlist\n");
        printf("3. queue\n");
        printf("4. push 11th-element in queue\n");
        printf("0. thoat\n");
        printf("-----------------\n");
        printf("chon: ");
        scanf("%d", &choose);
        getchar();
        switch(choose){
            case 1:{
                printf("\n-----array------\n" );
                printf("nhap ten tim kiem: ");
                char name[100];
                gets(name);
                Address a = binarySearch_array(arr, 10, name);
                printf("ket qua: %s\n%s%s\n", a.name, a.phone, a.email);
                break;
            }
            case 2:{
                printf("\n-----linkedlist------\n" );
                printf("nhap ten tim kiem: ");
                char name[100];
                gets(name);
                Node* x = binarySearch_linkedlist(root, name);
                printf("ket qua: %s\n%s%s\n", x->address.name, x->address.phone, x->address.email);
                break;
            }
            case 3:{
                printf("\n-----queue------\n" );
                printf("nhap ten tim kiem: ");
                char name[100];
                gets(name);
                Address x = search_(name);
                printf("ket qua: %s\n%s%s\n", x.name, x.phone, x.email);
                break;
            }
            case 4:{
                printf("element 10th BEFORE push: \n");
                printf("%s\n %s%s\n", q.array[9].name, q.array[9].phone, q.array[9].email);
                printf("element 10th AFTER push: \n");
                Address a1;
                strcpy(a1.name, "11-th element");
                strcpy(a1.phone , "03929932");
                strcpy(a1.email,  "google.com@gmail");
                pushIgnoreOver(a1);
                printf("%s\n%s\n%s\n", q.array[9].name, q.array[9].phone, q.array[9].email);
                break;
            }
            default: return;
        }
    }
}
