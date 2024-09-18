#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 50
typedef struct albero{
    int nodo;
    struct albero* left;
    struct albero* right;
    struct albero* padre;
    char colore;
}albero_t;
typedef albero_t* tree;
typedef struct nodo{ 
    int dato;
    tree root;
    struct nodo *next;
} nodo_t;
typedef nodo_t * Ptr_nodo;
#define INT_MAX 2147483647

Ptr_nodo aggiungistazione(Ptr_nodo, int, int*, tree);
void aggiungiauto(Ptr_nodo*, int, int, tree, int*);
void demoliscistazione(Ptr_nodo*, int, tree);
void inseriscirbtree(tree*, tree, int);
void rbinsertfixup(tree*, tree, tree);
void leftrotate(tree*,tree, tree);
void rightrotate(tree*,tree,tree);
void freerbtree(tree*,tree);
void eliminarbtree(tree*,tree,tree);
void rbtransplant(tree*,tree,tree,tree);
tree minimumtree(tree,tree);
tree maximumtree(tree,tree);
void visitaspecifica(int,Ptr_nodo,tree);
void visita(tree,tree);
void scorri(Ptr_nodo);
void rbdeletefixup(tree*,tree, tree);
tree searchtree(tree*, tree, int);
Ptr_nodo inseriscihead(Ptr_nodo, int);
Ptr_nodo inseriscicoda(Ptr_nodo, int);
void rottamaauto(Ptr_nodo*, int, int,tree);
void treedelete(tree*,tree,tree);
void transplant (tree*,tree,tree,tree);
void pianificapercorsofake(Ptr_nodo*,int,int,tree);
void percorsodadx(Ptr_nodo,Ptr_nodo,tree);
void percorsodasx(Ptr_nodo,Ptr_nodo,tree);
void stampafinale(Ptr_nodo);
void ricorrenzasx(Ptr_nodo,Ptr_nodo*,Ptr_nodo, Ptr_nodo,int,int*,tree);
void ricorrenzadx(Ptr_nodo,Ptr_nodo*,Ptr_nodo, Ptr_nodo,int,int*,tree);
Ptr_nodo preclist(Ptr_nodo,Ptr_nodo);
Ptr_nodo distruggilista(Ptr_nodo);
void pianificapercorso(Ptr_nodo,int,int,tree);
void inavanti(Ptr_nodo, Ptr_nodo, tree);
void inindietro(Ptr_nodo, Ptr_nodo, tree);
Ptr_nodo rimuovilista(Ptr_nodo, int);
Ptr_nodo inserisciinordine(Ptr_nodo, int);

