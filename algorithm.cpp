#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono;

double BubbleSort(vector<int> &v)// 버블정렬
{
	int n = static_cast<int>(v.size());
	system_clock::time_point start = system_clock::now();//시간측정 시작
	
	while (n > 0) {
		int lastModifiedIndex = 0;
		for (int currentIndex = 1; currentIndex < n; currentIndex++) {
			if (v[currentIndex - 1] > v[currentIndex]) { // 앞이 뒤보다 클 경우
				// 교환
				int temp = v[currentIndex - 1];
				v[currentIndex - 1] = v[currentIndex];
				v[currentIndex] = temp;
				lastModifiedIndex = currentIndex;//교환여부를 나타냄
			}
		}
		n = lastModifiedIndex;//n=0일 경우는 이미 정렬된경우 밖에 없음
	}

	system_clock::time_point end = system_clock::now();//시간측정 끝
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환
	return (double)(milliSec.count());
}
//=========================================================================================================
double SelectionSort(std::vector<int> &v) //선택정렬
{
	system_clock::time_point start = system_clock::now();//시간측정 시작

	for (int currentIndex = 0; currentIndex < v.size() - 1; currentIndex++) {
		int minIndex = currentIndex;//가장 왼쪽 인덱스를 미니멈 인덱스로 임시지정
		for (int i = currentIndex + 1; i < v.size(); i++) {//미니멈 인덱스 찾기
			if (v[i] < v[minIndex]) {//비교값이 현재 미니멈보다 작을때
				minIndex = i; //미니멈인덱스 갱신
			}
		}
		if (minIndex != currentIndex) {//비교중인 인덱스랑 미니멈 인덱스가 다를경우 비교값보다 작은 인덱스가 있기때문에 스왑
			int temp = v[currentIndex];
			v[currentIndex] = v[minIndex];
			v[minIndex] = temp;
		}
	}

	system_clock::time_point end = system_clock::now();//시간측정 끝
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환
	return (double)(milliSec.count());
}

//=========================================================================================================
static int partition_1(vector<int> &v, int startIndex, int endIndex) //순서상 중간값 파티션
{
	int pivotIndex = (startIndex + endIndex) / 2;
	int pivotValue = v[pivotIndex];//순서상 가운데 인덱스를 피봇
	while (true) {
		while (v[startIndex] < pivotValue) {//left 피봇
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex]>=v[startIndex]) {//right 피봇
			if (startIndex == endIndex) {// 두 피봇이 만났는 경우이며 두 피봇이 만난 지점을 반환
				return endIndex;
			}
			endIndex--;
		}

		
		// left 와 right 피봇을 교환
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_1(vector<int> &v, int startIndex, int endIndex) //순서상 중간값을 피봇으로 하는 퀵정렬
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_1(v, startIndex, endIndex);// 둘로 나뉨
		QuickSort_1(v, startIndex, pivotIndex);//앞 벡터
		QuickSort_1(v, pivotIndex + 1, endIndex);//뒷 벡터
	}
}
//=========================================================================================================
int FindMid(int a, int b, int c)//중앙값 구하는 함수
{
	if (a >= b) {
		if (b >= c) return b;
		else if (a <= c) return a;
		else return c;
	}
	else if(a >= c) return a;
	else if (b >= c) return c;
	else return b;
}

static int partition_2(vector<int> &v, int startIndex, int endIndex) //순서상 첫값,끝값,중간값을 비교하여 중앙값을 피봇으로 삼는 파티션
{
	int pivotIndex = (startIndex + endIndex) / 2;
	int pivotValue = FindMid(v[startIndex], v[endIndex], v[pivotIndex]);//중앙값 피봇지정
	
	while (true) {
		while (v[startIndex] < pivotValue) {//left 피봇
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex] >= v[startIndex]) {//right 피봇
			if (startIndex == endIndex) {// 두 피봇이 만났는 경우이며 두 피봇이 만난 지점을 반환
				return endIndex;
			}
			endIndex--;
		}
		// left 와 right 피봇을 교환
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_2(vector<int> &v, int startIndex, int endIndex) //순서상 중간값을 피봇으로 하는 퀵정렬
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_2(v, startIndex, endIndex);// 둘로 나뉨
		QuickSort_2(v, startIndex, pivotIndex);//앞 벡터
		QuickSort_2(v, pivotIndex + 1, endIndex);//뒷 벡터
	}
}
//=========================================================================================================
static int partition_worst(vector<int> &v, int startIndex, int endIndex) //제일 처음을 피벗으로 삼음
{
	int pivotIndex = startIndex;
	int pivotValue = v[pivotIndex];//순서상 제일 앞 인덱스를 피봇
	while (true) {
		while (v[startIndex] < pivotValue) {//left 피봇
			startIndex++;
		}

		while (v[endIndex] >= pivotValue && v[endIndex] >= v[startIndex]) {//right 피봇
			if (startIndex == endIndex) {// 두 피봇이 만났는 경우이며 두 피봇이 만난 지점을 반환
				return endIndex;
			}
			endIndex--;
		}


		// left 와 right 피봇을 교환
		int temp = v[startIndex];
		v[startIndex] = v[endIndex];
		v[endIndex] = temp;
	}
}

