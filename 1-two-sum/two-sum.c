#define TABLE_SIZE 20011
typedef struct HashNode{
    int key;
    int value;
    struct HashNode* next;
}HashNode;
 int hashfunction(int key){
    return (key>0 ? key : -key) % TABLE_SIZE;
 }
HashNode* search(HashNode* head, int key){
    HashNode* cur = head;
    while(cur!=NULL){
        if(cur->key == key){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // malloc result array
    int* result = malloc(2 * sizeof(int));
    if (result == NULL){
        return NULL;
    } 
    // init hash table
    HashNode* table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++){
        table[i] = NULL;
    }
    int needed = 0;
    for(int i = 0; i < numsSize ; i++){
        // Needed
        int needed = target - nums[i];
        int needed_hash = hashfunction(needed);
        // Search
        HashNode* head = table[needed_hash];
        HashNode* result_node = search(head, needed);
        if(result_node!=NULL){
                result[0] = i;
                result[1] = result_node->value;
                *returnSize = 2;
                return result;
        }
        // Insert: nums[i]
        int nums_hash = hashfunction(nums[i]);
        HashNode* new_node = malloc(sizeof(HashNode));
        new_node->key = nums[i];
        new_node->value = i;
        new_node->next = table[nums_hash];
        table[nums_hash] = new_node;
    }
    // not fount
    *returnSize = 0;
    return NULL;
}