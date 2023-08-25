#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *at;
    int siz;
} atribute;

typedef struct
{
    atribute *lh;// left hand
    int nblh;
    atribute *rh;// right hand
    int nbrh;
} FD;

atribute getAT()
{
    atribute res;
    char *buff;
    char c;
    int i = 0;
    buff = (char *)malloc(sizeof(char));
    while (c != '\n')
    {
        scanf("%c", &c);
        if (c != '\n'){
        buff = (char *)realloc(buff, (i+1) * sizeof(char));
        buff[i] = c;
        i++;
        }
    }
    buff[i] = '\0';
    res.at = buff;
    res.siz = i;
    return res;
}

int variabl = 1;// used to print the achieved number in filling DF's hands

FD getfd(atribute *Re,int nbr)
{
    FD toRes;
    int j = 1;
    int hds=1;
    atribute test;

    // ********Get left hand of FD*********
    printf("\t\tLeft hand [%d]: \n", variabl);
    toRes.lh = (atribute *)malloc(j * sizeof(atribute));
    toRes.nblh = 0;
    j++;
    if(!toRes.nblh)// first fill obligatory
    {
        do
        {
            printf("Left hand(x to stop)(1):");
            test=getAT();
            if(!strcmp(test.at,"x"))
                printf("\tYou have to add minimum one attribute!\n");
            else if(check(test,Re,nbr))
                printf("\tNot declared attribute!\n");
        }
        while(check(test,Re,nbr) || !strcmp(test.at,"x") || !check(test,toRes.lh,toRes.nblh));
        if(strcmp(test.at,"x"))
        {
            toRes.lh[0]=test;
            // printf("%s is added ", toRes.lh[0].at);
            toRes.nblh++;
            hds++;
        }
    }
    // *******in case u wanna add elements (optional)********
    do
    {
        do
        {
            printf("Left hand(x to stop)(%d):",hds);
            test=getAT();
            if(strcmp(test.at,"x") && check(test,Re,nbr))
                printf("\tNot declared attribute!\n");
            else if(!check(test,toRes.lh,toRes.nblh))
                printf("\tDuplicate attribute!\n");
        }
        while(check(test,Re,nbr) && strcmp(test.at,"x") || !check(test,toRes.lh,toRes.nblh));
        if(strcmp(test.at,"x"))
        {
            toRes.lh = (atribute *)realloc(toRes.lh, j * sizeof(atribute));
            toRes.lh[j - 1] =test;
            // printf("%s is added ", toRes.lh[j - 1].at);
            toRes.nblh++;
            j++;
            hds++;
        }
        else
            break;
    }
    while (1);

    hds=1;
    j = 1;
    // *********Get right hand of FD*********
    printf("\t\tRight hand [%d]: \n", variabl);
    toRes.rh = (atribute *)malloc(sizeof(atribute));
    toRes.nbrh = 0;
    j++;
    if(!toRes.nbrh)// first fill obligatory
    {
        do
        {
            printf("Right hand(x to stop)(1):");
            test=getAT();
            if(!strcmp(test.at,"x"))
                printf("\tYou have to add minimum one attribute!\n");
            else if(check(test,Re,nbr))
                printf("\tNot declared attribute!\n");
        }
        while(check(test,Re,nbr) || !strcmp(test.at,"x"));
        if(strcmp(test.at,"x"))
        {
            toRes.rh[0]=test;
            // printf("%s is added ", toRes.rh[0].at);
            toRes.nbrh++;
            hds++;
        }
    }
    // in case u wanna add elements (optional)
    do
    {
        do
        {
            printf("Right hand(x to stop)(%d):",hds);
            test=getAT();
            if(strcmp(test.at,"x") && check(test,Re,nbr))
                printf("\tNot declared attribute!\n");
            else if(!check(test,toRes.rh,toRes.nbrh))
                printf("\tDuplicate attribute!\n");
        }
        while(check(test,Re,nbr) && strcmp(test.at,"x") || !check(test,toRes.rh,toRes.nbrh));
        if(strcmp(test.at,"x"))
        {
            toRes.rh = (atribute *)realloc(toRes.rh, j * sizeof(atribute));
            toRes.rh[j - 1] =test;
            // printf("%s is added ", toRes.rh[j - 1].at);
            toRes.nbrh++;
            j++;
            hds++;
        }
        else
            break;
    }
    while (1);
    variabl++;
    return toRes;
}

