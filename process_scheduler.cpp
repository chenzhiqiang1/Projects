#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#define max_process_number 5
using namespace std;

/*��ȡ�ļ�����*/
void readFile(string process[], int arrival_time[], int running_time[], int priority_number[]){
	ifstream inputfile("C:/Users/joh n/Desktop/process_scheduler.txt");
	if (!inputfile){
		cout << "Unable to open file!" << endl;
		exit(0);
	}
	string buffer;
	istringstream instring;
	int i = 0;
	cout << "�����������£�" << endl;
	cout << "����" << ' ' << "����ʱ��" << ' ' << "����ʱ��" << ' ' << "������" << endl;
	while (getline(inputfile, buffer)){
		instring.clear();           //�������д��룬��ȡ�ļ����ݳ��˵�һ���⣬�������ݾ�����
		instring.str(buffer);
		instring >> process[i] >> arrival_time[i] >> running_time[i] >> priority_number[i];
		cout << process[i] << '\t' << arrival_time[i] << '\t' << running_time[i] << '\t' << priority_number[i] << endl;
		i++;
	}
	cout << endl;
	inputfile.close();
}

/*������ʱ���С����Խ��̽�������*/
void selectSort(string process[], int arrival_time[], int running_time[], int priority_number[]){
	string temp1;
	int temp2, temp3,temp4;
	int k;
	for (int i = 0; i < max_process_number - 1; i++){
		k = i;
		for (int j = i+1; j < max_process_number; j++){
			if (arrival_time[i]>arrival_time[j]){
				k = j;
				temp2 = arrival_time[k]; temp1 = process[k]; temp3 = running_time[k]; temp4 = priority_number[k];
				arrival_time[k] = arrival_time[i]; process[k] = process[i]; running_time[k] = running_time[i]; priority_number[k] = priority_number[i];
				arrival_time[i] = temp2; process[i] = temp1; running_time[i] = temp3; priority_number[i] = temp4;
			}
		}
	}
	/*for (int i = 0; i < max_process_number; i++)
		cout <<process[i] << ' ' << arrival_time[i] << ' ' << running_time[i] << ' ' << priority_number[i] << endl;*/
}

/*����ҵ���ȣ�����ռ���㷨*/
void ShortestJobFirst1(string process[], int arrival_time[], int running_time[], int priority_number[]){
	string sequence[max_process_number];                    //����ִ�д�������
	int responsing_time[max_process_number];             //��Ӧʱ��
	int cycling_time[max_process_number];                    //��תʱ��
	int nowTime = 0;                       //�����Ѿ�ִ�е�ʱ��
	int min = 0;                                 //�����ҵ���
	int n = 0;                                     //��¼ִ�д���
	string temp1;
	int temp2, temp3, temp4;

	for (int i = 0; i < max_process_number; i++,n++){
		min = i;
		for (int j = i; arrival_time[j] <= nowTime/*�����ѷ�������*/&&j<max_process_number;j++){
			if (running_time[min]>running_time[j])min = j;               //�����ѷ�������Ľ����е���̽���
		}
		sequence[n] = process[min];
		responsing_time[n] = nowTime - arrival_time[min];
		nowTime += running_time[min];
		cycling_time[n] =nowTime - arrival_time[min];
		/*��Ӧ�ý����������̣�û���ýṹ�壬��
		û�н����������̣�������н������������P5����*/
		temp1 = process[min]; temp2 = arrival_time[min]; temp3 = running_time[min]; temp4 = priority_number[min];
		process[min] = process[i]; arrival_time[min] = arrival_time[i];  running_time[min] = running_time[i]; priority_number[min] = priority_number[i];
		process[i] = temp1; arrival_time[i] = temp2; running_time[i] = temp3; priority_number[i] = temp4;
	}

	cout << "����ҵ����(����ռ)�㷨��" << endl;
	cout << "ִ�д���" << ' ' << "��Ӧʱ��" << ' ' << "��תʱ��" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << sequence[i]<< '\t'<< responsing_time[i] <<'\t'<< cycling_time[i] << endl;
	cout << endl;
}

