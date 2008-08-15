/*
 */
void build_jheap(long *x, int *y, int n) 
{
  long value;
  int this_node,parent_node,other,i ;

  for(i=1;i<n;i++) {
    this_node=i ; 
    parent_node=(i-1)/2 ; 
    value=x[this_node] ; 
    other=y[this_node] ;
    while(this_node!=0) {
      if(value>=x[parent_node]) {
        x[this_node]=x[parent_node] ; 
        y[this_node]=y[parent_node] ;
        this_node=parent_node ; 
        parent_node=(parent_node-1)/2 ; 
      }
      else break ;
    }
    x[this_node]=value ; 
    y[this_node]=other ;
  }
}
/*
 */
void heap_jsort(long *x, int *y, int n)
{

  long tail;
  int last, left, right,larger, this_node, other ;

  for(last=n-1;last>0;last--) {
    /* swap first position with last */
    /* tail needs to be filtered down into heap */
    tail=x[last] ; 
    other=y[last] ;
    x[last]=x[0] ; 
    y[last]=y[0] ;

    /* start at the root node */
    this_node=0 ;

    /* traverse the heap */
    while(1) {

      /* first look left */
      left=2*this_node+1 ; 

      /* if no left node, you've found the right slot */
      if(left>last-1) {
        break ; 
      }

      /* if there is a left node, then find whether left node */
      /* or right node (if any) is larger */
      right=left+1 ; 
      if(right>last-1 || x[right]<x[left]) 
        larger=left ;
      else
        larger=right ; 

      /* if tail is bigger than both left and right children */
      /* then it must go here, so stop traversing */
      if(tail>x[larger]) {
        break ; 
      }

      /* otherwise, move down */
      x[this_node]=x[larger] ; 
      y[this_node]=y[larger] ;
      this_node=larger ; 
    }
    /* after the loop, this_node points to the insertion spot */
    x[this_node]=tail ; 
    y[this_node]=other ;
  }
}
/*
 ***************************************************************************
 */
void juqsrt(int n, long x[], int y[])
{
	build_jheap(x,y,n);
	heap_jsort(x,y,n);
}
