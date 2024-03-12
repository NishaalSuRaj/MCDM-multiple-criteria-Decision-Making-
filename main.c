// Program to implement MCDM using WSM,WPM,AHP and TOPSIS in c


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//WSM

void wsm(double data[][10],double *weight,int a,int c)
{
    int i,j,b;
    int index[10];
    float sum[10],temp;
    for(i=0;i<a;i++)
    {
        sum[i]=0;
        for(j=0;j<c;j++)
        {
            sum[i] = sum[i] + data[i][j] * weight[j];
        }
    }
    for(i=0;i<a;i++)
    {
        index[i]=i;
    }
    printf("\n");
    for(i=0;i<a;i++)
    {
        for(j=i+1;j<a;j++)
        {
            if(sum[i] < sum[j])
            {
            	temp = sum[i];
            	sum[i]=sum[j];
            	sum[j]=temp;
            	b=index[i];
                index[i]=index[j];
                index[j]=b;
            }
        }
        if(i<a-1)
        {
            printf("alternative %d >",index[i]+1);
        }
        if(i>= a-1){
		
            printf("alternative %d ",index[i]+1);
        }

    }

}



// WPM


void wpm(double data[][10],double *weight,int a,int c)
{
    int i,j,b;
    int index[10];
    float prod[10],temp;
    for(i=0;i<a;i++)
    {
        prod[i]=1;
        for(j=0;j<c;j++)
        {
            prod[i] = prod[i] * pow(data[i][j] , weight[j]);
        }
    }
    for(i=0;i<a;i++)
    {
        index[i]=i;
    }
    printf("\n");
    for(i=0;i<a;i++)
    {
        for(j=i+1;j<a;j++)
        {
            if(prod[i] < prod[j])
            {
            	temp = prod[i];
            	prod[i]=prod[j];
            	prod[j]=temp;
            	b=index[i];
                index[i]=index[j];
                index[j]=b;
            }
        }
        if(i<a-1)
        {
            printf("alternative %d >",index[i]+1);
        }
        if(i>= a-1){
		
            printf("alternative %d ",index[i]+1);
        }

    }

}


//AHP


void normalize_data(double data[][10], double normalized[][10], int size) 
{
    double sum_col;
    int i,j;
    for (i = 0; i < size; i++) {
        sum_col = 0.0;
        for (j = 0; j < size; j++) {
            sum_col += data[j][i];
        }
        for (j = 0; j < size; j++) {
            normalized[j][i] = data[j][i] / sum_col;
        }
    }
}

void calculate_priority(double data[][10], double priority[], int size) 
{
    double normalized_data[10][10];
    int i,j;
    normalize_data(data, normalized_data, size);

    for (i = 0; i < size; i++) {
        priority[i] = 0.0;
        for (j = 0; j < size; j++) {
            priority[i] += normalized_data[i][j];
        }
        priority[i] /= size;
    }
}

double *ahp(double data[][10],int n,int m)
{
    double pairwise_data[10][10]; // Pairwise comparison data
    printf("Enter the pairwise comparison data:\n");
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &pairwise_data[i][j]);
        }
    }

    double *priority;
    priority = (double *)malloc(n*sizeof(double));
    calculate_priority(pairwise_data, priority, n);

    printf("Priority vector for alternatives:\n");
    for (i = 0; i < n; i++) {
        printf("%.4lf ", priority[i]);
    }
    printf("\n");
    return priority;
}
void ahp_cont(double data[][10],int n,int m)
{
    int i,j;
    float ci,avg,cr;
    float ri[10];
    double a3[10];
    double *weight =  ahp(data,n,m);
    float sum[10];
    ri[0]=0;
    ri[1]=0;
    ri[2]=0.58;
    ri[3]=0.9;
    ri[4]=1.15;
    ri[5]=1.24;
    ri[6]=1.32;
    ri[7]=1.41;
    ri[8]=1.45;
    ri[9]=1.49;
    
    for(i=0;i<n;i++)
    {
        sum[i]=0;
        for(j=0;j<n;j++)
        {
            sum[i] = sum[i] + data[i][j] * weight[j];
        }
    }
    for(i=0;i<n;i++)
    {
        a3[i] = sum[i]/weight[j];
    }
    int s=0;
    for(i=0;i<n;i++)
    {
        s = s + a3[i];
    }
    avg = s/n;
    ci = (avg - m)/(m-1);
    cr=ci/ri[n+1];
    if(cr > 0.1)
    {
        printf("Consistency is met ");
        wpm(data,weight,n,m);
    }
    else{
        printf("consistency is not met");
    }

}


//topsis

 void topsis(double data[][10],double *weight,int n,int m)
 {
        double ideal[10] ;
        double negativeIdeal[10];
        int i,j;
        // Calculate ideal and negative ideal solution
        for (j = 0; j < m; j++) {
            double max = 0;
            double min = 0;
            for (i = 0; i < n; i++) {
                if (data[i][j] > max) 
                    max = data[i][j];
                if (data[i][j] < min) 
                    min = data[i][j];
            }
            ideal[j] = max;
            negativeIdeal[j] = min;
        }

        // Calculate TOPSIS score
        double scores[n];
        for (i = 0; i < n; i++) {
            double sumOfSquareIdeal = 0.0;
            double sumOfSquareNegativeIdeal = 0.0;
            for (j = 0; j < m; j++) {
                sumOfSquareIdeal += pow(data[i][j] - ideal[j], 2);
                sumOfSquareNegativeIdeal += pow(data[i][j] - negativeIdeal[j], 2);
            }
            scores[i] = sqrt(sumOfSquareIdeal) / (sqrt(sumOfSquareIdeal) + sqrt(sumOfSquareNegativeIdeal));
        }
        printf("score vector for alternatives:\n");
    for (i = 0; i < n; i++) {
        printf("%.4lf ", scores[i]);
    }
    printf("\n");
        
    }


int main()
{
    int a,c,i,j;
    double data[10][10];
    printf("Enter Number of Criteria : ");
    scanf("%d",&c);
    printf("\nEnter Number of Alternatives : ");
    scanf("%d",&a);
    printf("\nEnter The Criteria for the Alternatives\n ");
    for(i=0;i<a;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%lf",&data[i][j]);
        }
    }
    while(1)
    {
        printf("\n\nSelect a MCDC Technique \n\n1.WSM\n2.WPM\n3.AHP\n4.TOPSIS\n5.EXIT\n\nEnter a Choice : ");
        scanf("%d",&i);
        switch (i)
        {
            case 1 :
            {
                double weight[10];
                printf("\n Enter the Weights \n");
                for(i=0;i<c;i++)
                {
                    printf("\nweight of criteria %d : ",i+1);
                    scanf("%lf",&weight[i]);
                }
                wsm(data,weight,a,c);
                break;
            }
            case 2 :
            {
                double weight[10];
                printf("\n Enter the Weights \n");
                for(i=0;i<c;i++)
                {
                    printf("\nweight of criteria %d : ",i+1);
                    scanf("%lf",&weight[i]);
                }
                wpm(data,weight,a,c);
                break;
            }
            case 3 :
            {
                ahp_cont(data,a,c);
                break;
            }
            case 4 :
            {
                double *weight = ahp(data,a,c);
                topsis(data,weight,a,c);
                break;
            }
            case 5 :
            {
                printf("Exiting....");
                exit(0);
            }
            default:
            printf("\nEnter Valid Choice......\n");
            break;
        }
    }
    return 0;
}
