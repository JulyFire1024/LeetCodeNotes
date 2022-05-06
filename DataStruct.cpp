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

void insertList(ListNode* &head,int x){  //ͷ�巨����ڵ�
   ListNode *p=new ListNode(x);
   if(head==nullptr){
      head=p;
   }
   else{
      p->next=head;
      head=p;
   }
}
ListNode* CreateList(vector<int>a)		//ͷ�巨����������
{
    ListNode *head=nullptr;
    if(a.size()>0) reverse(a.begin(),a.end());                   //ͷ�巽�������������Ǹ������е�����������ǰ����һ��
    for(int i=0;i<a.size();i++){                     //�õ���������˳�������
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





//�������Ľṹ�嶨��
#define null INT_MAX                        //�����۸�����null�ڵ㶨��Ϊint�����ֵ������ʶ��ս��
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
TreeNode *CreatTree(vector<int> &layerorder);       //���ݸ����Ĳ������н����ĺ���
int LayerOfTree(TreeNode *root);                    //�������Ĳ��������ڻ�������
void PrintTreeMatrix(vector<vector<int>> &matrix);  //���ڴ�ӡ���νṹר�õĶ�ά�����������
void PrintTree(TreeNode *root);                     //��ӡ���ĺ���
void PrintMatrix(vector<vector<int>> matrix);      //��ӡһ���ά����ĺ���
TreeNode *CreatTree(vector<int> &layerorder){   //���ݲ������н���
    int n=layerorder.size();
    if(n==0) return nullptr;                    //��������Ԫ�ظ���������������ؿ�ָ��
    queue<TreeNode*> q;
    TreeNode *root=new TreeNode(layerorder[0]); //��������㲢���
    q.push(root);
    for(int i=0;i<=(n-1)/2;i++){                //ֻ�账���һ����㵽���һ����Ҷ�ӽ��
        if(layerorder[i]==null) continue;       //����ǿս��������
        TreeNode* now=q.front();                //�Ӷ�����ȡ����ǰ���
        q.pop();
        int left=2*i+1,right=2*(i+1);           //���㵱ǰ�������Һ��ӵ�λ��
        if(left<n&&layerorder[left]!=null){     //������Ӵ����Ҳ�Ϊ��ʱ�������ӽ�㲢���
            now->left=new TreeNode(layerorder[left]);
            q.push(now->left);
        }
        if(right<n&&layerorder[right]!=null){   //����Һ��Ӵ����Ҳ�Ϊ��ʱ�����Һ��ӽ�㲢���
            now->right=new TreeNode(layerorder[right]);
            q.push(now->right);
        }
    }
    return root;                                //���ش����õ���
}
int LayerOfTree(TreeNode *root){                //���������ȡ����
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
void PrintTreeMatrix(vector<vector<int>> &matrix){  //��ӡ��������νṹ�Ķ�ά����
    int row=0,col=0;
    row=matrix.size();
    string flag=string(3,' ');                      //�հ�λ��ʹ��3���ո�ռ��
    if(row) col=matrix[0].size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(j) putchar(' ');
            if(matrix[i][j]==null) cout<<flag;      //����ǿսڵ����ӡ���ַ�
            else  printf("%3d",matrix[i][j]);       //������������ַ���ȵ�����
        }
        cout<<string(2,'\n');                       //�����о��Ա������ο�����̫��
    }
}
void PrintTree(TreeNode *root){                     //�����������һ����ά����
    if(root==nullptr){                              //����ǿ�����ֻ���NULL
        puts("NULL");return;
    }
    struct node{                                    //ÿһ���ڵ��Ӧ��ά�����е�һ������
        int x,y;
        node(){}
        node(int x_,int y_):x(x_),y(y_){}
    };
    unordered_map<TreeNode*,node> mp;               //�ڵ�ָ��Ͷ�ά��������Ķ�Ӧ��ϵ
    int layer=LayerOfTree(root);                    //��ȡ����
    int rol=(1<<layer)-1;                           //�����������������һ���������㣨ÿ��Ԫ���м��ÿո�ֿ�,��Ϊ��������λ��
    vector<vector<int>> matrix(layer,vector<int>(rol,null));    //�������Ķ�ά���飬��INT_MAX��ʼ��
    int offset=1<<(layer-2);                        //ƫ���������ĺ�������ڵ������ƫ����Ϊ1<<(layer-2)
    queue<TreeNode*> q;                             //�Բ�������ķ�ʽ���
    q.push(root);
    int i=0,j=rol/2;                                //���ڵ����ڵ�����Ϊ��һ�е��м�
    mp[root]=node(i,j);                             //��䲢��¼����
    matrix[i][j]=root->val;
    while(!q.empty()){                              //�������
        int size=q.size();
        for(int k=0;k<size;k++){
            TreeNode *now=q.front();
            q.pop();
            i=mp[now].x, j=mp[now].y;               //��ȡ��ͷԪ�ص�����
            if(now->left){                          //������Ӵ��ڣ���������Ӳ����
                q.push(now->left);
                int tempi=i+1,tempj=j-offset;       //����λ����һ�У���������ƫ��
                matrix[tempi][tempj]=now->left->val;
                mp[now->left]=node(tempi,tempj);
            }
            if(now->right){                         //�Һ���ͬ��
                q.push(now->right);
                int tempi=i+1,tempj=j+offset;       //�Һ���λ����һ�У���������ƫ��
                matrix[tempi][tempj]=now->right->val;
                mp[now->right]=node(tempi,tempj);
            }
        }
        offset>>=1;                                 //ƫ����ÿ�μ���
    }
    PrintTreeMatrix(matrix);                        //��ӡ���Ľ��
    return;
}
void PrintMatrix(vector<vector<int>> matrix){      //���ڴ�ӡ��ά����ĺ���
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