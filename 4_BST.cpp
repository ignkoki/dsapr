#include <iostream>
#include <cstring>
using namespace std;

struct node
{
    char k[20];
    char m[20];
    node* left;
    node* right;
};

class dict
{
public:
    node* root;
    void create();
    void disp(node* root);
    void insert(node* root, node* temp);
    int search(node* root, const char* k);
    int update(node* root, const char* k);
    node* del(node* root, const char* k);
    node* findMin(node* root);
};

void dict::create()
{
    node* temp;
    int ch;

    do
    {
        temp = new node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;

        temp->left = NULL;
        temp->right = NULL;

        if (root == NULL)
        {
            root = temp;
        }
        else
        {
            insert(root, temp);
        }

        cout << "\nDo you want to add more keywords? (1/0): ";
        cin >> ch;
    } while (ch == 1);
}

void dict::insert(node* root, node* temp)
{
    if (strcmp(temp->k, root->k) < 0)
    {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    }
    else
    {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

void dict::disp(node* root)
{
    if (root != NULL)
    {
        disp(root->left);
        cout << "\nKey Word: " << root->k;
        cout << "\tMeaning: " << root->m;
        disp(root->right);
    }
}

int dict::search(node* root, const char* k)
{
    int comparisons = 0;

    while (root != NULL)
    {
        comparisons++;

        if (strcmp(k, root->k) == 0)
        {
            cout << "\nNo of Comparisons: " << comparisons;
            return 1;
        }
        else if (strcmp(k, root->k) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return -1;
}

int dict::update(node* root, const char* k)
{
    while (root != NULL)
    {
        if (strcmp(k, root->k) == 0)
        {
            cout << "\nEnter the new meaning of the keyword " << root->k << ": ";
            cin >> root->m;
            return 1;
        }
        else if (strcmp(k, root->k) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return -1;
}

node* dict::del(node* root, const char* k)
{
    if (root == NULL)
    {
        cout << "\nElement not found";
        return root;
    }

    if (strcmp(k, root->k) < 0)
    {
        root->left = del(root->left, k);
        return root;
    }
    else if (strcmp(k, root->k) > 0)
    {
        root->right = del(root->right, k);
        return root;
    }

    if (root->left == NULL && root->right == NULL)
    {
        delete root;
        return NULL;
    }
    else if (root->right == NULL)
    {
        node* temp = root;
        root = root->left;
        delete temp;
        return root;
    }
    else if (root->left == NULL)
    {
        node* temp = root;
        root = root->right;
        delete temp;
        return root;
    }
    else
    {
        node* temp = findMin(root->right);
        strcpy(root->k, temp->k);
        strcpy(root->m, temp->m);
        root->right = del(root->right, temp->k);
        return root;
    }
}

node* dict::findMin(node* root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

int main()
{
    int ch;
    dict d;
    d.root = NULL;

    do
    {
        cout << "\nMenu\n1. Create\n2. Display\n3. Search\n4. Update\n5. Delete\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1:
                d.create();
                break;
            case 2:
                if (d.root == NULL)
                {
                    cout << "\nNo keywords in the dictionary.";
                }
                else
                {
                    cout << "\nDictionary Contents:";
                    d.disp(d.root);
                }
                break;
            case 3:
                if (d.root == NULL)
                {
                    cout << "\nDictionary is empty. Add keywords first.";
                }
                else
                {
                    cout << "\nEnter the keyword you want to search: ";
                    char k[20];
                    cin >> k;
                    if (d.search(d.root, k) == 1)
                        cout << "\nKeyword Found.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 4:
                if (d.root == NULL)
                {
                    cout << "\nDictionary is empty. Add keywords first.";
                }
                else
                {
                    cout << "\nEnter the keyword whose meaning you want to update: ";
                    char k[20];
                    cin >> k;
                    if (d.update(d.root, k) == 1)
                        cout << "\nMeaning Updated.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 5:
                if (d.root == NULL)
                {
                    cout << "\nDictionary is empty. Add keywords first.";
                }
                else
                {
                    cout << "\nEnter the keyword you want to delete: ";
                    char k[20];
                    cin >> k;
                    d.root = d.del(d.root, k);
                }
                break;
            default:
                cout << "\nInvalid choice.";
                break;
        }
    } while (ch <= 5);

    return 0;
}
