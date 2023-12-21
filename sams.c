#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*---------------定义结构体---------------*/
typedef struct student{
    int id;                 //学号
    char name[20];          //姓名
    int Actual_Attendance;  //实际出勤次数
    int Should_Attendance;  //应出勤次数
    double Attendance;      //出勤率
    struct student *next;
}STU;

/*---------------函数声明---------------*/
void Menu(void);
void Add_Students(STU **head);
void Delete_Student(STU **head);
void Edit_Student(STU **head);
void Average_Attendance(STU* head);
void Attendance_Ascending_Order(STU **head);
void Attendance_Descending_Order(STU **head);
void Id_Ascending_Order(STU **head);
void Id_Descending_Order(STU **head);
void Search_ID(STU* head);
void Search_Name(STU* head);
void Statistical_Analysis(STU* head);
void Print_Students(STU *head);
void Write_To_File(STU* head);
void Read_From_File(STU** head);

/*---------------程序开始---------------*/
int main(void)
{
    STU *head=NULL;
    int a;
    printf("欢迎使用【学生考勤管理系统】\n");
    while (1)
    {
        printf("是否展示菜单（1为是，0为否）：");
        scanf("%d",&a);
        if(a==1) Menu();
        printf("请输入您的选择：");
        scanf("%d",&a);
        switch (a)
        {
            case 1:
                printf("请输入要新建的学生数：");
                scanf("%d",&a);
                while (a--)
                Add_Students(&head);
                break;

            case 2:
                Delete_Student(&head);
                break;

            case 3:
                Edit_Student(&head);
                break;

            case 4:
                Average_Attendance(head);
                break;

            case 5:
                Attendance_Ascending_Order(&head);
                break;

            case 6:
                Attendance_Descending_Order(&head);
                break;

            case 7:
                Id_Ascending_Order(&head);
                break;

            case 8:
                Id_Descending_Order(&head);
                break;

            case 9:
                Search_ID(head);
                break;

            case 10:
                Search_Name(head);
                break;

            case 11:
                Statistical_Analysis(head);
                break;

            case 12:
                Print_Students(head);
                break;

            case 13:
                Write_To_File(head);
                break;
                    
            case 14:
                Read_From_File(&head);
                break;

            case 0:printf("程序结束，感谢使用！");
                exit(0);
            
            default:printf("输入错误!\n");
                break;
        }

        printf("【本次任务结束】\n【已开始新任务】\n");
        a=-1;
    }
    
    return 0;
}

//功能菜单
void Menu(void){
    printf("1.新建学生信息\n");
    printf("2.删除学生信息\n");
    printf("3.修改学生信息\n");
    printf("4.计算学生平均出勤率\n");   
    printf("5.按出勤率升序排序\n");
    printf("6.按出勤率降序排序\n");
    printf("7.按学号升序排序\n");
    printf("8.按学号降序排序\n");
    printf("9.按学号搜索\n");
    printf("10.按姓名搜索\n");
    printf("11.统计分析\n");
    printf("12.列出记录\n");
    printf("13.写入文件\n");
    printf("14.从文件中读取\n");
    printf("0.退出\n");
}

//1.新建学生信息
void Add_Students(STU **head){
    STU *New_Student=(STU*)malloc(sizeof(STU));
    if (New_Student == NULL) {
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }
    // 输入学生信息
    printf("输入学生的学号：");
    scanf("%d",&New_Student->id);
    printf("输入学生的姓名：");
    scanf("%s",New_Student->name);
    printf("输入学生的实际出勤次数：");
    scanf("%d",&New_Student->Actual_Attendance);
    printf("输入学生的应该出勤次数：");
    scanf("%d", &New_Student->Should_Attendance);
    
    New_Student->Attendance=(double)New_Student->Actual_Attendance/New_Student->Should_Attendance;
    New_Student->next = NULL;  // 设置新学生的下一个学生指针为NULL
    //将新学生添加到链表中
    if (*head==NULL) {
        *head=New_Student;  // 如果链表为空，将新学生设置为头节点
    }
    else {
        STU *current=*head;
        while (current->next!=NULL){
            current=current->next;  // 移动到链表的末尾
        }
        current->next=New_Student;  // 将新学生连接到链表的末尾
    }
}

//2.删除学生信息
void Delete_Student(STU **head){
    int xh;
    printf("请输入需要删除学生的学号：");
	scanf("%d", &xh);
    STU *current=*head;
    STU *Last=NULL;
    // 判断head是为否学生该的学号
    if (current->id==xh){
        *head=current->next;
        free(current); // 释放原始头节点的内存
        printf("学生信息已删除。\n");
        return ;
    }
    while(current!=NULL){
        if(xh==current->id){
            Last->next=current->next;
            free(current);
            printf("学生信息已删除。\n");
            return ;
        }
        Last=current;
        current=current->next;
    }
	printf("没有找到该学生！\n");
}