/*����ҵ���ȣ���ռ���㷨*/
void ShortestJobFirst2(string process[], int arrival_time[], int running_time[], int priority_number[]){
	selectSort(process, arrival_time, running_time, priority_number); //���������л�ԭ

	string sequence[1000];                    //����ִ�д������飬ÿ������ʱ����Ϊ1
	int responsing_time[max_process_number];             //��Ӧʱ��
	int cycling_time[max_process_number];                    //��תʱ��
	int runningTime[max_process_number] = { 0 };        //��¼ÿ�������Ѿ�ִ�е�ʱ��

	int sum_time = 0;                    //���н���һ��ִ�е�ʱ��
	for (int i = 0; i < max_process_number; i++){
		sum_time += running_time[i];
	}

	int nowTime = 0;                       //�����Ѿ�ִ�е�ʱ��
	int min = 0;                                 //�����ҵ���
	int n = 0;                                     //��¼ִ�д���
	/* �������������������P1������ʱ�����������н����ģ�����ÿ��min�����Գ�ʼ��Ϊ0��
	minӦ�ó�ʼ��Ϊ���н�����������ǰ�桢��û��ִ����Ľ������*/
	for (; n < sum_time; min=0,n++){
		for (int i = 0; i < max_process_number&&arrival_time[i] <= nowTime; i++){
			if (runningTime[i] >= running_time[i])continue;
			if (running_time[min]>running_time[i])min = i;
		}
		sequence[n] = process[min];
		runningTime[min]++;
		if (runningTime[min] == 1)responsing_time[min] = nowTime - arrival_time[min];
		nowTime++;
		if (runningTime[min] == running_time[min])cycling_time[min] = nowTime - arrival_time[min];
	}

	cout << "����ҵ����(��ռ)�㷨��" << endl;
	cout << "������ִ������Ϊ��" << endl;
	for (int i = 0; i < sum_time; i++)
		cout << sequence[i] << ' ';
	cout << endl;

	cout << "ִ�д���" << ' ' << "��Ӧʱ��" << ' ' << "��תʱ��" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << process[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;
}

/*������������ռ���㷨 */
void PrioritySchedule1(string process[], int arrival_time[], int running_time[], int priority_number[]){
	string sequence[max_process_number];                //����ִ�д�������
	int responsing_time[max_process_number];             //��Ӧʱ��
	int cycling_time[max_process_number];                    //��תʱ��
	int nowTime = 0;                       //�����Ѿ�ִ�е�ʱ��
	int n = 0;                                      //��¼ִ�д���
	int min = 0;                                 //��С���������
	string temp1;
	int temp2, temp3, temp4;

	for (int i = 0; i < max_process_number; i++, n++){
		min = i;
		for (int j = i; arrival_time[j] <= nowTime/*�����ѷ�������*/&&j<max_process_number; j++){
			if (priority_number[min]>priority_number[j])min = j;               //�����ѷ�������Ľ����е���̽���
		}
		sequence[n] = process[min];
		responsing_time[n] = nowTime - arrival_time[min];
		nowTime += running_time[min];
		cycling_time[n] = nowTime - arrival_time[min];
		/*��Ӧ�ý����������̣�û���ýṹ�壬��
		û�н����������̣�������н������������P5����*/
		temp1 = process[min]; temp2 = arrival_time[min]; temp3 = running_time[min]; temp4 = priority_number[min];
		process[min] = process[i]; arrival_time[min] = arrival_time[i];  running_time[min] = running_time[i]; priority_number[min] = priority_number[i];
		process[i] = temp1; arrival_time[i] = temp2; running_time[i] = temp3; priority_number[i] = temp4;
	}

	cout << "������(����ռ)�㷨��" << endl;
	cout << "ִ�д���" << ' ' << "��Ӧʱ��" << ' ' << "��תʱ��" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << sequence[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;
}

/*����������ռ���㷨 */
void PrioritySchedule2(string process[], int arrival_time[], int running_time[], int priority_number[]){
	selectSort(process, arrival_time, running_time, priority_number); //���������л�ԭ

	string sequence[1000];                    //����ִ�д������飬ÿ������ʱ����Ϊ1
	int responsing_time[max_process_number];             //��Ӧʱ��
	int cycling_time[max_process_number];                    //��תʱ��
	int runningTime[max_process_number] = { 0 };        //��¼ÿ�������Ѿ�ִ�е�ʱ��

	int sum_time = 0;                    //�������������
	for (int i = 0; i < max_process_number; i++){
		sum_time += running_time[i];
	}

	int nowTime = 0;                       //�����Ѿ�ִ�е�ʱ��
	int min = 0;                                 //�����ҵ���
	int n = 0;                                     //��¼ִ�д���
	/* �������������������P1������ʱ�����������н����ģ�����ÿ��min�����Գ�ʼ��Ϊ0��
	minӦ�ó�ʼ��Ϊ���н�����������ǰ�桢��û��ִ����Ľ������*/
	for (; n < sum_time; min = 0, n++){
		for (int i = 0; i < max_process_number&&arrival_time[i] <= nowTime; i++){
			if (runningTime[i] >= running_time[i])continue;
			if (priority_number[min]>priority_number[i])min = i;
		}
		sequence[n] = process[min];
		runningTime[min]++;
		if (runningTime[min] == 1)responsing_time[min] = nowTime - arrival_time[min];
		nowTime++;
		if (runningTime[min] == running_time[min])cycling_time[min] = nowTime - arrival_time[min];
	}

	cout << "������(��ռ)�㷨��" << endl;
	cout << "������ִ������Ϊ��" << endl;
	for (int i = 0; i < sum_time; i++)
		cout << sequence[i] << ' ';
	cout << endl;

	cout << "ִ�д���" << ' ' << "��Ӧʱ��" << ' ' << "��תʱ��" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << process[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;



}

int main(){
	string process[max_process_number];
	int arrival_time[max_process_number];
	int running_time[max_process_number];
	int priority_number[max_process_number];

	/*��ȡ�ļ�����*/
	readFile(process, arrival_time, running_time, priority_number);

	/*������ʱ���С����Խ��̽�������
	������ֳ��ĸ�����Ĳ������ˣ�Ӧ���ýṹ��QAQ*/
	selectSort(process, arrival_time, running_time, priority_number);

	/*����ҵ���ȣ�����ռ���㷨*/
	ShortestJobFirst1(process, arrival_time, running_time, priority_number);

	/*����ҵ���ȣ���ռ���㷨*/
	ShortestJobFirst2(process, arrival_time, running_time, priority_number);

	/*������������ռ���㷨 */
	PrioritySchedule1(process, arrival_time, running_time, priority_number);

	/*����������ռ���㷨 */
	PrioritySchedule2(process, arrival_time, running_time, priority_number);

	system("pause");      //û�����д��룬����ִ�к�����������
	return 0;
}