int main(){
    char stringa[DIM+1];
    int i, dimaggiunta, kmstazione, autmacchina, stazuno, stazdue;
    int search;
    int* flag;
    Ptr_nodo head=NULL;
    tree tnil;
    tree root;
    tnil=malloc(sizeof(albero_t));
    tnil->colore='b';
    tnil->nodo=0;
    while((scanf("%s",stringa))==1){
        //PARTE VISITA (INUTILE PER PROGETTO)
        if(!strcmp(stringa,"visitaspecifica")){
            if(scanf("%d",&search)){};
            visitaspecifica(search,head,tnil);
        }
        if(!strcmp(stringa,"stampa")){
            visita(head->root,tnil);
        }
        if(!strcmp(stringa,"scorri")){
            scorri(head);
        }
        if(!strcmp(stringa,"cercaalbero")){
            printf("metti valore da cercare\n");
            if(scanf("%d",&search)){};
            root=searchtree(&(head->root),tnil,search);
            printf("Il dato è %d\n",root->nodo);
        }
        //
        //PARTE AGGIUNGI.STAZIONE
        if(!strcmp(stringa,"aggiungi-stazione")){
            if(scanf("%d",&kmstazione)){}; //printf("Chiamerei aggiungistazione con %d",kmstazione);
            flag=malloc(sizeof(int));
            *flag=1;
            head=aggiungistazione(head,kmstazione,flag,tnil);
            if(*flag){
                if(scanf("%d",&dimaggiunta)){};   //printf("%d ",kmstazione); 
                for (i=0;i<dimaggiunta;i++){
                    if(scanf("%d",&autmacchina)){}; //printf("Chiamerei aggiungiauto con %d",autmacchina);
                    aggiungiauto(&head,kmstazione,autmacchina,tnil,flag);
                }
            }
            else{
                if(scanf("%d",&dimaggiunta)){}
                for (i=0;i<dimaggiunta;i++){
                    if(scanf("%d",&autmacchina)){}
                }
            }
            free(flag);
        }
        //PARTE AGGIUNGI.AUTO 
        if(!strcmp(stringa,"aggiungi-auto")){
            flag=malloc(sizeof(int));
            *flag=0;
            if(scanf("%d",&kmstazione)){}; 
            if(scanf("%d",&autmacchina)){};
            aggiungiauto(&head,kmstazione,autmacchina,tnil,flag);
            free(flag);
        }
        //PARTE ROTTAMA.AUTO
        if(!strcmp(stringa,"rottama-auto")){
            if(scanf("%d",&kmstazione)){}; 
            if(scanf("%d",&autmacchina)){};
            rottamaauto(&head,kmstazione,autmacchina,tnil);
        }
        //PARTE DEMOLISCI.STAZIONE
        if(!strcmp(stringa,"demolisci-stazione")){
            if(scanf("%d",&kmstazione)){};
            demoliscistazione(&head,kmstazione,tnil);
        }
        //PARTE PIANIFICA.PERCORSO
        if(!strcmp(stringa,"pianifica-percorso")){
            if(scanf("%d",&stazuno)){};
            if(scanf("%d",&stazdue)){};
            pianificapercorso(head,stazuno,stazdue,tnil);
        }
    }
    return 0;
}

Ptr_nodo aggiungistazione(Ptr_nodo head, int kmstazione, int* flag,tree tnil){
    if (!head || head->dato > kmstazione){
        printf("aggiunta\n");
        head=inseriscihead(head,kmstazione);
        head->root=tnil;
        return head;
    }
    if(head->dato==kmstazione){
        printf("non aggiunta\n");
        *flag=0;
        return head;
    }
    head->next = aggiungistazione(head->next, kmstazione, flag, tnil);
    return head;
}

Ptr_nodo inseriscihead(Ptr_nodo head, int n){
    Ptr_nodo tmp;
    tmp = malloc(sizeof(nodo_t)); 
    if(tmp != NULL){
        tmp->dato = n;
        tmp->next = head;
        head=tmp;
    } 
    return head;
}

void aggiungiauto(Ptr_nodo* head, int kmstazione,int autmacchina,tree tnil,int* flag){ 
    int found;
    found=0;
    while((*head) && !found){
        if((*head)->dato == kmstazione) 
            found = 1;
        else
            head = &((*head)->next);
    }
    if(found){
        inseriscirbtree(&((*head)->root),tnil,autmacchina);
        if(!(*flag)){
            printf("aggiunta\n");
        }
        //visita((*head)->root,tnil);
    }
    else printf("non aggiunta\n");
}

void scorri(Ptr_nodo head){
    while(head){
        printf("%d-",head->dato);
        head=head->next;
    }
    printf("\n");
}

void demoliscistazione(Ptr_nodo* head, int kmstazione,tree tnil){ 
    Ptr_nodo curr, prec, tmp;
    int found;
    found=0;
    tmp=malloc(sizeof(Ptr_nodo));
    curr = (*head);
    prec = NULL; 
    while(curr && ! found){
        if(curr->dato == kmstazione){ 
            found=1;
            tmp = curr;
            curr = curr->next; 
            if(prec!=NULL){
                prec->next = curr; 
            }
            else{
                (*head) = curr;
            } 
            while(tmp->root!=tnil){
                treedelete(&(tmp->root),tmp->root,tnil);
            }
        } 
        else{
            prec=curr;
            curr = curr->next;
        }
    }
    if(found){
        printf("demolita\n");
    }
    else{
        printf("non demolita\n");
    }
    free(tmp);
}