void showFD(FD *toShow, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        // *********Show the Left hand*********
        printf("\n\t");
        for (j = 0; j < toShow[i].nblh; j++)
        {
            if (j == toShow[i].nblh - 1)
                printf("%s", toShow[i].lh[j].at);
            else
                printf("%s,", toShow[i].lh[j].at);
        }
        printf(" --> ");
        // *********Show the Right hand*********
        for (j = 0; j < toShow[i].nbrh; j++)
        {
            if (j == toShow[i].nbrh - 1)
                printf("%s", toShow[i].rh[j].at);
            else
                printf("%s,", toShow[i].rh[j].at);
        }
    }
}

void showrelation(atribute *RE, int nbrOfAtr)
{
    atribute *relation=RE;
    int i;
    printf("\t\tR(");
    for (i = 0; i < nbrOfAtr; i++)
        if (nbrOfAtr == 0)
            printf(")");
        else if (i == nbrOfAtr - 1)
            printf(" %s)\n\t", relation[i].at);
        else
            printf(" %s,", relation[i].at);
}

void ShowInput(atribute *closu, int nb)
{
    int i;
    printf("\t\t{");
    for (i = 0; i < nb; i++)
        if (nb == 0)
            printf("}+ = ");
        else if (i == nb - 1)
            printf(" %s}+ =", closu[i].at);
        else
            printf(" %s,", closu[i].at);
}

void ShowSet(atribute *Set, int nb)
{
    int i;
    printf("\t\t{");
    for (i = 0; i < nb; i++)
        if (nb == 0)
            printf("} = ");
        else if (i == nb - 1)
            printf(" %s}", Set[i].at);
        else
            printf(" %s,", Set[i].at);
}

//check return 0 if the attribute |To| exist in the relation |Re| else 1
int check(atribute To,atribute *Re,int nbat)
{
    int i;
    int n;
    if(nbat==0)
        n=1;
    else
        n=nbat;
    for(i=0; i<nbat; i++)
        if(!strcmp(To.at,Re[i].at))
            return  0;
    return 1;
}

atribute *closure(FD* A,int n,atribute *B,int m)
{
    int i,j,add,a=m;
    atribute *res=malloc(m*sizeof(atribute));
    for(i=0; i<a; i++) //First of all add attributes of what we wanna calculate the closure to the set
        res[i]=B[i];
    int moved=1;
    while(moved)//while we add an attribute to the set search if it help to add another one else break
    {
        moved=0;
        for(i=0; i<n; i++)
        {
            add=0;
            for(j=0; j<A[i].nblh; j++)
            {
                if(check(A[i].lh[j],res,a))
                {
                    add=0;
                    break;
                }
                else
                    add=1;
            }
            if(add)
                for(j=0; j<A[i].nbrh; j++)
                {
                    if(check(A[i].rh[j],res,a))
                    {
                        a++;
                        res=(atribute *)realloc(res,a* sizeof(atribute));
                        res[a-1]=A[i].rh[j];
                        moved=1;
                    }
                }
        }
    }
    res->siz=a;
    return res;
}

