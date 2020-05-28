#include <iostream>
#include<string.h>
#include <iomanip>
#include <fstream>

using namespace std;

typedef struct tree
{
    char id;
    struct tree *left;
    struct tree *right;
} tree;

tree *Term();
tree *Atom();
tree *Form();

char s[100];
int i = 0;

tree *Form()
{
    tree *new_node = Term();
    while (s[i] == '+')
    {
        tree *p = new tree;
        p->id = '+';
        p->left = new_node;
        i++;
        p->right = Term();
        new_node = p;
    }
    return new_node;
}

tree *Term()
{
    tree *new_node = Atom();
    while(s[i] == '*')
    {
        tree *p = new tree;
        p->id = '*';
        p->left = new_node;
        i++;
        p->right = Atom();
        new_node = p;
    }
    return new_node;
}

tree *Atom()
{
    tree *new_node = new tree;
    new_node->left = NULL;
    new_node->right = NULL;
    if (s[i] == '0' || s[i] == '1')
    {
        new_node->id = s[i];
        i++;
    }
    if (s[i] == '!')
    {
        new_node->id = s[i];
        i++;
        new_node->left = Atom();
        new_node->right = NULL;
    }
    if (s[i] == '(')
    {
        i++;
        new_node = Form();
        i++;
    }
    return new_node;
}

bool result(tree *radix)
{
    if (radix)
    {
        if (radix->id == '0')
            return false;
        if (radix->id == '1')
            return true;
        if (radix->id == '+')
            return result(radix->left) + result(radix->right);
        if (radix->id == '*')
            return result(radix->left) * result(radix->right);
        if (radix->id == '!')
            return !result(radix->left);
    }
}

void show(tree* &radix, int n)
{
    if (radix)
    {
        show(radix->left, n + 1);
        cout << setw(3 * n) << radix->id << endl;
        show(radix->right, n + 1);
    }
}

int main()
{
    ifstream fin("input.txt");
    fin.getline(s, 100);
    fin.close();
    tree *new_node = Form();
    show(new_node, 1);
    cout << endl;
    cout << "Answer: " << result(new_node) << endl;
    return 0;
}
