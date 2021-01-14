//
//  bit_operation.cpp
//  my_crypto
//
//  Created by qTp on 12/22/20.
//  Copyright © 2020 qTp. All rights reserved.
//

#include "bit_operation.hpp"

int CompareBit(LinkedList *l, LinkedList *r){
    if (l->size > r ->size)
        return  1;
    if (l->size < r ->size)
        return -1;
        
    Node *pl = l->head;
    Node *pr = r->head;
    while (pl!=NULL && pl->data==pr->data){
        pl=pl->next;
        pr=pr->next;
    }
    if (pl==NULL)
        return 0;
    return pl->data?1:-1;
}

LinkedList *AddBit(LinkedList *x, LinkedList *y){
    LinkedList *rs= CreateList(0);
    Node *xt = x->tail;
    Node *yt = y->tail;
    bool c=0;
    while (xt!=NULL && yt!=NULL){
        AddHead(rs, xt->data^yt->data^c);
        c= (xt->data & yt->data)|(xt->data & c)|(yt->data & c);
        xt=xt->prev;
        yt=yt->prev;
    }
    
    Node *t=xt;
    if (yt!=NULL)
        t=yt;
    if (t!=NULL){
        while (c && t!=NULL){
            AddHead(rs, t->data^0^c);
            c= t->data & c;
            t=t->prev;
        }
//        if (t==NULL && c){
//            AddHead(rs, 1);
//        }
        while (t!=NULL){
            AddHead(rs, t->data);
            t=t->prev;
        }
    }
    if (c)
        AddHead(rs,1);
    
    if(rs->size>1)
        DeleteAtTail(rs);
    
    return rs;
}

LinkedList *SubBit(LinkedList *x, LinkedList *y){
    LinkedList *rs= CreateList(0);
    Node *xt = x->tail;
    Node *yt = y->tail;
    bool c=0;
    
    bool t;
    while (xt!=NULL && yt!=NULL){
        t = xt->data^yt->data^c;
        AddHead(rs, t);
        if (xt->data!=yt->data)
            c=!xt->data;
        else
            c=t;
        
        xt=xt->prev;
        yt=yt->prev;
    }
    Node *nt=xt;
    if (nt!=NULL){
        bool temp;
        while (c && nt!=NULL){
            temp=nt->data^0^c;
            AddHead(rs, temp);
            if (xt->data)
                c=0;
            else
                c=temp;
            nt=nt->prev;
        }
        while (nt!=NULL){
            AddHead(rs, nt->data);
            nt=nt->prev;
        }
    }
    if(rs->size>1)
        DeleteAtTail(rs);
    while (!rs->head->data)
        DeleteAtHead(rs);
    
    return rs;
}

LinkedList *ShiftLeftBit(LinkedList *x, int shift){
    while (shift>0){
        AddTail(x, 0);
        shift--;
    }
    x->size=x->size+shift;
    return x;
}

string pl(LinkedList *x){
    string rs="";
    Node *p=x->head;
    while (p!=NULL){
        rs=rs+(p->data?"1":"0");
        p=p->next;
    }
    return rs;
}

LinkedList *MulMod(LinkedList *x, LinkedList *y, LinkedList *m){
    LinkedList *rs= CreateList(0);
    LinkedList *z= CreateList(0);
    Node *yt = y->tail;
    
    if (yt->data)
        rs=CloneList(x);
    LinkedList *x1=CloneList(x);

    yt=yt->prev;
    while (yt!=NULL){
        ShiftLeftBit(x1, 1);
        if (CompareBit(x1, m)>0)
            x1=SubBit(x1, m);
        if (yt->data){
//            z=x1;
            rs=AddBit(rs, x1);
        }
        if (CompareBit(rs, m)>0)
            rs=SubBit(rs, m);
        yt=yt->prev;
    }
    
    return rs;
}

LinkedList *PowMod(LinkedList *x, LinkedList *p, LinkedList *m){
    LinkedList *rs= CreateList(1);
    
    Node *h=p->head;
    while(h!=NULL){
        rs=MulMod(rs, rs, m);
        if (h->data)
            rs=MulMod(rs, x, m);
        if (CompareBit(rs, m)>0)
            rs=SubBit(rs, m);
        h=h->next;
    }
    
    return rs;
}

LinkedList *l2= CreateList("10");
LinkedList *l3= CreateList("11");
LinkedList *l5= CreateList("101");
bool CheckPrime(LinkedList *x){
    LinkedList *m= CloneList(x);
    int r=0;
    DeleteAtTail(m);
    Node *p = m->tail;
    while (p!=NULL && !p->data){
        r++;
        DeleteAtTail(m);
        p = m->tail;
    }
    for(int i=r-1; i>=0; i--){
        AddTail(m, 0);
        LinkedList *t=PowMod(l2, m, x);
        if (!(t->size==1 && t->head->data))
            return false;
    }
    
    for(int i=r-1; i>=0; i--){
        AddTail(m, 0);
        LinkedList *t=PowMod(l3, m, x);
        if (!(t->size==1 && t->head->data))
            return false;
    }
    
    for(int i=r-1; i>=0; i--){
        AddTail(m, 0);
        LinkedList *t=PowMod(l5, m, x);
        if (!(t->size==1 && t->head->data))
            return false;
    }
    
    return true;
}

string ToDecString(LinkedList *x){
    if (x->size==0)
        return "0";
    
    string dec ="0";
    Node *h=x->head;
    while (h!=NULL){
        if (h->data)
            dec= X2a1Dec(dec);
        else
            dec= X2Dec(dec);
        h=h->next;
    }
    return dec;
}

string X2Dec(string dec){
    string rs=dec.substr(0);
    char c=0;
    long l= dec.length();
    for (long i=l-1; i>=0; i--){
        char t = dec[i]-48;
        if (t+t+c<10){
            rs[i]=t+t+c+48;
            c=0;
        }
        else{
            rs[i]=t+t+c-10+48;
            c=1;
        }
    }
    if (c==1){
        rs.insert(0, "1");
    }
    return rs;
}
string X2a1Dec(string dec){
    string rs=X2Dec(dec);
    long l= rs.length();
    // dec * 2 => max(dec[l]) = 8
    rs[l-1]= rs[l-1]+1;
    return rs;
}