void QuickSort_worst(vector<int> &v, int startIndex, int endIndex) //제일 처음값을 피봇으로 하는 퀵정렬
{
	if (startIndex < endIndex) {
		int pivotIndex = partition_worst(v, startIndex, endIndex);// 둘로 나뉨
		QuickSort_worst(v, startIndex, pivotIndex);//앞 벡터
		QuickSort_worst(v, pivotIndex + 1, endIndex);//뒷 벡터
	}
}
//=========================================================================================================
void Merge(vector<int> &v, int start, int middle, int end) 
{

	static vector<int> leftArray(middle - start + 1);
	static vector<int> rightArray(end - middle);

	//왼쪽 배열에 복사
	for (int i = 0; i < leftArray.size(); ++i)
		leftArray[i] = v[start + i];

	// 오른쪽 배열에 복사
	for (int i = 0; i < rightArray.size(); ++i)
		rightArray[i] = v[middle + 1 + i];

	int leftIndex = 0, rightIndex = 0; //왼쪽 오른쪽 인덱스 초기화
	int currentIndex = start;  //원본 배열에 병합하기 위해 배열 시작점 설정

	// 왼쪽과 오른쪽 배열 비교하면서 작은것부터 넣어 병합
	while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
		if (leftArray[leftIndex] <= rightArray[rightIndex]) {//왼쪽이 오른쪽보다 비교값이 작을때
			v[currentIndex] = leftArray[leftIndex];
			leftIndex++;
		}
		else {//오른쪽이 왼쪽보다 작거나 같을때
			v[currentIndex] = rightArray[rightIndex];
			rightIndex++;
		}
		currentIndex++;
	}

	// 남은 왼쪽배열 마저 병합
	while (leftIndex < leftArray.size()) v[currentIndex++] = leftArray[leftIndex++];

	//남은 오른쪽 배열 마저 병합
	while (rightIndex < rightArray.size()) v[currentIndex++] = rightArray[rightIndex++];
}


void MergeSort(vector<int> &v, int start, int end) 
{
	if (start < end) {
		// 중간점 찾기
		int middle = (start + end) / 2;

		MergeSort(v, start, middle); // 반으로 나뉜뒤 앞쪽 배열 정렬
		MergeSort(v, middle + 1, end);  // 뒷쪽배열 정렬

		Merge(v, start, middle, end); //나뉜 두 배열 merge
	}
}
//=========================================================================================================

double ShellSort(vector<int> &v)
{
	system_clock::time_point start = system_clock::now();//시간측정 시작

	for (int gapSize = v.size() / 2; gapSize > 0; gapSize /= 2) {
		for (int currentIndex = gapSize; currentIndex < v.size(); currentIndex++) {
			//삽입정렬을 위해 초기화
			int currentIndexCopy = currentIndex;
			int currentIndexValue = v[currentIndex];
			//gap단위로 건너 삽입정렬
			while (currentIndexCopy >= gapSize && v[currentIndexCopy - gapSize] > currentIndexValue) {
				v[currentIndexCopy] = v[currentIndexCopy - gapSize];
				currentIndexCopy -= gapSize;
			}
			v[currentIndexCopy] = currentIndexValue;
		}
	}

	system_clock::time_point end = system_clock::now();//시간측정 끝
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환
	return (double)(milliSec.count());
}

//=========================================================================================================
void pushbackReverse(vector<int>& v, int num) 
{
	for (unsigned int i = num; i > 0; i--) {
		v.push_back(i);
	}
}
void pushbackSorted(vector<int>& v, int num)
{
	for (unsigned int i = 0; i < num; i++) {
		v.push_back(i);
	}
}
void pushbackRandom(vector<int>& v, int num) 
{
	int tmp;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, num);
	for (int i = 0; i <num ; i++) {
		tmp = dis(gen);
		v.push_back(tmp);
	}
}
//=========================================================================================================
template<typename Func>
double RandomVectorSortAverage(int testCase, int vectorSize, Func SortType) //랜덤백터정렬을 테스트케이스 만큼 실행하여 각각 실행시간을 측정하여 평균값 반환
{
	
	double result = 0;
	for (int i = 0; i < testCase; i++) {
		vector<int> randomVector;
		pushbackRandom(randomVector, vectorSize);
		result += SortType(randomVector);
		randomVector.clear();
	}
	return result / testCase;
}

template<typename Func>
double ReverseVectorSort(int vectorSize, Func SortType) //역으로 나열된 백터를 정렬하여 실행시간 반환
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackReverse(reverseVector, vectorSize);
	return SortType(reverseVector);
}

template<typename Func>
double SortedVectorSort(int vectorSize, Func SortType) //역으로 나열된 백터를 정렬하여 실행시간 반환
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackSorted(reverseVector, vectorSize);
	return SortType(reverseVector);
}

