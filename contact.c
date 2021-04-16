#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"
//int cmp_name(const void* e1, const void* e2)
//{
//	return strcmp((struct cotact*)e1, (struct contact*)e2);
//}
int scancontact(int num, int size);
static int findname(struct contact* ps,char name[max_name])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(name, ps->date[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
}
//加载文件
void loadcontact(struct contact* ps)
{
	struct lis tmp = { 0 };
	FILE* pf = fopen("contact.txt", "rb");
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(struct lis), 1, pf))
	{
		//判断通讯录是否已满
		int ret = scancontact(ps->num , ps->size);
		//判断是否添加（如果已满则添加）
		ifadd(ps, ret);
		ps->date[ps->size] = tmp;
		ps->size++;
	}
	fclose(pf);
	pf = NULL;
}
void init_contact(struct contact* ps)
{
	//memset(ps->date, 0, sizeof(ps->date));
	struct lis* p = (struct lis*)malloc(initpeo * sizeof(struct lis));
	if (p != NULL)
	{
		ps->date = p;
	}
	ps->size = 0;
	ps->num = initpeo;
	loadcontact(ps);
}
void addcontact(struct contact* ps)
{
	printf("姓名：");
	scanf("%s", ps->date[ps->size].name);//name是数组 可以不加&
	printf("年龄：");
	scanf("%d", &ps->date[ps->size].age);//age是整型 要加&
	printf("性别：");
	scanf("%s", ps->date[ps->size].sex);
	printf("电话：");
	scanf("%s", ps->date[ps->size].tele);
	printf("地址：");
	scanf("%s", ps->date[ps->size].addr);
	ps->size++;
}
int scancontact(int num, int size)
{
	if (num == size)
	{
		return 0;//已满
	}
	else
	{
		return 1;//未满
	}
}
void ifadd(struct contact* ps, int ret)
{
	if (ret == 0)
	{
		struct lis* p1 = realloc(ps->date, (ps->num+2) * sizeof(struct lis));
		if (p1 != NULL)
		{
			ps->date = p1;
			printf("已添加两个空间\n");
			ps->num += 2;
		}

	}
}
void showcontact(struct contact* ps)
{
	int i = 0;
	printf("%-10s\t%-10s\t%-10s\t%-20s\t%-20s\n", "姓名", "年龄", "性别", "电话", "地址");
	if (ps->size == 0)
	{
		printf("通讯录为空!\n");
	}
	for (i = 0; i < ps->size; i++)
	{
			printf("%-10s\t%-10d\t%-10s\t%-20s\t%-20s\n"
				, ps->date[i].name
				, ps->date[i].age
				, ps->date[i].sex
				, ps->date[i].tele
				, ps->date[i].addr);
	}
	
}
void delcontact(struct contact* ps)
{
	char name[max_name];
	printf("请输入要删除者的姓名：");
	scanf("%s", name);
	int ret = findname(ps,name);
	if (ret == -1)
	{
		printf("通讯录中无此人！\n");
	}
	else
	{
		int j = 0;
		for (j = ret; j < ps->size - 1; j++)
		{
			ps->date[j] = ps->date[j + 1];
		}
		ps->size--;
	}
}
void searchcontact(struct contact* ps)
{
	char name[max_name];
	printf("请输入要查找联系人的姓名：");
	scanf("%s", name);
	int i= findname(ps, name);
	if (i != -1)
	{
		printf("%-10s\t%-10s\t%-10s\t%-20s\t%-20s\n", "姓名", "年龄", "性别", "电话", "地址");
		printf("%-10s\t%-10d\t%-10s\t%-20s\t%-20s\n"
			, ps->date[i].name
			, ps->date[i].age
			, ps->date[i].sex
			, ps->date[i].tele
			, ps->date[i].addr);
	}
	else
	{
		printf("查无此人\n");
	}
}
void modifycontact(struct contact* ps)
{
	printf("请输入要修改的联系人的姓名：");
	char name[max_name];
	scanf("%s", name);
	int i = findname(ps, name);
	if (i != -1)
	{
		printf("姓名：");
		scanf("%s", ps->date[i].name);//name是数组 可以不加&
		printf("年龄：");
		scanf("%d", &ps->date[i].age);//age是整型 要加&
		printf("性别：");
		scanf("%s", ps->date[i].sex);
		printf("电话：");
		scanf("%s", ps->date[i].tele);
		printf("地址：");
		scanf("%s", ps->date[i].addr);
	}
	else
	{
		printf("查无此人！\n");
	}
}
//void qsort (void* base, size_t num, size_t size,
//int(*compar)(const void*, const void*));
//typedef struct stu
//{
//	char name[10];
//	int age;
//}stu;
int cmp_name(struct lis ps,struct lis ps1)
{
	return strcmp(ps.name, ps1.name);
}
void my_sort(struct contact* ps)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ps->size-1; i++)
	{
		for (j = 0; j < ps->size-1-i; j++)
		{
			int ret = cmp_name(ps->date[j],ps->date[j+1]);
			if (ret > 0)
			{
				//交换
				struct lis tmp;
				tmp = ps->date[j+1];
				ps->date[j + 1] = ps->date[j];
				ps->date[j] = tmp;
			}
		}
	}
}
void sortcontact(struct contact* ps)
{
	//使用库函数
	//qsort(ps->date, ps->size, sizeof(ps->date[0]), cmp_name);//成功 
	//自己设计一个分类函数
	my_sort(ps);//成功！
}
void clearcontact(struct contact* ps)
{
	init_contact(ps);
}
void destorycontact(struct contact* ps)
{
	free(ps->date);
	ps->date = NULL;
}
void savecontact(struct contact* ps)
{
	FILE* pf = fopen("contact.txt", "wb");
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->date[i]), sizeof(struct lis), 1, pf);
	}
	fclose(pf);
	pf = NULL;
}