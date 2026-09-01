/*
const int MAXN = 200005;
int nxt[MAXN], prv[MAXN];

// Construir la lista 1,2,...,n con centinelas en 0 y n+1
for(int i = 0; i <= n; i++) nxt[i] = i + 1;
for(int i = 1; i <= n + 1; i++) prv[i] = i - 1;

// Borrar el elemento v en O(1)  <- desenlazar
void borrar(int v){
nxt[prv[v]] = nxt[v];
prv[nxt[v]] = prv[v];
}

// Recorrer la lista viva:
for(int i = nxt[0]; i != n + 1; i = nxt[i]) cout << i << " ";
*/


/*
Invierte
ListNode* reverse(ListNode* head){
ListNode *prev = nullptr, *curr = head;
while(curr){
ListNode* next = curr->next;  // guardo el siguiente ANTES de romper
curr->next = prev;            // doy vuelta la flecha
prev = curr;                  // avanzo prev
curr = next;                  // avanzo curr
}
return prev;                      // prev quedó en el último nodo = nueva cabeza
}
*/



/*
La tortuga y la liebre
ListNode *slow = head, *fast = head;
while(fast && fast->next){
slow = slow->next;
fast = fast->next->next;
}
// slow = nodo medio
*/


/*
Hay ciclo ?
bool hasCycle(ListNode* head){
ListNode *slow = head, *fast = head;
while(fast && fast->next){
slow = slow->next;
fast = fast->next->next;
if(slow == fast) return true;
}
return false;
}
*/

/*
Merge de dos listas ordenadas
ListNode* merge(ListNode* a, ListNode* b){
ListNode dummy(0);
ListNode* tail = &dummy;
while(a && b){
if(a->val <= b->val){ tail->next = a; a = a->next; }
else                { tail->next = b; b = b->next; }
tail = tail->next;
}
tail->next = (a ? a : b);   // pego lo que sobre
return dummy.next;
}
*/


/*
Eliminar k-esimo desde el final
ListNode dummy(0); dummy.next = head;
ListNode *fast = &dummy, *slow = &dummy;
for(int i = 0; i < k; i++) fast = fast->next;   // abro un hueco de k
while(fast->next){ fast = fast->next; slow = slow->next; }
ListNode* del = slow->next;
slow->next = del->next;   // slow es el ANTERIOR al que borro
delete del;
*/

/*
Pila parentesis balanceados
bool valido(const string& s){
char st[200005]; int top = 0;      // pila con array, sin STL
for(char c : s){
if(c=='(' || c=='[' || c=='{') st[top++] = c;
else{
if(top == 0) return false;              // cierre sin apertura
char o = st[--top];
if((c==')' && o!='(') || (c==']' && o!='[') || (c=='}' && o!='{'))
return false;
}
}
return top == 0;                                 // no deben quedar abiertos
}
*/


/*
Cola circular con array
int q[MAXN], front = 0, rear = 0, sz = 0;
void enqueue(int x){ q[rear] = x; rear = (rear + 1) % MAXN; sz++; }
int  dequeue(){ int x = q[front]; front = (front + 1) % MAXN; sz--; return x; }
bool empty(){ return sz == 0; }
*/
