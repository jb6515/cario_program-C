// ��� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#pragma warning(disable:4013)

// �Լ� ����
int menu(void);
void carin(void);
void dataadd(char* cnum, int* time);
void carout(void);
void carlist(void);
void file_save(void);
void opt_save(void);
void file_load(void);
void opt_load(void);
void option_setting(void);

// ����ü ����
typedef struct Carinfomation
{
	char cnum[12];
	int intime[3];
	int outtime[3];
} Cinfo;

// �����Ҵ�
Cinfo *data;

// ���� ����
int size = 0;
int opt[10] = { 0 };

// ���� �Լ�
int main(void)
{
	data = NULL;
	int choice = 0;
	opt_load();
	while (1)
	{
		choice = menu();
		if (choice == 7)
			break;
		switch (choice)
		{
		case 1:
			carin();
			break;
		case 2:
			carout();
			break;
		case 3:
			carlist();
			break;
		case 4:
			file_save();
			break;
		case 5:
			file_load();
			break;
		case 6:
			option_setting();
			break;
		}
	}
	opt_save();
	return 0;
}

int menu(void)					// �޴� ��� �� �Է�
{
	int i = 0;
	system("cls");
	printf("�޴� \n");
	printf("1. ����\n");
	printf("2. ����\n");
	printf("3. ���\n");
	printf("4. ����\n");
	printf("5. �ε�\n");
	printf("6. �ɼ�\n");
	printf("7. ����\n");
	scanf("%d", &i);
	while (getchar() != '\n');		// �Է¹��۸� ���
	return i;
}

void carin(void)				// ����
{
	int i;
	struct Carinfomation car;
	struct tm *t;
	time_t timer;
	FILE* fp;

	if (opt[0] == 1)
		file_load();

	system("cls");
	printf("���� ��ȣ : ");
	scanf("%s", car.cnum);
	while (getchar() != '\n');

	for (i = 0; i < size; i++)
	{
		if (strcmp(data[i].cnum, car.cnum) == 0)
		{
			printf("�̹� ������ �����Դϴ�.\n");
			system("pause");
			return;
		}
	}

	timer = time(NULL);
	t = localtime(&timer);
	car.intime[0] = t->tm_hour;
	car.intime[1] = t->tm_min;
	car.intime[2] = t->tm_sec;

	system("cls");
	printf("������ȣ : %s\n", car.cnum);
	printf("�����ð� : %d�� %d�� %d��\n", car.intime[0], car.intime[1], car.intime[2]);
	dataadd(car.cnum, car.intime);
	system("pause");
	fp = fopen("log.txt", "a");
	fprintf(fp, "%d�� %d�� %d��  %s ����\n", car.intime[0], car.intime[1], car.intime[2], car.cnum);
	fclose(fp);

	if (opt[0] == 1)
		file_save();
}

void dataadd(char* cnum, int* time)
{
	size++;
	int i = 0, j = 0, k = 0;
	if (data == NULL)
		data = (Cinfo*)malloc(sizeof(Cinfo));

	if (size > 1)
	{

		Cinfo* temp = (Cinfo*)malloc(sizeof(Cinfo)*size);
		for (i = 0; i < size - 1; i++)
		{
			temp[j] = data[i];
			j++;
		}
		strcpy(temp[j].cnum, cnum);
		for (k = 0; k < 3; k++)
		{
			temp[j].intime[k] = time[k];
		}
		free(data);
		data = temp;

	}
	else
	{
		strcpy(data[size - 1].cnum, cnum);
		for (i = 0; i < 3; i++)
			data[size - 1].intime[i] = time[i];

	}
	printf("������ �߰� ����\n");
}