int main()
{
    int i = 0, j = 1;
    int nbrOfAtr = 0; // the number of attributes
    int nbrOfFD = 0;  // the number of FD
    char stp;
    atribute testAT;
    FD testFD;
    atribute *RE = malloc(sizeof(atribute)); // the relation
    FD *functionDe = malloc(sizeof(FD));     // the function Dependency
    int neew=2;//print the number of added atribute

    // *********Add atribut*********
    do
    {
        if(!nbrOfAtr)
            do
            {
                printf("Add attribute (x to stop)!(1): ");
                testAT = getAT();
                if(!strcmp(testAT.at,"x") || testAT.at[0]=='\0' || testAT.at[0]==' ')
                    printf("\tYou have to add minimum one att!\n");
                else if (strcmp(testAT.at,"x") && testAT.at[0]!='\0' && testAT.at[0]!=' ')
                {
                    RE[nbrOfAtr] = testAT;
                    nbrOfAtr++;
                    RE = (atribute *)realloc(RE, (nbrOfAtr + 1) * sizeof(atribute));
                }
            }
            while(!strcmp(testAT.at,"x") || testAT.at[0]=='\0' || testAT.at[0]==' ');
        else
        {
            printf("Add attribute (x to stop)!(%d): ",neew);
            testAT = getAT();
            if(!check(testAT,RE,nbrOfAtr))
            {
                printf("\tAlready exists attribute!\n");
            }
            else if (testAT.at[0]=='\0' || testAT.at[0]==' ')
                printf("\tNot supported form!\n");
            else if (strcmp(testAT.at,"x") && testAT.at[0]!='\0' && testAT.at[0]!=' ')
            {
                RE[nbrOfAtr] = testAT;
                nbrOfAtr++;
                RE = (atribute *)realloc(RE, (nbrOfAtr + 1) * sizeof(atribute));
                neew++;
            }
        }
    }
    while (strcmp(testAT.at,"x"));

    // The relation we have
    showrelation(RE, nbrOfAtr);
printf("\n%d\n",RE->siz);
    // Filling the DF
    while(stp!='n')
    {
        testFD = getfd(RE,nbrOfAtr);
        functionDe[nbrOfFD]=testFD;
        nbrOfFD++;
        functionDe = (FD *)realloc(functionDe, (nbrOfFD + 1) * sizeof(FD));
        do
        {
            printf("\t\tWanna add a FD ?(y/n): ");
            scanf("%c",&stp);
            getchar();
        }
        while(stp!='n' && stp!='y');
    }
    //show what we have and ask for the closure to calculate
    system("cls");
    // The relation we have
    printf("\n\t\tWe have :\n");
    showrelation(RE, nbrOfAtr);
    //Show the FDs
    printf("\tand :");
    showFD(functionDe,nbrOfFD);

    int CalMembers=0;//the number of members in the set
    atribute *closu= malloc(sizeof(atribute));
    printf("\n\tGive the set {set}+ (x to stop)!: \n");
    do
    {
        if(!CalMembers)
        {
            do
            {
                printf("SET{%d}: ",CalMembers+1);
                testAT = getAT();
                if(!strcmp(testAT.at,"x"))
                    printf("\tYou have to add minimum one att!\n");
            }
            while(!strcmp(testAT.at,"x"));
        }
        else
        {
            printf("SET{%d}: ",CalMembers+1);
            testAT = getAT();
        }
        if(check(testAT,RE,nbrOfAtr) && strcmp(testAT.at,"x"))
        {
            printf("\tNot declared attribute!\n");
        }
        else if(!check(testAT,closu,CalMembers) && strcmp(testAT.at,"x"))
            printf("\tDuplicate attribute!\n");
        else if (strcmp(testAT.at,"x"))
        {
            closu[CalMembers] = testAT;
            CalMembers++;
            closu = (atribute *)realloc(closu, (CalMembers + 1) * sizeof(atribute));
            // system("cls");
        }
    }
    while (strcmp(testAT.at,"x"));

    ShowInput(closu,CalMembers);
    atribute* seet=closure(functionDe,nbrOfFD,closu,CalMembers);
    ShowSet(seet,seet->siz);
}
