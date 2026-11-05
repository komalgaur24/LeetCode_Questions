int cmpFunc(const void* a, const void* b)
{ return *(int*)a - *(int*)b; }

int findTheDistanceValue(
    int* arr1, int arr1Size,
    int* arr2, int arr2Size,
    int d
) {
    int result=0, i, l, r, m, flag;

    qsort(arr2, arr2Size, sizeof(int), cmpFunc);
    for(i=0; i<arr1Size; i++) {
        for(l=0,r=arr2Size,m=(l+r)/2,flag=1; l<r; m=(l+r)/2) {
            if(abs(arr1[i]-arr2[m])<=d){ flag=0; break; }
            if(arr1[i]<arr2[m]){ r=m; }else{ l=m+1; }
        } result+=flag;
    }

    return result;
}