template<typename Func>
double ForQuickSortRandomVectorSortAverage(int testCase, int vectorSize, Func SortType) //랜덤백터정렬을 테스트케이스 만큼 실행하여 각각 실행시간을 측정하여 평균값 반환
{
	
	double result = 0;
	for (int i = 0; i < testCase; i++) {
		vector<int> randomVector;
		pushbackRandom(randomVector, vectorSize);

		system_clock::time_point start = system_clock::now();//시간측정 시작
		SortType(randomVector, 0, (vectorSize - 1));
		system_clock::time_point end = system_clock::now();//시간측정 끝
		milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환
		result += (double)(milliSec.count());
		randomVector.clear();
	}
	return result / testCase;
}
template<typename Func>
double ForQuickSortReverseVectorSort(int vectorSize, Func SortType) //역으로 나열된 백터를 정렬하여 실행시간 반환
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackReverse(reverseVector, vectorSize);

	system_clock::time_point start = system_clock::now();//시간측정 시작
	SortType(reverseVector, 0, (vectorSize - 1));
	system_clock::time_point end = system_clock::now();//시간측정 끝
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환
	
	return (double)(milliSec.count());
}

template<typename Func>
double ForQuickSortSortedVectorSort(int vectorSize, Func SortType) //역으로 나열된 백터를 정렬하여 실행시간 반환
{
	vector<int> reverseVector;
	//reverseVector.resize(vectorSize);
	pushbackSorted(reverseVector, vectorSize);

	system_clock::time_point start = system_clock::now();//시간측정 시작
	SortType(reverseVector, 0, static_cast<int>(vectorSize - 1));
	system_clock::time_point end = system_clock::now();//시간측정 끝
	milliseconds milliSec = duration_cast<milliseconds>(end - start);//틱을 밀리초로 변환

	return (double)(milliSec.count());
}

int main() 
{
	
	cout << "SortedBubbleSort \t" << SortedVectorSort(10000, BubbleSort) << "  ms" << endl;
	cout <<"randomBubbleSort \t"<< RandomVectorSortAverage(5, 10000, BubbleSort) << " ms" << endl;
	cout << "reverseBubbleSort \t"<<ReverseVectorSort(10000, BubbleSort) << "  ms" << endl;
	cout << endl;
	cout << "SortedSelectionSort \t" << SortedVectorSort(10000, SelectionSort) << "  ms" << endl;
	cout << "randomSelectionSort \t" << RandomVectorSortAverage(5, 10000, SelectionSort) << " ms" << endl;
	cout << "reverseSelectionSort \t" << ReverseVectorSort(10000, SelectionSort) << "  ms" << endl;
	cout << endl;
	
	cout << "quckSort_IndexMid_Pivot_Sorted \t\t" << ForQuickSortSortedVectorSort(10000, QuickSort_1) << "ms" << endl;
	cout << "quckSort_IndexMid_Pivot_Random \t\t" << ForQuickSortRandomVectorSortAverage(5, 10000, QuickSort_1) << "ms" << endl;
	cout << "quckSort_IndexMid_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(10000, QuickSort_1) << "ms" << endl;
	cout << endl;
	cout << "quckSort_ValueMid_Pivot_Sorted \t\t" << ForQuickSortSortedVectorSort(10000, QuickSort_2) << "ms" << endl;
	cout << "quckSort_ValueMid_Pivot_Random \t\t" << ForQuickSortRandomVectorSortAverage(5, 10000, QuickSort_2) << "ms" << endl;
	cout << "quckSort_ValueMid_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(10000, QuickSort_2) << "ms" << endl;
	cout << endl;
	
	cout << "quckSort_FirstIndex_Pivot_Sorted \t" << ForQuickSortSortedVectorSort(1000, QuickSort_worst) << "ms" << endl;
	cout << "quckSort_FirstIndex_Pivot_Random \t" << ForQuickSortRandomVectorSortAverage(5, 1000, QuickSort_worst) << "ms" << endl;
	cout << "quckSort_FirstIndex_Pivot_Reverse \t" << ForQuickSortReverseVectorSort(1000, QuickSort_worst) << "ms" << endl;
	cout << endl;


	cout << "MergeSortSorted \t" << ForQuickSortSortedVectorSort(10000, MergeSort) << "ms" << endl;
	cout << "MergeSortRandom \t" << ForQuickSortRandomVectorSortAverage(5, 10000, MergeSort) << "ms" << endl;
	cout << "MergeSortReverse \t" << ForQuickSortReverseVectorSort(10000, MergeSort) << "ms" << endl;
	cout << endl;
	
	cout << "SortedShellSort \t" << SortedVectorSort(10000, ShellSort) << "  ms" << endl;
	cout << "randomShellSort \t" << RandomVectorSortAverage(5, 10000, ShellSort) << " ms" << endl;
	cout << "reverseShellSort \t" << ReverseVectorSort(10000, ShellSort) << "  ms" << endl;
	cout << endl;
	


	string exit;
	while (true) {
		cout << "종료할려면 exit 입력";
		cin >> exit;
		if (exit == "exit")
			return 0;
	}
}