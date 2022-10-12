#include <iostream>
using namespace std;

struct dataMahasiswa
{
    string nama;
    string prodi;
    int ipk;
};

struct Node
{
    dataMahasiswa data;
    struct Node *next;
};

int lenght(Node *head)
{
    int panjang = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        temp = temp->next;
        panjang++;
    }
    return panjang;
}

int linkedList2Array(Node *head, int *arr)
{
    // Cek banyak data
    int panjang = lenght(head);
    for (int i = 0; i < panjang; i++)
    {
        arr[i] = head->data.ipk;
        head = head->next;
    }
    return panjang;
}

int array2LinkedList(Node *head, int *arr)
{
    // Cek banyak data
    int panjang = lenght(head);
    for (int i = 0; i < panjang; i++)
    {
        head->data.ipk = arr[i];
        head = head->next;
    }
    return panjang;
}

int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            // put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}

struct Node *getTail(struct Node *cur)
{
    while (cur != NULL && cur->next != NULL)
    {
        cur = cur->next;
    }
    return cur;
}

struct Node *partition(struct Node *head, struct Node *end, struct Node **newHead, struct Node **newEnd)
{
    struct Node *pivot = end;
    struct Node *prev = NULL, *cur = head, *tail = pivot;
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot)
    {
        if (cur->data.ipk < pivot->data.ipk)
        {
            // First node that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
            {

                (*newHead) = cur;
            }
            prev = cur;
            cur = cur->next;
        }
        else
        { // If cur node is greater than pivot
            // Move cur node to next of tail, and change
            // tail
            if (prev)
            {
                prev->next = cur->next;
            }
            struct Node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    // If the pivot data is the smallest element in the
    // current list, pivot becomes the head
    if ((*newHead) == NULL)
    {
        (*newHead) = pivot;
    }
    // Update newEnd to the current last node
    (*newEnd) = tail;
    return pivot;

}

struct Node *quickSortRecur(struct Node *head, struct Node *end)
{
    if (!head || head == end)
    {
        return head;
    }
    Node *newHead = NULL, *newEnd = NULL;
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    struct Node *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        struct Node *tmp = newHead;

        while (tmp->next != pivot)
        {
            tmp = tmp->next;
            tmp->next = NULL;
            // Recur for the list before pivot
            newHead = quickSortRecur(newHead, tmp);
            // Change next of last node of the left half to
            // pivot
            tmp = getTail(newHead);
            tmp->next = pivot;
        }
        // Recur for the list after the pivot element
        pivot->next = quickSortRecur(pivot->next, newEnd);
        return newHead;
    }
}

void quickSort(struct Node **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

Node *SortedMerge(Node *a, Node *b);
void FrontBackSplit(Node *source, Node **frontRef, Node **backRef);

Node *SortedMerge(Node *a, Node *b)
{
    Node *result = NULL;
    /* Base cases */
    if (a == NULL)
        return (b);

    else if (b == NULL)
        return (a);
    if (a->data.ipk <= b->data.ipk)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
};

void FrontBackSplit(Node *source, Node **frontRef, Node **backRef)
{
    Node *fast;
    Node *slow;
    slow = source;
    fast = source->next;
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
};

void MergeSort(Node **headRef)
{
    Node *head = *headRef;
    Node *a;
    Node *b;
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
};

int isEmpty(Node **head)
{
    if (*head == NULL)
    {
        cout << "LinkedList kosong" << endl;
        return 1;
    }
    else
        return 0;
}

void printData(Node *head)
{
    isEmpty(&head);
    while (head != NULL)
    {
        cout << "Nama Mahasiswa : " << head->data.nama << " ";
        cout << "Nama Prodi : " << head->data.prodi << " ";
        cout << "IPK : " << head->data.ipk << " " << endl;
        head = head->next;
    }
}

void addFirst(Node **head)
{
    Node *nodeBaru = new Node;
    cout << "Masukan Nama : ";
    fflush(stdin);
    getline(cin, nodeBaru->data.nama);
    cout << "Masukan Prodi : ";
    fflush(stdin);
    getline(cin, nodeBaru->data.prodi);
    cout << "Masukan IPK : ";
    cin >> nodeBaru->data.ipk;
    nodeBaru->next = *head;
    *head = nodeBaru;
}

void addLast(Node **head)
{
    Node *nodeBaru = new Node();
    cout << "Masukan Nama : ";
    fflush(stdin);
    getline(cin, nodeBaru->data.nama);
    cout << "Masukan Prodi : ";
    fflush(stdin);
    getline(cin, nodeBaru->data.prodi);
    cout << "Masukan IPK : ";
    cin >> nodeBaru->data.ipk;
    nodeBaru->next = NULL;

    if (*head == NULL)
    {
        *head = nodeBaru;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = nodeBaru;
}

void deleteFirst(Node **head)
{
    if (*head == NULL)
    {
        cout << "LinkedList kosong" << endl;
        return;
    }
    *head = (*head)->next;
}

void deleteLast(Node **head)
{
    if (*head == NULL)
    {
        cout << "LinkedList kosong" << endl;
        return;
    }
    if ((*head)->next == NULL)
    {
        *head = NULL;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = NULL;
}

void updateData(Node **head)
{
    if (*head == NULL)
    {
        cout << "LinkedList kosong" << endl;
        return;
    }
    string nama;
    cout << "Masukan data nama yang akan diubah : ";
    fflush(stdin);
    getline(cin, nama);
    Node *temp = (*head);
    while (temp != NULL)
    {
        if (temp->data.nama == nama)
        {
            cout << "Masukan data nama yang baru : ";
            cin >> temp->data.nama;
            cout << "Masukan data prodi yang baru : ";
            cin >> temp->data.prodi;
            cout << "Masukan data ipk yang baru : ";
            cin >> temp->data.ipk;
            cout << "Data berhasil diubah" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Data tidak ditemukan" << endl;
}

int main()
{
    struct Node *HEAD = NULL;
    int menu;
    int arr[lenght(HEAD)];
    while (menu != 12)
    {
        cout << "==== MENU ====" << endl;
        cout << "1. Tambah Data Pertama" << endl;
        cout << "2. Tambah Data Terakhir" << endl;
        cout << "3. Hapus Data Pertama" << endl;
        cout << "4. Hapus Data Terakhir" << endl;
        cout << "5. Update Data" << endl;
        cout << "6. Tampilkan Data" << endl;
        cout << "7. Sorting Data Merge" << endl;
        cout << "8. Sorting Data Quick" << endl;
        cout << "9. Sorting Data Shell" << endl;
        cout << "10. Exit Program" << endl;
        cout << "Masukkan Pilihan: ";
        cin >> menu;
        
        switch (menu)
        {
        case 1:
            addFirst(&HEAD);
            break;
        case 2:
            addLast(&HEAD);
            break;
        case 3:
            deleteFirst(&HEAD);
            break;
        case 4:
            deleteLast(&HEAD);
            break;
        case 5:
            updateData(&HEAD);
            break;
        case 6:
            printData(HEAD);
            break;
        case 7:
            MergeSort(&HEAD);
            break;
        case 8:
            quickSort(&HEAD);
            break;
        case 9:
            linkedList2Array(HEAD,arr);
            shellSort(arr, lenght(HEAD));
            array2LinkedList(HEAD,arr);
            break;
        default:
            cout << "Pilihan Tidak Ada" << endl;
        }
    }
    return 0;
}
