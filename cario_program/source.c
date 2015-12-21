// 헤더 선언
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
int menu(void);							// 메뉴 함수
void carin(void);						// 입차 함수
void dataadd(char* cnum, int* time);				// 입차시 데이터를 추가하는 함수
void carout(void);						// 출차 함수
void carlist(void);						// 입차한 차량 리스트를 보여주는 함수
void file_save(void);						// 현재 입차리스트를 이진파일로 저장하는 함수
void opt_save(void);						// 현재 옵션을 이진파일로 저장하는 함수
void file_load(void);						// 이진파일을 입차리스트로 불러오는 함수
void opt_load(void);						// 이진파일에서 현재 옵션으로 불러오는 함수
void option_setting(void);					// 옵션을 켜고 끌 수 있는 메뉴를 제공하는 함수

// 구조체 선언
typedef struct Carinfomation
{
	char cnum[12];						// 차량 번호
	int intime[3];						// 입차시간 (시간, 분, 초)
	int outtime[3];						// 출차시간 (시간, 분, 초)
} Cinfo;

// 동적할당
Cinfo *data;

// 전역 변수 선언 및 초기화
int size = 0;							// 현재 입차한 차량 수를 초기화
int opt[10] = { 0 };						// 옵션을 저장할 변수를 초기화

// 메인 함수
int main(void)
{
	data = NULL;						// 동적할당 초기화
	int choice = 0;						// 메뉴 선택을 저장할 변수 초기화
	opt_load();						// 저장된 옵션을 불러옴
	while (1)						// 무한루프
	{
		choice = menu();				// 메뉴함수를 불러와 선택한 메뉴번호를 choice에 저장
		if (choice == 7)				// choice가 7일 경우
			break;					// 종료
		switch (choice)					// choice값을 switch를 사용하여 해당하는 함수를 불러옴
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
	opt_save();						// 프로그램 종료전에 현재옵션을 option.dat에 저장함
	return 0;						// 프로그램 종료
}

int menu(void)							// 메뉴 출력 및 입력
{
	int i = 0;						// 
	system("cls");
	printf("메뉴 \n");
	printf("1. 입차\n");
	printf("2. 출차\n");
	printf("3. 목록\n");
	printf("4. 저장\n");
	printf("5. 로드\n");
	printf("6. 옵션\n");
	printf("7. 종료\n");
	scanf("%d", &i);
	while (getchar() != '\n');		// 입력버퍼를 비움
	return i;
}

void carin(void)				// 입차
{
	int i;
	struct Carinfomation car;
	struct tm *t;
	time_t timer;
	FILE* fp;

	if (opt[0] == 1)
		file_load();

	system("cls");
	printf("차량 번호 : ");
	scanf("%s", car.cnum);
	while (getchar() != '\n');

	for (i = 0; i < size; i++)
	{
		if (strcmp(data[i].cnum, car.cnum) == 0)
		{
			printf("이미 입차한 차량입니다.\n");
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
	printf("차량번호 : %s\n", car.cnum);
	printf("입차시간 : %d시 %d분 %d초\n", car.intime[0], car.intime[1], car.intime[2]);
	dataadd(car.cnum, car.intime);
	system("pause");
	fp = fopen("log.txt", "a");
	fprintf(fp, "%d시 %d분 %d초  %s 입차\n", car.intime[0], car.intime[1], car.intime[2], car.cnum);
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
	printf("데이터 추가 성공\n");
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
	printf("차량 번호 : ");
	scanf("%s", cnum);
	while (getchar() != '\n');

	if (data == NULL)
	{
		printf("차량 정보가 존재하지 않습니다.\n");
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
			printf("차량번호 : %s\n", cnum);
			printf("입차시간 : %d시 %d분 %d초\n", data[i].intime[0], data[i].intime[1], data[i].intime[2]);
			printf("출차시간 : %d시 %d분 %d초\n", data[i].outtime[0], data[i].outtime[1], data[i].outtime[2]);
			system("pause");
			break;
		}
		else if (i == size - 1)
		{
			printf("차량 정보가 존재하지 않습니다.\n");
			system("pause");
			return;
		}
	}
	fp = fopen("log.txt", "a");
	fprintf(fp, "%d시 %d분 %d초  %s 출차\n", data[i].outtime[0], data[i].outtime[1], data[i].outtime[2], cnum);
	fclose(fp);

	fp = fopen("complete.txt", "a");
	fprintf(fp, "%s 입차시간 : %d시 %d분 %d초 출차시간 : %d시 %d분 %d초\n", cnum, data[i].intime[0], data[i].intime[1], data[i].intime[2], data[i].outtime[0], data[i].outtime[1], data[i].outtime[2]);

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
	printf("차량번호\t입차시간\n");
	for (i = 0; i < size; i++)
		printf("%s\t%d시 %d분 %d초\n", data[i].cnum, data[i].intime[0], data[i].intime[1], data[i].intime[2]);
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
	char a[5] = "켜짐";
	char b[5] = "꺼짐";
	char c[5];
	int choice;
	system("cls");
	printf("   옵션\n\n");
	if (opt[0] == 0)
		strcpy(c, b);
	else
		strcpy(c, a);
	printf("1. 자동저장 (%s)\n", c);
	printf("2. 저장된 데이터 삭제\n");
	printf("3. 뒤로가기\n");

	scanf("%d", &choice);
	switch (choice) {
	case 1:
		if (opt[0] == 0)
		{
			printf("자동 저장옵션 켜짐\n");
			opt[0] = 1;
		}
		else
		{
			printf("자동 저장옵션 꺼짐\n");
			opt[0] = 0;
		}
		break;
	case 2:
		
		system("del data.dat");
		system("del log.txt");
		system("del complete.txt");
		system("pause");
		break;
	case 3:
		break;
	}
}
