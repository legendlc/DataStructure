#include <cstdio>
#include <set>
using namespace std;

bool isValid(int* vec, int number, int ssize)
{
    set<int> inStack;
    set<int> popped;
    set<int> notPushed;
    //at the beginning, all elements are outside
    for(int i = 0; i < number; i++)
    {
        notPushed.insert(i+1);
    }
    //once we pop a element, we know that
    //any element smaller than it is either has been poped or still in stack
    //any element bigger than it hasn't been pushed
    //and size of inStack can't be larger than stackSize
    for(int i = 0; i < number; i++)
    {
        int tmp = vec[i];
        //remove from unknown, add to popped
        if(notPushed.find(tmp) != notPushed.end())
            notPushed.erase(tmp);
        else if(inStack.find(tmp) != inStack.end())
            inStack.erase(tmp);
        else
            return false;
        if(popped.find(tmp) != popped.end())
            return false;
        popped.insert(tmp);
        for(int k = 1; k < tmp; k++)
        {
            if(inStack.find(k) == inStack.end())
            {  // k not in stack
                if(notPushed.find(k) != notPushed.end())
                {  // k should be in stack
                    notPushed.erase(k);
                    inStack.insert(k);
                }
                else // k should be in popped
                {
                    if(popped.find(k) == popped.end())
                        return false;  //fail
                }
            }
        }
        if(inStack.size() >= ssize)
            return false;
        for(int k = tmp + 1; k <= number; k++)
        {
            if(notPushed.find(k) == notPushed.end())
            {
                if(popped.find(k) == popped.end())
                    return false;
            }
        }
    }
    return true;
}

int main()
{
    int stackSize, number, times;
    scanf("%d%d%d", &stackSize, &number, &times);
    int* vec = new int[number];
    for(int i = 0; i < times; i++)
    {
        for(int j = 0; j < number; j++)
        {
            scanf("%d", &(vec[j]));
        }

        bool res = isValid(vec, number, stackSize);
        if(res == true)
            printf("YES");
        else
            printf("NO");
        if(i < times - 1)
            printf("\n");
    }
    delete[] vec;
    return 0;
}