//3.修改学生信息
void Edit_Student(STU **head){
    int xh;
    printf("请输入需要修改学生信息的学生的学号：");
	scanf("%d",&xh);
    STU *current=*head;
	while(current!=NULL){
        if (xh==current->id){
            printf("输入学生的学号：");
            scanf("%d",&current->id);
            printf("输入学生的姓名：");
            scanf("%s",current->name);
            printf("输入学生的实际出勤次数：");
            scanf("%d",&current->Actual_Attendance);
            printf("输入学生的应该出勤次数：");
            scanf("%d", &current->Should_Attendance);
            current->Attendance=(double)current->Actual_Attendance/current->Should_Attendance;
            printf("学生信息修改成功！\n");
            return ;
        }
        current=current->next;  // 移动到链表的末尾
    }
	printf("没有找到该学生！\n");
}

//4.计算学生平均出勤率
void Average_Attendance(STU* head){
    STU* current=head;
    double average=0;
    int n=0;
    while (current!=NULL) {
        average+=current->Attendance;//求出勤率的和
        n++;// 求人数
        current=current->next;
    }
    average=average/n*100;
    printf("%.2lf%%\n",average);
}

//5.按出勤率升序排序
void Attendance_Ascending_Order(STU **head){
     // 检查链表为空或只有一个节点的情况
    if (*head == NULL || (*head)->next == NULL) {
        printf("无需排序。\n");
        return ;
    }

    STU *temp;  // 临时节点用于交换
    STU **ptr;  // 双重指针用于遍历链表
    
    int swapped; // 交换标志
    do {
        swapped = 0; // 重置交换标志
        ptr = head;  // 指向链表头部的指针的指针

        // 遍历链表
        while (*ptr!=NULL&& (*ptr)->next!= NULL) {
            if ((*ptr)->Attendance > (*ptr)->next->Attendance) {
                // 通过指针交换节点位置
                temp = (*ptr)->next; // 存储下一个节点
                (*ptr)->next = temp->next; // 当前节点的下一个指向temp的下一个
                temp->next = *ptr; // temp指向当前节点
                *ptr = temp; // 更新链表头部指针
                
                swapped = 1; // 标记已交换
            }
            ptr = &(*ptr)->next; // 移动到下一个节点
        }
    } while (swapped); // 如果本轮没有交换，则排序完成

    // 输出排序结果
    printf("排序完成！\n是否输出：（1为是，0为否）:");
    int a;
    scanf("%d", &a);
    if (a == 1) {
        Print_Students(*head); // 输出排序后的结果
    }
}

//6.按出勤率降序排序
void Attendance_Descending_Order(STU **head){
   // 检查链表为空或只有一个节点的情况
    if (*head == NULL || (*head)->next == NULL) {
        printf("无需排序。\n");
        return ;
    }

    STU *temp;  // 临时节点用于交换
    STU **ptr;  // 双重指针用于遍历链表
    
    int swapped; // 交换标志
    do {
        swapped = 0; // 重置交换标志
        ptr = head;  // 指向链表头部的指针的指针

        // 遍历链表
        while (*ptr!=NULL&& (*ptr)->next!= NULL) {
            if ((*ptr)->Attendance<(*ptr)->next->Attendance) {
                // 通过指针交换节点位置
                temp = (*ptr)->next; // 存储下一个节点
                (*ptr)->next = temp->next; // 当前节点的下一个指向temp的下一个
                temp->next = *ptr; // temp指向当前节点
                *ptr = temp; // 更新链表头部指针
                
                swapped = 1; // 标记已交换
            }
            ptr = &(*ptr)->next; // 移动到下一个节点
        }
    } while (swapped); // 如果本轮没有交换，则排序完成

    // 输出排序结果
    printf("排序完成！\n是否输出：（1为是，0为否）:");
    int a;
    scanf("%d", &a);
    if (a == 1) {
        Print_Students(*head); // 输出排序后的结果
    }
}

//7.按学号升序排序
void Id_Ascending_Order(STU **head){
    // 检查链表为空或只有一个节点的情况
    if (*head == NULL || (*head)->next == NULL) {
        printf("无需排序。\n");
        return ;
    }

    STU *temp;  // 临时节点用于交换
    STU **ptr;  // 双重指针用于遍历链表
    
    int swapped; // 交换标志
    do {
        swapped = 0; // 重置交换标志
        ptr = head;  // 指向链表头部的指针的指针

        // 遍历链表
        while (*ptr!=NULL&& (*ptr)->next!= NULL) {
            if ((*ptr)->id > (*ptr)->next->id) {
                // 通过指针交换节点位置
                temp = (*ptr)->next; // 存储下一个节点
                (*ptr)->next = temp->next; // 当前节点的下一个指向temp的下一个
                temp->next = *ptr; // temp指向当前节点
                *ptr = temp; // 更新链表头部指针
                
                swapped = 1; // 标记已交换
            }
            ptr = &(*ptr)->next; // 移动到下一个节点
        }
    } while (swapped); // 如果本轮没有交换，则排序完成

    // 输出排序结果
    printf("排序完成！\n是否输出：（1为是，0为否）:");
    int a;
    scanf("%d", &a);
    if (a == 1) {
        Print_Students(*head); // 输出排序后的结果
    }
}

