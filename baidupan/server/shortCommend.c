#include "head.h"
#include "work_que.h"
#include "factory.h"
//获得根目录下文件表-------------------------------------------------------------------------------
int cdRoot(char *result)
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	//和数据库进行连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("数据库连接失败\n");
		return -1;
	}
	char query[500]="select * from catalogue where pid=0";
	//对之前连接的数据库进行query的SQL语句操作
	int t;
	t=mysql_query(conn,query);
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中	
	if(res) //结果不为空
	{
		while((row=mysql_fetch_row(res))!=NULL)//从结果中拿行数据 如果拿完数据则row为 NULL
		{	
			sprintf(result,"%s%8s%s%s%s",result,row[3],"--------------",row[6],"\n");
		}
	}else{ 
		printf("获得结果失败\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	mysql_close(conn);//关闭连接
	return 0;
}
//显示id下的文件信息-------------------------------------------------------------------------------
int cdSelfID(char *id,char *result)
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	//和数据库进行连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("数据库连接失败\n");
		return -1;
	}
	char query[500]="select * from catalogue where pid=";
	sprintf(query,"%s%s",query,id);
	//对之前连接的数据库进行query的SQL语句操作
	int t;
	t=mysql_query(conn,query);
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中	
	if(res) //结果不为空
	{
		while((row=mysql_fetch_row(res))!=NULL)//从结果中拿行数据 如果拿完数据则row为 NULL
		{	
			sprintf(result,"%s%8s%s%s%s",result,row[3],"--------------",row[6],"\n");
		}
	}else{ 
		printf("获得结果失败\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	mysql_close(conn);//关闭连接
	return 0;
}
//实现cd命令----------------------------------------------------------------------------------------
int cdCommend(char *id,char *filename,char *result)//id经过此函数发生改变
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	//和数据库进行连接
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("数据库连接失败\n");
		return -1;
	}
	//拼接SQL操作语句
	char query1[300]="select * from catalogue where pid=";//query就是要用的select语句就是MySQL语句
	char query2[100]=" and filename='";
	char query3[100]="'";//注意query命令语句后面不需要自己加分号	
	sprintf(query1,"%s%s%s%s%s",query1,id,query2,filename,query3);
	int t;
	//对之前连接的数据库进行query的SQL语句操作
	t=mysql_query(conn,query1);
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	//将操作结果存入res中
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	strcpy(id,row[1]);
	memset(query1,0,sizeof(query1));
	strcpy(query1,"select * from catalogue where pid=");
	sprintf(query1,"%s%s",query1,id);
	//释放结果集，不然无法继续使用
	mysql_free_result(res);
	//对之前连接的数据库进行query的SQL语句操作
	t=mysql_query(conn,query1);
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中	
	if(res) //结果不为空
	{
		while((row=mysql_fetch_row(res))!=NULL)//从结果中拿行数据 如果拿完数据则row为 NULL
		{	
			sprintf(result,"%s%8s%s%s%s",result,row[3],"--------------",row[6],"\n");
		}
	}else{ 
		printf("获得结果失败\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	mysql_close(conn);//关闭连接
	return 0;
}


//实现cd..命令--------------------------------------------------------------------------------
int cdFormer(char* id,char *result)//id经过该函数发生改变
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	//对数据库进行连接
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("连接数据库失败\n");
		return -1;
	}
	//拼接SQL语句
	char query[300]="select * from catalogue where id=";//query就是要用的select语句就是MySQL语句
	sprintf(query,"%s%s",query,id);
	int t;
	//进行第一次SQL语句操作
	t=mysql_query(conn,query);//对之前连接的数据库进行query的SQL语句操作
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句执行失败\n");
		return -1;
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中
	row=mysql_fetch_row(res);
	strcpy(id,row[2]);
	//进行第二次查找pid==pid的数据信息
	mysql_free_result(res);//释放结果集 不然无法继续使用
	memset(query,0,sizeof(query));
	strcpy(query,"select * from catalogue where pid=");
	sprintf(query,"%s%s",query,id);
	t=mysql_query(conn,query);
	if(t)//SQL语句操作失败
	{
		printf("SQL语句执行失败\n");
		return -1;
	}
	res=mysql_use_result(conn);	
	if(res) //结果不为空
	{
		while((row=mysql_fetch_row(res))!=NULL)//从结果中拿行数据 如果拿完数据则row为 NULL
		{	
			sprintf(result,"%s%8s%s%s%s",result,row[3],"--------------",row[6],"\n");
		}
	}else{ //操作完结果为空
		printf("执行结果为空\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	mysql_close(conn);//关闭连接
	return 0;
}



//实现mkdir命令----------------------------------------------------------------------------------
int makeDirent(char *username,char *pid,char *filename,char *filetype)
{
	MYSQL *conn;//MYSQL结构体指针
	//MYSQL_RES *res;//接收结果的指针
	//MYSQL_ROW row;//接收行数据的信息
	char* server="localhost";//数据库的IP localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	//数据库进行连接
	conn=mysql_init(NULL);//初始化MYSQL结构体指针
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("数据库链接失败\n");
		return -1;
	}
	

	//连接成功，对数据库执行SQL语句
	int t;
	char sqlcommend[500]={0};
	char query1[300]="insert into catalogue(username,pid,filename,filetype) values('";
	char query2[100]="',";
	char query3[100]=",'";
	char query4[100]="','";
	char query5[100]="')";
	//将SQL语句组合起来
	sprintf(sqlcommend,"%s%s%s%s%s%s%s%s%s",query1,username,query2,pid,query3,filename,query4,filetype,query5);
	t=mysql_query(conn,sqlcommend);//对链接的数据库进行query的SQL语句操作
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
	}
	mysql_close(conn);//关闭数据库链接
	return 0;
}
//实现pwd功能----------------------------------------------------------------------------------------
int cataloguePwd(char *id,char *result)//id未发生改变
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//conn传出参数进行和数据库的链接
	{
		printf("数据库连接失败\n");
		return -1;
	}
	//数据库链接成功，开始进行SQL语句的操作
	char pid[50]={0};//存储目录pid
	char query[100]="select * from catalogue where id=";//query就是要用的select语句就是MySQL语句
	char sqlcommend[300]={0};//用来存完整sql命令
	char showcatalogue[300]={0};
	char tmpcatalogue[300]={0};
	int t;
	sprintf(sqlcommend,"%s%s",query,id);
	t=mysql_query(conn,sqlcommend);//对之前连接的数据库进行query的SQL语句操作
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中
	if(res) //结果不为空
	{
		row=mysql_fetch_row(res);
		strcpy(pid,row[2]);
		sprintf(showcatalogue,"%s%s","/",row[3]);
	}else{ //操作完结果为空
		printf("操作结果为空\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	while(strcmp(pid,"0")!=0)//父目录不是根目录，将父目录的信息搞出来
	{
		memset(sqlcommend,0,sizeof(sqlcommend));
		sprintf(sqlcommend,"%s%s",query,pid);
		t=mysql_query(conn,sqlcommend);//对之前连接的数据库进行query的SQL语句操作
		if(t)//t=1 SQL语句操作失败
		{
			printf("SQL语句操作失败\n");
		}
		res=mysql_use_result(conn);//将操作获得的结果存入res中
		if(res) //结果不为空
		{
			row=mysql_fetch_row(res);
			memset(pid,0,sizeof(pid));
			strcpy(pid,row[2]);
			memset(tmpcatalogue,0,sizeof(tmpcatalogue));
			sprintf(tmpcatalogue,"%s%s%s","/",row[3],showcatalogue);
			memset(showcatalogue,0,sizeof(showcatalogue));
			strcpy(showcatalogue,tmpcatalogue);
		}else{ //操作完结果为空
			printf("操作结果为空\n");
			return -1;
		}
		mysql_free_result(res);//释放结果集，不然无法继续使用
	}
	strcpy(result,showcatalogue);
	mysql_close(conn);//关闭连接
	return 0;
}

//实现remove功能-------------------------------------------------------------------------------
//------------------------------------数据结构-------------------------------------------------
/*
typedef struct id_node{
	char id[20];//用来存储要删除的数据库中的一行的id
	struct id_node *pNext;
}IDnode_t,*pIDnode_t;//节点结构
typedef struct{
	pIDnode_t queHead,queTail;//队列头，队列尾；
	int size;//队列中的节点数；
}QueID_t,*pQueID_t;//队列结构
*/
//-------------------------------从队列头部拿出id信息------------------------------------------
int getID(pQueID_t pQue,char *id)//队列为空则返回-1，不空则返回0；id为传出参数
{
	pIDnode_t pQueTmp;
	if(0==pQue->size)//队列为空
	{
		//printf("此时队列为空\n");
		return -1;
	}else{  //队列不为空
		strcpy(id,pQue->queHead->id);
		pQueTmp=pQue->queHead;
		pQue->queHead=pQue->queHead->pNext;
		if(pQue->queHead==NULL)//队列为空
		{
			pQue->queTail=NULL;
		}
	}
	pQue->size--;
	free(pQueTmp);
	pQueTmp=NULL;
	return 0;
}
//-------------------------------将新节点尾插法插入队列-----------------------------------------
int insertID(pQueID_t pQue,char *id)
{
	pIDnode_t pNewID;
	pNewID=(pIDnode_t)calloc(1,sizeof(IDnode_t));//为新节点创造空间
	strcpy(pNewID->id,id);
	//将新节点放到队列中
	if(0==pQue->size)//队列为空
	{
		pQue->queHead=pQue->queTail=pNewID;
	}else{//队列不为空
		pQue->queTail->pNext=pNewID;
		pQue->queTail=pNewID;
	}
	pQue->size++;
	return 0;
}
//--------------------------输入父目录id和文件名/获得目标id--------------------------------------
int getRootID(char *id,char *filename)
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	char query1[300]="select * from catalogue where pid=";//query就是要用的select语句就是MySQL语句
	char query2[100]=" and filename='";
	char query3[100]="'";//注意query命令语句后面不需要自己加分号
	sprintf(query1,"%s%s%s%s%s",query1,id,query2,filename,query3);
	int t;
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//conn传出参数进行和数据库的链接
	{
		printf("数据库连接失败\n");
		return -1;
	}
	t=mysql_query(conn,query1);//对之前连接的数据库进行query的SQL语句操作
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	res=mysql_use_result(conn);//将操作获得的结果存入res中
	row=mysql_fetch_row(res);
	strcpy(id,row[1]);
	return 0;
}
//-----------------------------将输入的id的一行信息删除掉------------------------------------------
int smallDelete(char *id)
{
	MYSQL *conn;//数据库MYSQL结构体指针
	//MYSQL_RES *res;//存储结果的指针
	//MYSQL_ROW row;//存储行数据
	char* server="localhost";//数据库的IP localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	//和数据库链接
	conn=mysql_init(NULL);//将MYSQL结构体指针初始化
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("数据库连接失败\n");//连接失败
		return -1;
	}
	//和数据库链接成功
	char query[200]="delete from catalogue where id=";//query就是要进行的SQL语句操作
	sprintf(query,"%s%s",query,id);
	int t;
	//对链接成功的数据库进行query语句操作
	t=mysql_query(conn,query);
	if(t)//t=1 操作失败
	{
		printf("SQL语句操作语言操作失败\n");
		return -1;
	}
	mysql_close(conn);//关闭链接
	return 0;
}
//-----------------------获得id的孩子id，并将孩子id依次加入到队列中---------------------------
int getChildID(pQueID_t pQue,char *id)
{
	MYSQL *conn;//mysql的结构体指针
	MYSQL_RES *res;//查询结果 select 从表中查找数据
	MYSQL_ROW row;//数据库中的一行数据
	char* server="localhost";//数据库的ip localhost本地
	char* user="root";//用户名
	char* password="123";//密码
	char* database="catalogue";//要访问的数据库名称
	//进行数据库的链接
	conn=mysql_init(NULL);//进行初始化 将mysql结构体指针conn初始化
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))//conn传出参数进行和数据库的链接
	{
		printf("数据库连接失败\n");
		return -1;
	}
	//对SQL语句进行拼接
	char query[300]="select * from catalogue where pid=";
	sprintf(query,"%s%s",query,id);
	//进行SQL语句执行
	int t;
	t=mysql_query(conn,query);
	if(t)//t=1 SQL语句操作失败
	{
		printf("SQL语句操作失败\n");
		return -1;
	}
	//将操作获得的结果存入res中	
	res=mysql_use_result(conn);
	//结果有无信息的标志
	//int resflag=0;
	if(res) //结果不为空
	{
		while((row=mysql_fetch_row(res))!=NULL)//如果没有子id则不会进入while循环
		{
			insertID(pQue,row[1]);			
		}
	}else{ 
		printf("获得结果错误\n");
		return -1;
	}
	mysql_free_result(res);//释放结果集，不然无法继续使用
	mysql_close(conn);//关闭连接
	return 0;
}
//--------------------------------执行删除目录的所有操作------------------------------------------
int removeCatalogue(char *tmpid,char *filename)//父目录id  要删除的filename
{
	char id[20]={0};
	strcpy(id,tmpid);
	QueID_t Que;
	memset(&Que,0,sizeof(QueID_t));
	//获得要删除的根目录的id
	getRootID(id,filename);
	//将根目录id放入队列中
	insertID(&Que,id);
	memset(id,0,sizeof(id));
	while(getID(&Que,id)!=-1)//队列不为空
	{
		getChildID(&Que,id);//将该id的孩子id放入队列
		smallDelete(id);
		memset(id,0,sizeof(id));
	}
	return 0;

}


