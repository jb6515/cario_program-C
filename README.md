# cario_program-C

차량 입출차 프로그램

사용한 프로그래밍언어 : C언어
사용된 C언어 내용
- 파일입출력
- 구조체
- 동적할당
- time.h함수

프로그램 기능 및 설명
- 입차
- 출차
- 목록
- 저장
- 로드
- 옵션
- 종료

구현한 함수들
- int menu(void); // 메뉴를 불러오는 함수
- void carin(void); // 입차 함수
- void dataadd(char* cnum, int* time); // 입차시 데이터를 추가하는 함수
- void carout(void); // 출차 함수
- void carlist(void); // 입차한 차들의 리스트를 불러오는 함수
- void file_save(void); // 파일을 저장하는 함수
- void opt_save(void); // 옵션을 저장하는 함수
- void file_load(void); // 파일을 불러오는 함수
- void opt_load(void); // 옵션을 불러오는 함수
- void option_setting(void); // 옵션메뉴 함수

입차시
- 차량 번호를 입력받음
- 입차 여부 확인
- 현재 시간을 불러옴
- 현재 시간과 차량번호를 동적할당하여 추가(datadd함수를 호출)
- log파일에 차량번호와 입차시간을 기록
- 자동저장옵션이 켜져있을 경우 data.bin에 현재 데이터들을 기록

출차시
- 차량 번호를 입력받음
- 입차 여부를 확인
- 현재 시간을 불러옴
- log파일에 차량번호와 출차시간을 기록
- compelete.txt파일에 입차시간과 출차 시간을 기록
- 차량 번호에 대한 정보를 삭제(동적할당)
- 자동저장옵션이 켜져있을 경우 data.bin에 현재 데이터들을 기록

옵션
- 별도로 setting.dat파일에 이진형식으로 저장
- 프로그램 시작시 옵션을 불러오고, 프로그램 종료시 옵션을 저장