//8.按学号降序排序
void Id_Descending_Order(STU **head){
    // 检查链表为空或只有一个节点的情况
    if (*head == NULL || (*head)->next == NULL) {
        printf("无需排序。\n");
        return ;
    }

    STU *temp;  // 临时节点用于交换
    STU **ptr;  // 双重指针用于遍历链表
    
    int swapped; // 交换标志
    do {
        swapped = 0; // 重置交换标志
        ptr = head;  // 指向链表头部的指针的指针

        // 遍历链表
        while (*ptr!=NULL&& (*ptr)->next!= NULL) {
            if ((*ptr)->id < (*ptr)->next->id) {
                // 通过指针交换节点位置
                temp = (*ptr)->next; // 存储下一个节点
                (*ptr)->next = temp->next; // 当前节点的下一个指向temp的下一个
                temp->next = *ptr; // temp指向当前节点
                *ptr = temp; // 更新链表头部指针
                
                swapped = 1; // 标记已交换
            }
            ptr = &(*ptr)->next; // 移动到下一个节点
        }
    } while (swapped); // 如果本轮没有交换，则排序完成

    // 输出排序结果
    printf("排序完成！\n是否输出：（1为是，0为否）:");
    int a;
    scanf("%d", &a);
    if (a == 1) {
        Print_Students(*head); // 输出排序后的结果
    }
}

//9.按学号搜索
void  Search_ID(STU* head){
    int xh;
	printf("输入你想查找学生的学号：");
	scanf("%d", &xh);
    STU *current=head;
	while (current!=NULL){
        if (xh==current->id){
            printf("姓名：%-20s学号：%-10d实际出勤次数：%-5d\t应出勤次数：%-5d\t出勤率%.2lf\n",current->name,current->id,current->Actual_Attendance,current->Should_Attendance,current->Attendance*100);
            return ;
        }
        current=current->next;  // 移动到链表的末尾
    }
	printf("没有找到该学生！\n");
}

//10.按姓名搜索
void Search_Name(STU* head){
    char x[20];
	printf("输入你想查找学生的姓名：");
	scanf("%s", x);
    STU *current=head;
	while (current!=NULL){
        if (strcmp(x,current->name)==0){
            printf("姓名：%-20s学号：%-10d实际出勤次数：%-5d\t应出勤次数：%-5d\t出勤率%.2lf\n",current->name,current->id,current->Actual_Attendance,current->Should_Attendance,current->Attendance*100);
            return ;
        }
        current=current->next;  // 移动到链表的末尾
    }
	printf("没有找到该学生！\n");
}

//11.统计分析
void Statistical_Analysis(STU* head){
    STU* current=head;
    printf("全勤人员名单：\n");
    while (current!=NULL){
        if (current->Attendance==1)
            printf("姓名：%-20s学号：%-10d\n",current->name,current->id);
        current=current->next;
    }
    current=head;
    printf("\n非全勤人员名单：\n");
    while (current!=NULL){
        if (current->Attendance<1)
            printf("姓名：%-20s\t学号：%-10d\n",current->name,current->id);
        current=current->next;
    }
}

//12.打印链表中的学生信息
void Print_Students(STU* head) {
    STU* current=head;
    while (current!=NULL) {
        printf("姓名：%-20s学号：%-10d实际出勤次数：%-5d应出勤次数：%-5d出勤率%.2lf%%\n",current->name,current->id,current->Actual_Attendance,current->Should_Attendance,current->Attendance*100);
        current=current->next;
    }
}

//13.写入文件
void Write_To_File(STU* head){
    FILE* file = fopen("sams.dat", "w");
    if (file == NULL) {
        perror("文件打开失败!");
        exit(EXIT_FAILURE);
    }
    STU* current=head;
    while (current!= NULL) {
        fprintf(file,"%s,%d,%d,%d,%lf\n",current->name,current->id,current->Actual_Attendance,current->Should_Attendance,current->Attendance);
        current = current->next;
    }
    fclose(file);
    printf("数据写入完成！");
}

//14.从文件中读取
void Read_From_File(STU** head){
    FILE* file = fopen("sams.dat", "r");
    if (file == NULL) {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }
    STU* New_Student=NULL;
    STU** lastPtr=head; 
    while (1){
        New_Student = (STU*)malloc(sizeof(STU)); // 为每个新学生分配内存
        if (New_Student == NULL) {
            perror("内存分配失败");
            exit(EXIT_FAILURE);
        }

        if (fscanf(file,"%[^,],%d,%d,%d,%lf\n", New_Student->name,&New_Student->id,&New_Student->Actual_Attendance,&New_Student->Should_Attendance,&New_Student->Attendance)!=5){
            free(New_Student); 
            break;
        }
        New_Student->next=NULL;
        *lastPtr=New_Student; // 将新节点连接到当前最后一个节点的 next 指针上
        lastPtr=&((*lastPtr)->next); // 更新 lastPtr 到新的最后一个节点的 next 指针位置
    
        printf("数据读取完成！");
    }
    
    fclose(file);
}