void carout(void)
{
	FILE* fp;
	int i, k = 0, j;
	char cnum[12];
	struct tm *t;
	time_t timer;

	if (opt[0] == 1)
		file_load();

	system("cls");
	printf("���� ��ȣ : ");
	scanf("%s", cnum);
	while (getchar() != '\n');

	if (data == NULL)
	{
		printf("���� ������ �������� �ʽ��ϴ�.\n");
		system("pause");
		return;
	}

	for (i = 0; i < size; i++)
	{
		if (strcmp(data[i].cnum, cnum) == 0)
		{
			timer = time(NULL);
			t = localtime(&timer);
			data[i].outtime[0] = t->tm_hour;
			data[i].outtime[1] = t->tm_min;
			data[i].outtime[2] = t->tm_sec;
			system("cls");
			printf("������ȣ : %s\n", cnum);
			printf("�����ð� : %d�� %d�� %d��\n", data[i].intime[0], data[i].intime[1], data[i].intime[2]);
			printf("�����ð� : %d�� %d�� %d��\n", data[i].outtime[0], data[i].outtime[1], data[i].outtime[2]);
			system("pause");
			break;
		}
		else if (i == size - 1)
		{
			printf("���� ������ �������� �ʽ��ϴ�.\n");
			system("pause");
			return;
		}
	}
	fp = fopen("log.txt", "a");
	fprintf(fp, "%d�� %d�� %d��  %s ����\n", data[i].outtime[0], data[i].outtime[1], data[i].outtime[2], cnum);
	fclose(fp);

	fp = fopen("complete.txt", "a");
	fprintf(fp, "%s �����ð� : %d�� %d�� %d�� �����ð� : %d�� %d�� %d��\n", cnum, data[i].intime[0], data[i].intime[1], data[i].intime[2], data[i].outtime[0], data[i].outtime[1], data[i].outtime[2]);

	fclose(fp);

	Cinfo* temp = (Cinfo*)malloc(sizeof(Cinfo)*(size - 1));
	for (j = 0; j < size; j++)
	{
		if (j != i)
		{
			temp[k] = data[j];
			k++;
		}
	}
	free(data);
	data = temp;
	size--;

	if (opt[0] == 1)
		file_save();
}

void carlist(void)
{
	int i;
	system("cls");
	if (opt[0] == 1)
		file_load();
	printf("������ȣ\t�����ð�\n");
	for (i = 0; i < size; i++)
		printf("%s\t%d�� %d�� %d��\n", data[i].cnum, data[i].intime[0], data[i].intime[1], data[i].intime[2]);
	system("pause");
}

void file_save(void)
{
	FILE* fp = fopen("data.dat", "wb");
	if (fp == NULL)
		return;
	fwrite(&size, sizeof(int), 1, fp);
	fwrite(data, sizeof(Cinfo), size, fp);
	fclose(fp);
}

void opt_save(void)
{
	FILE* fp = fopen("setting.dat", "wb");
	if (fp == NULL)
		return;
	fwrite(opt, sizeof(int), 10, fp);
	fclose(fp);
}

void file_load(void)
{
	FILE* fp = fopen("data.dat", "rb");
	if (fp == NULL)
		return;
	fread(&size, sizeof(int), 1, fp);
	data = (Cinfo*)malloc(sizeof(Cinfo)*size);
	fread(data, sizeof(Cinfo), size, fp);
	fclose(fp);
}

void opt_load(void)
{
	FILE* fp = fopen("setting.dat", "rb");
	if (fp == NULL)
		return;
	fread(opt, sizeof(int), 10, fp);
	fclose(fp);
}

void option_setting(void)
{
	char a[5] = "����";
	char b[5] = "����";
	char c[5];
	int choice;
	system("cls");
	printf("   �ɼ�\n\n");
	if (opt[0] == 0)
		strcpy(c, b);
	else
		strcpy(c, a);
	printf("1. �ڵ����� (%s)\n", c);
	printf("2. ����� ������ ����\n");

	scanf("%d", &choice);
	switch (choice) {
	case 1:
		if (opt[0] == 0)
		{
			printf("�ڵ� ����ɼ� ����\n");
			opt[0] = 1;
		}
		else
		{
			printf("�ڵ� ����ɼ� ����\n");
			opt[0] = 0;
		}
		break;
	case 2:
		system("del data.dat");
		system("del log.txt");
		system("pause");
		break;
	}
}