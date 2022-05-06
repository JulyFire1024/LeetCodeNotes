//https://blog.songjiahao.com/archives/362#toc-head-5

#include<bits/stdc++.h>
using namespace std;
struct ListNode {
   int val;
   ListNode *next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

void insertList(ListNode* &head,int x){  //头插法插入节点
   ListNode *p=new ListNode(x);
   if(head==nullptr){
      head=p;
   }
   else{
      p->next=head;
      head=p;
   }
}
ListNode* CreateList(vector<int>a)		//头插法建立单链表
{
    ListNode *head=nullptr;
    if(a.size()>0) reverse(a.begin(),a.end());                   //头插方法创建的链表是给定序列的逆序，这里提前逆置一下
    for(int i=0;i<a.size();i++){                     //得到给定序列顺序的链表
      insertList(head,a[i]);
    }
   return head;
}

void DispList(ListNode*L)					
{
	ListNode*p=L;
	while(p!=NULL){
		  cout<<p->val<<" -> ";
		  p=p->next;
	}
	cout<<endl;
}


int getLenght(ListNode* head){
   int len=0;
   while(head){
      len++;
      head=head->next;
   }
   return len;
}





//二叉树的结构体定义
#define null INT_MAX                        //把力扣给定的null节点定义为int的最大值，用于识别空结点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
TreeNode *CreatTree(vector<int> &layerorder);       //根据给定的层序序列建树的函数
int LayerOfTree(TreeNode *root);                    //计算树的层数，用于绘制树形
void PrintTreeMatrix(vector<vector<int>> &matrix);  //用于打印树形结构专用的二维数组输出函数
void PrintTree(TreeNode *root);                     //打印树的函数
void PrintMatrix(vector<vector<int>> matrix);      //打印一般二维数组的函数
TreeNode *CreatTree(vector<int> &layerorder){   //根据层序序列建树
    int n=layerorder.size();
    if(n==0) return nullptr;                    //计算序列元素个数，如果空树返回空指针
    queue<TreeNode*> q;
    TreeNode *root=new TreeNode(layerorder[0]); //创建根结点并入队
    q.push(root);
    for(int i=0;i<=(n-1)/2;i++){                //只需处理第一个结点到最后一个非叶子结点
        if(layerorder[i]==null) continue;       //如果是空结点则跳过
        TreeNode* now=q.front();                //从队列中取出当前结点
        q.pop();
        int left=2*i+1,right=2*(i+1);           //计算当前结点的左右孩子的位置
        if(left<n&&layerorder[left]!=null){     //如果左孩子存在且不为空时创建左孩子结点并入队
            now->left=new TreeNode(layerorder[left]);
            q.push(now->left);
        }
        if(right<n&&layerorder[right]!=null){   //如果右孩子存在且不为空时创建右孩子结点并入队
            now->right=new TreeNode(layerorder[right]);
            q.push(now->right);
        }
    }
    return root;                                //返回创建好的树
}
int LayerOfTree(TreeNode *root){                //层序遍历获取树高
    if(root==nullptr) return 0;
    int layer=0;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        layer++;
        int size=q.size();
        for(int i=0;i<size;i++){
            TreeNode* now=q.front();
            q.pop();
            if(now->left) q.push(now->left);
            if(now->right) q.push(now->right);
        }
    }
    return layer;
}
void PrintTreeMatrix(vector<vector<int>> &matrix){  //打印填充了树形结构的二维数组
    int row=0,col=0;
    row=matrix.size();
    string flag=string(3,' ');                      //空白位置使用3个空格占用
    if(row) col=matrix[0].size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(j) putchar(' ');
            if(matrix[i][j]==null) cout<<flag;      //如果是空节点则打印空字符
            else  printf("%3d",matrix[i][j]);       //否则输出三个字符宽度的数字
        }
        cout<<string(2,'\n');                       //增大行距以避免树形看起来太扁
    }
}
void PrintTree(TreeNode *root){                     //根据树形填充一个二维数组
    if(root==nullptr){                              //如果是空树则只输出NULL
        puts("NULL");return;
    }
    struct node{                                    //每一个节点对应二维数组中的一个坐标
        int x,y;
        node(){}
        node(int x_,int y_):x(x_),y(y_){}
    };
    unordered_map<TreeNode*,node> mp;               //节点指针和二维数组坐标的对应关系
    int layer=LayerOfTree(root);                    //获取树高
    int rol=(1<<layer)-1;                           //按照满二叉树的最后一行数量计算（每个元素中间用空格分开,共为奇数个空位）
    vector<vector<int>> matrix(layer,vector<int>(rol,null));    //用于填充的二维数组，用INT_MAX初始化
    int offset=1<<(layer-2);                        //偏移量，根的孩子与根节点的坐标偏移量为1<<(layer-2)
    queue<TreeNode*> q;                             //以层序遍历的方式填充
    q.push(root);
    int i=0,j=rol/2;                                //根节点所在的坐标为第一行的中间
    mp[root]=node(i,j);                             //填充并记录坐标
    matrix[i][j]=root->val;
    while(!q.empty()){                              //层序遍历
        int size=q.size();
        for(int k=0;k<size;k++){
            TreeNode *now=q.front();
            q.pop();
            i=mp[now].x, j=mp[now].y;               //获取队头元素的坐标
            if(now->left){                          //如果左孩子存在，则左孩子入队并填充
                q.push(now->left);
                int tempi=i+1,tempj=j-offset;       //左孩子位于下一行，并且向左偏移
                matrix[tempi][tempj]=now->left->val;
                mp[now->left]=node(tempi,tempj);
            }
            if(now->right){                         //右孩子同理
                q.push(now->right);
                int tempi=i+1,tempj=j+offset;       //右孩子位于下一行，并且向右偏移
                matrix[tempi][tempj]=now->right->val;
                mp[now->right]=node(tempi,tempj);
            }
        }
        offset>>=1;                                 //偏移量每次减半
    }
    PrintTreeMatrix(matrix);                        //打印最后的结果
    return;
}
void PrintMatrix(vector<vector<int>> matrix){      //用于打印二维数组的函数
    int row=0,col=0;
    row=matrix.size();
    if(row) col=matrix[0].size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(j) putchar(' ');
            cout<<matrix[i][j];
        }
        printf("\n");
    }
}