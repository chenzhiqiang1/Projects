#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#define max_process_number 5
using namespace std;

/*读取文件数据*/
void readFile(string process[], int arrival_time[], int running_time[], int priority_number[]){
	ifstream inputfile("C:/Users/joh n/Desktop/process_scheduler.txt");
	if (!inputfile){
		cout << "Unable to open file!" << endl;
		exit(0);
	}
	string buffer;
	istringstream instring;
	int i = 0;
	cout << "进程序列如下：" << endl;
	cout << "进程" << ' ' << "到达时间" << ' ' << "运行时间" << ' ' << "优先数" << endl;
	while (getline(inputfile, buffer)){
		instring.clear();           //不加这行代码，读取文件数据除了第一行外，其他数据均出错
		instring.str(buffer);
		instring >> process[i] >> arrival_time[i] >> running_time[i] >> priority_number[i];
		cout << process[i] << '\t' << arrival_time[i] << '\t' << running_time[i] << '\t' << priority_number[i] << endl;
		i++;
	}
	cout << endl;
	inputfile.close();
}

/*按到达时间从小到大对进程进行排序*/
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

/*短作业优先（非抢占）算法*/
void ShortestJobFirst1(string process[], int arrival_time[], int running_time[], int priority_number[]){
	string sequence[max_process_number];                    //进程执行次序数组
	int responsing_time[max_process_number];             //响应时间
	int cycling_time[max_process_number];                    //周转时间
	int nowTime = 0;                       //进程已经执行的时间
	int min = 0;                                 //最短作业序号
	int n = 0;                                     //记录执行次序
	string temp1;
	int temp2, temp3, temp4;

	for (int i = 0; i < max_process_number; i++,n++){
		min = i;
		for (int j = i; arrival_time[j] <= nowTime/*进程已发出请求*/&&j<max_process_number;j++){
			if (running_time[min]>running_time[j])min = j;               //计算已发出请求的进程中的最短进程
		}
		sequence[n] = process[min];
		responsing_time[n] = nowTime - arrival_time[min];
		nowTime += running_time[min];
		cycling_time[n] =nowTime - arrival_time[min];
		/*还应该交换两个进程，没有用结构体，神烦
		没有交换两个进程，最后运行结果出现了两个P5进程*/
		temp1 = process[min]; temp2 = arrival_time[min]; temp3 = running_time[min]; temp4 = priority_number[min];
		process[min] = process[i]; arrival_time[min] = arrival_time[i];  running_time[min] = running_time[i]; priority_number[min] = priority_number[i];
		process[i] = temp1; arrival_time[i] = temp2; running_time[i] = temp3; priority_number[i] = temp4;
	}

	cout << "短作业优先(非抢占)算法：" << endl;
	cout << "执行次序" << ' ' << "响应时间" << ' ' << "周转时间" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << sequence[i]<< '\t'<< responsing_time[i] <<'\t'<< cycling_time[i] << endl;
	cout << endl;
}

