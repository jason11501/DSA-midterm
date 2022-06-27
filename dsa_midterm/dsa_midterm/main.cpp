//
//  main.cpp
//  dsa_midterm
//
//  Created by jason on 25/06/2022.
//

#include "Header.h"

Student Input()
{
    Student e;
    cout << "Nhap ten hoc sinh: ";
    getline(cin, e.fullName);
    cout << "Nhap tuoi hoc sinh: ";
    cin >> e.age;
    cin.ignore();
    cout << "Nhap gioi tinh hoc vien: ";
    getline(cin, e.sex);
    cout << "Nhap diem: ";
    cin >> e.point;
    cin.ignore();

    return e;
}

Node* GetNode(Student e)
{
    Node* newNode = new Node;
    newNode->infor = e;
    newNode->nextNode = nullptr;
    return newNode;
}

void AddLast(Node*& head, Student e)
{
    Node* newNode = GetNode(e);
    if (!head)
        head = newNode;
    else
    {
        Node* temp = head;
        while (temp->nextNode)
            temp = temp->nextNode;
        temp->nextNode = newNode;
    }
}

int AveragePointFemale(Node* root)
{
    float total = 0;
    int count = 0;
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (node->infor.sex == FEMALE)
        {
            total += node->infor.point;
            count++;
        }
    }

    return total / count;
}

int GetMaxAge(Node* root)
{
    int age = 0;
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (node->infor.sex == MALE && node->infor.age > age)
            age = node->infor.age;
    }
    return age;
}

int GetMaxPoint(Node* root)
{
    int max = 0;
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (node->infor.sex == MALE && node->infor.point > max)
            max = node->infor.point;
    }
    return max;
}

ostream& operator<<(ostream& out, const Student& e)
{
    out << e.fullName << ", " << e.age << ", " << e.sex << ", " << e.point << '\n';
    return out;
}

void OutputOldest(Node* root)
{
    int maxAge = GetMaxAge(root);
    int maxPoint = GetMaxPoint(root);
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (node->infor.sex == MALE && node->infor.age == maxAge && node->infor.point == maxPoint)
            cout << node->infor;
    }
}

bool DeleteNode(Node*& root, int age)
{
    Node* before = nullptr; // = 0 || == false
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (node->infor.age > age)
        {
            //First node
            if (!before)
            {
                root = node->nextNode;
                delete node;
            }
            else
            {
                before->nextNode = node->nextNode;
                delete node;
            }
            return true;
        }

        before = node;
    }
    return false;
}

void DeleteNodeAgeGreaterThan(Node*& root, int age)
{
    while (DeleteNode(root, age));
}

void Destroy(Node* root)
{
    while (root)
    {
        Node* temp = root;
        root = root->nextNode;
        delete temp;
    }
}

void convertListToArray(Node *root, Array &a)
{
    int i = 0;
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        a[i].fullName = node->infor.fullName;
        a[i].age = node->infor.age;
        a[i].sex = node->infor.sex;
        a[i].point = node->infor.point;
        i++;
    }
}

void convertArrayToList(Array& a,Node *&root)
{
    int i = 0;
    for (Node* node = root; node != nullptr; node = node->nextNode)
    {
        if (i == a.size) break;
        node->infor.fullName = a[a.size - i - 1].fullName;
        node->infor.age = a[a.size - i - 1].age;
        node->infor.sex = a[a.size - i - 1].sex;
        node->infor.point = a[a.size - i - 1].point;
        i++;
    }
}

bool operator< (Student firstStudent, Student secondStudent)
{
    return firstStudent.point < secondStudent.point;
}

bool operator> (Student firstStudent, Student secondStudent)
{
    return firstStudent.point > secondStudent.point;
}

bool operator== (Student firstStudent, Student secondStudent)
{
    return firstStudent.point == secondStudent.point;
}

bool operator>>= (Student firstStudent, Student secondStudent)
{
    return firstStudent.age < secondStudent.age;
}

bool operator<<= (Student firstStudent, Student secondStudent)
{
    return firstStudent.fullName < secondStudent.fullName;
}

void Merge(Array& a, const int& start, const int& mid, const int& end)
{
    Array left(mid - start + 1);
    Array right(end - mid);
    for (int i = 0; i < left.size; i++)
        left[i] = a[start + i];
    for (int i = 0; i < right.size; i++)
        right[i] = a[start + i + left.size];

    int indexL = 0, indexR = 0, index = start;
    while (indexL < left.size && indexR < right.size)
    {
        if (left[indexL] < right[indexR])
            a[index] = left[indexL++];
        else if (left[indexL] > right[indexR])
            a[index] = right[indexR++];
        else if (left[indexL] == right[indexR]) // equal point
        {
            if (left[indexL] >>= right[indexR]) // greater age
                a[index] = right[indexR++];
            else if (left[indexL].age > right[indexR].age)
                a[index] = left[indexL++];
            else if (left[indexL].age == right[indexR].age)
            {
                if (left[indexL] <<= right[indexR]) // name alphabet
                    a[index] = left[indexL++];
                else if (left[indexL].fullName > right[indexR].fullName)
                    a[index] = right[indexR++];
            }
                
        }
        index++;
    }

    //Left still remains
    while (indexL < left.size)
        a[index++] = left[indexL++];

    //Right still remains
    while (indexR < right.size)
        a[index++] = right[indexR++];
}

void MergeSort(Array& a, const int& start, const int& end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(a, start, mid);
        MergeSort(a, mid + 1, end);
        Merge(a, start, mid, end);
    }
}

void MergeSort(Array& a)
{
    MergeSort(a, 0, a.size - 1);
}

Node* ReadFile(string fileName)
{
    ifstream stream(fileName);
    Node* root = nullptr;

    if (stream)
    {
        int n;
        stream >> n;
        stream.get();
        for (int i = 0; i < n; i++)
        {
            string temp;
            Student e;
            getline(stream, e.fullName, ',');
            stream.get();
            getline(stream, temp, ',');
            e.age = stoi(temp);
            stream.get();
            getline(stream, e.sex, ',');
            getline(stream, temp);
            e.point = stoi(temp);

            if ((e.fullName.length() > MAX_NAME_LENGTH) || (e.point < 0 || e.point > 100))
                continue;
            else
                AddLast(root, e);
        }
    }
    stream.close();
    return root;
}

void OutputToFile(string file, Node* root)
{
    ofstream stream(file, std::ios_base::app);// append
    if (stream)
    {
        for (Node* temp = root; temp != nullptr; temp = temp->nextNode)
            stream << temp->infor;
    }
    stream.close();
}

int main()
{
    Node* root = ReadFile("/Users/jason/Downloads/dsa_midterm/dsa_midterm/input.txt");
    
//    cout << "Nhap thong tin nhan vien can them\n";
//    Student e = Input();
    
//    AddLast(root, e);
    
//    cout << "Sinh vien gioi tinh Nam lon tuoi nhat: ";
//    OutputOldest(root);
    
//    cout << "\nĐiểm trung binh sinh vien nu: " << AveragePointFemale(root) << '\n';
//    DeleteNodeAgeGreaterThan(root, 25);
    
    Array a(7);
    convertListToArray(root, a);
    MergeSort(a);
    convertArrayToList(a, root);
    
    OutputToFile("/Users/jason/Downloads/dsa_midterm/dsa_midterm/output.txt", root);
    Destroy(root);
    return 0;
}
