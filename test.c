#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"
//大项目：通讯录的实现(使用动态内存管理（malloc,calloc等），首先给通讯录三个联系人的空间，如果通讯录已满，则添加两个联系人，依次类推)
//改进：利用文件管理  使数据可以被保存
void menu()
{
	printf("**************************************\n");
	printf("***0.exit                     1.add***\n");
	printf("***2.del                   3.search***\n");
	printf("***4.modify                  5.show***\n");
	printf("***6.sort                   7.clear***\n");
	printf("***8.save                          ***\n");
	printf("**************************************\n");
}
int main()
{
	struct contact con;
	//初始化通讯录
	init_contact(&con);
	int input;
	do
	{
		menu();
		int i = sizeof(struct lis) ;
		//判断通讯录是否已满
		int ret = scancontact(con.num,con.size);
		//判断是否添加（如果已满则添加）
		ifadd(&con,ret);
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{ 
		case 0:
			savecontact(&con);
			destorycontact(&con);//即释放申请的空间，避免内存泄露
			printf("退出成功！\n");
			break;
		case 1:
			addcontact(&con);
			break;
		case 2:
			delcontact(&con);
			break;
		case 3:
			searchcontact(&con);
			break;
		case 4:
			modifycontact(&con);
			break;
		case 5:
			showcontact(&con);
			break;
		case 6:
			sortcontact(&con);
			break;
		case 7:
			printf("已清空！\n");
			clearcontact(&con);
			break;
		case 8:
			savecontact(&con);
			printf("已保存\n");
			break;
		default:
			printf("输入错误，请重新输入：\n");
			break;
		}
			
	} while (input);
	return 0;
}