/*短作业优先（抢占）算法*/
void ShortestJobFirst2(string process[], int arrival_time[], int running_time[], int priority_number[]){
	selectSort(process, arrival_time, running_time, priority_number); //将进程序列还原

	string sequence[1000];                    //进程执行次序数组，每个进程时间间隔为1
	int responsing_time[max_process_number];             //响应时间
	int cycling_time[max_process_number];                    //周转时间
	int runningTime[max_process_number] = { 0 };        //记录每个进程已经执行的时间

	int sum_time = 0;                    //所有进程一共执行的时间
	for (int i = 0; i < max_process_number; i++){
		sum_time += running_time[i];
	}

	int nowTime = 0;                       //进程已经执行的时间
	int min = 0;                                 //最短作业序号
	int n = 0;                                     //记录执行次序
	/* 现在是特殊情况，进程P1是运行时间最长且最后运行结束的，所以每次min都可以初始化为0。
	min应该初始化为所有进程中排在最前面、还没有执行完的进程序号*/
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

	cout << "短作业优先(抢占)算法：" << endl;
	cout << "各进程执行序列为：" << endl;
	for (int i = 0; i < sum_time; i++)
		cout << sequence[i] << ' ';
	cout << endl;

	cout << "执行次序" << ' ' << "响应时间" << ' ' << "周转时间" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << process[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;
}

/*优先数（非抢占）算法 */
void PrioritySchedule1(string process[], int arrival_time[], int running_time[], int priority_number[]){
	string sequence[max_process_number];                //进程执行次序数组
	int responsing_time[max_process_number];             //响应时间
	int cycling_time[max_process_number];                    //周转时间
	int nowTime = 0;                       //进程已经执行的时间
	int n = 0;                                      //记录执行次序
	int min = 0;                                 //最小优先数序号
	string temp1;
	int temp2, temp3, temp4;

	for (int i = 0; i < max_process_number; i++, n++){
		min = i;
		for (int j = i; arrival_time[j] <= nowTime/*进程已发出请求*/&&j<max_process_number; j++){
			if (priority_number[min]>priority_number[j])min = j;               //计算已发出请求的进程中的最短进程
		}
		sequence[n] = process[min];
		responsing_time[n] = nowTime - arrival_time[min];
		nowTime += running_time[min];
		cycling_time[n] = nowTime - arrival_time[min];
		/*还应该交换两个进程，没有用结构体，神烦
		没有交换两个进程，最后运行结果出现了两个P5进程*/
		temp1 = process[min]; temp2 = arrival_time[min]; temp3 = running_time[min]; temp4 = priority_number[min];
		process[min] = process[i]; arrival_time[min] = arrival_time[i];  running_time[min] = running_time[i]; priority_number[min] = priority_number[i];
		process[i] = temp1; arrival_time[i] = temp2; running_time[i] = temp3; priority_number[i] = temp4;
	}

	cout << "优先数(非抢占)算法：" << endl;
	cout << "执行次序" << ' ' << "响应时间" << ' ' << "周转时间" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << sequence[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;
}

/*优先数（抢占）算法 */
void PrioritySchedule2(string process[], int arrival_time[], int running_time[], int priority_number[]){
	selectSort(process, arrival_time, running_time, priority_number); //将进程序列还原

	string sequence[1000];                    //进程执行次序数组，每个进程时间间隔为1
	int responsing_time[max_process_number];             //响应时间
	int cycling_time[max_process_number];                    //周转时间
	int runningTime[max_process_number] = { 0 };        //记录每个进程已经执行的时间

	int sum_time = 0;                    //这里代码冗余了
	for (int i = 0; i < max_process_number; i++){
		sum_time += running_time[i];
	}

	int nowTime = 0;                       //进程已经执行的时间
	int min = 0;                                 //最短作业序号
	int n = 0;                                     //记录执行次序
	/* 现在是特殊情况，进程P1是运行时间最长且最后运行结束的，所以每次min都可以初始化为0。
	min应该初始化为所有进程中排在最前面、还没有执行完的进程序号*/
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

	cout << "优先数(抢占)算法：" << endl;
	cout << "各进程执行序列为：" << endl;
	for (int i = 0; i < sum_time; i++)
		cout << sequence[i] << ' ';
	cout << endl;

	cout << "执行次序" << ' ' << "响应时间" << ' ' << "周转时间" << endl;
	for (int i = 0; i < max_process_number; i++)
		cout << process[i] << '\t' << responsing_time[i] << '\t' << cycling_time[i] << endl;
	cout << endl;



}

int main(){
	string process[max_process_number];
	int arrival_time[max_process_number];
	int running_time[max_process_number];
	int priority_number[max_process_number];

	/*读取文件数据*/
	readFile(process, arrival_time, running_time, priority_number);

	/*按到达时间从小到大对进程进行排序，
	这就体现出四个数组的不方便了，应该用结构体QAQ*/
	selectSort(process, arrival_time, running_time, priority_number);

	/*短作业优先（非抢占）算法*/
	ShortestJobFirst1(process, arrival_time, running_time, priority_number);

	/*短作业优先（抢占）算法*/
	ShortestJobFirst2(process, arrival_time, running_time, priority_number);

	/*优先数（非抢占）算法 */
	PrioritySchedule1(process, arrival_time, running_time, priority_number);

	/*优先数（抢占）算法 */
	PrioritySchedule2(process, arrival_time, running_time, priority_number);

	system("pause");      //没有这行代码，程序执行后出现闪退情况
	return 0;
}