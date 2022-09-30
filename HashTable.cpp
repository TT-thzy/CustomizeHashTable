#include <string.h>
#include <malloc.h>
#include <stdio.h>

#define HASHSIZE 5

typedef struct Node
{
    /* data */
    char *key;       //key值
    char *value;     //value值
    Node *following; //下一个结点（用于解决哈希冲突问题）
};

class HashTable
{
private:
    /* data */
    Node *node[HASHSIZE]; //哈希表初始数据（哈希表底层就是使用数组来实现）
public:
    HashTable(/* args */);
    ~HashTable();
    size_t hash(const char *key);
    Node *lookup(const char *key);
    bool install(const char *key, const char *value);
    const char *get(const char *key);
    void display();

private:
    char *strdup(const char *str); //给每个节点分配空间
};

/*
method:构造方法
param:null 
*/
HashTable::HashTable(/* args */)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        /* code */
        node[i] = nullptr;
    }
}
/*
method:析构方法
param:null 
*/
HashTable::~HashTable()
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        /* code */
        Node *next = node[i];
        while (next)
        {
            /* code */
            Node *temp = next->following; //临时空间存储链表中的下一个节点
            //清空
            next->key = nullptr;
            next->value = nullptr;
            next->following = nullptr;
            next = temp;
        }
    }
}
/*
method:为每个节点分配空间
param:const char *str 
*/
char *HashTable::strdup(const char *str)
{
    int len = strlen(str) + 1;
    char *ns = (char *)malloc(len * sizeof(char));
    strcpy(ns, str);
    if (ns == nullptr)
        return nullptr;
    else
        return ns;
}
/*
method:hash算法 （time33算法：给每个字符*33）
param:const char *key 
*/
size_t HashTable::hash(const char *key)
{
    size_t hash = 0;
    while (*key)
    {
        hash += (hash << 5) + (*key++);
    }
    return hash % HASHSIZE;
}
/*
method:根据key查找结点Node
param:const char *key 
思路：首先是用Hash函数计算头地址，然后根据头地址向下一个个去查找结点，如果结点的key和查找的key值相同，则匹配成功
*/
Node *HashTable::lookup(const char *key)
{
    Node *tmp;
    size_t index;
    index = hash(key);
    for (tmp = node[index]; tmp; tmp = tmp->following)
    {
        /* code */
        if (strcmp(key, tmp->key) == 0)
        {
            /* code */
            return tmp;
        }
    }
    return NULL;
}
/*
method:插入
param:const char* key,const char* value
思路：首先是查看该key值的结点是否存在，如果存在则更改value值就好，如果不存在，则插入新结点。
*/
bool HashTable::install(const char *key, const char *value)
{
    size_t index;
    Node *np;
    if (!(np = lookup(key)))
    {   //哈希表中无此key
        index = hash(key);
        np = (Node *)malloc(sizeof(Node));
        if (!np)
            return false;
        np->key = strdup(key);
        if (np->key == nullptr)
            return false;
        //头插法
        np->following = node[index]; //设置新节点的下一个节点
        node[index] = np;            //把新节点设置为头结点
        //尾插法
        
    }
    else
    {
        free(np->value);
    }
    np->value = strdup(value);
    if (np->key == nullptr)
        return false;
    return true;
}
/*
method:打印
param:const char* key,const char* value
*/
void HashTable::display()
{
    Node *temp;
    for (int i = 0; i < HASHSIZE; ++i)
    {
        if (!node[i])
        {
            printf("[]\n");
        }
        else
        {
            printf("[");
            for (temp = node[i]; temp; temp = temp->following)
            {
                printf("[%s][%s] ", temp->key, temp->value);
            }
            printf("]\n");
        }
    }
}

void testHash(HashTable *ht)
{
    const char *key[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};
    const char *value[] = {"value1", "value2", "value3", "value4", "value5", "value6", "value7", "value8", "value9", "value10", "value11"};
    for (int i = 0; i < 11; ++i)
    {
        ht->install(key[i], value[i]);
    }
}
int main(int argc, char const *argv[])
{
    HashTable ht;
    testHash(&ht);
    ht.display();
    return 0;
}