//TUTTA LA PARTE SU RB TREES
void visita(tree root,tree tnil){
    if (root!=tnil){
        printf("%d\n",root->nodo);
        printf("Figlio sinistro:\n");
        visita(root->left,tnil);
        printf("Figlio destro:\n");
        visita(root->right,tnil);
    }
}

void inseriscirbtree(tree* root, tree tnil, int autmacchina){
    tree x,y,z;
    z=malloc(sizeof(albero_t));
    z->nodo=autmacchina;
    y=tnil;
    x=(*root);
    while(x!=tnil){
        y=x;
        if (z->nodo<x->nodo){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    z->padre=y;
    if(y==tnil){
        *(root)=z;
    }
    else if(z->nodo<y->nodo){
        y->left=z;
    }
    else{
        y->right=z;
    }
    z->left=tnil;
    z->right=tnil;
    z->colore='r';
    rbinsertfixup(root,z,tnil);
}

void rbinsertfixup(tree* root, tree z,tree tnil){
    tree y;
    while(z->padre->colore=='r'){
        if(z->padre==z->padre->padre->left){
            y=z->padre->padre->right;
            if(y->colore=='r'){
                z->padre->colore='b';
                y->colore='b';
                z->padre->padre->colore='r';
                z=z->padre->padre;
            }
            else{
                if(z==z->padre->right){
                    z=z->padre;
                    leftrotate(root,z,tnil);
                }
                z->padre->colore='b';
                z->padre->padre->colore='r';
                rightrotate(root,z->padre->padre,tnil);
            }
        }
        else{
            y=z->padre->padre->left;
            if(y->colore=='r'){
                z->padre->colore='b';
                y->colore='b';
                z->padre->padre->colore='r';
                z=z->padre->padre;
            }
            else{
                if(z==z->padre->left){
                    z=z->padre;
                    rightrotate(root,z,tnil);
                }
                z->padre->colore='b';
                z->padre->padre->colore='r';
                leftrotate(root,z->padre->padre,tnil);
            }
        }
    }
    (*root)->colore='b';
}

void leftrotate(tree* root,tree x,tree tnil){
    tree y;
    y=x->right;
    x->right=y->left;
    if(y->left!=tnil){
        y->left->padre=x;
    }
    y->padre=x->padre;
    if(x->padre==tnil){
        (*root)=y;
    }
    else if(x==x->padre->left){
        x->padre->left=y;
    }
    else{
        x->padre->right=y;
    }
    y->left=x;
    x->padre=y;
}

void rightrotate(tree* root,tree x,tree tnil){
    tree y;
    y=x->left;
    x->left=y->right;
    if(y->right!=tnil){
        y->right->padre=x;
    }
    y->padre=x->padre;
    if(x->padre==tnil){
        (*root)=y;
    }
    else if(x==x->padre->right){
        x->padre->right=y;
    }
    else{
        x->padre->left=y;
    }
    y->right=x;
    x->padre=y;
}

tree searchtree(tree* root, tree tnil, int value){
    while((*root)!=tnil&&value!=(*root)->nodo){
        if(value<(*root)->nodo){
            root=(&(*root)->left);
        }
        else{
            root=(&(*root)->right);
        }
    }
    return (*root);
}

/*void eliminarbtree(tree* root,tree z,tree tnil){
    tree x,y;
    char coloreoriginale;
    y=z;
    printf("y.nodo è %d, ed il figlio sinistro è %d\n",y->nodo,y->left->nodo);
    coloreoriginale=y->colore;
    if(z->left==tnil){
        x=z->right;
        rbtransplant(root,z,z->right,tnil);
    }
    else{
        if(z->right==tnil){
            x=z->left;
            rbtransplant(root,z,z->right,tnil);
        }
        else{
            y=minimumtree(z->right,tnil);
            coloreoriginale=y->colore;
            x=y->right;
            if(y!=z->right){
                rbtransplant(root,y,y->right,tnil);
                y->right=z->right;
                y->right->padre=y;
            }
            else{
                x->padre=y;
            }
            rbtransplant(root,z,y,tnil);
            y->left=z->left;
            y->left->padre=y;
            y->colore=z->colore;
        }
    }
    free(z);
    if(coloreoriginale=='b'){
        rbdeletefixup(root,x,tnil);
    }
}*/

/*void rbtransplant(tree* root,tree u,tree v,tree tnil){
    if(u->padre==tnil){
        (*root)=v;
    }
    else{
        if(u==u->padre->left){
            u->padre->left=v;
        }
        else{
            u->padre->left=v;
        }
    }
    v->padre=u->padre;
}*/

/*void rbdeletefixup(tree* root,tree x,tree tnil){
    tree w;
    while(x!=(*root)&&x->colore=='b'){
        if(x==x->padre->left){
            w=x->padre->left;
            if(w->colore=='r'){
                w->colore='b';
                x->padre->colore='r';
                leftrotate(root,x->padre,tnil);
                w=x->padre->right;
            }
            if(w->left->colore=='b'&&w->right->colore=='b'){
                w->colore='r';
                x=x->padre;
            }
            else{
                if(w->right->colore=='b'){
                    w->left->colore='b';
                    w->colore='r';
                    rightrotate(root,w,tnil);
                    w=x->padre->right;
                }
                w->colore=x->padre->colore;
                x->padre->colore='b';
                w->right->colore='b';
                leftrotate(root,x->padre,tnil);
                x=(*root);
            }
        }
        else{
            w=x->padre->left;
            if(w->colore=='r'){
                w->colore='b';
                x->padre->colore='r';
                rightrotate(root,x->padre,tnil);
                w=x->padre->left;
            }
            if(w->right->colore=='b'&&w->left->colore=='b'){
                w->colore='r';
                x=x->padre;
            }
            else{
                if(w->left->colore=='b'){
                    w->right->colore='b';
                    w->colore='r';
                    leftrotate(root,w,tnil);
                    w=x->padre->left;
                }
                w->colore=x->padre->colore;
                x->padre->colore='b';
                w->left->colore='b';
                rightrotate(root,x->padre,tnil);
                x=(*root);
            }
        }
    }
    x->colore='b';
}*/

tree maximumtree(tree root,tree tnil){
    if(root==tnil){
        return tnil;
    }
    while(root->right!=tnil){
        root=root->right;
    }
    return root;
}

tree minimumtree(tree root,tree tnil){
    if(root==tnil){
        return tnil;
    }
    while(root->left!=tnil){
        root=root->left;
    }
    return root;
}

void rottamaauto(Ptr_nodo* head,int kmstazione, int autmacchina,tree tnil){
    int found;
    tree value;
    found=0;
    while((*head) && !found){
        if((*head)->dato == kmstazione) 
            found = 1;
        else
            head = &((*head)->next);
    }
    if(found){
        value=searchtree(&((*head)->root),tnil,autmacchina);
        if(value!=tnil){
            treedelete(&((*head)->root),value,tnil);
            //visita((*head)->root,tnil);
            printf("rottamata\n");
        }
        else{
            printf("non rottamata\n");
        }
    }
    else printf("non rottamata\n");
}

void treedelete(tree* root,tree z,tree tnil){
    tree y;
    if(z->left==tnil){
        transplant(root,z,z->right,tnil);
    }
    else{
        if(z->right==tnil){
            transplant(root,z,z->left,tnil);
        }
        else{
            y=minimumtree(z->right,tnil);
            if(y!=z->right){
                transplant(root,y,y->right,tnil);
                y->right=z->right;
                y->right->padre=y;
            }
            transplant(root,z,y,tnil);
            y->left=z->left;
            y->left->padre=y;
        }
    }
    free(z);
}

void transplant(tree* root,tree u,tree v,tree tnil){
    if(u->padre==tnil){
        (*root)=v;
    }
    else{
            if(u==u->padre->left){
                u->padre->left=v;
            }
            else{
                u->padre->right=v;
            }
    }
    if(v!=tnil){
        v->padre=u->padre;
    }
}
//

void pianificapercorsofake(Ptr_nodo* head,int uno,int due, tree tnil){
    Ptr_nodo l,r;
    l=(*head);
    r=(*head);
    while(r->dato!=due){
        r=r->next;
    }
    while(l->dato!=uno){
        l=l->next;
    }
    if (uno<due){
        percorsodasx(l,r,tnil);
    }
    else {
        if (uno>due){
        percorsodadx(l,r,tnil);
        }
        else{
            printf("%d",l->dato);
            printf("\n");
        }
    }
}

void percorsodasx(Ptr_nodo l,Ptr_nodo r,tree tnil){
    int distanza, count, max, dest;
    tree flag;
    Ptr_nodo hmin,hdef,curr,canc,prec;
    count=0;
    max=INT_MAX;
    hmin=malloc(sizeof(nodo_t));
    hdef=malloc(sizeof(nodo_t));
    hmin=NULL;
    hdef=NULL;
    distanza=r->dato-l->dato;
    flag=maximumtree(l->root,tnil);
    if(flag->nodo>=distanza){
        hdef=inseriscicoda(hdef,l->dato);
        hdef=inseriscicoda(hdef,r->dato);
        stampafinale(hdef);
    }
    else{
        if(flag->nodo<l->next->dato-l->dato){
            printf("nessun percorso\n");
        }
        else{
            hmin=inseriscicoda(hmin,l->dato);
            count=count+1;
            curr=l->next;
            while(flag->nodo>=curr->dato-l->dato&&curr!=r){
                dest=count;
                prec=hmin;
                canc=hmin->next;
                dest--;
                while(dest!=0){
                    prec=prec->next;
                    canc=canc->next;
                    dest--;
                }
                prec->next=distruggilista(canc);
                ricorrenzasx(hmin,&hdef,curr,r,count,&max,tnil);
                curr=curr->next;
            }
            if(hdef){
                stampafinale(hdef);
                printf("\n");
            }
            else{
                printf("nessun percorso\n");
            }
        }
    }
}

void ricorrenzasx(Ptr_nodo hmin, Ptr_nodo* htmp, Ptr_nodo l,Ptr_nodo r,int count,int* max,tree tnil){
    int distanza,dest;
    tree flag;
    Ptr_nodo curr,canc,prec;
    distanza=r->dato-l->dato;
    flag=maximumtree(l->root,tnil);
    if(flag->nodo>=distanza){
        count=count+2;
        if(count<(*max)){
            //printf("sto inserendo %d e %d\n",l->dato,r->dato);
            hmin=inseriscicoda(hmin,l->dato);
            hmin=inseriscicoda(hmin,r->dato);
            curr=hmin;
            if(*htmp){
                (*htmp)=distruggilista((*htmp));
                (*htmp)=malloc(sizeof(nodo_t));
                (*htmp)=NULL;
            }
            while(curr){
                (*htmp)=inseriscicoda((*htmp),curr->dato);
                curr=curr->next;
            }
            (*max)=count;
        }
    }
    else{
        if(!(flag->nodo<l->next->dato-l->dato)){
            count++;
            hmin=inseriscicoda(hmin,l->dato);
            curr=l->next;
            while(flag->nodo>=curr->dato-l->dato&&curr!=r){
                dest=count;
                prec=hmin;
                canc=hmin->next;
                dest--;
                while(dest!=0){
                    prec=prec->next;
                    canc=canc->next;
                    dest--;
                }
                prec->next=distruggilista(canc);
                ricorrenzasx(hmin,htmp,curr,r,count,max,tnil);
                curr=curr->next;
            }
        }
    }
}

void percorsodadx(Ptr_nodo l,Ptr_nodo r,tree tnil){
    int distanza, count, max,dest;
    tree flag;
    Ptr_nodo hmin,hdef,curr,canc,prec;
    count=0;
    max=INT_MAX;
    hmin=NULL;
    hdef=NULL;
    distanza=l->dato-r->dato;
    flag=maximumtree(l->root,tnil);
    if(flag->nodo>=distanza){
        hdef=inseriscicoda(hdef,l->dato);
        hdef=inseriscicoda(hdef,r->dato);
        stampafinale(hdef);
    }
    else{
        curr=preclist(l,r);
        if(flag->nodo<l->dato-curr->dato){
            printf("nessun percorso\n");
        }
        else{
            hmin=inseriscicoda(hmin,l->dato);
            count=count+1;
            while(flag->nodo>=l->dato-curr->dato&&curr!=r){
                dest=count;
                prec=hmin;
                canc=hmin->next;
                dest--;
                while(dest!=0){
                    prec=prec->next;
                    canc=canc->next;
                    dest--;
                }
                prec->next=distruggilista(canc);
                ricorrenzadx(hmin,&hdef,curr,r,count,&max,tnil);
                curr=preclist(curr,r);
            }
            if(hdef){
                stampafinale(hdef);
                printf("\n");
            }
            else{
                printf("nessun percorso\n");
            }
        }
    }
}

Ptr_nodo preclist(Ptr_nodo l, Ptr_nodo r){
    while(r->next!=l){
        r=r->next;
    }
    return r;
}

Ptr_nodo distruggilista(Ptr_nodo head){ 
    Ptr_nodo tmp;
    while(head!= NULL){
        tmp = head;
        head = head->next; 
        free(tmp);
    }
    return NULL;
}

void ricorrenzadx(Ptr_nodo hmin, Ptr_nodo* htmp, Ptr_nodo l,Ptr_nodo r,int count,int* max,tree tnil){
    int distanza,dest;
    tree flag;
    Ptr_nodo curr,prec,canc;
    distanza=l->dato-r->dato;
    flag=maximumtree(l->root,tnil);
    if(flag->nodo>=distanza){
        count=count+2;
        if(count<=(*max)){
            hmin=inseriscicoda(hmin,l->dato);
            hmin=inseriscicoda(hmin,r->dato);
            curr=hmin;
            if(*htmp){
                (*htmp)=distruggilista((*htmp));
                htmp=malloc(sizeof(nodo_t));
                (*htmp)=NULL;
            }
            while(curr){
                (*htmp)=inseriscicoda((*htmp),curr->dato);
                curr=curr->next;
            }
            (*max)=count;
        }
    }
    else{
        curr=preclist(l,r);
        if(!(flag->nodo<l->dato-curr->dato)){
            count++;
            hmin=inseriscicoda(hmin,l->dato);
            while(flag->nodo>l->dato-curr->dato&&curr!=r){
                dest=count;
                prec=hmin;
                canc=hmin->next;
                dest--;
                while(dest!=0){
                    prec=prec->next;
                    canc=canc->next;
                    dest--;
                }
                prec->next=distruggilista(canc);
                ricorrenzadx(hmin,htmp,curr,r,count,max,tnil);
                curr=preclist(curr,r);
            }
        }
    }
}

Ptr_nodo inseriscicoda(Ptr_nodo head, int n){
    Ptr_nodo tmp, prec;
    tmp = malloc(sizeof(nodo_t)); 
    tmp->dato = n;
    tmp->next = NULL;
    if(head == NULL){
        head = tmp;
    }
    else{
        prec=head;
        while(prec->next!=NULL){
            prec=prec->next;
        }
        prec->next=tmp;
    }
    return head;
}

void stampafinale(Ptr_nodo hmin){
    printf("%d",hmin->dato);
    hmin=hmin->next;
    while(hmin!=NULL){
        printf(" %d",hmin->dato);
        hmin=hmin->next;
    }
    printf("\n");
}

void visitaspecifica(int search,Ptr_nodo head,tree tnil){
    Ptr_nodo curr;
    int found;
    found=0;
    curr = head;
    while(curr && ! found){
        if(curr->dato == search){ 
            found=1; 
        } 
        else{
            curr = curr->next;
        }
    }
    if(found){
        visita(curr->root,tnil);
    }
    else{
        printf("non presente\n");
    }
}

void pianificapercorso(Ptr_nodo head,int uno,int due, tree tnil){
    Ptr_nodo l,r;
    l=head;
    r=head;
    while(r->dato!=due){
        r=r->next;
    }
    while(l->dato!=uno){
        l=l->next;
    }
    if (uno<due){
        inavanti(l,r,tnil);
    }
    else {
        if (uno>due){
        inindietro(l,r,tnil);
        }
        else{
            printf("%d",l->dato);
            printf("\n");
        }
    }
}

void inavantifirst(Ptr_nodo l, Ptr_nodo r, tree tnil){
    int max,autonomia,distanza,thistotal,heretor,flag;
    Ptr_nodo curr,save,finallist,tmp;
    flag=0;
    max=0;
    finallist=NULL;
    finallist=inseriscicoda(finallist,l->dato);
    autonomia=(maximumtree(l->root,tnil))->nodo;
    curr=l->next;
    distanza=curr->dato-l->dato;
    heretor=r->dato-l->dato;
    tmp=l;
    while(!flag){
        if(autonomia>=heretor){
            break;
        }
        while(autonomia>=distanza){
            thistotal=((maximumtree(curr->root,tnil))->nodo+curr->dato);
            if((thistotal>max)){
                if(thistotal>=r->dato){
                    if((!flag)){
                        flag=1;
                        max=thistotal;
                        save=curr;
                    }
                }
                else{
                    max=thistotal;
                    save=curr;
                }
            }
            curr=curr->next;
            distanza=curr->dato-tmp->dato;
        }
        if(max==0){
            printf("nessun percorso\n");
            return;
        }
        finallist=inseriscicoda(finallist,save->dato);
        autonomia=(maximumtree(save->root,tnil))->nodo;
        tmp=save;
        heretor=r->dato-save->dato;
        max=0;
        curr=save->next;
        distanza=curr->dato-save->dato;
    }
    finallist=inseriscicoda(finallist,r->dato);
    stampafinale(finallist);
}

void inindietro(Ptr_nodo l, Ptr_nodo r, tree tnil){
    int max,autonomia,distanza,thistotal,heretor,flag,count;
    Ptr_nodo curr,save,finallist,tmp;
    flag=0;
    max=0;
    count=1;
    finallist=NULL;
    finallist=inseriscicoda(finallist,l->dato);
    autonomia=(maximumtree(l->root,tnil))->nodo;
    curr=preclist(l,r);
    distanza=l->dato-curr->dato;
    heretor=l->dato-r->dato;
    tmp=l;
    while(!flag){
        if(autonomia>=heretor){
            flag=1;
            break;
        }
        while(autonomia>=distanza){
            thistotal=((maximumtree(curr->root,tnil))->nodo+distanza);
            heretor=curr->dato-r->dato;
            if((thistotal>=max)){
                if((thistotal-distanza)>=heretor){
                    flag=1;
                    max=thistotal;
                    save=curr;
                }
                else{
                    max=thistotal;
                    save=curr;
                }
            }
            curr=preclist(curr,r);
            distanza=tmp->dato-curr->dato;
        }
        if(max==0){
            printf("nessun percorso\n");
            return;
        }
        finallist=inseriscicoda(finallist,save->dato);
        count++;
        autonomia=(maximumtree(save->root,tnil))->nodo;
        tmp=save;
        heretor=save->dato-r->dato;
        max=0;
        curr=preclist(save,r);
        distanza=save->dato-curr->dato;
    }
    finallist=inseriscicoda(finallist,r->dato);
    count++;
    if(count>2){
        Ptr_nodo curruno,succuno,precuno,move;
        int precdue,succdue,currdue,autprec,autcurr;
        succuno=r;
        succdue=r->dato;
        move=finallist;
        curruno=r->next;
        while(move->next->dato!=succdue){
            move=move->next;
        }
        currdue=move->dato;
        while(curruno->dato<currdue){
            curruno=curruno->next;
        }
        move=finallist;
        while(move->next->dato!=currdue){
            move=move->next;
        }
        precdue=move->dato;
        precuno=curruno->next;
        while(precuno->dato<precdue){
            precuno=precuno->next;
        }
        while (precuno!=l){
            autprec=maximumtree(precuno->root,tnil)->nodo;
            curruno=preclist(curruno,succuno);
            distanza=precuno->dato-curruno->dato;
            save=NULL;
            while(curruno!=succuno&&autprec>=distanza){
                autcurr=maximumtree(curruno->root,tnil)->nodo;
                if(autcurr>=curruno->dato-succuno->dato){
                    save=curruno;
                }
                curruno=preclist(curruno,succuno);
                distanza=precuno->dato-curruno->dato;
            }
            if(save!=NULL){
                finallist=rimuovilista(finallist,currdue);
                finallist=inserisciinordine(finallist,save->dato);
            }
            succdue=currdue;
            currdue=precdue;
            move=finallist;
            while(move->next->dato!=currdue){
                move=move->next;
            }
            precdue=move->dato;
            curruno=precuno;
            while(succuno->dato<succdue){
                succuno=succuno->next;
            }
            while(precuno->dato<precdue){
                precuno=precuno->next;
            }
        }
        autprec=maximumtree(precuno->root,tnil)->nodo;
        curruno=preclist(curruno,succuno);
        distanza=precuno->dato-curruno->dato;
        save=NULL;
        while(curruno!=succuno&&autprec>=distanza){
            autcurr=maximumtree(curruno->root,tnil)->nodo;
            if(autcurr>=curruno->dato-succuno->dato){
                save=curruno;
            }
            curruno=preclist(curruno,succuno);
            distanza=precuno->dato-curruno->dato;
        }
        if(save!=NULL){
            finallist=rimuovilista(finallist,currdue);
            finallist=inserisciinordine(finallist,save->dato);
        }
    }
    stampafinale(finallist);
}

void inavanti(Ptr_nodo l, Ptr_nodo r, tree tnil){
    int autonomia,distanza,flag;
    Ptr_nodo curr,save,finallist,tmp;
    flag=0;
    finallist=NULL;
    finallist=inseriscihead(finallist,r->dato);
    curr=preclist(r,l);
    tmp=r;
    while(!flag){
        save=NULL;
        while(curr!=l){
            distanza=tmp->dato-curr->dato;
            autonomia=(maximumtree(curr->root,tnil)->nodo);
            if (autonomia>=distanza){
                save=curr;
            }
            curr=preclist(curr,l);
        }
        distanza=tmp->dato-curr->dato;
        autonomia=(maximumtree(curr->root,tnil)->nodo);
        if (autonomia>=distanza){
                flag=1;
                save=curr;
        }
        else{
            tmp=save;
            curr=preclist(save,l);
        }
        if(save!=NULL){
            finallist=inseriscihead(finallist,save->dato);
        }
        else{
            printf("nessun percorso\n");
            return;
        }
    }
    stampafinale(finallist);
}

/*void inindietrofake(Ptr_nodo l, Ptr_nodo r, tree tnil){
    int autonomia,distanza,flag,autdasx;
    Ptr_nodo curr,save,finallist,tmp,move,main,post,prec,rem;
    flag=0;
    finallist=NULL;
    finallist=inseriscihead(finallist,r->dato);
    curr=r->next;
    tmp=r;
    while(!flag){
        save=NULL;
        while(curr!=l){
            distanza=curr->dato-tmp->dato;
            autonomia=(maximumtree(curr->root,tnil)->nodo);
            if (autonomia>=distanza){
                save=curr;
            }
            curr=curr->next;
        }
        distanza=curr->dato-tmp->dato;
        autonomia=(maximumtree(curr->root,tnil)->nodo);
        if (autonomia>=distanza){
                flag=1;
                save=curr;
        }
        else{
            tmp=save;
        }
        if(save!=NULL){
            finallist=inseriscihead(finallist,save->dato);
            curr=save->next;
        }
        else{
            printf("nessun percorso\n");
            return;
        }
    }
    stampafinale(finallist);
}*/

Ptr_nodo inserisciinordine(Ptr_nodo head, int n){ 
    if (!head || head->dato < n){
        return inseriscihead(head,n);
    }
    head->next = inserisciinordine(head->next, n); 
    return head;
}

Ptr_nodo rimuovilista(Ptr_nodo head, int n){ 
    Ptr_nodo curr, prec, tmp;
    int found;
    found=0;
    curr = head;
    prec = NULL; 
    while(curr && ! found){
        if(curr->dato == n){ 
            found=1;
            tmp = curr;
            curr = curr->next; 
            if(prec!=NULL)
                prec->next = curr; 
            else
                head = curr; 
            free(tmp);
        } else{
            prec=curr;
            curr = curr->next;
        } 
    }
    return head;
}
 